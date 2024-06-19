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

class Shortest_Path_Algorythms {
public:
    // Dijkstra dla listy sąsiedztwa
    static std::vector<int> dijkstraAdjacencyList(const Adjacency_List& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        std::vector<int> previous(graph.vertexes, -1);
        distances[start] = 0;

        using pii = std::pair<int, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int dist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (dist > distances[u]) continue;

            for (const auto& [v, weight] : graph.list[u]) {
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                    pq.emplace(distances[v], v);
                }
            }
        }

        return reconstructPath(previous, start, end);
    }

    // Dijkstra dla macierzy incydencji
    static std::vector<int> dijkstraIncidenceMatrix(const Incidence_Matrix& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        std::vector<int> previous(graph.vertexes, -1);
        distances[start] = 0;

        using pii = std::pair<int, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int dist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (dist > distances[u]) continue;

            for (int j = 0; j < graph.edges; ++j) {
                if (graph.matrix[u][j] > 0) {
                    int weight = graph.matrix[u][j];
                    for (int i = 0; i < graph.vertexes; ++i) {
                        if (i != u && graph.matrix[i][j] != 0) {
                            int v = i;
                            if (distances[u] + weight < distances[v]) {
                                distances[v] = distances[u] + weight;
                                previous[v] = u;
                                pq.emplace(distances[v], v);
                            }
                        }
                    }
                }
            }
        }

        return reconstructPath(previous, start, end);
    }

    // Ford-Bellman dla listy sąsiedztwa
    static std::vector<int> bellmanFordAdjacencyList(const Adjacency_List& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        std::vector<int> previous(graph.vertexes, -1);
        distances[start] = 0;

        for (int i = 0; i < graph.vertexes - 1; ++i) {
            for (int u = 0; u < graph.vertexes; ++u) {
                for (const auto& [v, weight] : graph.list[u]) {
                    if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                        previous[v] = u;
                    }
                }
            }
        }

        return reconstructPath(previous, start, end);
    }

    // Ford-Bellman dla macierzy incydencji
    static std::vector<int> bellmanFordIncidenceMatrix(const Incidence_Matrix& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max());
        std::vector<int> previous(graph.vertexes, -1);
        distances[start] = 0;

        for (int i = 0; i < graph.vertexes - 1; ++i) {
            for (int j = 0; j < graph.edges; ++j) {
                for (int u = 0; u < graph.vertexes; ++u) {
                    if (graph.matrix[u][j] > 0) {
                        int weight = graph.matrix[u][j];
                        for (int v = 0; v < graph.vertexes; ++v) {
                            if (graph.matrix[v][j] != 0 && distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                                distances[v] = distances[u] + weight;
                                previous[v] = u;
                            }
                        }
                    }
                }
            }
        }

        return reconstructPath(previous, start, end);
    }




private:
    // Rekonstrukcja najkrótszej ścieżki
    static std::vector<int> reconstructPath(const std::vector<int>& previous, int start, int end) {
        std::vector<int> path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        if (path.size() > 1 && path[0] == start) {
            return path;
        }

        return {}; // Brak ścieżki
    }
};




#endif //PROJEKT_AIZO_2_SHORTHEST_PATH_ALGORYTHMS_H
