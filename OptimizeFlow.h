#ifndef OPTIMIZEFLOW_H
#define OPTIMIZEFLOW_H

#include <queue>
#include "Graph.h"
#include "WaterReservoir.h"
#include "DeliverySite.h"

//TODO: add OptimizeFlow.h and .cpp to cmakelists.txt

void testAndVisit(std::queue<GraphNode*> &q, Pipeline* e, GraphNode* w, double residual);
bool findAugmentingPath(Graph* g, GraphNode* s, GraphNode* t);
double findMinResidualAlongPath(GraphNode* s, GraphNode* t);
void augmentFlowAlongPath(WaterReservoir* s, DeliverySite* t, double f);
void edmondsKarp(Graph* g, WaterReservoir* mainSource, DeliverySite* mainDelivery);

#endif // OPTIMIZEFLOW_H
