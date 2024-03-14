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
            for (auto vertex : vertices)
                removeVertex(vertex);
        }

        void addVertex(GraphNode data) {
            vertices.push_back(&data);
        }
        void removeVertex(GraphNode* vertex) {
            vertices.erase(std::remove(vertices.begin(), vertices.end(), vertex), vertices.end());
            for (auto edge : pipes)
                removePipe(edge);
            delete vertex;
        }
        std::vector<GraphNode*> getAllVertex() {
            return vertices;
        }
        void addPipe(const std::string& source, const std::string& destination, double capacity, bool direction) {
            //TODO
        }
        void removePipe(Pipeline* pipe) {
            //TODO
        }
    private:
        std::vector<GraphNode*> vertices;
        std::vector<Pipeline*> pipes;
};

#endif //DA_GRAPH_H
