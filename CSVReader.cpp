//
// Created by francisco-araujo on 3/13/24.
//

#include "CSVReader.h"

CSVReader::CSVReader(std::string filename):filename(std::move(filename)) {}

void CSVReader::readReservoirData(Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Skip the header line
    std::string header;
    std::getline(file, header);

    // Read CSV data
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string reservoirName, municipality, code, idStr, maxDeliveryStr;
        int id;
        double maxDelivery;
        // Assuming the last two columns are empty and ignored
        if (std::getline(ss, reservoirName, ',') &&
            std::getline(ss, municipality, ',') &&
            std::getline(ss, idStr, ',') && // Read the ID as string
            std::getline(ss, code, ',') &&
            std::getline(ss, maxDeliveryStr, ',')) {
            // Convert the ID from string to integer
            try {
                id = std::stoi(idStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid ID format in reservoir: " << idStr << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            try {
                maxDelivery = std::stoi(maxDeliveryStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid max delivery format in reservoir: " << idStr << std::endl;
                continue; // Skip this line if max delivery is not a valid integer
            }
            graph.addVertex(WaterReservoir(reservoirName, municipality, id, code, maxDelivery));
        }

    }

    file.close();
}

void CSVReader::readCitiesData(Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Skip the header line
    std::string header;
    std::getline(file, header);

    // Read CSV data
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cityName, code, idStr, demandStr, populationStr2, populationStr1;
        int id, population;
        double demand;
        // Assuming the last column is not needed
        if (std::getline(ss, cityName, ',') &&
            std::getline(ss, idStr, ',') &&
            std::getline(ss, code, ',') &&
            std::getline(ss, demandStr, ',') &&
            std::getline(ss, populationStr1, ',') &&
            std::getline(ss, populationStr2, ',')) {
            try {
                id = std::stoi(idStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid ID format in Delivery sites: " << idStr << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            try {
                demand = std::stoi(demandStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid demand format in Delivery sites: " << demandStr << std::endl;
                continue; // Skip this line if demand is not a valid integer
            }
            try {
                std::string populationStr = populationStr1.erase(0, 1) + populationStr2.erase(populationStr2.size() - 1);
                population = std::stod(populationStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid population format in Delivery sites: " << populationStr1 + populationStr2 << std::endl;
                continue; // Skip this line if population is not a valid double
            }

            graph.addVertex(DeliverySite(cityName, id, code, demand, population));
        }
    }

    file.close();
}

void CSVReader::readStationsData(Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Skip the header line
    std::string header;
    std::getline(file, header);

    // Read CSV data
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string code, idStr;
        int id;
        // Assuming the last column is not needed
        if (std::getline(ss, idStr, ',') && std::getline(ss, code, ',')) {
            try {
                id = std::stoi(idStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid ID format in Stations: " << idStr << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            graph.addVertex(PumpingStation(id, code));
        }
    }

    file.close();
}


void CSVReader::readPipesData(Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Skip the header line
    std::string header;
    std::getline(file, header);

    // Read CSV data
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string source, destination, capacityStr, directionStr;
        double capacity;
        bool direction;
        // Assuming the last column is not needed
        if (std::getline(ss, source, ',') &&
            std::getline(ss, destination, ',') &&
            std::getline(ss, capacityStr, ',') &&
            std::getline(ss, directionStr, ',')) {
            try {
                capacity = std::stoi(capacityStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid capacity format in Pipes: " << capacityStr << std::endl;
                continue; // Skip this line if capacity is not a valid integer
            }
            try {
                direction = std::stoi(directionStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid direction format in Pipes: " << directionStr << std::endl;
                continue; // Skip this line if direction is not a valid integer
            }
            graph.addPipe(source, destination, capacity, direction);
        }
    }

    file.close();
}