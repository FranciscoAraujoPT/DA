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
        std::string reservoirName, municipality, code;
        int id;
        double maxDelivery;
        // Assuming the last two columns are empty and ignored
        if (std::getline(ss, reservoirName, ',') &&
            std::getline(ss, municipality, ',') &&
            ss >> id &&
            std::getline(ss, code, ',') &&
            ss >> maxDelivery) {
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
        std::string cityName, code;
        int id;
        double demand;
        int population; // Assuming population is read as string
        // Assuming the last column is not needed
        if (std::getline(ss, cityName, ',') &&
            ss >> id &&
            std::getline(ss, code, ',') &&
            ss >> demand &&
            ss >> population) {
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
        std::string code;
        int id;
        // Assuming the last column is not needed
        if (ss >> id && std::getline(ss, code, ',')) {
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
        std::string source, destination;
        double capacity;
        bool direction;
        // Assuming the last column is not needed
        if (std::getline(ss, source, ',') &&
            std::getline(ss, destination, ',') &&
            ss >> capacity &&
            ss >> direction) {
            graph.addPipe(source, destination, capacity, direction);
        }
    }

    file.close();
}