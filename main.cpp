#include <iostream>
#include <fstream>

#include "CSVReader.h"
#include "Graph.h"
#include "OptimizeFlow.h"
#include <iomanip>

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

void printMenuOptions(){
    std::cout << "Flow Optimization Menu:" << std::endl;
    std::cout << "1. Reservoir Reports" << std::endl;
    std::cout << "2. Cities Reports" << std::endl;
    std::cout << "3. Pipes Reports" << std::endl;
    std::cout << "4. Execute Edmonds-Karp Algorithm" << std::endl;
    std::cout << "5. Add/Remove Reservoir" << std::endl;
    std::cout << "6. Exit" << std::endl;
}


#include <iostream>
#include <iomanip>
#include <vector>
#include "Graph.h" // Include necessary headers for accessing graph data

/*
void printReport(const std::string& reportType, Graph* graph) {
    std::cout << reportType << " reports: " << std::endl;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> data;

    if (reportType == "Reservoir") {
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
    } else if (reportType == "Cities") {

    } else if (reportType == "Pipes") {

    } else {
        std::cout << "Invalid report type." << std::endl;
        return;
    }
}*/

void printReport(const std::string& reportType, Graph* graph) {
    std::cout << reportType << " reports: " << std::endl;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> data;

    if (reportType == "Reservoir") {
        std::cout << std::setw(15) << std::left << "Reservoir ID"
                  << std::setw(10) << std::left << "Code"
                  << std::setw(30) << std::left << "Name"
                  << std::setw(30) << std::left << "Municipality"
                  << std::setw(15) << std::left << "Max delivery"
                  << std::setw(5) << std::left << "Available" << std::endl;
        for (auto reservoir : graph->getReservoirs()) {
            std::cout << std::setw(15) << std::left << reservoir->getID()
                      << std::setw(10) << std::left << reservoir->getCode()
                      << std::setw(30) << std::left << reservoir->getName()
                      << std::setw(30) << std::left << reservoir->getMunicipality()
                      << std::setw(15) << std::left << reservoir->getMaxDelivery()
                      << std::setw(5) << std::left << (reservoir->isAvailable() ? "Yes" : "No") << std::endl;
        }
    } else if (reportType == "Cities") {
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
                    << std::fixed << std::setprecision(0) // Set fixed-point format with precision 0 . needed for large populations i.e. Lisboa
                      << std::setw(15) << std::left << city->getPopulation()
                      << std::setw(15) << std::left << city->getDemand()
                      << std::setw(20) << std::left << city->getWaterReceive() << std::endl;
        }
    } else if (reportType == "Pipes") {
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
    } else {
        std::cout << "Invalid report type." << std::endl;
        return;
    }

    for (const auto& header : headers) {
        std::cout << std::setw(15) << std::left << header;
    }
    std::cout << std::endl;

    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << std::setw(15) << std::left << cell;
        }
        std::cout << std::endl;
    }
}

void removeReservoirsMenu(Graph* graph){
    bool menuOpen = true;

    while(menuOpen) {
        int choice;
        while(true) {
            printReport("Reservoir",graph);
            std::cout << "Reservoir ID: ";
            int reservoirId;
            std::cin >> reservoirId;

            bool reservoirFound = false;
            for (auto reservoir: graph->getReservoirs()) {
                if (reservoir->getID() == reservoirId) {
                    reservoirFound = true;
                    std::cout << "Reservoir is " << (reservoir->isAvailable() ? "available" : "not available")
                              << ". Do you wish to " << (reservoir->isAvailable() ? "remove" : "add")
                              << " it? (y/n): ";
                    char choice;
                    std::cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        reservoir->setAvailable(!reservoir->isAvailable());
                        std::cout << "Reservoir is now "
                                  << (reservoir->isAvailable() ? "available" : "not available") << ".\n";
                    } else {
                        std::cout << "Reservoir remains "
                                  << (reservoir->isAvailable() ? "available" : "not available") << ".\n";
                    }
                    break;
                }
            }

            if (!reservoirFound) {
                std::cout << "Reservoir with ID " << reservoirId << " not found.\n";
            }

            std::cout << "Do you want to add/remove another reservoir? (y/n): ";
            char anotherChoice;
            std::cin >> anotherChoice;
            if (anotherChoice == 'n' || anotherChoice == 'N') {
                break; // Exit the inner loop
            }
        }
        printReport("Reservoir",graph);
        break;
    }

}

void menu(Graph* graph) {
    printMenuOptions();

    bool menuOpen = true;

    while(menuOpen) {
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                printReport("Reservoir", graph);
                break;
            case 2:
                printReport("Cities", graph);
                break;
            case 3:
                printReport("Pipes", graph);
                break;
            case 4:
                OptimizeFlow().edmondsKarp(graph, graph->getSource(), graph->getDestination());
                break;
            case 5:
                removeReservoirsMenu(graph);
                break;
            case 6:
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
    std::string reservoir_filename = "./data/Reservoir.csv";
    std::string stations_filename = "./data/Stations.csv";
    std::string cities_filename = "./data/Cities.csv";
    std::string pipes_filename = "./data/Pipes.csv";

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

