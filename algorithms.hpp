#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>

class Algorithms
{
public:
    Algorithms();
    ~Algorithms();

    void insertionSort(std::vector<int> &);
    void bubbleSort(std::vector<int> &);
    void selectionSort(std::vector<int> &);

private:
};

Algorithms::Algorithms() {}
Algorithms::~Algorithms() {}

void Algorithms::insertionSort(std::vector<int> &arr)
{
    for (int i = 1; i < arr.size(); i++)
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

#endif