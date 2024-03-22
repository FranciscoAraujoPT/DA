//
// Created by francisco-araujo on 3/14/24.
//

#include "GraphNode.h"

GraphNode::GraphNode(const int id, std::string code) : id_(id), code_(std::move(code)) {}

int &GraphNode::getID() { return id_; }

std::string &GraphNode::getCode() { return code_; }

std::vector<Pipeline*> &GraphNode::getPipes() { return pipes_; }

void GraphNode::addPipe(Pipeline* pipe){ pipes_.push_back(pipe); }

bool GraphNode::isVisited() const { return visited; }

void GraphNode::setVisited(bool status) { visited = status; }

void GraphNode::setPath(Pipeline* newPath) { this->path = newPath; }

Pipeline *GraphNode::getPath() { return path; }
