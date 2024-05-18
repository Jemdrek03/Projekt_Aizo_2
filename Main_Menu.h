//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_MAIN_MENU_H
#define PROJEKT_AIZO_2_MAIN_MENU_H

#include <fstream>
#include <iostream>

class Main_Menu{

public:
    static void show_MainMenu()
    {
        int rodzajDanych = -1;
        std::string nazwaPliku;
        int TMP;

        while(rodzajDanych != TMP )
        {

            //Mozliwosc wyboru opcji poczatkowych
            int zrodloDanych = -1;
            std::cout << "1. Wczytaj dane z pliku" << std::endl;
            std::cout << "2. Wygeneruj dane losowo" << std::endl;
            std::cout << "3. Wyswietl graf listowo i macierzowo" << std::endl;
            std::cout << "Wybierz rodzaj danych: ";
            //Obsluga blednego wyboru opcji poczatkowych
            while (!(std::cin >> rodzajDanych) || rodzajDanych < 1 || rodzajDanych > 3) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wprowadz ponownie: ";
            }


        }


    }


};


#endif //PROJEKT_AIZO_2_MAIN_MENU_H
