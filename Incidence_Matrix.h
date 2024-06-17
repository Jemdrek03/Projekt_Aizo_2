//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_INCIDENCE_MATRIX_H
#define PROJEKT_AIZO_2_INCIDENCE_MATRIX_H

#include <iostream>
#include <vector>
#include "Main_Menu.h"

struct Incidence_Matrix {
    int vertexes;
    int edges;
    std::vector<std::vector<int>> matrix;

    Incidence_Matrix(int v, int e) : vertexes(v), edges(e), matrix(v, std::vector<int>(e, 0)) {}
};


Incidence_Matrix toIncidenceMatrix(const Dane& graph) {
    Incidence_Matrix im(graph.vertexes, graph.edges);

    for (int i = 0; i < graph.edges; ++i) {
        int u = graph.first[i];
        int v = graph.second[i];
        im.matrix[u][i] = 1;
        im.matrix[v][i] = -1; // For directed graph. Use 1 for undirected graph.
    }

    return im;
}



#endif //PROJEKT_AIZO_2_INCIDENCE_MATRIX_H
