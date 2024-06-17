//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_SHOW_GRAPH_H
#define PROJEKT_AIZO_2_SHOW_GRAPH_H


#include <iostream>
#include "Main_Menu.h"

class Show_Graph{
public:

    static void show_Graph_1( const Dane& graph)
    {
        std::cout<<"Liczba krawedzi: "<<graph.edges<<std::endl;
        std::cout<<"Liczba wierzcholkow: "<<graph.vertexes<<std::endl;
        for(int i = 0; i < graph.edges; i++)
        {
            std::cout<<"Z krawedzi "<<graph.first[i]<<" do krawedzi"<<graph.second[i]<<" o wadze"<<graph.third[i]<<std::endl;
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

    static void show_Graph_3(const Incidence_Matrix& im)
    {
        for (int i = 0; i < im.vertexes; ++i) {
            for (int j = 0; j < im.edges; ++j) {
                std::cout << im.matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

};




#endif //PROJEKT_AIZO_2_SHOW_GRAPH_H
