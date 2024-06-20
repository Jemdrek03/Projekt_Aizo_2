//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_MST_ALGORYTHMS_H
#define PROJEKT_AIZO_2_MST_ALGORYTHMS_H


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include "Adjacency_List.h"
#include "Incidence_Matrix.h"



// Struktura Edge
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight; // Operator porównania dla sortowania krawędzi według wagi
    }
};

//Struktura prim
struct prim {
    std::vector<int> parent; // Wektor rodziców w MST
    std::vector<int> key; // Wektor kluczy (kosztów)
    int vertexes; // Liczba wierzchołków
};

// Struktura dla wyników algorytmu Kruskala
struct kruskal{
    std::vector<Edge> mst; // Wektor krawędzi w MST
    int vertexes; // Liczba wierzchołków
};


// Klasa MST_Algorithms
class MST_Algorythms {
public:

    // Algorytm Prima dla listy sąsiedztwa
    static prim primAdjacencyList(const Adjacency_List& graph) {
        prim result;
        result.vertexes = graph.vertexes; // Ustawienie liczby wierzchołków
        result.parent.resize(graph.vertexes, -1); // Inicjalizacja wektora rodziców
        result.key.resize(graph.vertexes, std::numeric_limits<int>::max()); // Inicjalizacja wektora kluczy

        std::vector<bool> inQueue(graph.vertexes, true); // Wektor przechowujący informację o wierzchołkach w kolejce

        // Kolejka priorytetowa do przechowywania wierzchołków z ich kluczami
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        result.key[0] = 0; // Klucz startowego wierzchołka ustawiony na 0
        pq.emplace(0, 0); // Dodanie wierzchołka startowego do kolejki

        while (!pq.empty()) {
            int u = pq.top().second; // Pobranie wierzchołka z kolejki
            pq.pop();
            inQueue[u] = false; // Ustawienie, że wierzchołek nie jest już w kolejce

            // Przeglądanie sąsiadów wierzchołka
            for (const auto& [v, weight] : graph.list[u]) {
                if (inQueue[v] && weight < result.key[v]) {
                    result.parent[v] = u; // Ustawienie rodzica wierzchołka
                    result.key[v] = weight; // Aktualizacja klucza
                    pq.emplace(weight, v); // Dodanie sąsiada do kolejki
                }
            }
        }
        return result;
    }

    // Algorytm Prima dla macierzy incydencji
    static prim primIncidenceMatrix(const Incidence_Matrix& graph) {
        prim result;
        result.vertexes = graph.vertexes; // Ustawienie liczby wierzchołków
        result.parent.resize(graph.vertexes, -1); // Inicjalizacja wektora rodziców
        result.key.resize(graph.vertexes, std::numeric_limits<int>::max()); // Inicjalizacja wektora kluczy

        std::vector<bool> inQueue(graph.vertexes, true); // Wektor przechowujący informację o wierzchołkach w kolejce

        // Kolejka priorytetowa do przechowywania wierzchołków z ich kluczami
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        result.key[0] = 0; // Klucz startowego wierzchołka ustawiony na 0
        pq.emplace(0, 0); // Dodanie wierzchołka startowego do kolejki

        while (!pq.empty()) {
            int u = pq.top().second; // Pobranie wierzchołka z kolejki
            pq.pop();
            inQueue[u] = false; // Ustawienie, że wierzchołek nie jest już w kolejce

            // Lista sąsiadów wierzchołka
            std::vector<std::pair<int, int>> Neigh;

            // Przeglądanie wszystkich krawędzi
            for (int j = 0; j < graph.edges; ++j) {
                if(graph.matrix[u][j] != 0) {
                    for(int i = 0; i < graph.vertexes; i++) {
                        if(i != u && graph.matrix[i][j] != 0) {
                            Neigh.push_back({i, abs(graph.matrix[i][j])});
                        }
                    }
                }
            }

            // Przeglądanie sąsiadów wierzchołka
            for (const auto& [v, weight] : Neigh) {
                if (inQueue[v] && weight < result.key[v]) {
                    result.parent[v] = u; // Ustawienie rodzica wierzchołka
                    result.key[v] = weight; // Aktualizacja klucza
                    pq.emplace(weight, v); // Dodanie sąsiada do kolejki
                }
            }
        }
        return result;
    }



