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
        const int& getId() const;
        const std::string& getCode() const;
        const std::vector<Pipeline*>& getPipes() const;
        void addPipe(Pipeline* pipe);

    private:
        int id_;
        std::string code_;
        std::vector<Pipeline*> pipes_;
};

#endif //DA_GRAPHNODE_H
