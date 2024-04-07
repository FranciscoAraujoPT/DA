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
    std::cout << "4. Pumping Stations Reports" << std::endl;
    std::cout << "5. Execute Edmonds-Karp Algorithm" << std::endl;
    std::cout << "6. Reliability and Sensitivity to Failures" << std::endl;
    std::cout << "7. Exit" << std::endl;
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
                  << std::setw(20) << std::left << "Possible Flow"
                  << std::setw(10) << std::left << "Available" << std::endl;
        for (auto pipe: graph->getAllPipes()) {
            std::cout << std::setw(15) << std::left << pipe->getSource()->getCode()
                      << std::setw(20) << std::left << pipe->getDestination()->getCode()
                      << std::setw(15) << std::left << pipe->getCapacity()
                      << std::setw(15) << std::left << pipe->getDirection()
                      << std::setw(10) << std::left << pipe->getFlow()
                      << std::setw(20) << std::left << pipe->getCapacity() - pipe->getFlow()
                      << std::setw(10) << std::left << (pipe->isAvailable() ? "Yes" : "No") << std::endl;
        }
    }else if (reportType == "Pumping Station"){
        std::cout << std::setw(5) << std::left << "ID"
                  << std::setw(10) << std::left << "Code"
                  << std::setw(10) << std::left << "Available";

        for (auto station : graph->getAllVertex()) {
            PumpingStation *pumpingStation = dynamic_cast<PumpingStation *>(station);

            if(pumpingStation != nullptr){
                std::cout << std::setw(5) << std::left << pumpingStation->getID()
                          << std::setw(10) << std::left << pumpingStation->getCode()
                          << std::setw(10) << std::left << (pumpingStation->isAvailable() ? "Yes" : "No") << std::endl;
            }
        }
        }
    else {
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

void removePipelinesMenu(Graph* graph) {
    bool menuOpen = true;

    while (menuOpen) {
        char sourceType;
        std::cout << "Is the source a reservoir (R) or pumping station (P)? ";
        std::cin >> sourceType;

        char destinationType;
        std::cout << "Is the destination a pumping station (P) or delivery site / city (D)? ";
        std::cin >> destinationType;

        bool validInput = false;
        GraphNode* sourceNode = nullptr;
        GraphNode* destinationNode = nullptr;

        if ((sourceType == 'R' || sourceType == 'r') && (destinationType == 'P' || destinationType == 'p')) {
            validInput = true;
            std::cout << "Enter reservoir ID: ";
            int reservoirId;
            std::cin >> reservoirId;
            sourceNode = graph->getReservoirById(reservoirId);

            std::cout << "Enter pumping station ID: ";
            int pumpingStationId;
            std::cin >> pumpingStationId;
            destinationNode = graph->getPumpingStationById(pumpingStationId);
        } else if ((sourceType == 'P' || sourceType == 'p') && (destinationType == 'P' || destinationType == 'p')) {
            validInput = true;
            std::cout << "Enter pumping station ID: ";
            int sourceId;
            std::cin >> sourceId;
            sourceNode = graph->getPumpingStationById(sourceId);

            std::cout << "Enter pumping station ID: ";
            int destinationId;
            std::cin >> destinationId;
            destinationNode = graph->getPumpingStationById(destinationId);
        } else if ((sourceType == 'P' || sourceType == 'p') && (destinationType == 'D' || destinationType == 'd')) {
            validInput = true;
            std::cout << "Enter pumping station ID: ";
            int pumpingStationId;
            std::cin >> pumpingStationId;
            sourceNode = graph->getPumpingStationById(pumpingStationId);

            std::cout << "Enter delivery site ID: ";
            int deliverySiteId;
            std::cin >> deliverySiteId;
            destinationNode = graph->getDeliverySiteById(deliverySiteId);
        }

        if (!validInput || sourceNode == nullptr || destinationNode == nullptr) {
            std::cout << "Invalid input. Please try again.\n";
            continue; // Restart the loop to allow re-entering input
        }

        // Check if there exists a pipeline between the source and destination nodes
        bool pipelineFound = false;
        for (auto pipeline : graph->getAllPipes()) {
            if (pipeline->getSource() == sourceNode && pipeline->getDestination() == destinationNode) {
                pipelineFound = true;
                std::cout << "Pipeline is " << (pipeline->isAvailable() ? "available" : "not available")
                          << ". Do you wish to " << (pipeline->isAvailable() ? "remove" : "add")
                          << " it? (y/n): ";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    pipeline->setAvailable(!pipeline->isAvailable());
                    std::cout << "Pipeline is now "
                              << (pipeline->isAvailable() ? "available" : "not available") << ".\n";
                } else {
                    std::cout << "Pipeline remains "
                              << (pipeline->isAvailable() ? "available" : "not available") << ".\n";
                }
                break;
            }
        }

        if (!pipelineFound) {
            std::cout << "No pipeline found between the specified source and destination nodes.\n";
        }

        std::cout << "Do you want to remove another pipeline? (y/n): ";
        char anotherChoice;
        std::cin >> anotherChoice;
        if (anotherChoice == 'n' || anotherChoice == 'N') {
            break; // Exit the loop
        }
    }
}

