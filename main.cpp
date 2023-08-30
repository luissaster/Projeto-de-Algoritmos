#include <iostream>
#include <vector>
#include <chrono>
#include "fileManager.hpp"
#include "algoritmos/insertionSort.hpp"

int main(void)
{
    int op, sizeChoice, inputChoice;
    std::string fileAddress;
    std::vector<int> array;
    auto timeStart = std::chrono::high_resolution_clock::now();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeStart);

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
            std::cout << "Escolha o tipo de entrada:" << std::endl
                      << "1 - Aleatoria" << std::endl
                      << "2 - Crescente" << std::endl
                      << "3 - Decrescente" << std::endl;
            std::cin >> inputChoice;
            system("cls");

            std::cout << "Especifique o tamanho da entrada (10, 100, 1000, 10000, 100000, 1000000, ...):" << std::endl;
            std::cin >>
                sizeChoice;
            system("cls");

            fileAddress = gerarArquivo(inputChoice, sizeChoice);
            array = carregarArquivo(fileAddress);

            timeStart = std::chrono::high_resolution_clock::now();
            array = insertionSort(array);
            timeEnd = std::chrono::high_resolution_clock::now();
            totalDuration = std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeStart);

            salvarArquivo(array, inputChoice, sizeChoice);

            std::cout << "Tempo de execucao: " << totalDuration.count() << " segundos." << std::endl;
            system("pause");

            break;

        case 2: // COMING SOON...
            break;
        }
    } while (op != 0);
    return 0;
}