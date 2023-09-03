#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP
#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> insertionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int aux = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > aux)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = aux;
    }
    return arr;
}

#endif