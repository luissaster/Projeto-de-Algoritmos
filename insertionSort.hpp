#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP
#include <iostream>
#include <vector>

std::vector<int> insertionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int aux = arr[i]; // Valor do elemento atual
        int j = i - 1;    // Elemento anterior ao atual

        while (j >= 0 && arr[j] > aux)
        {
            arr[j + 1] = arr[j]; // Move o elemento anterior para a direita
            j--;                 // Move para o próximo elemento anterior
        }
        arr[j + 1] = aux; // Move aux
    }
    return arr;
}

#endif