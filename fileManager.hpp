#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <filesystem>
#include "interface.hpp"

enum FileType
{
    Input,
    Output,
    Time
};
enum AlgorithmType
{
    Zero,
    Insertion_Sort,
    Bubble_Sort,
    Selection_Sort,
    Shell_Sort
};
enum InputType
{
    None,
    Random,
    Crescente,
    Decrescente
};

class FileManager
{
public:
    FileManager();
    ~FileManager();

    std::string generateFile(AlgorithmType algorithm, InputType inputStyle, int inputSize);
    std::vector<int> loadFile(const std::string &fileName);
    bool checkIfDirectoryExists(const std::string &address);
    void saveFile(const std::vector<int> &arr, AlgorithmType algorithm, InputType inputStyle, int inputSize);
    void saveTime(AlgorithmType algorithm, InputType inputStyle, int inputSize, std::chrono::milliseconds time);
    std::string generateFileAddress(AlgorithmType algorithm, InputType input, int inputSize, FileType fileType);
};

FileManager::FileManager() {}
FileManager::~FileManager() {}

std::string FileManager::generateFile(AlgorithmType algorithm, InputType inputStyle, int inputSize)
{
    std::string fileName = generateFileAddress(algorithm, inputStyle, inputSize, Input);
    std::ofstream file(fileName);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> range(-1000000, 1000000);

    if (!file.is_open())
    {
        std::cerr << "Error opening the file -> " << fileName << "." << std::endl;
        return "";
    }

    file << inputSize << std::endl;

    std::vector<int> arr(inputSize);
    switch (inputStyle)
    {
    case Random:
        std::generate(arr.begin(), arr.end(), [&]() { return range(generator); });
        break;
    case Crescente:
        std::generate(arr.begin(), arr.end(), [&]() { return range(generator); });
        std::sort(arr.begin(), arr.end());
        break;
    case Decrescente:
        std::generate(arr.begin(), arr.end(), [&]() { return range(generator); });
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        break;
    }

    for (int num : arr)
    {
        file << num << std::endl;
    }
    file.close();

    std::cout << "Input file saved successfully -> " << fileName << std::endl;
    return fileName;
}

std::vector<int> FileManager::loadFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    std::vector<int> arr;
    int size, num;

    if (!file.is_open())
    {
        std::cerr << "Error opening the file -> " << fileName << "." << std::endl;
        return arr;
    }

    file >> size;

    for (int i = 0; i < size; i++)
    {
        file >> num;
        arr.push_back(num);
    }

    file.close();
    return arr;
}

bool FileManager::checkIfDirectoryExists(const std::string &address)
{
    std::filesystem::path normalizedPath = address;
    normalizedPath = normalizedPath.make_preferred(); // Use the proper path separator for the operating system

    try
    {
        std::filesystem::create_directories(normalizedPath);
        std::cout << "Folder(s) created successfully -> " << address << std::endl;
        return true;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Failed to create folder(s) -> " << normalizedPath.string() << " - " << ex.what() << std::endl;
        return false;
    }
}

void FileManager::saveFile(const std::vector<int> &arr, AlgorithmType algorithm, InputType inputStyle, int inputSize)
{
    std::string fileName = generateFileAddress(algorithm, inputStyle, inputSize, Output);
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        std::cerr << "Error opening the file for writing." << std::endl;
        return;
    }

    file << inputSize << std::endl;

    for (int num : arr)
    {
        file << num << std::endl;
    }

    file.close();
    std::cout << "Output file saved successfully -> " << fileName << std::endl;
}

void FileManager::saveTime(AlgorithmType algorithm, InputType inputStyle, int inputSize, std::chrono::milliseconds time)
{
    std::string fileName = generateFileAddress(algorithm, inputStyle, inputSize, Time);
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("Error opening the file -> " + fileName);
    }

    std::string algorithmName;
    switch (algorithm)
    {
    case Insertion_Sort:
        algorithmName = "Insertion Sort";
        break;
    case Bubble_Sort:
        algorithmName = "Bubble Sort";
        break;
    case Selection_Sort:
        algorithmName = "Selection Sort";
        break;
    case Shell_Sort:
        algorithmName = "Shell Sort";
        break;
    default:
        throw std::runtime_error("Algorithm doesn't exist in saveTime() function. Check fileManager.hpp.");
    }

    std::string inputStyleText;
    switch (inputStyle)
    {
    case Random:
        inputStyleText = std::to_string(inputSize) + " random element(s)";
        break;
    case Crescente:
        inputStyleText = std::to_string(inputSize) + " random element(s) in ascending order";
        break;
    case Decrescente:
        inputStyleText = std::to_string(inputSize) + " random element(s) in descending order";
        break;
    default:
        throw std::runtime_error("Invalid input style.");
    }

    file << "Algorithm: " << algorithmName << std::endl;
    file << "Input: " << inputStyleText << std::endl;
    file << "Time spent: " << time.count() << " milliseconds." << std::endl;

    file.close();
    std::cout << "Time saved successfully -> " << fileName << std::endl;
}

std::string FileManager::generateFileAddress(AlgorithmType algorithm, InputType input, int inputSize, FileType fileType)
{
    std::string algorithmName;
    switch (algorithm)
    {
        case Insertion_Sort:
            algorithmName = "Insertion Sort";
            break;
        case Bubble_Sort:
            algorithmName = "Bubble Sort";
            break;
        case Selection_Sort:
            algorithmName = "Selection Sort";
            break;
        case Shell_Sort:
            algorithmName = "Shell Sort";
            break;
    }

    std::string inputName;
    switch (input)
    {
        case Random:
            inputName = "Random";
            break;
        case Crescente:
            inputName = "Crescente";
            break;
        case Decrescente:
            inputName = "Decrescente";
            break;
    }

    std::string fileTypeName;
    switch (fileType)
    {
        case Input:
            fileTypeName = "Arquivos de Entrada";
            break;
        case Output:
            fileTypeName = "Arquivos de Saida";
            break;
        case Time:
            fileTypeName = "Arquivos de Tempo";
            break;
    }

    std::string typeName = algorithmName + "/" + fileTypeName + "/" + inputName + "/";
    if (!checkIfDirectoryExists(typeName))
    {
        return "";
    }

    switch (fileType)
    {
        case Input:
            fileTypeName = "Entrada";
            break;
        case Output:
            fileTypeName = "Saida";
            break;
        case Time:
            fileTypeName = "Tempo";
            break;
    }

    typeName += fileTypeName + inputName + std::to_string(inputSize) + ".txt";
    return typeName;
}

#endif
