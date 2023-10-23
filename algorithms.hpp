#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <string>

// To add a new algorithm, follow these steps:
//
// 1. Add the new enum in AlgorithmType
// 2. Add the new algorithm in includedAlgorithms (same index as in the enum)
// 3. Add the algorithm case in runAlgorithm in interface.hpp
//

// These are used for printing the selected algorithm in chooseInputStyle and chooseInputSize
std::vector<std::string> includedAlgorithms = {"Zero", "Insertion Sort", "Bubble Sort", "Selection Sort", "Shell Sort", "Merge Sort", "Quick Sort"};
std::vector<std::string> includedInputStyles = {"None", "Random", "Ascending", "Descending"};

enum AlgorithmType
{
    Zero,
    Insertion_Sort,
    Bubble_Sort,
    Selection_Sort,
    Shell_Sort,
    Merge_Sort,
    Quick_Sort
};

enum InputType
{
    None,
    Random,
    Crescente,
    Decrescente
};

enum FileType
{
    Input,
    Output,
    Time
};

class Algorithms
{
public:
    Algorithms();
    ~Algorithms();

    // Comparision algorithms
    void insertionSort(std::vector<int> &);
    void bubbleSort(std::vector<int> &);
    void selectionSort(std::vector<int> &);
    void shellSort(std::vector<int> &);

    // Divide and conquer algorithms
    void merge(std::vector<int> &, int, int, int);
    void mergeSort(std::vector<int> &, int, int);
    void quickSort(std::vector<int> &, int, int);
    int partition(std::vector<int> &, int, int);
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
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
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
        if (minIndex != i)
        {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

void Algorithms::shellSort(std::vector<int> &arr)
{
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

void Algorithms::merge(std::vector<int> &arr, int start, int middle, int end)
{
    std::vector<int> sortedArr;

    int i = start;
    int j = middle + 1;

    while (i <= middle && j <= end)
    {
        if (arr[i] <= arr[j])
        {
            sortedArr.push_back(arr[i]);
            ++i;
        }
        else
        {
            sortedArr.push_back(arr[j]);
            ++j;
        }
    }

    while (i <= middle)
    {
        sortedArr.push_back(arr[i]);
        ++i;
    }

    while (j <= end)
    {
        sortedArr.push_back(arr[j]);
        ++j;
    }

    for (int k = start; k <= end; ++k)
        arr[k] = sortedArr[k - start];
}

void Algorithms::mergeSort(std::vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void Algorithms::quickSort(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int Algorithms::partition(std::vector<int> &arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}
#endif
