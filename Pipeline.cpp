//
// Created by francisco-araujo on 3/13/24.
//

#include "Pipeline.h"

Pipeline::Pipeline(GraphNode* source, GraphNode* destination, double capacity, bool direction) : source(source), destination(destination), capacity(capacity), direction(direction){

}

GraphNode * Pipeline::getSource() { return this->source; }

GraphNode * Pipeline::getDestination() { return this->destination; }

double Pipeline::getCapacity() const { return this->capacity; }

bool Pipeline::getDirection() const { return this->direction; }

double Pipeline::getFlow() const { return flow; }

void Pipeline::setFlow(double newFlow) { this->flow = newFlow; }

bool Pipeline::operator<(Pipeline& other) const { return capacity > other.getCapacity(); }
