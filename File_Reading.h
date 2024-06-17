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
    std::cout<< fileName << std::endl;
    int edge = 0, vertex = 0;
    result.edges = edge;
    result.vertexes = vertex;
    std::ifstream file(fileName);
    if(file.good())
    {

        file >> edge >> vertex;

        int* first = new int[edge];
        int* second = new int[edge];
        int* third = new int[edge];
        for( int i = 0; i < edge; i++)
        {
            file >> first[i] >> second[i] >> third[i];
        }

        result.first = first;
        result.second = second;
        result.third = third;

    }
    else
    {
        std::cout<<"Plik nie zostal poprawnie otworzony lub nie istnieje"<<std::endl;
        std::cout<<"Prosze wpisac jeszcze raz nazwe pliku: "<<std::endl;
    }

    file.close();
    return result;


}


#endif //PROJEKT_AIZO_2_FILE_READING_H
