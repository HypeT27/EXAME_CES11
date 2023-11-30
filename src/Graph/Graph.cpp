//
// Created by gabri on 26/11/2023.
//

#include "Graph.h"

void Graph::addVertices(char vertice) {
    if (vertices.find(vertice) == vertices.end()) {
        vertices[vertice] = {};
    }
}

void Graph::addEdges(char vertice1, char vertice2) {
    addVertices(vertice1);
    addVertices(vertice2);
    vertices[vertice1].push_back(vertice2);
    vertices[vertice2].push_back(vertice1);
}

std::vector<char> Graph::findMinimalPath(char begin, char end) {
    std::unordered_map<char, char> predecessores;
    std::queue<char> fila;

    for (const auto& it : vertices) {
        predecessores[it.first] = '\0';
    }

    fila.push(begin);

    while (!fila.empty()) {
        char actual = fila.front();
        fila.pop();

        for (char neighbor : vertices[actual]) {
            if (predecessores[neighbor] == '\0') {
                predecessores[neighbor] = actual;
                fila.push(neighbor);
            }
        }
    }

    std::vector<char> path;
    char actual = end;
    while (actual != '\0') {
        path.push_back(actual);
        actual = predecessores[actual];
    }

    std::reverse(path.begin(), path.end());

    return path;
}

