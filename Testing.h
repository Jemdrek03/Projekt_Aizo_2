//
// Created by Jędrzej Radłowski on 17.06.2024.
//

#ifndef PROJEKT_AIZO_2_TESTING_H
#define PROJEKT_AIZO_2_TESTING_H

#include <iostream>
#include <random>
#include <chrono>
#include "File_Reading.h"
#include "Generate.h"
#include "Incidence_Matrix.h"
#include "Adjacency_List.h"

class Testing{
public:
    static void start_Testing()
    {
        std::ofstream plikWyjsciowy("correct_results.txt");
        Dane result;
        int* size = new int[7] {25, 50, 75, 100, 125, 150, 175};

        plikWyjsciowy<<"Rozpoczynam pomiar czasu: "<<std::endl;

        //Dla Dijkstra
        plikWyjsciowy<<"Dijkstra dla sas"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<dijkAdj(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<dijkAdj(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<dijkAdj(siz,0.99)<<std::endl;

        }

        //Dla Dijkstra
        plikWyjsciowy<<"Dijkstra dla mac"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<dijkInc(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<dijkInc(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<dijkInc(siz,0.99)<<std::endl;

        }

        //Dla Forda
        plikWyjsciowy<<"Ford-Bellman dla sas"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<fordAdj(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<fordAdj(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<fordAdj(siz,0.99)<<std::endl;

        }

        //Dla Forda
        plikWyjsciowy<<"Ford-Bellman dla mac"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<fordInc(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<fordInc(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<fordInc(siz,0.99)<<std::endl;

        }

        //Dla Prima
        plikWyjsciowy<<"Prima dla mac"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<primAdj(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<primAdj(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<primAdj(siz,0.99)<<std::endl;

        }

        //Dla Prima
        plikWyjsciowy<<"Prima dla inc"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<primInc(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<primInc(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<primInc(siz,0.99)<<std::endl;

        }

        //Dla Kruskala
        plikWyjsciowy<<"Kruskal dla mac"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<kruAdj(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<kruAdj(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<kruAdj(siz,0.99)<<std::endl;

        }

        //Dla Kruskala
        plikWyjsciowy<<"Kruskal dla inc"<<std::endl;
        for(int i = 0; i < 7; i++ )
        {
            int siz = size[i];
            plikWyjsciowy<<"Rozmiar: "<<siz<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.25<<" wynik: "<<kruInc(siz,0.25)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.50<<" wynik: "<<kruInc(siz,0.5)<<std::endl;
            plikWyjsciowy<<"gestosc: "<<0.99<<" wynik: "<<kruInc(siz,0.99)<<std::endl;

        }

        Incidence_Matrix im = toIncidenceMatrix(result);
        Incidence_Matrix im1 = toIncidenceMatrix1(result);
        Adjacency_List al = toAdjacencyList(result);
        Adjacency_List al1 = toAdjacencyList1(result);

    }

    static int generate(int size)
    {
        std::random_device rd;  // Inicjuje generator
        std::mt19937 gen(rd()); // Użyj generatora Mersenne Twister dla liczb całkowitych

        // Określ zakres losowania
        std::uniform_int_distribution<> dis(0, size - 1); // Rozkład jednorodny od 0 do x
        int randomNumber;

        return  randomNumber = dis(gen);
    }

    static float dijkAdj(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Adjacency_List al = toAdjacencyList(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            Shortest_Path_Algorythms::dijkstraAdjacencyList(al, generate(size), generate(size) );
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro >(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }

    static float dijkInc(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Incidence_Matrix im = toIncidenceMatrix(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            Shortest_Path_Algorythms::dijkstraIncidenceMatrix(im, generate(size), generate(size) );
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro>(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }

    static float fordAdj(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Adjacency_List al = toAdjacencyList(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            Shortest_Path_Algorythms::bellmanFordAdjacencyList(al, generate(size), generate(size) );
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro>(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }

    static float fordInc(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Incidence_Matrix im = toIncidenceMatrix(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            Shortest_Path_Algorythms::bellmanFordIncidenceMatrix(im, generate(size), generate(size) );
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro>(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }



    static float primAdj(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Adjacency_List al1 = toAdjacencyList1(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            MST_Algorythms::primAdjacencyList(al1);
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro>(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }
    static float primInc(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Incidence_Matrix im1 = toIncidenceMatrix1(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            MST_Algorythms::primIncidenceMatrix(im1 );
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro>(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }
    static float kruAdj(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Adjacency_List al1 = toAdjacencyList1(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            MST_Algorythms::kruskalAdjacencyList((al1));
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro>(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }
    static float kruInc(int size, float density)
    {
        Dane result;
        float suma = 0.0, czas = 0.0;
        for( int j = 0; j < 100; j++)
        {
            result = generateData(size, density);
            Incidence_Matrix im1 = toIncidenceMatrix1(result);
            auto t1 = std::chrono::high_resolution_clock::now();
            MST_Algorythms::kruskalIncidenceMatrix(im1 );
            auto t2 = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration<float, std::micro>(t2 - t1);
            czas = ms_int.count();
            suma += czas;
        }
        suma /= 100.0;
        return suma;
    }





};



#endif //PROJEKT_AIZO_2_TESTING_H
