#ifndef PROJEKT_AIZO_2_GENERATE_H
#define PROJEKT_AIZO_2_GENERATE_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "File_Reading.h"

Dane generateData(int vertexes, float density) {
    Dane result;
    result.vertexes = vertexes;
    int maxEdges = vertexes * (vertexes - 1) / 2; // Maksymalna liczba krawędzi w grafie nieskierowanym
    int edges = static_cast<int>(maxEdges * density); // Liczba krawędzi na podstawie gęstości
    edges = std::max(edges, vertexes - 1); // Upewnij się, że mamy co najmniej vertexes-1 krawędzi, aby połączyć wszystkie wierzchołki
    result.edges = edges;

    std::vector<int> first(edges);
    std::vector<int> second(edges);
    std::vector<int> third(edges);

    srand(static_cast<unsigned int>(time(0))); // Inicjalizacja generatora liczb losowych

    // Tworzenie "szkieletu" grafu, aby upewnić się, że każdy wierzchołek jest osiągalny
    for (int i = 0; i < vertexes; ++i) {
        first[i] = i;
        if(i == vertexes-1){
            second[i] = 0;
        }
        else {
            second[i] = i + 1;
        }
        third[i] = rand() % 20 + 1; // Losowa waga/przepustowość w zakresie od 1 do 20
    }

    // Dodawanie pozostałych krawędzi na podstawie gęstości
    for (int i = vertexes; i < edges; ++i) {
        first[i] = rand() % vertexes;
        second[i] = rand() % vertexes;
        while (second[i] == first[i]) { // Upewnij się, że nie mamy krawędzi do tego samego wierzchołka
            second[i] = rand() % vertexes;
        }
        third[i] = rand() % 20 + 1; // Losowa waga/przepustowość w zakresie od 1 do 20
    }

    // Tasowanie krawędzi, aby szkielet nie był zawsze w tej samej kolejności
    std::vector<int> indices(edges);
    for (int i = 0; i < edges; ++i) {
        indices[i] = i;
    }
    std::random_shuffle(indices.begin(), indices.end());

    int* finalFirst = new int[edges];
    int* finalSecond = new int[edges];
    int* finalThird = new int[edges];

    for (int i = 0; i < edges; ++i) {
        finalFirst[i] = first[indices[i]];
        finalSecond[i] = second[indices[i]];
        finalThird[i] = third[indices[i]];
    }

    result.first = finalFirst;
    result.second = finalSecond;
    result.third = finalThird;

    return result;
}

#endif //PROJEKT_AIZO_2_GENERATE_H