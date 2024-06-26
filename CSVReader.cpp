//
// Created by francisco-araujo on 3/13/24.
//

#include "CSVReader.h"

CSVReader::CSVReader(std::string filename, char delimiter):filename(std::move(filename)), delimiter(delimiter){}

void CSVReader::readReservoirData(Graph* graph) {
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
        if (std::getline(ss, reservoirName, delimiter) &&
            std::getline(ss, municipality, delimiter) &&
            std::getline(ss, idStr, delimiter) && // Read the ID as string
            std::getline(ss, code, delimiter) &&
            std::getline(ss, maxDeliveryStr, '\r')) {
            // Convert the ID from string to integer
            try {
                idStr.erase(std::remove(idStr.begin(), idStr.end(), '"'), idStr.end());
                idStr.erase(std::remove(idStr.begin(), idStr.end(), ','), idStr.end());
                id = std::stoi(idStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid ID format in reservoir: " << line << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            try {
                maxDeliveryStr.erase(std::remove(maxDeliveryStr.begin(), maxDeliveryStr.end(), '"'), maxDeliveryStr.end());
                maxDeliveryStr.erase(std::remove(maxDeliveryStr.begin(), maxDeliveryStr.end(), ','), maxDeliveryStr.end());
                maxDelivery = std::stoi(maxDeliveryStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid max delivery format in reservoir: " << line << std::endl;
                continue; // Skip this line if max delivery is not a valid integer
            }

            graph->addMainPipe(graph->getSource(), graph->addVertex(graph->addReservoir(new WaterReservoir(reservoirName, municipality, id, code, maxDelivery))), maxDelivery);
        }

    }

    file.close();
}

void CSVReader::readCitiesData(Graph* graph) {
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
        std::string cityName, code, idStr, demandStr, populationStr;
        int id;
        double demand, population;
        // Assuming the last column is not needed
        if (std::getline(ss, cityName, delimiter) &&
            std::getline(ss, idStr, delimiter) &&
            std::getline(ss, code, delimiter) &&
            std::getline(ss, demandStr, delimiter) &&
            std::getline(ss, populationStr, '\r')){
            try {
                idStr.erase(std::remove(idStr.begin(), idStr.end(), '"'), idStr.end());
                idStr.erase(std::remove(idStr.begin(), idStr.end(), ','), idStr.end());
                id = std::stoi(idStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid ID format in Delivery sites: " << line << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            try {
                demandStr.erase(std::remove(demandStr.begin(), demandStr.end(), '"'), demandStr.end());
                demandStr.erase(std::remove(demandStr.begin(), demandStr.end(), ','), demandStr.end());
                demand = std::stoi(demandStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid demand format in Delivery sites: " << line << std::endl;
                continue; // Skip this line if demand is not a valid integer
            }
            try {
                populationStr.erase(std::remove(populationStr.begin(), populationStr.end(), '"'), populationStr.end());
                populationStr.erase(std::remove(populationStr.begin(), populationStr.end(), ','), populationStr.end());
                population = std::stod(populationStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid population format in Delivery sites: " << line << std::endl;
                continue; // Skip this line if population is not a valid double
            }
            graph->addMainPipe(graph->addVertex(graph->addCities(new DeliverySite(cityName, id, code, demand, population))),
                               graph->getDestination(), demand);
        }
    }

    file.close();
}

void CSVReader::readStationsData(Graph* graph) {
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
        if (std::getline(ss, idStr, delimiter) && std::getline(ss, code, '\r')) {
            try {
                idStr.erase(std::remove(idStr.begin(), idStr.end(), '"'), idStr.end());
                idStr.erase(std::remove(idStr.begin(), idStr.end(), ','), idStr.end());
                id = std::stoi(idStr);
            } catch (const std::invalid_argument& e) {
                //std::cerr << "Invalid ID format in Stations: " << line << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            code.erase(std::remove(code.begin(), code.end(), '"'), code.end());
            code.erase(std::remove(code.begin(), code.end(), ','), code.end());
            graph->addVertex(new PumpingStation(id, code));
        }
    }

    file.close();
}


void CSVReader::readPipesData(Graph* graph) {
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
        if (std::getline(ss, source, delimiter) &&
            std::getline(ss, destination, delimiter) &&
            std::getline(ss, capacityStr, delimiter) &&
            std::getline(ss, directionStr, '\r')) {
            try {
                capacityStr.erase(std::remove(capacityStr.begin(), capacityStr.end(), '"'), capacityStr.end());
                capacityStr.erase(std::remove(capacityStr.begin(), capacityStr.end(), ','), capacityStr.end());
                capacity = std::stoi(capacityStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid capacity format in Pipes: " << line << std::endl;
                continue; // Skip this line if capacity is not a valid integer
            }
            try {
                directionStr.erase(std::remove(directionStr.begin(), directionStr.end(), '"'), directionStr.end());
                directionStr.erase(std::remove(directionStr.begin(), directionStr.end(), ','), directionStr.end());
                direction = std::stoi(directionStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid direction format in Pipes: " << line << std::endl;
                continue; // Skip this line if direction is not a valid integer
            }
            graph->addPipe(source, destination, capacity, direction);
        }
    }

    file.close();
}