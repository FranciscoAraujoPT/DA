//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_PIPELINE_H
#define DA_PIPELINE_H

#include <string>

class GraphNode;

class Pipeline{
public:
    Pipeline(GraphNode* source, GraphNode* destination, double capacity, bool direction);

    GraphNode * getSource() ;
    GraphNode * getDestination() ;
    double getCapacity() const;
    bool getDirection() const;
private:
    GraphNode *source; // Source service (water reservoir, pumping station, or delivery site)
    GraphNode *destination; // Target service (water reservoir, pumping station, or delivery site)
    double capacity; // Maximum capacity of the pipe
    bool direction; // Direction of connection (1 - unidirectional, 0 - bidirectional)
};


#endif //DA_PIPELINE_H
