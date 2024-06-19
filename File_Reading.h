//
// Created by Jędrzej Radłowski on 18/05/2024.
//

#ifndef PROJEKT_AIZO_2_FILE_READING_H
#define PROJEKT_AIZO_2_FILE_READING_H


#include <string>
#include <iostream>
#include <fstream>

struct Dane {
    int edges;
    int vertexes;
    int* first;
    int* second;
    int* third;

};

Dane readData(const std::string& fileName)
{
    Dane result;
    std::cout << "Otwieranie pliku: " << fileName << std::endl;
    int edge = 0, vertex = 0;

    std::ifstream file(fileName);
    if (file.is_open()) {
        std::cout << "Plik zostal otworzony pomyslnie." << std::endl;
        file >> edge >> vertex;

        if (file.fail()) {
            std::cerr << "Blad przy wczytywaniu liczby krawedzi i wierzcholkow." << std::endl;
            file.close();
            return result;
        }

        std::cout << "Liczba krawedzi: " << edge << ", Liczba wierzcholkow: " << vertex << std::endl;

        result.edges = edge;
        result.vertexes = vertex;

        int* first = new int[edge];
        int* second = new int[edge];
        int* third = new int[edge];

        for (int i = 0; i < edge; i++) {
            file >> first[i] >> second[i] >> third[i];
            if (file.fail()) {
                std::cerr << "Blad przy wczytywaniu krawedzi nr " << i << std::endl;
                delete[] first;
                delete[] second;
                delete[] third;
                file.close();
                return result;
            }
            std::cout << "Krawedz " << i << ": " << first[i] << " -> " << second[i] << " o wadze " << third[i] << std::endl;
        }

        result.first = first;
        result.second = second;
        result.third = third;
    } else {
        std::cerr << "Plik nie zostal poprawnie otworzony lub nie istnieje." << std::endl;
    }

    file.close();
    return result;
}


#endif //PROJEKT_AIZO_2_FILE_READING_H
