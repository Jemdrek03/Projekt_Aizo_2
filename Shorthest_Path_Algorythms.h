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
    static std::pair<std::vector<int>, int> dijkstraAdjacencyList(const Adjacency_List& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max()); // Inicjalizacja wektora odległości maksymalnymi wartościami
        std::vector<int> previous(graph.vertexes, -1); // Wektor przechowujący poprzednie wierzchołki na ścieżce
        distances[start] = 0; // Odległość do wierzchołka startowego wynosi 0

        using pii = std::pair<int, int>; // Skrócenie zapisu pary int, int
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq; // Kolejka priorytetowa do przechowywania wierzchołków do odwiedzenia
        pq.emplace(0, start); // Dodanie wierzchołka startowego do kolejki

        while (!pq.empty()) {
            int dist = pq.top().first; // Pobranie odległości do wierzchołka
            int u = pq.top().second; // Pobranie wierzchołka
            pq.pop(); // Usunięcie wierzchołka z kolejki

            if (dist > distances[u]) continue; // Jeżeli odległość jest większa niż zarejestrowana, przejdź dalej

            for (const auto& [v, weight] : graph.list[u]) {
                // Jeśli znaleziono krótszą ścieżkę do sąsiada
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight; // Aktualizacja odległości do sąsiada
                    previous[v] = u; // Ustawienie poprzedniego wierzchołka
                    pq.emplace(distances[v], v); // Dodanie sąsiada do kolejki
                }
            }
        }

        // Zwrócenie znalezionej ścieżki oraz jej łącznej wagi
        return reconstructPath(previous, distances[end], start, end);
    }

    // Dijkstra dla macierzy incydencji
    static std::pair<std::vector<int>, int> dijkstraIncidenceMatrix(const Incidence_Matrix& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max()); // Inicjalizacja wektora odległości maksymalnymi wartościami
        std::vector<int> previous(graph.vertexes, -1); // Wektor przechowujący poprzednie wierzchołki na ścieżce
        distances[start] = 0; // Odległość do wierzchołka startowego wynosi 0

        using pii = std::pair<int, int>; // Skrócenie zapisu pary int, int
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq; // Kolejka priorytetowa do przechowywania wierzchołków do odwiedzenia
        pq.emplace(0, start); // Dodanie wierzchołka startowego do kolejki

        while (!pq.empty()) {
            int dist = pq.top().first; // Pobranie odległości do wierzchołka
            int u = pq.top().second; // Pobranie wierzchołka
            pq.pop(); // Usunięcie wierzchołka z kolejki

            if (dist > distances[u]) continue; // Jeżeli odległość jest większa niż zarejestrowana, przejdź dalej

            for (int j = 0; j < graph.edges; ++j) {
                if (graph.matrix[u][j] > 0) { // Sprawdzenie, czy wierzchołek jest połączony z krawędzią
                    int weight = graph.matrix[u][j]; // Pobranie wagi krawędzi
                    for (int i = 0; i < graph.vertexes; ++i) { // Przejście przez wszystkie wierzchołki
                        if (i != u && graph.matrix[i][j] != 0) { // Sprawdzenie, czy wierzchołek i jest połączony z krawędzią
                            int v = i; // Pobranie wierzchołka sąsiedniego
                            if (distances[u] + weight < distances[v]) {
                                distances[v] = distances[u] + weight; // Aktualizacja odległości do sąsiada
                                previous[v] = u; // Ustawienie poprzedniego wierzchołka
                                pq.emplace(distances[v], v); // Dodanie sąsiada do kolejki
                            }
                        }
                    }
                }
            }
        }

        return reconstructPath(previous, distances[end], start, end);
    }

    // Algorytm Forda-Bellmana dla listy sąsiedztwa
    static std::pair<std::vector<int>, int> bellmanFordAdjacencyList(const Adjacency_List& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max()); // Inicjalizacja wektora odległości maksymalnymi wartościami
        std::vector<int> previous(graph.vertexes, -1); // Wektor przechowujący poprzednie wierzchołki na ścieżce
        distances[start] = 0; // Odległość do wierzchołka startowego wynosi 0

        // Główna pętla algorytmu Forda-Bellmana
        for (int i = 0; i < graph.vertexes - 1; ++i) {
            for (int u = 0; u < graph.vertexes; ++u) {
                // Przejście przez sąsiadów wierzchołka
                for (const auto& [v, weight] : graph.list[u]) {
                    // Jeśli znaleziono krótszą ścieżkę do sąsiada
                    if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight; // Aktualizacja odległości do sąsiada
                        previous[v] = u; // Ustawienie poprzedniego wierzchołka
                    }
                }
            }
        }

        // Zwrócenie znalezionej ścieżki oraz jej łącznej wagi
        return reconstructPath(previous, distances[end], start, end);
    }


    // Algorytm Forda-Bellmana dla macierzy incydencji
    static std::pair<std::vector<int>, int> bellmanFordIncidenceMatrix(const Incidence_Matrix& graph, int start, int end) {
        std::vector<int> distances(graph.vertexes, std::numeric_limits<int>::max()); // Inicjalizacja wektora odległości maksymalnymi wartościami
        std::vector<int> previous(graph.vertexes, -1); // Wektor przechowujący poprzednie wierzchołki na ścieżce
        distances[start] = 0; // Odległość do wierzchołka startowego wynosi 0

        // Główna pętla algorytmu Forda-Bellmana
        for (int i = 0; i < graph.vertexes - 1; ++i) {
            for (int j = 0; j < graph.edges; ++j) {
                for (int u = 0; u < graph.vertexes; ++u) {
                    if (graph.matrix[u][j] > 0) { // Sprawdzenie, czy wierzchołek jest połączony z krawędzią
                        int weight = graph.matrix[u][j]; // Pobranie wagi krawędzi
                        for (int v = 0; v < graph.vertexes; ++v) { // Przejście przez wszystkie wierzchołki
                            // Jeśli znaleziono krótszą ścieżkę do sąsiada
                            if (graph.matrix[v][j] != 0 && distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                                distances[v] = distances[u] + weight; // Aktualizacja odległości do sąsiada
                                previous[v] = u; // Ustawienie poprzedniego wierzchołka
                            }
                        }
                    }
                }
            }
        }

        // Zwrócenie znalezionej ścieżki oraz jej łącznej wagi
        return reconstructPath(previous, distances[end], start, end);
    }

private:
    // Rekonstrukcja najkrótszej ścieżki
    static std::pair<std::vector<int>, int> reconstructPath(const std::vector<int>& previous, int totalWeight, int start, int end) {
        std::vector<int> path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        if (path.size() > 1 && path[0] == start) {
            return {path, totalWeight};
        }

        return {{}, std::numeric_limits<int>::max()}; // Brak ścieżki
    }
};

#endif //PROJEKT_AIZO_2_SHORTHEST_PATH_ALGORYTHMS_H
