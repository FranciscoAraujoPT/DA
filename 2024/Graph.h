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

#define INF std::numeric_limits<double>::max()

class Graph {
    public:
        explicit Graph() {
            vertices.push_back(source);
            vertices.push_back(destination);
        }

        ~Graph() {
            for (GraphNode* vertex : vertices){
                for (Pipeline* pipe : vertex->getPipes()){
                    delete pipe;
                }
                delete vertex;
            }
        }

        GraphNode * addVertex(GraphNode* data) {
            vertices.push_back(data);
            return data;
        }
        std::vector<GraphNode *> getAllVertex() {
            return vertices;
        }
        void addPipe(const std::string& source_code, const std::string& destination_code, double capacity, bool direction) {
            GraphNode* s = findVertexByCode(source_code);
            GraphNode* d = findVertexByCode(destination_code);
            if(s != nullptr && d != nullptr){
                auto *pipe = new Pipeline(s, d, capacity, true);
                if(!direction){
                    auto *pipeBro = new Pipeline(d, s, capacity, true);
                    d->addPipe(pipeBro);
                    pipeBro->setBrotherPipe(pipe);
                    pipe->setBrotherPipe(pipeBro);
                }
                s->addPipe(pipe);
                pipes.push_back(pipe);
            } else {
                std::cerr << "Source: " << ((s==nullptr)? "null": source_code) << "\tDestination: " << ((d == nullptr) ? "null" : destination_code) << std::endl;
            }
        }
        void addMainPipe(GraphNode* source, GraphNode* destination, double capacity) {
            if(source != nullptr && destination != nullptr){
                auto *pipe = new Pipeline(source, destination, capacity, true);
                source->addPipe(pipe);
                pipes.push_back(pipe);
            } else {
                std::cerr << "Source: " <<((source==nullptr)?"null":source->getCode()) << "\tDestination: " << ((destination==nullptr)?"null":destination->getCode()) << std::endl;
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

        WaterReservoir* getSource(){ return source; }
        void setSource(WaterReservoir* newSource) { this->source = newSource; }
        DeliverySite* getDestination(){ return destination; }
        void setDestination(DeliverySite* newDestination) { this->destination = newDestination; }

        WaterReservoir* addReservoir(WaterReservoir *reservoir) {
            reservoirs.push_back(reservoir);
            return reservoir;
        }

        std::vector<WaterReservoir*> getReservoirs() { return reservoirs;}

        DeliverySite* addCities(DeliverySite *city) {
            cities.push_back(city);
            return city;
        }

        std::vector<DeliverySite*> getCities() { return cities;}

    PumpingStation* getPumpingStationById(int id) {
        for (auto vertex : vertices) {
            // Attempt to cast the current vertex to a PumpingStation pointer
            PumpingStation* pumpingStation = dynamic_cast<PumpingStation*>(vertex);

            if (pumpingStation != nullptr && pumpingStation->getID() == id) {
                return pumpingStation;
            }
        }
        return nullptr;
    }


    DeliverySite* getDeliverySiteById(int id) {
        for (auto city : cities) {
            if (city->getID() == id) {
                return city;
            }
        }
        return nullptr;
    }

    WaterReservoir* getReservoirById(int id) {
        for (auto reservoir : reservoirs) {
            if (reservoir->getID() == id) {
                return reservoir;
            }
        }
        return nullptr;
    }

    void restoreOriginalSettings(){
            for(auto vertex : vertices){
                vertex->setAvailable(true);
            }
        }

    private:
        WaterReservoir* source = new WaterReservoir("main_source", "", 0, "main_source_0", 0);
        DeliverySite* destination = new DeliverySite("main_deliver", 0, "main_delivery_0", 0, 0);
        std::vector<GraphNode*> vertices;
        std::vector<WaterReservoir*> reservoirs;
        std::vector<DeliverySite*> cities;
        std::vector<Pipeline*> pipes;
};

#endif //DA_GRAPH_H
