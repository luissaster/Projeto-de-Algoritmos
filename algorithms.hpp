#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>

class Algorithms
{
public:
    Algorithms();
    ~Algorithms();
    // Comparision Algorithms
    void insertionSort(std::vector<int> &);
    void bubbleSort(std::vector<int> &);
    void selectionSort(std::vector<int> &);
    void shellSort(std::vector<int> &);

};

Algorithms::Algorithms() {}
Algorithms::~Algorithms() {}

void Algorithms::insertionSort(std::vector<int> &arr)
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
}

void Algorithms::bubbleSort(std::vector<int> &arr)
{
    bool swapped;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap vec[j] and vec[j+1]
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void Algorithms::selectionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void Algorithms::shellSort(std::vector<int> &arr){
    int n = arr.size();
    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2)
    {
        for (int i = intervalo; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= intervalo && arr[j - intervalo] > temp; j -= intervalo)
            {
                arr[j] = arr[j - intervalo];
            }
            arr[j] = temp;
        }
    }
}
#endif