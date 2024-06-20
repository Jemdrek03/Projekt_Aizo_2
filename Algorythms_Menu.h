//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_ALGORYTHMS_MENU_H
#define PROJEKT_AIZO_2_ALGORYTHMS_MENU_H



#include <iostream>
#include <limits>
#include "Main_Menu.h"
#include "MST_Menu.h"
#include "Shortest_Path_Menu.h"
#include "Incidence_Matrix.h"
#include "Adjacency_List.h"
#include "Show_Menu.h"

class Algorythms_Menu{

public:
    static void show_Algorythm_Menu(const Dane& result)
    {

        int ktory = -1;

        // opcje wyboru algorytmu
        while( ktory != 4 ) {
            std::cout << "1. Algorytm MST " << std::endl;
            std::cout << "2. Algorytm najkrotszej sciezki " << std::endl;
            std::cout << "3. Wyswietlenie grafu " << std::endl;
            std::cout << "4. Powrot " << std::endl;

            while (!(std::cin >> ktory) || ktory < 1 || ktory > 4) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wprowadz ponownie: ";
            }

            //Zamiana dotychczasowej struktury grafu na te potrzebne w dalszej czesci programu
            Incidence_Matrix im = toIncidenceMatrix(result);
            Incidence_Matrix im1 = toIncidenceMatrix1(result);
            Adjacency_List al = toAdjacencyList(result);
            Adjacency_List al1 = toAdjacencyList1(result);
            if (ktory == 4)
                break;
            switch (ktory) {
                case 1:
                    MST_Menu::show_Menu_MST(al1, im1);
                    break;
                case 2:
                    Shortest_Path_Menu::show_Menu_Short(al, im);
                    break;
                case 3:
                    Show_Menu::show_Menu(result, al, im);
                    break;

            }
        }


    }

};




#endif //PROJEKT_AIZO_2_ALGORYTHMS_MENU_H
