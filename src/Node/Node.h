//
// Created by gabri on 04/12/2023.
//

#ifndef EXAME_CES11_NODE_H
#define EXAME_CES11_NODE_H

#include <vector>

class Node {
public:
    Node();
    bool isPlayerOnMe = false;
    bool isVisited = false;
    void addNode(Node* node);
    bool points(Node*);
    void defineLevel(int);
private:
    int level;
    std::vector<Node*> pointsTo;
};


#endif //EXAME_CES11_NODE_H
