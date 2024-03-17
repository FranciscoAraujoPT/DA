#include <iostream>
#include <fstream>

#include "CSVReader.h"
#include "Graph.h"

// Function to test the given vertex 'w' and visit it if conditions are met
void testAndVisit(std::queue<GraphNode*> &q, Pipeline* e, GraphNode* w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
bool findAugmentingPath(Graph* g, GraphNode* s, GraphNode* t) {
    // Mark all vertices as not visited
    for(auto v : g->getAllVertex()) {
        v->setVisited(false);
    }
    // Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<GraphNode*> q;
    q.push(s);
    // BFS to find an augmenting path
    while( !q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        // Process outgoing edges
        for(auto e: v->getPipes()) {
            testAndVisit(q, e, e->getDestination(), e->getCapacity() - e->getFlow());
        }
        // Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getSource(), e->getFlow());
        }
    }

    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
double findMinResidualAlongPath(GraphNode* s, GraphNode* t) {
    double f = INF;
    // Traverse the augmenting path to find the minimum residual capacity
    for (GraphNode* v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDestination() == v) {
            f = std::min(f, e->getCapacity() - e->getFlow());
            v = e->getSource();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDestination();
        }
    }

    // Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
void augmentFlowAlongPath(WaterReservoir* s, DeliverySite* t, double f) {
    // Traverse the augmenting path and update the flow values accordingly
    for (GraphNode* v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDestination() == v) {
            e->setFlow(flow + f);
            v = e->getSource();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDestination();
        }
    }

    auto* final_city = static_cast<DeliverySite *>(t->getPath()->getSource());
    final_city->setWaterReceive(t->getPath()->getFlow());
    t->setWaterReceive(t->getPath()->getFlow());
}

// Main function implementing the Edmonds-Karp algorithm
void edmondsKarp(Graph* g, WaterReservoir* mainSource, DeliverySite* mainDelivery) {
    // Validate source and target_code vertices
    if (mainSource == nullptr || mainDelivery == nullptr){
        throw std::logic_error("Invalid source and/or delivery vertex");
    }

    // Initialize flow on all edges to 0
    for (auto v : g->getAllVertex()) {
        for (auto e: v->getPipes()) {
            e->setFlow(0);
        }
    }

    // While there is an augmenting path, augment the flow along the path
    while(findAugmentingPath(g, mainSource, mainDelivery)) {
        double f = findMinResidualAlongPath(mainSource, mainDelivery);
        augmentFlowAlongPath(mainSource, mainDelivery, f);
    }
}

int main() {

    std::string reservoir_filename = "./data/Reservoirs_Madeira.csv";
    std::string stations_filename = "./data/Stations_Madeira.csv";
    std::string cities_filename = "./data/Cities_Madeira.csv";
    std::string pipes_filename = "./data/Pipes_Madeira.csv";

    auto* graph = new Graph;

    // Read reservoirs data
    CSVReader reservoirReader(reservoir_filename);
    reservoirReader.readReservoirData(graph);

    // Read stations data
    CSVReader stationsReader(stations_filename);
    stationsReader.readStationsData(graph);

    // Read cities data
    CSVReader citiesReader(cities_filename);
    citiesReader.readCitiesData(graph);

    // Read pipes data
    CSVReader pipesReader(pipes_filename);
    pipesReader.readPipesData(graph);

    edmondsKarp(graph, graph->getSource(), graph->getDestination());
    std::ofstream output("output.txt");
    char line[150];
    if (output.is_open()){
        output << "Cities reports: " << std::endl;
        std::cout << "Cities reports: " << std::endl;
        for (DeliverySite* city : graph->getCities()){
            snprintf(line, 150,"\tCity ID: %-3d\tCode: %-5s\tName: %-15s\tPopulation: %-5.0f\tDemand: %-4.0f\tWater Received: %-5.0f\n",
                   city->getID(), city->getCode().c_str(),city->getCityName().c_str(), city->getPopulation(), city->getDemand(), city->getWaterReceive());
            output << line;
            std::cout << line;
        }
        output.close();
    } else {
        std::cerr << "Error opening file\n";
    }



    return 0;
}
