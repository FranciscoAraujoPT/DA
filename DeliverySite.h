//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_DELIVERYSITE_H
#define DA_DELIVERYSITE_H

#include <string>
#include "GraphNode.h"

class DeliverySite : public GraphNode{
public:
    DeliverySite(std::string  city, int id, const std::string& code, double demand, int population);

private:
    std::string city;
    int id{};
    std::string code;
    double demand;
    int population;
};

#endif //DA_DELIVERYSITE_H
