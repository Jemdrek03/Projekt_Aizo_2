//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_SHOW_GRAPH_H
#define PROJEKT_AIZO_2_SHOW_GRAPH_H


#include <iostream>
#include <iomanip>
#include "Main_Menu.h"
#include "Shorthest_Path_Algorythms.h"
#include "MST_Algorythms.h"

class Show_Graph{
public:


    //Wyswietlanie ogolnych informacji o grafie
    static void show_Graph_1( const Dane& graph)
    {
        std::cout<<"Liczba krawedzi: "<<graph.edges<<std::endl;
        std::cout<<"Liczba wierzcholkow: "<<graph.vertexes<<std::endl;
        for(int i = 0; i < graph.edges; i++)
        {
            std::cout<<"Z krawedzi "<<graph.first[i]<<" do krawedzi "<<graph.second[i]<<" o wadze "<<graph.third[i]<<std::endl;
        }
    }

    //Wyswietlanie grafu dla listy sasiedztwa
    static void show_Graph_2(const Adjacency_List& al)
    {
        for (int i = 0; i < al.vertexes; ++i) {
            std::cout << "Wierzcholek " << i << ":";
            for (const auto& [neighbor, weight] : al.list[i]) {
                std::cout << " -> (" << neighbor << ", " << weight << ")";
            }
            std::cout << std::endl;
        }
    }

    //Wyswietlanie grafu dla macierzy incydencji
    static void show_Graph_3(const Incidence_Matrix& im) {
        std::cout << "  "; // Space for row headers
        for (int j = 0; j < im.edges; ++j) {
            std::cout << "E" << j << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < im.vertexes; ++i) {
            std::cout << "V" << i << " "; // Row headers
            for (int j = 0; j < im.edges; ++j) {
                if (im.matrix[i][j] > 1) {
                    std::cout << std::setw(2) << 1 << " ";
                } else {
                    std::cout << std::setw(2) << im.matrix[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }


    //Wyswietlanie wynikow po algorytmach Dijkstry i Bellmana-Forda
    static void show_Graph_Path(const std::pair<std::vector<int>, int>& result)
    {
        const std::vector<int>& path = result.first;
        int totalWeight = result.second;

        for(int v : path)
        {
            std::cout << v << " -> ";
        }
        std::cout << "null" << std::endl;

        if(totalWeight != std::numeric_limits<int>::max()) {
            std::cout << "Calkowita waga sciezki: " << totalWeight << std::endl;
        } else {
            std::cout << "Sciezka nie zostala znaleziona" << std::endl;
        }
    }


    //Wyswietlanie wynikow dla algorytmu Prima
    static void show_MST(const prim& result)
    {
        int totalWeight = 0;
        std::cout << "Krawedzie MST:\n";
        for (int i = 1; i < result.vertexes; ++i) {
            std::cout << "Krawedz z wierzcholka " << result.parent[i] << " do wierzcholka " << i << " z waga " << result.key[i] << "\n";
            totalWeight += result.key[i];
        }
        std::cout << "Calkowita waga MST: " << totalWeight << "\n";
    }

    //Wyswietlanie wynikow dla algorytmu Kruskala
    static void show_MST(const kruskal& result)
    {
        int totalWeight = 0;
        std::cout << "Krawedzie MST:\n";
        for (const auto& edge : result.mst) {
            std::cout << "Krawedz z wierzcholka " << edge.u << " do wierzcholka " << edge.v << " z waga " << edge.weight << "\n";
            totalWeight += edge.weight;
        }
        std::cout << "Calkowita waga MST: " << totalWeight << "\n";
    }

};




#endif //PROJEKT_AIZO_2_SHOW_GRAPH_H
