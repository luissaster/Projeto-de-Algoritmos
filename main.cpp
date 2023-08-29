#include <iostream>
#include <vector>
#include "fileManager.hpp"
#include "algoritmos/insertionSort.hpp"

int main(void)
{
    int op, sizeChoice;
    std::vector<int> array = {};
    do
    {
        system("cls");
        std::cout << "Escolha o algoritmo:" << std::endl
                  << "1 - Insertion sort" << std::endl
                  << "0 - Encerrar" << std::endl;
        std::cin >> op;

        switch (op)
        {
        case 0: // END PROGRAM
            break;

        case 1: // INSERTION-SORT
            system("cls");
            std::cout << "Escolha o tamanho da entrada" << std::endl
                      << "1 - 10" << std::endl
                      << "2 - 100" << std::endl
                      << "3 - 1000" << std::endl
                      << "4 - 10000" << std::endl
                      << "5 - 100000" << std::endl
                      << "6 - 1000000" << std::endl;
            std::cin >> sizeChoice;
            switch (sizeChoice)
            {
            case 1:
                array = loadInputFile(1);
                array = insertionSort(array);
                saveToFile(array, "saida/10.txt");
                break;
            case 2:
                array = loadInputFile(2);
                array = insertionSort(array);
                saveToFile(array, "saida/100.txt");
                break;
            case 3:
                array = loadInputFile(3);
                array = insertionSort(array);
                saveToFile(array, "saida/1000.txt");
                break;
            case 4:
                array = loadInputFile(4);
                array = insertionSort(array);
                saveToFile(array, "saida/10000.txt");
                break;
            case 5:
                array = loadInputFile(5);
                array = insertionSort(array);
                saveToFile(array, "saida/100000.txt");
                break;
            case 6:
                array = loadInputFile(6);
                array = insertionSort(array);
                saveToFile(array, "saida/1000000.txt");
                break;
            default:
                std::cout << "Tamanho invalido." << std::endl;
                break;
            }

        case 2: // COMING SOON...
            break;
        }
    } while (op != 0);
    return 0;
}