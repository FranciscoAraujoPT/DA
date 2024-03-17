//
// Created by francisco-araujo on 3/14/24.
//

#ifndef DA_GRAPHNODE_H
#define DA_GRAPHNODE_H

#include <string>
#include <utility>
#include <vector>

#include "Pipeline.h"

class GraphNode {
    public:
        GraphNode(int id, std::string  code);

        const int& getID() const;
        const std::string& getCode() const;
        const std::vector<Pipeline*>& getPipes() const;
        void addPipe(Pipeline* pipe);
        bool isVisited() const;
        void setVisited(bool status);
        void setPath(Pipeline* path);
        Pipeline *getPath();
        std::vector<Pipeline*> getIncoming();

private:
        int id_;
        std::string code_;
        std::vector<Pipeline*> pipes_;
        bool visited = false;
        Pipeline* path = nullptr;
        std::vector<Pipeline*> incoming;
};

#endif //DA_GRAPHNODE_H
