cmake_minimum_required(VERSION 3.28)
project(Projekt_Aizo_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt_Aizo_2 Projekt_main.cpp
        "MST_Algorythms.h"
        Shorthest_Path_Algorythms.h
        Generate.h
        File_Reading.h
        Main_Menu.h
        "Algorythms_Menu.h"
        MST_Menu.h
        Shortest_Path_Menu.h
        Show_Graph.h
        Adjacency_List.h
        Incidence_Matrix.h
        Show_Menu.h
        Testing.h
        dane_mst1.txt)
