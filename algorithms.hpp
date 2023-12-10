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
std::vector<std::string> includedAlgorithms = {"Zero", "Insertion Sort", "Bubble Sort", "Selection Sort",
                                               "Shell Sort", "Merge Sort", "Quick Sort(First)", "Quick Sort(Average)",
                                               "Quick Sort(Median of three)", "Quick Sort(Random)", "Heap Sort (min heap)"};
std::vector<std::string> includedInputStyles = {"None", "Random", "Ascending", "Descending"};

enum AlgorithmType
{
    Zero,
    Insertion_Sort,
    Bubble_Sort,
    Selection_Sort,
    Shell_Sort,
    Merge_Sort,
    Quick_Sort_First,
    Quick_Sort_Average,
    Quick_Sort_Median,
    Quick_Sort_Random,
    Heap_Sort
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

enum PivotType // used in quick sort
{
    First,
    Average,
    MedianOfThree,
    RandomPivot
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
    void quickSort(std::vector<int> &, int, int, PivotType);
    int partition(std::vector<int> &, int, int, PivotType);

    // Heap Sort
    void minHeapify(std::vector<int> &, int, int);
    void buildMinHeap(std::vector<int> &);
    void heapSort(std::vector<int> &);

    // Heap Sort extras
    int heapMinimum(std::vector<int> &);
    int heapExtractMin(std::vector<int> &);
    void heapIncreaseKey(std::vector<int> &, int value, int position);
    void heapInsert(std::vector<int> &, int value);
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

int Algorithms::partition(std::vector<int> &arr, int low, int high, PivotType pivotType)
{
    int pivotIndex, mid;
    switch (pivotType)
    {
    case First:
        pivotIndex = low;
        break;
    case Average:
        pivotIndex = (low + high) / 2;
        break;
    case MedianOfThree:
        mid = (low + high) / 2;
        if (arr[low] > arr[high])
            std::swap(arr[low], arr[high]);
        if (arr[mid] > arr[high])
            std::swap(arr[mid], arr[high]);
        if (arr[low] > arr[mid])
            std::swap(arr[low], arr[mid]);
        pivotIndex = mid;
        break;
    case RandomPivot:
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(low, high);
        pivotIndex = dis(gen);
        break;
    }

    int pivot = arr[pivotIndex];
    int i = low - 1;

    std::swap(arr[pivotIndex], arr[high]);

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

void Algorithms::quickSort(std::vector<int> &arr, int low, int high, PivotType pivotType)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high, pivotType);
        quickSort(arr, low, pivotIndex - 1, pivotType);
        quickSort(arr, pivotIndex + 1, high, pivotType);
    }
}

void Algorithms::minHeapify(std::vector<int> &heap, int i, int heap_size)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < heap_size && heap[left] > heap[smallest])
        smallest = left;
    if (right < heap_size && heap[right] > heap[smallest])
        smallest = right;
    if (smallest != i)
    {
        std::swap(heap[i], heap[smallest]);
        minHeapify(heap, smallest, heap_size);
    }
}
void Algorithms::buildMinHeap(std::vector<int> &heap)
{
    int heap_size = heap.size();
    for (int i = (heap_size / 2) - 1; i >= 0; --i)
    {
        minHeapify(heap, i, heap_size);
    }
}

void Algorithms::heapSort(std::vector<int> &arr)
{
    int heap_size = arr.size();
    buildMinHeap(arr);
    for (int i = heap_size - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        minHeapify(arr, 0, i);
    }
}

int Algorithms::heapMinimum(std::vector<int> &heap)
{
    return heap[0];
}

int Algorithms::heapExtractMin(std::vector<int> &heap)
{
    int min = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    minHeapify(heap, 0, heap.size());
    return min;
}

void Algorithms::heapIncreaseKey(std::vector<int> &heap, int value, int position)
{
    heap[position] = value;
    while (position > 0 && heap[(position - 1) / 2] > heap[position])
    {
        std::swap(heap[position], heap[(position - 1) / 2]);
        position = (position - 1) / 2;
    }
}

void Algorithms::heapInsert(std::vector<int> &heap, int value)
{
    minHeapify(heap, 0, heap.size());
    heap.push_back(value);
    heapIncreaseKey(heap, value, heap.size() - 1);
}
#endif
