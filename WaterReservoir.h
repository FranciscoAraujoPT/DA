//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_WATERRESERVOIR_H
#define DA_WATERRESERVOIR_H

#include <string>
#include "GraphNode.h"

class WaterReservoir : public GraphNode {
    public:
        WaterReservoir(const std::string &name, const std::string &municipality, int id, const std::string &code, double maxDelivery);

    private:
        std::string name;
        std::string municipality;
        double maxDelivery;
};

#endif //DA_WATERRESERVOIR_H
