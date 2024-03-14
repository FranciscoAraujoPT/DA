//
// Created by francisco-araujo on 3/14/24.
//

#include "GraphNode.h"

GraphNode::GraphNode(const int id, std::string code) : id_(id), code_(std::move(code)) {}

const int &GraphNode::getId() const { return id_; }

const std::string &GraphNode::getCode() const { return code_; }

const std::vector<Pipeline> &GraphNode::getPipes() const {
    return pipes_;
}