#ifndef OPTIMIZEFLOW_H
#define OPTIMIZEFLOW_H

#include <stack>
#include "GraphNode.h"
#include "WaterReservoir.h"
#include "DeliverySite.h"
#include "Graph.h"


class OptimizeFlow {
    private:
        static bool testAndVisit(std::stack<GraphNode*> &q, Pipeline* e, GraphNode* w, double residual);
        static bool findAugmentingPath(GraphNode* s, GraphNode* t);
        static double findMinResidualAlongPath(GraphNode* s, GraphNode* t);
        static void augmentFlowAlongPath(WaterReservoir* s, DeliverySite* t, double f);

    public:
        static void edmondsKarp(Graph* g);

};

#endif // OPTIMIZEFLOW_H
