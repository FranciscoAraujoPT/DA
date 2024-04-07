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
        GraphNode(int id, std::string  code, bool available);

        const int& getID() const;
        const std::string& getCode() const;
        const std::vector<Pipeline*>& getPipes() const;
        void addPipe(Pipeline* pipe);
        bool isVisited() const;
        void setVisited(bool status);
        void setPath(Pipeline* path);
        Pipeline *getPath();
        virtual bool isAvailable();
        virtual void setAvailable(bool a);

private:
        int id_;
        std::string code_;
        std::vector<Pipeline*> pipes_;
        std::vector<Pipeline*> incomingPipes;
        std::vector<Pipeline*> outgoingPipes;
        bool visited = false;
        Pipeline* path = nullptr;
        bool available;
};

#endif //DA_GRAPHNODE_H
