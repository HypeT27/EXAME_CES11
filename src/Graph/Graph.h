//
// Created by gabri on 26/11/2023.
//

#ifndef EXAME_CES11_GRAPH_H
#define EXAME_CES11_GRAPH_H
#include "../Entities/Entity.h"
#include "unordered_map"
#include "queue"

class Graph {
public:
    void addVertices(char vertice);
    void addEdges(char vertice1, char vertice2);
    std::vector<char> findMinimalPath(char begin, char end);
private:
    std::unordered_map<char, std::vector<char>> vertices;
};


#endif //EXAME_CES11_GRAPH_H
