//Program ten implementuje rozne algorytmy grafowe oraz umozliwia pomiar czasu wybranego algorytmu
//Grafy prezentowane sa w postaci listowej (lista poprzednikow i nastepnikow) a takze macierzowej (macierz incydencji)
//Zaimplementowane algorytmy grafowe to: Algorytm Djisktry, Forda-Bellmana, Prima, Kruskala, Forda-Fulkersona(??)


#include <iostream>
#include "Main_Menu.h"


int Projekt_main() {
    Main_Menu::show_MainMenu();
    std::cin.ignore(1);
    std::cin.get();


}
