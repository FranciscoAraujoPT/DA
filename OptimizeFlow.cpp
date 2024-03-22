#include "OptimizeFlow.h"

void OptimizeFlow::testAndVisit(std::queue<GraphNode*> &q, Pipeline* e, GraphNode* w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool OptimizeFlow::findAugmentingPath(Graph* g, GraphNode* s, GraphNode* t) {
    for (auto v : g->getAllVertex()) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<GraphNode*> q;
    q.push(s);
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e : v->getPipes()) {
            if (!e->getDirection() && e->getDestination() == v) {
                testAndVisit(q, e, e->getSource(), e->getCapacity() - e->getFlow());
            } else {
                testAndVisit(q, e, e->getDestination(), e->getCapacity() - e->getFlow());
            }
        }
    }
    return t->isVisited();
}

double OptimizeFlow::findMinResidualAlongPath(GraphNode* s, GraphNode* t) {
    double f = INF;
    for (GraphNode* v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDestination() == v) {
            v = e->getSource();
        } else {
            v = e->getDestination();
        }
        f = std::min(f, e->getCapacity() - e->getFlow());
    }
    return f;
}

void OptimizeFlow::augmentFlowAlongPath(WaterReservoir* s, DeliverySite* t, double f) {
    for (GraphNode* v = t; v != s;) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDestination() == v) {
            v = e->getSource();
        } else {
            v = e->getDestination();
        }
        e->setFlow(flow + f);
    }
    auto* final_city = static_cast<DeliverySite*>(t->getPath()->getSource());
    final_city->setWaterReceive(t->getPath()->getFlow());
    t->setWaterReceive(t->getPath()->getFlow());
}

void OptimizeFlow::edmondsKarp(Graph* g, WaterReservoir* mainSource, DeliverySite* mainDelivery) {
    if (mainSource == nullptr || mainDelivery == nullptr) {
        throw std::logic_error("Invalid source and/or delivery vertex");
    }
    for (auto v : g->getAllVertex()) {
        for (auto e : v->getPipes()) {
            e->setFlow(0);
        }
    }
    while (findAugmentingPath(g, mainSource, mainDelivery)) {
        double f = findMinResidualAlongPath(mainSource, mainDelivery);
        augmentFlowAlongPath(mainSource, mainDelivery, f);
    }
}
