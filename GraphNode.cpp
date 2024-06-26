//
// Created by francisco-araujo on 3/14/24.
//

#include "GraphNode.h"

GraphNode::GraphNode(const int id, std::string code, bool available) : id_(id), code_(std::move(code)), available(available) {}

const int &GraphNode::getID() const { return id_; }

const std::string &GraphNode::getCode() const { return code_; }

const std::vector<Pipeline*> &GraphNode::getPipes() const { return pipes_; }

void GraphNode::addPipe(Pipeline* pipe){ pipes_.push_back(pipe); }

bool GraphNode::isVisited() const { return visited; }

void GraphNode::setVisited(bool status) { visited = status; }

void GraphNode::setPath(Pipeline* newPath) { this->path = newPath; }

Pipeline *GraphNode::getPath() { return path; }

bool GraphNode::isAvailable() { return available; } //meant to be overridden

void GraphNode::setAvailable(bool a) {this->available = a; }