void removePumpingStationsMenu(Graph* graph) {
    bool menuOpen = true;

    while (menuOpen) {
        int choice;
        while (true) {
            printReport("Pumping Station", graph);
            std::cout << "Pumping Station ID: ";
            int stationId;
            std::cin >> stationId;

            bool stationFound = false;
            for (auto station : graph->getAllVertex()) {
                PumpingStation* pumpingStation = dynamic_cast<PumpingStation*>(station);

                if (station->getID() == stationId && pumpingStation != nullptr) {
                    stationFound = true;
                    std::cout << "Pumping Station is " << (station->isAvailable() ? "available" : "not available")
                              << ". Do you wish to " << (station->isAvailable() ? "remove" : "add")
                              << " it? (y/n): ";
                    char choice;
                    std::cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        station->setAvailable(!station->isAvailable());
                        std::cout << "Pumping Station is now "
                                  << (station->isAvailable() ? "available" : "not available") << ".\n";
                    } else {
                        std::cout << "Pumping Station remains "
                                  << (station->isAvailable() ? "available" : "not available") << ".\n";
                    }
                    break;
                }
            }

            if (!stationFound) {
                std::cout << "Pumping Station with ID " << stationId << " not found.\n";
            }

            std::cout << "Do you want to add/remove another pumping station? (y/n): ";
            char anotherChoice;
            std::cin >> anotherChoice;
            if (anotherChoice == 'n' || anotherChoice == 'N') {
                break; // Exit the inner loop
            }
        }
        printReport("Pumping Station", graph);
        break;
    }
}

void removeEntitiesMenu(Graph* graph){
    char entityType;
    std::cout << "Do you want to remove a pumping station (P), pipe (I), or reservoir (R)? ";
    std::cin >> entityType;

    OptimizeFlow().edmondsKarp(graph,graph->getSource(),graph->getDestination());

    std::vector<DeliverySite*> cities = graph->getCities();
    std::vector<DeliverySite*> citiesCopy = graph->getCities();
    std::vector<std::tuple<std::string, int, int>> affectedCitiesInfo;

    switch (entityType) {
        case 'P':
        case 'p':
            removePumpingStationsMenu(graph);
            break;
        case 'I':
        case 'i':
            removePipelinesMenu(graph);
            break;
        case 'R':
        case 'r':
            removeReservoirsMenu(graph);
            break;
        default:
            std::cout << "Invalid option.\n";
            break;
    }

    OptimizeFlow().edmondsKarp(graph,graph->getSource(),graph->getDestination());

    for (size_t i = 0; i < cities.size(); ++i) {
        double originalCityFlow = citiesCopy[i]->getWaterReceive();
        double newCityFlow = cities[i]->getWaterReceive();
        if (originalCityFlow != newCityFlow) {
            affectedCitiesInfo.push_back(std::make_tuple(cities[i]->getCityName(), originalCityFlow, newCityFlow));
        }
    }

    if(affectedCitiesInfo.size()>0){std::cout << "List Of Affected Cities" << std::endl;

    std::cout << std::setw(15) << std::left << "Affected City"
              << std::setw(15) << std::left << "Original Flow"
              << std::setw(15) << std::left << "New Flow" << std::endl;}

    for (auto info : affectedCitiesInfo) {
        std::cout << std::setw(15) << std::left << std::get<0>(info)
                  << std::setw(15) << std::left << std::get<1>(info)
                  << std::setw(15) << std::left << std::get<2>(info) << std::endl;
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
                printReport("Pumping Station",graph);
            case 5:
                OptimizeFlow().edmondsKarp(graph, graph->getSource(), graph->getDestination());
                break;
            case 6:
                removeEntitiesMenu(graph);
                break;
            case 7:
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

    Graph* graph = new Graph;

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

