//
// Created by Jędrzej Radłowski on 12/06/2024.
//

#ifndef PROJEKT_AIZO_2_MST_MENU_H
#define PROJEKT_AIZO_2_MST_MENU_H


#include <iostream>
#include <limits>
#include "Incidence_Matrix.h"
#include "Adjacency_List.h"
#include "Show_Graph.h"
#include "MST_Algorythms.h"

class MST_Menu{

public:
    static void show_Menu_MST(const Adjacency_List& al, const Incidence_Matrix& im)
    {

        int ktory = -1;

        // Wybor algorytmu MST
        while( ktory != 3 ) {
            std::cout << "1. Algorytm Prima " << std::endl;
            std::cout << "2. Algorytm Kruskala " << std::endl;
            std::cout << "3. Powrot " << std::endl;

            while (!(std::cin >> ktory) || ktory < 1 || ktory > 3) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wprowadz ponownie: ";
            }
            if (ktory == 3) break;
            switch (ktory) {
                case 1:
                    std::cout<<"Dla listy sasiedztwa: ";
                    Show_Graph::show_MST(MST_Algorythms::primAdjacencyList(al));
                    std::cout<<std::endl<<"Dlat macierzy incydencji: ";
                    Show_Graph::show_MST(MST_Algorythms::primIncidenceMatrix(im));
                    std::cout<<std::endl;
                    break;
                case 2:
                    std::cout<<"Dla listy sasiedztwa: ";
                    Show_Graph::show_MST(MST_Algorythms::kruskalAdjacencyList(al));
                    std::cout<<std::endl<<"Dlat macierzy incydencji: ";
                    Show_Graph::show_MST(MST_Algorythms::kruskalIncidenceMatrix(im));
                    std::cout<<std::endl;
                    break;
                case 3:

                    break;

            }
        }


    }

};



#endif //PROJEKT_AIZO_2_MST_MENU_H
