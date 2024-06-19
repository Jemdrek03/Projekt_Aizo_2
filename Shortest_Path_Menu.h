//
// Created by Jędrzej Radłowski on 12/06/2024.
//

#ifndef PROJEKT_AIZO_2_SHORTEST_PATH_MENU_H
#define PROJEKT_AIZO_2_SHORTEST_PATH_MENU_H

#include <iostream>
#include <limits>
#include "Incidence_Matrix.h"
#include "Adjacency_List.h"
#include "Shorthest_Path_Algorythms.h"
#include "Show_Graph.h"

class Shortest_Path_Menu{

public:
        static void show_Menu_Short(const Adjacency_List& al, const Incidence_Matrix& im)
        {

            int which = -1;
            int beggining = 0, end = 0;

            while( which != 3 ) {
                std::cout << "1. Algorytm Dijkstry " << std::endl;
                std::cout << "2. Algorytm Forda-Bellmana " << std::endl;
                std::cout << "3. Powrot " << std::endl;

                while (!(std::cin >> which) || which < 1 || which > 3) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Wprowadz ponownie: ";
                }

                if (which == 3) break;
                std::cout<<"Wprowadz wierzcholek poczatkowy "<<std::endl;
                while (!(std::cin >> beggining) || beggining < 0 || beggining > al.vertexes - 1) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Wprowadz ponownie: ";
                }
                std::cout<<"Wprowadz wierzcholek koncowy "<<std::endl;
                while (!(std::cin >> end) || end < 0 || end > al.vertexes - 1) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Wprowadz ponownie: ";
                }
                switch (which) {
                    case 1:
                        std::cout<<"Dla listy sasiedztwa: ";
                        Show_Graph::show_Graph_Path(Shortest_Path_Algorythms::dijkstraAdjacencyList(al, beggining, end ));
                        std::cout<<std::endl<<"Dlat macierzy incydencji: ";
                        Show_Graph::show_Graph_Path(Shortest_Path_Algorythms::dijkstraIncidenceMatrix(im, beggining, end ));
                        std::cout<<std::endl;
                        break;
                    case 2:
                        std::cout<<"Dla listy sasiedztwa: ";
                        Show_Graph::show_Graph_Path(Shortest_Path_Algorythms::bellmanFordAdjacencyList(al, beggining, end ));
                        std::cout<<std::endl<<"Dlat macierzy incydencji: ";
                        Show_Graph::show_Graph_Path(Shortest_Path_Algorythms::bellmanFordIncidenceMatrix(im, beggining, end ));
                        std::cout<<std::endl;
                        break;
                    case 3:

                        break;

                    }
            }


        }

};



#endif //PROJEKT_AIZO_2_SHORTEST_PATH_MENU_H
