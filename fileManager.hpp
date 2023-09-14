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
class FileManager
{
public:
    FileManager();
    ~FileManager();

    std::string generateFile(int algorithm, int inputStyle, int inputSize);
    std::vector<int> loadFile(const std::string &fileName);
    bool checkIfDirectoryExists(const std::string &address);
    void saveFile(const std::vector<int> &arr, int algorithm, int inputStyle, int inputSize);
    void saveTime(int algorithm, int inputStyle, int inputSize, std::chrono::milliseconds time);

private:
    std::string generateFileName(int algorithm, int inputStyle, int inputSize);
    std::string generateOutputFileName(int algorithm, int inputStyle, int inputSize);
    std::string generateTimeFileName(int algorithm, int inputStyle, int inputSize);
};

FileManager::FileManager() {}
FileManager::~FileManager() {}

std::string FileManager::generateFile(int algorithm, int inputStyle, int inputSize)
{
    std::vector<int> arr;
    std::string fileName = generateFileName(algorithm, inputStyle, inputSize);
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

    switch (inputStyle)
    {
    case 1: // Random
        for (int i = 0; i < inputSize; i++)
        {
            arr.push_back(range(generator));
        }
        break;
    case 2: // Ascending
        for (int i = 0; i < inputSize; i++)
        {
            arr.push_back(range(generator));
        }
        std::sort(arr.begin(), arr.end());
        break;
    case 3: // Descending
        for (int i = 0; i < inputSize; i++)
        {
            arr.push_back(range(generator));
        }
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
    // Use std::filesystem::path to handle the path
    std::filesystem::path normalizedPath = address;

    // Replace all occurrences of '/' and '\' with the appropriate path separator
    normalizedPath = normalizedPath.make_preferred();

    // Create the directory path
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

void FileManager::saveFile(const std::vector<int> &arr, int algorithm, int inputStyle, int inputSize)
{
    std::string fileName = generateOutputFileName(algorithm, inputStyle, inputSize);
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

void FileManager::saveTime(int algorithm, int inputStyle, int inputSize, std::chrono::milliseconds time)
{
    std::string fileName = generateTimeFileName(algorithm, inputStyle, inputSize);
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        std::cerr << "Error opening the file -> " << fileName << std::endl;
        return;
    }

    file << "Algorithm: ";
    switch (algorithm)
    {
    case 1:
        file << "Insertion Sort";
        break;
        // Add cases for other algorithms if needed

    default:
        std::cerr << "Invalid algorithm." << std::endl;
        return;
    }
    file << std::endl;

    file << "Input: ";
    switch (inputStyle)
    {
    case 1:
        file << inputSize << " random element(s)";
        break;
    case 2:
        file << inputSize << " random element(s) in ascending order";
        break;
    case 3:
        file << inputSize << " random element(s) in descending order";
        break;
    default:
        std::cerr << "Invalid input style." << std::endl;
        return;
    }
    file << std::endl;

    file << "Time spent: " << time.count() << " milliseconds." << std::endl;

    file.close();
    std::cout << "Time saved successfully -> " << fileName << std::endl;
}

std::string FileManager::generateFileName(int algorithm, int inputStyle, int inputSize)
{
    std::string typeName, inputName;
    switch (algorithm)
    {
    case 1: // Insertion Sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Insertion Sort/Arquivos de Entrada/Random";
            inputName = "Random";
            break;
        case 2:
            typeName = "Insertion Sort/Arquivos de Entrada/Crescente";
            inputName = "Crescente";
            break;
        case 3:
            typeName = "Insertion Sort/Arquivos de Entrada/Decrescente";
            inputName = "Decrescente";
            break;
        default:
            std::cerr << "Invalid input type." << std::endl;
            return "";
        }
        break;
        // Add cases for other algorithms if needed

    default:
        std::cerr << "Invalid algorithm." << std::endl;
        return "";
    }

    // Create the directory structure
    if (!checkIfDirectoryExists(typeName))
    {
        return "";
    }

    // Append the file name with .txt
    typeName += "/Entrada" + inputName + std::to_string(inputSize) + ".txt";

    return typeName;
}

std::string FileManager::generateOutputFileName(int algorithm, int inputStyle, int inputSize)
{
    std::string typeName, inputName;
    switch (algorithm)
    {
    case 1: // Insertion Sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Insertion Sort/Arquivos de Saida/Random";
            inputName = "Random";
            break;
        case 2:
            typeName = "Insertion Sort/Arquivos de Saida/Crescente";
            inputName = "Crescente";
            break;
        case 3:
            typeName = "Insertion Sort/Arquivos de Saida/Decrescente";
            inputName = "Decrescente";
            break;
        }
        break;

    case 2: // Bubble Sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Bubble Sort/Arquivos de Saida/Random";
            inputName = "Random";
            break;
        case 2:
            typeName = "Bubble Sort/Arquivos de Saida/Crescente";
            inputName = "Crescente";
            break;

        case 3:
            typeName = "Bubble Sort/Arquivos de Saida/Decrescente";
            inputName = "Decrescente";
            break;
        }
        break;

    case 3: // Selection Sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Selection Sort/Arquivos de Saida/Random";
            inputName = "Random";
            break;
        case 2:
            typeName = "Selection Sort/Arquivos de Saida/Crescente";
            inputName = "Crescente";
            break;
        case 3:
            typeName = "Selection Sort/Arquivos de Saida/Decrescente";
            inputName = "Decrescente";
            break;
        }
        break;
    }

    // Create the directory structure
    if (!checkIfDirectoryExists(typeName))
    {
        return "";
    }

    // Append the file name with .txt
    typeName += "/Saida" + inputName + std::to_string(inputSize) + ".txt";

    return typeName;
}

std::string FileManager::generateTimeFileName(int algorithm, int inputStyle, int inputSize)
{
    std::string typeName, inputName;
    switch (algorithm)
    {
    case 1: // Insertion Sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Insertion Sort/Arquivos de Tempo/Random";
            inputName = "Random";
            break;
        case 2:
            typeName = "Insertion Sort/Arquivos de Tempo/Crescente";
            inputName = "Crescente";
            break;
        case 3:
            typeName = "Insertion Sort/Arquivos de Tempo/Decrescente";
            inputName = "Decrescente";
            break;
        default:
            std::cerr << "Invalid input type." << std::endl;
            return "";
        }
        break;
        // Add cases for other algorithms if needed

    default:
        std::cerr << "Invalid algorithm." << std::endl;
        return "";
    }

    // Create the directory structure
    if (!checkIfDirectoryExists(typeName))
    {
        return "";
    }

    // Append the file name with .txt
    typeName += "/Tempo" + inputName + std::to_string(inputSize) + ".txt";

    return typeName;
}

#endif
