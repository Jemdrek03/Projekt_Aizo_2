//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_SHOW_MENU_H
#define PROJEKT_AIZO_2_SHOW_MENU_H


#include <iostream>
#include <limits>
#include "Show_Graph.h"

class Show_Menu{

public:
    static void show_Menu(const Dane& result,const Adjacency_List& aj, const Incidence_Matrix& im)
    {

        int which = -1;

        //Wybor opcji wyswietlenia grafu
        while( which != 4 ) {
            std::cout << "1. Wyswietlanie ogolnych informajii o grafie " << std::endl;
            std::cout << "2. Wyswietlenie listy poprzednikow " << std::endl;
            std::cout << "3. Wyswietlenie macierzy incydencji " << std::endl;
            std::cout << "4. Powrot " << std::endl;

            while (!(std::cin >> which) || which < 1 || which > 4) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wprowadz ponownie: ";
            }
            if (which == 4) break;
            switch (which) {
                case 1:
                    Show_Graph::show_Graph_1(result);
                    break;
                case 2:
                    Show_Graph::show_Graph_2(aj);
                    break;
                case 3:
                    Show_Graph::show_Graph_3(im);
                    break;
                case 4:
                    break;

            }
        }


    }

};







#endif //PROJEKT_AIZO_2_SHOW_MENU_H
