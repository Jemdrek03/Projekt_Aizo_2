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

    static void show_Graph_1( const Dane& graph)
    {
        std::cout<<"Liczba krawedzi: "<<graph.edges<<std::endl;
        std::cout<<"Liczba wierzcholkow: "<<graph.vertexes<<std::endl;
        for(int i = 0; i < graph.edges; i++)
        {
            std::cout<<"Z krawedzi "<<graph.first[i]<<" do krawedzi "<<graph.second[i]<<" o wadze "<<graph.third[i]<<std::endl;
        }
    }


    static void show_Graph_2(const Adjacency_List& al)
    {
        for (int i = 0; i < al.vertexes; ++i) {
            std::cout << "Vertex " << i << ":";
            for (const auto& [neighbor, weight] : al.list[i]) {
                std::cout << " -> (" << neighbor << ", " << weight << ")";
            }
            std::cout << std::endl;
        }
    }

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

    static void show_Graph_Path(const std::vector<int>& path)
    {
        for( int v : path)
        {
            std::cout<<v<<" -> ";
        }
        std::cout<<"null"<<std::endl;
    }

    static void show_MST(const prim& result)
    {
        int totalWeight = 0;
        std::cout << "MST Edges:\n";
        for (int i = 1; i < result.vertexes; ++i) {
            std::cout << "Edge from vertex " << result.parent[i] << " to vertex " << i << " with weight " << result.key[i] << "\n";
            totalWeight += result.key[i];
        }
        std::cout << "Total cost of MST: " << totalWeight << "\n";
    }

    static void show_MST(const kruskal& result)
    {
        int totalWeight = 0;
        std::cout << "MST Edges:\n";
        for (const auto& edge : result.mst) {
            std::cout << "Edge from vertex " << edge.u << " to vertex " << edge.v << " with weight " << edge.weight << "\n";
            totalWeight += edge.weight;
        }
        std::cout << "Total cost of MST: " << totalWeight << "\n";
    }

};




#endif //PROJEKT_AIZO_2_SHOW_GRAPH_H
