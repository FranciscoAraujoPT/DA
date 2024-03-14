#include <iostream>
#include "CSVReader.h"
#include "Graph.h"

int main() {

    std::string reservoir_filename = "./data/Reservoirs_Madeira.csv";
    std::string stations_filename = "./data/Stations_Madeira.csv";
    std::string cities_filename = "./data/Cities_Madeira.csv";
    std::string pipes_filename = "./data/Pipes_Madeira.csv";

    Graph graph;

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

    // Display vertices and edges information
    std::cout << "Vertices:" << std::endl;
    for (auto vertex : graph.getAllVertex()) {
        std::cout << "Vertex: " << vertex->getId() << std::endl;
        std::cout << "Adjacent Vertices: ";
        for (auto edge : vertex->getPipes()) {
            std::cout << edge.getDestination()->getId() << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
