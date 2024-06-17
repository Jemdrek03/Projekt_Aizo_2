//
// Created by Jędrzej Radłowski on 12/06/2024.
//

#ifndef PROJEKT_AIZO_2_SHORTEST_PATH_MENU_H
#define PROJEKT_AIZO_2_SHORTEST_PATH_MENU_H

#include <iostream>
#include <limits>
#include "Incidence_Matrix.h"
#include "Adjacency_List.h"



class Shortest_Path_Menu{

public:
        static void show_Menu_Short(const Adjacency_List& al, const Incidence_Matrix& im)
        {

            int which = -1;

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
                switch (which) {
                    case 1:


                        break;
                    case 2:

                        break;
                    case 3:

                        break;

                    }
            }


        }

};



#endif //PROJEKT_AIZO_2_SHORTEST_PATH_MENU_H
