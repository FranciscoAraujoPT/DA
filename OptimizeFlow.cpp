#include "OptimizeFlow.h"

bool OptimizeFlow::findAugmentingPath(Graph* g, GraphNode* s, GraphNode* t) {
    for (auto v : g->getAllVertex()) {
        v->setPath(nullptr);
        v->setVisited(false);
    }
    s->setVisited(true);
    std::stack<GraphNode*> stack;
    stack.push(s);
    while (!stack.empty() && !t->isVisited()) {
        bool flag = false;
        auto v = stack.top();
        GraphNode* maxFlowVertex = nullptr;
        for (auto e : v->getPipes()) {
            if (!e->isAvailable()) {
                continue; // Skip unavailable pipeline
            }
            if (!e->getSource()->isAvailable() || !e->getDestination()->isAvailable()) {
                continue; // Skip if either source or destination is unavailable
            }
            auto residual = e->getCapacity()-e->getFlow();
            if (!e->getDestination()->isVisited() && residual > 0 && e->isAvailable() && e->getDestination()->isAvailable()) {
                if(maxFlowVertex == nullptr){
                    maxFlowVertex = e->getDestination();
                    maxFlowVertex->setPath(e);
                    stack.push(maxFlowVertex);
                    flag = true;
                    maxFlowVertex->setVisited(true);    
                } else if((maxFlowVertex->getPath()->getCapacity()-maxFlowVertex->getPath()->getFlow()) < residual){
                    maxFlowVertex->setPath(nullptr);
                    maxFlowVertex->setVisited(false);
                    stack.pop();
                    maxFlowVertex = e->getDestination();
                    maxFlowVertex->setPath(e);
                    stack.push(maxFlowVertex);
                    maxFlowVertex->setVisited(true);
                    flag = true;
                }
            }
        }
        if(!flag){
            v->setPath(nullptr);
            stack.pop();
        }
        std::cout << "\t\tpart1" << v->getCode() << std::endl;

    }
    return t->isVisited();
}

double OptimizeFlow::findMinResidualAlongPath(GraphNode* s, GraphNode* t) {
    double f = INF;
    for (GraphNode* v = t; v != s;) {
        auto e = v->getPath();
        f = std::min(f, e->getCapacity() - e->getFlow());
        std::cout << "\t\tpart2" <<f << std::endl;
        v = e->getSource();
    }
    return f;
}

void OptimizeFlow::augmentFlowAlongPath(WaterReservoir* s, DeliverySite* t, double f) {
    for (GraphNode* v = t; v != s;) {
        auto e = v->getPath();
        v = e->getSource();
        if(e->getBrotherPipe() != nullptr){
            e->getBrotherPipe()->setFlow(e->getFlow() + f);
        }
        std::cout << f << std::endl;
        e->setFlow(e->getFlow() + f);
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
        if (f > 1) {
            f = f /2;
        }
        augmentFlowAlongPath(mainSource, mainDelivery, f);
    }
}
