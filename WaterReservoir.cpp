//
// Created by francisco-araujo on 3/13/24.
//

#include "WaterReservoir.h"

WaterReservoir::WaterReservoir(const std::string &name, const std::string &municipality, int id,
                               const std::string &code, double maxDelivery, bool available) : name(name), municipality(municipality),
                                                                              GraphNode(id, code), maxDelivery(maxDelivery), available(available){}

std::string WaterReservoir::getName() { return name; }

std::string WaterReservoir::getMunicipality() { return municipality; }

double WaterReservoir::getMaxDelivery() const { return maxDelivery; }

bool WaterReservoir::isAvailable() {return available; }

void WaterReservoir::setAvailable(bool available){ WaterReservoir::available = available;}
