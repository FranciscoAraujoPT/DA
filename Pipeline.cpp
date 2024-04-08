//
// Created by francisco-araujo on 3/13/24.
//

#include "Pipeline.h"

Pipeline::Pipeline(GraphNode* source, GraphNode* destination, double capacity, bool available) : source(source), destination(destination), capacity(capacity), available(available){

}

GraphNode * Pipeline::getSource() { return this->source; }

GraphNode * Pipeline::getDestination() { return this->destination; }

double Pipeline::getCapacity() const { return this->capacity; }

Pipeline* Pipeline::getBrotherPipe() const { return this->pipeBro; }

void Pipeline::setBrotherPipe(Pipeline* brother) {  this->pipeBro = brother; }

double Pipeline::getFlow() const { return flow; }

void Pipeline::setFlow(double newFlow) { this->flow = newFlow; }

bool Pipeline::isAvailable() const { return this->available; }

void Pipeline::setAvailable(bool newAvailable) {this->available = newAvailable;}
