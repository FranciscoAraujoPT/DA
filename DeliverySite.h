//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_DELIVERYSITE_H
#define DA_DELIVERYSITE_H

#include <string>
#include "GraphNode.h"

class DeliverySite : public GraphNode{
    public:
        DeliverySite(std::string  city, int id, const std::string& code, double demand, double population);

        std::string getCityName();
        double getDemand();
        double getPopulation();
        double getWaterReceive();
        void setWaterReceive(double waterReceived);

    private:
        std::string city;
        double demand;
        double population;
        double receive = 0;
};

#endif //DA_DELIVERYSITE_H
