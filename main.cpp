#include <iostream>
#include <fstream>

#include "CSVReader.h"
#include "Graph.h"
#include "OptimizeFlow.h"
#include <iomanip>


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
                OptimizeFlow().edmondsKarp(graph);
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