    // Algorytm Kruskala dla listy sąsiedztwa
    static kruskal kruskalAdjacencyList(const Adjacency_List& graph) {
        kruskal result;
        std::vector<Edge> edges;

        // Tworzenie wektora krawędzi
        for (int u = 0; u < graph.vertexes; ++u) {
            for (const auto& [v, weight] : graph.list[u]) {
                edges.push_back({u, v, weight});
            }
        }

        // Sortowanie krawędzi według wagi
        std::sort(edges.begin(), edges.end());

        // Inicjalizacja wektorów rodziców i rang
        std::vector<int> parent(graph.vertexes);
        std::iota(parent.begin(), parent.end(), 0);
        std::vector<int> rank(graph.vertexes, 0);

        // Wektor krawędzi w MST
        std::vector<Edge> mst;

        // Przeglądanie krawędzi
        for (const auto& edge : edges) {
            int u = find(parent, edge.u);
            int v = find(parent, edge.v);

            // Dodanie krawędzi do MST, jeśli nie tworzy cyklu
            if (u != v) {
                mst.push_back(edge);
                unionSets(parent, rank, u, v);
            }
        }

        result.vertexes = graph.vertexes;
        result.mst = mst;

        return result;
    }

    // Algorytm Kruskala dla macierzy incydencji
    static kruskal kruskalIncidenceMatrix(const Incidence_Matrix& graph) {
        kruskal result;
        std::vector<Edge> edges;

        // Tworzenie wektora krawędzi
        for (int j = 0; j < graph.edges; ++j) {
            int u = -1, v = -1, weight = -1;
            for (int i = 0; i < graph.vertexes; ++i) {
                if (graph.matrix[i][j] > 0) {
                    u = i;
                    weight = graph.matrix[i][j];
                } else if (graph.matrix[i][j] < 0) {
                    v = i;
                }
            }
            if (u != -1 && v != -1) {
                edges.push_back({u, v, weight});
            }
        }

        // Sortowanie krawędzi według wagi
        std::sort(edges.begin(), edges.end());

        // Inicjalizacja wektorów rodziców i rang
        std::vector<int> parent(graph.vertexes);
        std::iota(parent.begin(), parent.end(), 0);
        std::vector<int> rank(graph.vertexes, 0);

        // Wektor krawędzi w MST
        std::vector<Edge> mst;

        // Przeglądanie krawędzi
        for (const auto& edge : edges) {
            int u = find(parent, edge.u);
            int v = find(parent, edge.v);

            // Dodanie krawędzi do MST, jeśli nie tworzy cyklu
            if (u != v) {
                mst.push_back(edge);
                unionSets(parent, rank, u, v);
            }
        }

        result.vertexes = graph.vertexes;
        result.mst = mst;

        return result;
    }


private:
    // Znajdowanie korzenia drzewa dla danego wierzchołka
    static int find(std::vector<int>& parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    // Łączenie dwóch zbiorów w jeden
// parent - wektor przechowujący rodziców wierzchołków
// rank - wektor przechowujący rangi wierzchołków
// u - pierwszy wierzchołek
// v - drugi wierzchołek
    static void unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v) {
        // Znajdź korzenie zbiorów, do których należą wierzchołki u i v
        int rootU = find(parent, u);
        int rootV = find(parent, v);

        // Jeśli ranga korzenia u jest mniejsza niż ranga korzenia v
        if (rank[rootU] < rank[rootV]) {
            // Ustaw korzeń u jako potomka korzenia v
            parent[rootU] = rootV;
        }
            // Jeśli ranga korzenia u jest większa niż ranga korzenia v
        else if (rank[rootU] > rank[rootV]) {
            // Ustaw korzeń v jako potomka korzenia u
            parent[rootV] = rootU;
        }
            // Jeśli rangi korzeni u i v są równe
        else {
            // Ustaw korzeń v jako potomka korzenia u i zwiększ rangę korzenia u
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
};


#endif //PROJEKT_AIZO_2_MST_ALGORYTHMS_H
