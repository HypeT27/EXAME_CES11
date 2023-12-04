//
// Created by gabri on 04/12/2023.
//

#include "Node.h"

Node::Node() = default;

void Node::addNode(Node* node) {
    this->pointsTo.push_back(node);
}

bool Node::points(Node* node) {
    for(auto n : pointsTo)
        if(node->level == n->level)
            return true;
    return false;
}

void Node::defineLevel(int newLevel) {
    level = newLevel;
}
