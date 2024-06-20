//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_ADJACENCY_LIST_H
#define PROJEKT_AIZO_2_ADJACENCY_LIST_H


// Struktura reprezentująca listę sąsiedztwa
struct Adjacency_List {
    int vertexes; //liczba wierzcholkow
    std::vector<std::vector<std::pair<int, int>>> list; // Lista sąsiedztwa, przechowująca pary (wierzchołek, waga)

    Adjacency_List(int v) : vertexes(v), list(v) {} // Konstruktor inicjalizujący liczbę wierzchołków i tworzący pustą listę sąsiedztwa
};

// Funkcje przekształcające dane grafu na listę sąsiedztwa

Adjacency_List toAdjacencyList(const Dane& graph) {
    Adjacency_List al(graph.vertexes); // Tworzenie obiektu listy sąsiedztwa z odpowiednią liczbą wierzchołków

    // Iteracja przez wszystkie krawędzie grafu
    for (int i = 0; i < graph.edges; ++i) {
        int u = graph.first[i]; // Początkowy wierzchołek krawędzi
        int v = graph.second[i]; // Końcowy wierzchołek krawędzi
        int weight = graph.third[i]; // Waga krawędzi
        al.list[u].emplace_back(v, weight); // Dodanie krawędzi do listy sąsiedztwa
    }

    return al;
}

//analogicznie z jedna zmiana
Adjacency_List toAdjacencyList1(const Dane& graph) {
    Adjacency_List al(graph.vertexes);

    for (int i = 0; i < graph.edges; ++i) {
        int u = graph.first[i];
        int v = graph.second[i];
        int weight = graph.third[i];
        al.list[u].emplace_back(v, weight);
        al.list[v].emplace_back(u, weight); // Dodanie odwrotnej krawędzi dla grafu nieskierowanego
    }

    return al;
}


#endif //PROJEKT_AIZO_2_ADJACENCY_LIST_H
