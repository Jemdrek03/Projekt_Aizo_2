//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_MST_ALGORYTHMS_H
#define PROJEKT_AIZO_2_MST_ALGORYTHMS_H


#include <iostream>

class Shortest_Path_Menu{

public:
    static void show_Menu_Short()
    {

        int ktory = -1;

        while( ktory != 3 ) {
            std::cout << "1. Algorytm Prima " << std::endl;
            std::cout << "2. Algorytm Kruskala " << std::endl;
            std::cout << "3. Powrot do wyboru typu algorytm " << std::endl;

            while (!(std::cin >> ktory) || ktory < 1 || ktory > 3) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wprowadz ponownie: ";
            }
            if (ktory == 3) break;
            switch (ktory) {
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




#endif //PROJEKT_AIZO_2_MST_ALGORYTHMS_H
