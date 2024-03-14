//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_PUMPINGSTATION_H
#define DA_PUMPINGSTATION_H

#include <string>
#include "GraphNode.h"

class PumpingStation : public GraphNode{
    public:
        PumpingStation(int id, const std::string& code);

    private:
        int id;
        std::string code;
};

#endif //DA_PUMPINGSTATION_H
