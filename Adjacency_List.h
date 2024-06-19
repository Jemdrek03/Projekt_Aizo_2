//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_ADJACENCY_LIST_H
#define PROJEKT_AIZO_2_ADJACENCY_LIST_H



struct Adjacency_List {
    int vertexes;
    std::vector<std::vector<std::pair<int, int>>> list;

    Adjacency_List(int v) : vertexes(v), list(v) {}
};

Adjacency_List toAdjacencyList(const Dane& graph) {
    Adjacency_List al(graph.vertexes);

    for (int i = 0; i < graph.edges; ++i) {
        int u = graph.first[i];
        int v = graph.second[i];
        int weight = graph.third[i];
        al.list[u].emplace_back(v, weight);
        // For undirected graph, add the reverse edge
        // al.list[v].emplace_back(u, weight);
    }

    return al;
}

Adjacency_List toAdjacencyList1(const Dane& graph) {
    Adjacency_List al(graph.vertexes);

    for (int i = 0; i < graph.edges; ++i) {
        int u = graph.first[i];
        int v = graph.second[i];
        int weight = graph.third[i];
        al.list[u].emplace_back(v, weight);
        al.list[v].emplace_back(u, weight);
        // For undirected graph, add the reverse edge
        // al.list[v].emplace_back(u, weight);
    }

    return al;
}


#endif //PROJEKT_AIZO_2_ADJACENCY_LIST_H
