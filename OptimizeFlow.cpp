#include "OptimizeFlow.h"

bool OptimizeFlow::testAndVisit(std::stack<GraphNode*> &q, Pipeline* e, GraphNode* w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
        return true;
    }
    return false;
}

bool OptimizeFlow::findAugmentingPath(GraphNode* s, GraphNode* t) {
    s->setVisited(true);
    std::stack<GraphNode*> stack;
    stack.push(s);
    while (!stack.empty() && !t->isVisited()) {
        bool flag = false;
        auto v = stack.top();
        std::cout << v->getCode() << std::endl;
        double bestCapacity = INF;
        std::sort(v->getPipes().begin(), v->getPipes().end());

        for (auto p : v->getPipes()) {
            if (!p->getDirection() && p->getDestination() == v) {
                if (testAndVisit(stack, p, p->getSource(), p->getCapacity() - p->getFlow())) {
                    std::cout << "\t\t\tWTF! " << v->getCode() << std::endl;
                    flag = true;
                    break;
                }
            } else {
                if (testAndVisit(stack, p, p->getDestination(), p->getCapacity() - p->getFlow())) {
                    std::cout << "\t\t\tWTF!!! " << p->getDestination()->getCode() << std::endl;
                    flag = true;
                    break;
                }
            }
        }
        if(!flag){
            v->setPath(nullptr);
            stack.pop();
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

void OptimizeFlow::edmondsKarp(Graph* g) {
    WaterReservoir* mainSource = g->getSource();
    DeliverySite* mainDelivery = g->getDestination();

    if (mainSource == nullptr || mainDelivery == nullptr) {
        throw std::logic_error("Invalid source and/or delivery vertex");
    }
    for (auto v : g->getAllVertex()) {
        for (auto e : v->getPipes()) {
            e->setFlow(0);
        }
    }

    while (true) {
        for (auto v : g->getAllVertex()) {
            v->setVisited(false);
        }
        if(!findAugmentingPath(mainSource, mainDelivery)){
            break;
        }
        double f = findMinResidualAlongPath(mainSource, mainDelivery);
        augmentFlowAlongPath(mainSource, mainDelivery, f);
    }
}
