#ifndef OPTIMIZEFLOW_H
#define OPTIMIZEFLOW_H

#include "WaterReservoir.h"
#include "PumpingStation.h"
#include "Pipeline.h"
#include "DeliverySite.h"
#include "Graph.h"

class OptimizeFlow {
    private:
        void testAndVisit(std::queue<GraphNode*> &q, Pipeline* e, GraphNode* w, double residual);
        bool findAugmentingPath(GraphNode* s, GraphNode* t);
        double findMinResidualAlongPath(GraphNode* s, GraphNode* t);
        void augmentFlowAlongPath(WaterReservoir* s, DeliverySite* t, double f);

    public:
        void edmondsKarp(Graph* g);
};

#endif // OPTIMIZEFLOW_H
