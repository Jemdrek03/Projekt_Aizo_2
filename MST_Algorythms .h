//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_MST_ALGORYTHMS_H
#define PROJEKT_AIZO_2_MST_ALGORYTHMS_H


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "File_Reading.h"
#include "Generate.h"
#include "Adjacency_List.h"
#include "Incidence_Matrix.h"

class MST_Algorithms {
public:
    // Algorytm Prima dla macierzy incydencji
    static void primIncidenceMatrix(const Incidence_Matrix& graph) {
        int V = graph.vertexes;
        std::vector<int> parent(V, -1); // Tablica przechowująca rodziców w drzewie MST
        std::vector<int> key(V, std::numeric_limits<int>::max()); // Tablica przechowująca wagi krawędzi do wybranych wierzchołków
        std::vector<bool> inMST(V, false); // Tablica oznaczająca, czy wierzchołek jest już w MST

        // Rozpoczęcie od wierzchołka 0
        int start = 0;
        key[start] = 0;

        while (true) {
            int u = -1;
            // Znajdowanie wierzchołka o najmniejszym kluczu, który nie jest jeszcze w MST
            for (int i = 0; i < V; ++i) {
                if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                    u = i;
                }
            }

            if (u == -1) break; // Jeśli nie znaleziono wierzchołka, przerwij

            inMST[u] = true;

            // Aktualizacja kluczy sąsiednich wierzchołków
            for (int e = 0; e < graph.edges; ++e) {
                int v = -1;
                if (graph.matrix[u][e] == 1) { // Szukamy wierzchołka sąsiadującego z u
                    for (int i = 0; i < V; ++i) {
                        if (i != u && graph.matrix[i][e] == -1) {
                            v = i;
                            break;
                        }
                    }
                    if (v != -1 && !inMST[v] && graph.weights[e] < key[v]) {
                        parent[v] = u;
                        key[v] = graph.weights[e];
                    }
                }
            }
        }

        // Wyświetlenie MST
        std::cout << "Minimum Spanning Tree (Prim's Algorithm - Incidence Matrix):\n";
        for (int i = 1; i < V; ++i) {
            std::cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << "\n";
        }
    }

    // Algorytm Kruskala dla macierzy incydencji
    static void kruskalIncidenceMatrix(const Incidence_Matrix& graph) {
        int V = graph.vertexes;
        int E = graph.edges;
        std::vector<std::pair<int, std::pair<int, int>>> edges; // Wektor krawędzi

        // Zbieranie wszystkich krawędzi
        for (int e = 0; e < E; ++e) {
            int u = -1, v = -1, weight = -1;
            for (int i = 0; i < V; ++i) {
                if (graph.matrix[i][e] == 1) {
                    u = i;
                } else if (graph.matrix[i][e] == -1) {
                    v = i;
                    weight = graph.weights[e];
                }
            }
            edges.emplace_back(weight, std::make_pair(u, v));
        }

        // Sortowanie krawędzi według wag
        std::sort(edges.begin(), edges.end());

        std::vector<int> parent(V); // Tablica przechowująca rodziców dla struktury find-union
        std::vector<int> rank(V, 0); // Rangi dla struktury find-union

        // Inicjalizacja parent dla każdego wierzchołka
        for (int i = 0; i < V; ++i) {
            parent[i] = i;
        }

        // Wektor przechowujący krawędzie w MST
        std::vector<std::pair<int, std::pair<int, int>>> mst;

        // Algorytm Kruskala
        for (auto edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;

            // Znajdowanie rodzica dla u i v
            int set_u = find(parent, u);
            int set_v = find(parent, v);

            // Jeśli u i v nie są w tym samym zbiorze, to dodaj krawędź do MST
            if (set_u != set_v) {
                mst.push_back(edge);
                union_set(parent, rank, set_u, set_v);
            }
        }



    // Algorytm Prima dla listy sąsiedztwa
    static void primAdjacencyList(const Adjacency_List& graph) {
        int V = graph.vertexes;
        std::vector<int> parent(V, -1); // Tablica przechowująca rodziców w drzewie MST
        std::vector<int> key(V, std::numeric_limits<int>::max()); // Tablica przechowująca wagi krawędzi do wybranych wierzchołków
        std::vector<bool> inMST(V, false); // Tablica oznaczająca, czy wierzchołek jest już w MST

        // Priorytetowa kolejka do wybierania najmniejszej wagi krawędzi
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        // Rozpoczęcie od wierzchołka 0
        int start = 0;
        pq.emplace(0, start);
        key[start] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            inMST[u] = true;

            // Przetwarzanie sąsiadów wierzchołka u
            for (const auto& [v, weight] : graph.list[u]) {
                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.emplace(weight, v);
                }
            }
        }

        // Wyświetlenie MST
        std::cout << "Minimum Spanning Tree (Prim's Algorithm - Adjacency List):\n";
        for (int i = 1; i < V; ++i) {
            std::cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << "\n";
        }
    }

    // Algorytm Kruskala dla listy sąsiedztwa
    static void kruskalAdjacencyList(const Adjacency_List& graph) {
        int V = graph.vertexes;
        std::vector<std::pair<int, std::pair<int, int>>> edges; // Wektor krawędzi
        std::vector<int> parent(V); // Tablica przechowująca rodziców dla struktury find-union
        std::vector<int> rank(V, 0); // Rangi dla struktury find-union

        // Inicjalizacja parent dla każdego wierzchołka
        for (int i = 0; i < V; ++i) {
            parent[i] = i;
        }

        // Zbieranie wszystkich krawędzi
        for (int u = 0; u < V; ++u) {
            for (const auto& [v, weight] : graph.list[u]) {
                edges.emplace_back(weight, std::make_pair(u, v));
            }
        }

        // Sortowanie krawędzi według wag
        std::sort(edges.begin(), edges.end());

        // Wektor przechowujący krawędzie w MST
        std::vector<std::pair<int, std::pair<int, int>>> mst;

        // Algorytm Kruskala
        for (auto edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;

            // Znajdowanie rodzica dla u i v
            int set_u = find(parent, u);
            int set_v = find(parent, v);

            // Jeśli u i v nie są w tym samym zbiorze, to dodaj krawędź do MST
            if (set_u != set_v) {
                mst.push_back(edge);
                union_set(parent, rank, set_u, set_v);
            }
        }

        // Wyświetlenie MST
        std::cout << "Minimum Spanning Tree (Kruskal's Algorithm - Adjacency List):\n";
        for (auto edge : mst) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            std::cout << "Edge: " << u << " - " << v << " Weight: " << weight << "\n";
        }
    }

private:
    // Funkcja find dla struktury find-union
    static int find(std::vector<int>& parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]); // Path compression
        }
        return parent[i];
    }

    // Funkcja union dla struktury find-union
    static void union_set(std::vector<int>& parent, std::vector<int>& rank, int u, int v) {
        int root_u = find(parent, u);
        int root_v = find(parent, v);

        if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
};



#endif //PROJEKT_AIZO_2_MST_ALGORYTHMS_H
