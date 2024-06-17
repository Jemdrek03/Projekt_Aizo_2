//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_GENERATE_H
#define PROJEKT_AIZO_2_GENERATE_H

#include <cstdlib>
#include <ctime>
#include "File_Reading.h"

Dane generateData(int vertexes, int density)
{

    Dane result;
    result.vertexes = vertexes;
    int maxEdges = vertexes * (vertexes - 1) / 2; // Maksymalna liczba krawędzi w grafie nieskierowanym
    int edges = static_cast<int>(maxEdges * density); // Liczba krawędzi na podstawie gęstości
    result.edges = edges;

    int* first = new int[edges];
    int* second = new int[edges];
    int* third = new int[edges];

    srand(static_cast<unsigned int>(time(0))); // Inicjalizacja generatora liczb losowych

    for (int i = 0; i < edges; ++i) {
        first[i] = rand() % vertexes;
        second[i] = rand() % vertexes;
        while (second[i] == first[i]) { // Upewnij się, że nie mamy krawędzi do tego samego wierzchołka
            second[i] = rand() % vertexes;
        }
        third[i] = rand() % 100 + 1; // Losowa waga/przepustowość w zakresie od 1 do 100
    }

    result.first = first;
    result.second = second;
    result.third = third;

    return result;


}



#endif //PROJEKT_AIZO_2_GENERATE_H
