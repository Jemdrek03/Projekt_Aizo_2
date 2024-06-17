//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_SHORTHEST_PATH_ALGORYTHMS_H
#define PROJEKT_AIZO_2_SHORTHEST_PATH_ALGORYTHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "File_Reading.h"
#include "Generate.h"
#include "Adjacency_List.h"
#include "Incidence_Matrix.h"

class Shortest_Path_Algorithms {
public:
    // Algorytm Dijkstry dla listy sąsiedztwa
    static std::vector<int> dijkstraAdjacencyList(const Adjacency_List& graph, int start) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        distances[start] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int dist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (dist > distances[u]) continue;

            for (const auto& [v, weight] : graph.list[u]) {
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    pq.emplace(distances[v], v);
                }
            }
        }

        return distances;
    }

    // Algorytm Dijkstry dla macierzy incydencji
    static std::vector<int> dijkstraIncidenceMatrix(const Incidence_Matrix& graph, int start) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        distances[start] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int dist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (dist > distances[u]) continue;

            for (int e = 0; e < graph.edges; ++e) {
                if (graph.matrix[u][e] != 0) {
                    int v = -1;
                    for (int i = 0; i < graph.vertexes; ++i) {
                        if (graph.matrix[i][e] != 0 && i != u) {
                            v = i;
                            break;
                        }
                    }
                    if (v != -1) {
                        int weight = std::abs(graph.matrix[u][e]); // Assuming weight is stored in the matrix
                        if (distances[u] + weight < distances[v]) {
                            distances[v] = distances[u] + weight;
                            pq.emplace(distances[v], v);
                        }
                    }
                }
            }
        }

        return distances;
    }

    // Algorytm Forda-Bellmana dla listy sąsiedztwa
    static std::vector<int> bellmanFordAdjacencyList(const Adjacency_List& graph, int start) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        distances[start] = 0;

        for (int i = 1; i < graph.vertexes - 1; ++i) {
            for (int u = 0; u < graph.vertexes; ++u) {
                for (const auto& [v, weight] : graph.list[u]) {
                    if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                    }
                }
            }
        }

        return distances;
    }

    // Algorytm Forda-Bellmana dla macierzy incydencji
    static std::vector<int> bellmanFordIncidenceMatrix(const Incidence_Matrix& graph, int start) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        distances[start] = 0;

        for (int i = 1; i < graph.vertexes - 1; ++i) {
            for (int e = 0; e < graph.edges; ++e) {
                int u = -1, v = -1, weight = 0;
                for (int j = 0; j < graph.vertexes; ++j) {
                    if (graph.matrix[j][e] != 0) {
                        if (u == -1) u = j;
                        else v = j;
                    }
                }
                weight = std::abs(graph.matrix[u][e]); // Assuming weight is stored in the matrix

                if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                }
            }
        }

        return distances;
    }

    // Metoda wywołująca algorytm Dijkstry dla listy sąsiedztwa
    static void dijkstraForAdjacencyList(const Adjacency_List& graph, int start) {
        auto distances = dijkstraAdjacencyList(graph, start);
        std::cout << "Dijkstra (Adjacency List) distances from vertex " << start << ":\n";
        for (int i = 0; i < distances.size(); ++i) {
            std::cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }

    // Metoda wywołująca algorytm Dijkstry dla macierzy incydencji
    static void dijkstraForIncidenceMatrix(const Incidence_Matrix& graph, int start) {
        auto distances = dijkstraIncidenceMatrix(graph, start);
        std::cout << "Dijkstra (Incidence Matrix) distances from vertex " << start << ":\n";
        for (int i = 0; i < distances.size(); ++i) {
            std::cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }

    // Metoda wywołująca algorytm Forda-Bellmana dla listy sąsiedztwa
    static void bellmanFordForAdjacencyList(const Adjacency_List& graph, int start) {
        auto distances = bellmanFordAdjacencyList(graph, start);
        std::cout << "Bellman-Ford (Adjacency List) distances from vertex " << start << ":\n";
        for (int i = 0; i < distances.size(); ++i) {
            std::cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }

    // Metoda wywołująca algorytm Forda-Bellmana dla macierzy incydencji
    static void bellmanFordForIncidenceMatrix(const Incidence_Matrix& graph, int start) {
        auto distances = bellmanFordIncidenceMatrix(graph, start);
        std::cout << "Bellman-Ford (Incidence Matrix) distances from vertex " << start << ":\n";
        for (int i = 0; i < distances.size(); ++i) {
            std::cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }
};






#endif //PROJEKT_AIZO_2_SHORTHEST_PATH_ALGORYTHMS_H
