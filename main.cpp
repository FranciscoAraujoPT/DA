#include <iostream>
#include "CSVReader.h"
#include "Graph.h"

int main() {

    std::string reservoir_filename = "./data/Reservoir.csv";
    std::string stations_filename = "./data/Stations.csv";
    std::string cities_filename = "./data/Cities.csv";
    std::string pipes_filename = "./data/Pipes.csv";

    Graph* graph = new Graph();

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

    // Display vertices and pipes information
    std::cout << "Pipes:" << std::endl;
    for (Pipeline* pipe : graph->getAllPipes()) {
        std::cout << "\tSource: " << pipe->getSource()->getCode() << "\tDestination: " <<
            pipe->getDestination()->getCode() << "\tCapacity: " << pipe->getCapacity()
            << "\tDirection: " << ((pipe->getDirection())?"Unidirectional":"Bidirectional") << std::endl;
    }

    std::cout << "Vertices:" << std::endl;
    for (GraphNode* vertex : graph->getAllVertex()) {
        std::cout << "\tVertex: " << vertex->getId() << "\n\tCode: " << vertex->getCode() << std::endl;
        for(Pipeline* pipe : vertex->getPipes()){
            if(pipe->getSource() == vertex){
                std::cout << "\t\t\t\tDestionation: " << pipe->getDestination()->getCode() << std::endl;
            } else {
                std::cout << "\t\t\t\tDestionation: " << pipe->getSource()->getCode() << std::endl;
            }

        }
    }

    return 0;
}
