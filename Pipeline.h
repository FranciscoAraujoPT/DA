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
        double getFlow() const;
        void setFlow(double d);
        bool operator<(Pipeline& other) const;

private:
        GraphNode *source; // Source service (water reservoir, pumping station, or delivery site)
        GraphNode *destination; // Target service (water reservoir, pumping station, or delivery site)
        double capacity; // Maximum capacity of the pipe
        bool direction; // Direction of connection (true - unidirectional, false - bidirectional)
        double flow = 0;
};


#endif //DA_PIPELINE_H
