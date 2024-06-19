//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_MAIN_MENU_H
#define PROJEKT_AIZO_2_MAIN_MENU_H

#include <fstream>
#include <iostream>
#include <limits>
#include "File_Reading.h"
#include "Generate.h"
#include "Algorythms_Menu.h"
#include "Testing.h"


class Main_Menu{

public:
    static void show_MainMenu()
    {
        int rodzajDanych = -1;
        int vertexes = 0;
        float density;
        std::string fileName;

        while(rodzajDanych != 4)
        {

            //Mozliwosc wyboru opcji poczatkowych
            std::cout << "1. Wczytaj dane z pliku" << std::endl;
            std::cout << "2. Wygeneruj dane losowo" << std::endl;
            std::cout << "3. Testowanie" << std::endl;
            std::cout << "4. Zakoncz program" << std::endl;
            std::cout << "Wybierz rodzaj danych: ";
            //Obsluga blednego wyboru opcji poczatkowych
            while (!(std::cin >> rodzajDanych) || rodzajDanych < 1 || rodzajDanych > 4) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wprowadz ponownie: ";
            }
            Dane result;
            switch(rodzajDanych){
                case 1:
                    std::cout<<"Podaj nazwe pliku: ";
                    std::cin >> fileName;
                    result = readData(fileName);
                    break;

                case 2:
                    std::cout<<"Podaj ilosc wierzcholkow grafu: ";
                    std::cin>>vertexes;
                    std::cout<<"Podaj gestosc grafu: ";
                    std::cin>>density;
                    result = generateData(vertexes, density);
                    break;

                case 3:
                    Testing::start_Testing();
                    break;
                case 4:
                    break;

            }
            if(rodzajDanych == 4 || rodzajDanych == 3) break;

            Algorythms_Menu::show_Algorythm_Menu(result);
        }


    }


};


#endif //PROJEKT_AIZO_2_MAIN_MENU_H
