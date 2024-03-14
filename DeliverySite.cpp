//
// Created by francisco-araujo on 3/13/24.
//

#include "DeliverySite.h"

#include <utility>

DeliverySite::DeliverySite(std::string  city, int id, const std::string& code, double demand, double population)
        : city(std::move(city)), GraphNode(id, code), demand(demand), population(population) {}