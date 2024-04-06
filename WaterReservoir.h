//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_WATERRESERVOIR_H
#define DA_WATERRESERVOIR_H

#include <string>
#include "GraphNode.h"

class WaterReservoir : public GraphNode {
    public:
        WaterReservoir(const std::string &name, const std::string &municipality, int id, const std::string &code, double maxDelivery, bool available);

        std::string getName();
        std::string getMunicipality();
        double  getMaxDelivery() const;
        bool isAvailable() override;
        void setAvailable(bool available);

    private:
        std::string name;
        std::string municipality;
        double maxDelivery;
        bool available;
};

#endif //DA_WATERRESERVOIR_H
