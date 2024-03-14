//
// Created by francisco-araujo on 3/14/24.
//

#ifndef DA_GRAPH_H
#define DA_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "GraphNode.h"

class Graph {
    public:
        ~Graph() {
            for (GraphNode* vertex : vertices){
                for (Pipeline* pipe : vertex->getPipes()){
                    delete pipe;
                }
                delete vertex;
            }
        }
        void addVertex(GraphNode* data) {
            vertices.push_back(data);
        }
        std::vector<GraphNode *> getAllVertex() {
            return vertices;
        }
        void addPipe(const std::string& source, const std::string& destination, double capacity, bool direction) {
            GraphNode* s = findVertexByCode(source);
            GraphNode* d = findVertexByCode(destination);
            if(s != nullptr && d != nullptr){
                auto *pipe = new Pipeline(s, d, capacity, direction);
                if(!direction){
                    d->addPipe(pipe);
                }
                s->addPipe(pipe);
                pipes.push_back(pipe);
            }
        }
        std::vector<Pipeline *> getAllPipes() {
            return pipes;
        }
        GraphNode* findVertexByCode(const std::string& code) const {
            for (auto v : vertices)
                if (v->getCode() == code)
                    return v;
            return nullptr;
        }
        Pipeline* findPipeBySourceAndDest(GraphNode* source, GraphNode* destination) const {
            for (auto pipe : pipes)
                if (pipe->getSource() == source && pipe->getDestination() == destination)
                    return pipe;
            return nullptr;
        }
    private:
        std::vector<GraphNode*> vertices;
        std::vector<Pipeline*> pipes;
};

#endif //DA_GRAPH_H
