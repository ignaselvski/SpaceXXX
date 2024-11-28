#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <limits.h>
#include <iostream>
#include <time.h>

int main() {
    // Create a new graph
    graph* metro = newGraph(MAXV);

    // Read the CSV file to populate the graph
    readCSV(metro, "rotas.csv");

    short option;
    do {
        option = menu();

        switch (option) {
        case 1: {
            std::string startStation, endStation;
            system("CLS");
            std::cout << "\n\t: Digite o nome da estação de origem: ";
            std::cin >> startStation;
            std::cout << "\n\t Digite o nome da estação de destino: ";
            std::cin >> endStation;

            int start = wayIndex(metro, startStation.c_str());
            int end = wayIndex(metro, endStation.c_str());

            wayFinder(metro, start, end);
            system("PAUSE");
            system("CLS");
            break;
        }
        case 2: {
            std::string stationName;
            system("CLS");
            std::cout << "\n\t Digite o nome da estação: ";
            std::cin >> stationName;

            connections(metro, stationName.c_str());
            system("PAUSE");
            system("CLS");
            break;
        }
        case 0:
            std::cout << "Encerrando." << std::endl;
            break;
        default:
            system("CLS");
            std::wcout << "Opção invpalida tente novamente." << std::endl;
            system("PAUSE");
        }
    } while (option != 0);

    // Free the graph memory
    freeGraph(metro);

    return 0;
}