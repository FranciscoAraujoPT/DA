#include <iostream>
#include <fstream>

#include "CSVReader.h"
#include "Graph.h"
#include "OptimizeFlow.h"
#include <iomanip>

/*
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
    while(!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        // Process outgoing edges
        for(auto e: v->getPipes()) {
            if(!e->getDirection() && e->getDestination() == v){
                testAndVisit(q, e, e->getSource(), e->getCapacity() - e->getFlow());
            } else {
                testAndVisit(q, e, e->getDestination(), e->getCapacity() - e->getFlow());
            }
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
            v = e->getSource();
        }
        else {
            v = e->getDestination();
        }
        f = std::min(f, e->getCapacity() - e->getFlow());
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
            v = e->getSource();
        }
        else {
            v = e->getDestination();
        }
        e->setFlow(flow + f);
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
    while(findAugmentingPath(g, mainSource, mainDelivery))  {
        double f = findMinResidualAlongPath(mainSource, mainDelivery);
        augmentFlowAlongPath(mainSource, mainDelivery, f);
    }
}
*/

void menu(Graph* graph) {
    std::cout << "Flow Optimization Menu:" << std::endl;
    std::cout << "1. Reservoir Reports" << std::endl;
    std::cout << "2. Cities Reports" << std::endl;
    std::cout << "3. Pipes Reports" << std::endl;
    std::cout << "4. Execute Edmonds-Karp Algorithm" << std::endl;
    std::cout << "5. Exit" << std::endl;

    bool menuOpen = true;

    while(menuOpen) {
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Reservoir reports: " << std::endl;
                std::cout << std::setw(15) << std::left << "Reservoir ID"
                          << std::setw(10) << std::left << "Code"
                          << std::setw(30) << std::left << "Name"
                          << std::setw(30) << std::left << "Municipality"
                          << std::setw(15) << std::left << "Max delivery" << std::endl;
                for (auto reservoir : graph->getReservoirs()) {
                    std::cout << std::setw(15) << std::left << reservoir->getID()
                              << std::setw(10) << std::left << reservoir->getCode()
                              << std::setw(30) << std::left << reservoir->getName()
                              << std::setw(30) << std::left << reservoir->getMunicipality()
                              << std::setw(15) << std::left << reservoir->getMaxDelivery() << std::endl;
                }
                break;
            case 2:
                std::cout << "Cities reports: " << std::endl;
                std::cout << std::setw(10) << std::left << "City ID"
                          << std::setw(10) << std::left << "Code"
                          << std::setw(20) << std::left << "Name"
                          << std::setw(15) << std::left << "Population"
                          << std::setw(15) << std::left << "Demand"
                          << std::setw(20) << std::left << "Water Received" << std::endl;
                for (DeliverySite *city: graph->getCities()) {
                    std::cout << std::setw(10) << std::left << city->getID()
                              << std::setw(10) << std::left << city->getCode()
                              << std::setw(20) << std::left << city->getCityName()
                              << std::setw(15) << std::left << city->getPopulation()
                              << std::setw(15) << std::left << city->getDemand()
                              << std::setw(20) << std::left << city->getWaterReceive() << std::endl;
                }
                break;
            case 3:
                std::cout << "Pipes reports: " << std::endl;
                std::cout << std::setw(15) << std::left << "Source Code"
                          << std::setw(20) << std::left << "Destination Code"
                          << std::setw(15) << std::left << "Capacity"
                          << std::setw(15) << std::left << "Direction"
                          << std::setw(10) << std::left << "Flow"
                          << std::setw(20) << std::left << "Possible Flow" << std::endl;
                for (auto pipe: graph->getAllPipes()) {
                    std::cout << std::setw(15) << std::left << pipe->getSource()->getCode()
                              << std::setw(20) << std::left << pipe->getDestination()->getCode()
                              << std::setw(15) << std::left << pipe->getCapacity()
                              << std::setw(15) << std::left << pipe->getDirection()
                              << std::setw(10) << std::left << pipe->getFlow()
                              << std::setw(20) << std::left << pipe->getCapacity() - pipe->getFlow() << std::endl;
                }
                break;
            case 4:
                //edmondsKarp(graph, graph->getSource(), graph->getDestination());
                std::cout << "Not Implemented yet" << std::endl;
                break;
            case 5:
                std::cout << "Exiting..." << std::endl;
                menuOpen = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
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

    menu(graph); // Call the menu function

    // Perform any cleanup if needed

    delete graph; // Clean up dynamically allocated memory

    return 0;
}

