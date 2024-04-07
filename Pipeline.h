//
// Created by francisco-araujo on 3/13/24.
//

#ifndef DA_PIPELINE_H
#define DA_PIPELINE_H

#include <string>

class GraphNode;

class Pipeline{
    public:
        Pipeline(GraphNode* source, GraphNode* destination, double capacity, bool direction, bool available);

        GraphNode * getSource() ;
        GraphNode * getDestination() ;
        double getCapacity() const;
        bool getDirection() const;
        double getFlow() const;
        bool isAvailable() const;
        void setAvailable(bool a);

    void setFlow(double d);

private:
        GraphNode *source; // Source service (water reservoir, pumping station, or delivery site)
        GraphNode *destination; // Target service (water reservoir, pumping station, or delivery site)
        double capacity; // Maximum capacity of the pipe
        bool direction; // Direction of connection (true - unidirectional, false - bidirectional)
        double flow = 0;
        bool available = true;
};


#endif //DA_PIPELINE_H
