//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_INCIDENCE_MATRIX_H
#define PROJEKT_AIZO_2_INCIDENCE_MATRIX_H

#include <iostream>
#include <vector>
#include "Main_Menu.h"


// Struktura reprezentująca macierz incydencji
struct Incidence_Matrix {
    int vertexes; // Liczba wierzchołków
    int edges; // Liczba krawędzi
    std::vector<std::vector<int>> matrix; // Macierz incydencji

    // Konstruktor inicjalizujący liczbę wierzchołków i krawędzi oraz tworzący zerową macierz incydencji
    Incidence_Matrix(int v, int e) : vertexes(v), edges(e), matrix(v, std::vector<int>(e, 0)) {}
};

// Funkcje przekształcające dane grafu na macierz incydencji
Incidence_Matrix toIncidenceMatrix(const Dane& graph) {
    Incidence_Matrix im(graph.vertexes, graph.edges);

    // Iteracja przez wszystkie krawędzie grafu
    for (int i = 0; i < graph.edges; ++i) {
        int u = graph.first[i]; // Początkowy wierzchołek krawędzi
        int v = graph.second[i]; // Końcowy wierzchołek krawędzi
        im.matrix[u][i] = graph.third[i]; // Ustawienie wagi krawędzi dla wierzchołka początkowego
        im.matrix[v][i] = -1; // Ustawienie -1 dla wierzchołka końcowego (dla grafu skierowanego)
    }

    return im;
}

Incidence_Matrix toIncidenceMatrix1(const Dane& graph) {
    Incidence_Matrix im(graph.vertexes, graph.edges);

    for (int i = 0; i < graph.edges; ++i) {
        int u = graph.first[i];
        int v = graph.second[i];
        im.matrix[u][i] = graph.third[i];
        im.matrix[v][i] = -graph.third[i]; // Ustawienie ujemnej wagi dla wierzchołka końcowego (dla grafu nieskierowanego)
    }

    return im;
}





#endif //PROJEKT_AIZO_2_INCIDENCE_MATRIX_H
