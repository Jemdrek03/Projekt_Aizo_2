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
        return weight < other.weight;
    }
};

struct prim {
    std::vector<int> parent;
    std::vector<int> key;
    int vertexes;
};

struct kruskal{
    std::vector<Edge> mst;
    int vertexes;
};


// Klasa MST_Algorithms
class MST_Algorythms {
public:

    // Funkcja wykonująca algorytm Prima na liście sąsiedztwa
    static prim primAdjacencyList(const Adjacency_List& graph) {
        prim result;
        result.vertexes = graph.vertexes;
        result.parent.resize(graph.vertexes, -1);
        result.key.resize(graph.vertexes, std::numeric_limits<int>::max());

        std::vector<bool> inQueue(graph.vertexes, true);

        // Priority queue to store vertices with their key values
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        // Start from vertex 0
        result.key[0] = 0;
        pq.emplace(0, 0); // (key, vertex)

        while (!pq.empty()) {
            int u = pq.top().second; // Pobieramy wierzchołek z kolejki (drugi element pary)
            pq.pop();

            inQueue[u] = false;

            for (const auto& [v, weight] : graph.list[u]) {
                if (inQueue[v] && weight < result.key[v]) {
                    result.parent[v] = u;
                    result.key[v] = weight;
                    pq.emplace(weight, v); // Umieszczamy nowy klucz i wierzchołek w kolejce
                }
            }
        }

        return result;
    }

    static prim primIncidenceMatrix(const Incidence_Matrix& graph) {
        prim result;
        result.vertexes = graph.vertexes;
        result.parent.resize(graph.vertexes, -1);
        result.key.resize(graph.vertexes, std::numeric_limits<int>::max());

        std::vector<bool> inQueue(graph.vertexes, true);

        // Priority queue to store vertices with their key values
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        // Start from vertex 0
        result.key[0] = 0;
        pq.emplace(0, 0); // (key, vertex)

        while (!pq.empty()) {
            int u = pq.top().second; // Pobieramy wierzchołek z kolejki (drugi element pary)
            pq.pop();

            inQueue[u] = false;
            std::vector<std::pair<int, int>> Neigh;

            for (int j = 0; j < graph.edges; ++j) {
                if(graph.matrix[u][j] != 0)
                {
                    for(int i = 0; i < graph.vertexes; i++)
                    {
                        if(i != u && graph.matrix[i][j] != 0)
                        {
                            Neigh.push_back({i, abs(graph.matrix[i][j])});
                        }
                    }
                }
            }
            for (const auto& [v, weight] : Neigh) {
                if (inQueue[v] && weight < result.key[v]) {
                    result.parent[v] = u;
                    result.key[v] = weight;
                    pq.emplace(weight, v); // Umieszczamy nowy klucz i wierzchołek w kolejce
                }
            }

        }

        return result;
    }



    // Kruskal dla listy sąsiedztwa
    static kruskal kruskalAdjacencyList(const Adjacency_List& graph) {
        kruskal result;
        std::vector<Edge> edges;
        for (int u = 0; u < graph.vertexes; ++u) {
            for (const auto& [v, weight] : graph.list[u]) {
                edges.push_back({u, v, weight});
            }
        }

        std::sort(edges.begin(), edges.end());

        std::vector<int> parent(graph.vertexes);
        std::iota(parent.begin(), parent.end(), 0);

        std::vector<int> rank(graph.vertexes, 0);

        std::vector<Edge> mst;

        for (const auto& edge : edges) {
            int u = find(parent, edge.u);
            int v = find(parent, edge.v);

            if (u != v) {
                mst.push_back(edge);
                unionSets(parent, rank, u, v);
            }
        }

        result.vertexes = graph.vertexes;
        result.mst = mst;

        return result;
    }

    // Kruskal dla macierzy incydencji
    static kruskal kruskalIncidenceMatrix(const Incidence_Matrix& graph) {
        kruskal result;
        std::vector<Edge> edges;
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

        std::sort(edges.begin(), edges.end());

        std::vector<int> parent(graph.vertexes);
        std::iota(parent.begin(), parent.end(), 0);

        std::vector<int> rank(graph.vertexes, 0);

        std::vector<Edge> mst;

        for (const auto& edge : edges) {
            int u = find(parent, edge.u);
            int v = find(parent, edge.v);

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
    static int find(std::vector<int>& parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    static void unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v) {
        int rootU = find(parent, u);
        int rootV = find(parent, v);
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
};


#endif //PROJEKT_AIZO_2_MST_ALGORYTHMS_H
