//
// Created by francisco-araujo on 3/13/24.
//

#include "DeliverySite.h"

#include <utility>

DeliverySite::DeliverySite(std::string  city, int id, const std::string& code, double demand, double population)
        : city(std::move(city)), GraphNode(id, code, true), demand(demand), population(population) {}

        std::string DeliverySite::getCityName() {return city;}

        double DeliverySite::getDemand() { return demand; }

        double DeliverySite::getPopulation() { return population; }

        double DeliverySite::getWaterReceive() { return receive; }

        void DeliverySite::setWaterReceive(double waterReceived) { this->receive = waterReceived; }
