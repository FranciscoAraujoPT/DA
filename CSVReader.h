//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_CSVREADER_H
#define DA_CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

#include "WaterReservoir.h"
#include "PumpingStation.h"
#include "Pipeline.h"
#include "DeliverySite.h"
#include "Graph.h"

class CSVReader {
private:
    std::string filename;
public:
    explicit CSVReader(std::string  filename);

    void readReservoirData(Graph& graph);
    void readPipesData(Graph& graph);
    void readCitiesData(Graph& graph);
    void readStationsData(Graph& graph);
};

#endif //DA_CSVREADER_H
