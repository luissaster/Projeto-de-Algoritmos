#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

std::string gerarArquivo(int tipo, int tamanho)
{
    std::ofstream arquivo;
    std::string nomeArquivo;

    switch (tipo)
    {
    case 1:
        nomeArquivo = "entrada/random/entradarandom" + std::to_string(tamanho) + ".txt";
        break;
    case 2:
        nomeArquivo = "entrada/crescente/entradacrescente" + std::to_string(tamanho) + ".txt";
        break;
    case 3:
        nomeArquivo = "entrada/decrescente/entradadecrescente" + std::to_string(tamanho) + ".txt";
        break;
    default:
        std::cout << "Tipo de entrada inválido." << std::endl;
    }

    arquivo.open(nomeArquivo);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir o arquivo -> " << nomeArquivo << "." << std::endl;
        return NULL;
    }

    // Gerador pseudoaleatorio
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> range(-1000000, 1000000);

    // Escrever o tamanho na primeira linha do txt
    arquivo << tamanho << std::endl;

    std::vector<int> numeros;

    switch (tipo)
    {
    case 1: // Números aleatorios
        for (int i = 0; i < tamanho; i++)
        {
            numeros.push_back(range(generator));
        }
        break;

    case 2: // Números aleatorios em ordem crescente
        for (int i = 0; i < tamanho; ++i)
        {
            numeros.push_back(range(generator));
        }
        std::sort(numeros.begin(), numeros.end());
        break;

    case 3: // Números aleatorios em ordem decrescente
        for (int i = 0; i < tamanho; ++i)
        {
            numeros.push_back(range(generator));
        }
        std::sort(numeros.begin(), numeros.end(), std::greater<int>());
        break;
    }

    for (int num : numeros)
    {
        arquivo << num << std::endl;
    }

    arquivo.close();
    return nomeArquivo;
}

std::vector<int> carregarArquivo(const std::string &nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);
    std::vector<int> numeros;

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir o arquivo -> " << nomeArquivo << "." << std::endl;
        return numeros;
    }

    int tamanho;
    arquivo >> tamanho;

    int num;
    for (int i = 0; i < tamanho; i++)
    {
        arquivo >> num;
        numeros.push_back(num);
    }

    arquivo.close();

    return numeros;
}

void salvarArquivo(const std::vector<int> &numeros, int tipo, int tamanho)
{
    std::ofstream arquivo;
    std::string nomeArquivo;

    switch (tipo)
    {
    case 1:
        nomeArquivo = "saida/random/saidarandom" + std::to_string(tamanho) + ".txt";
        break;
    case 2:
        nomeArquivo = "saida/crescente/saidacrescente" + std::to_string(tamanho) + ".txt";
        break;
    case 3:
        nomeArquivo = "saida/decrescente/saidadecrescente" + std::to_string(tamanho) + ".txt";
        break;
    default:
        std::cout << "Tipo inválido." << std::endl;
        return;
    }

    arquivo.open(nomeArquivo);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir o arquivo para escrita." << std::endl;
        return;
    }

    arquivo << tamanho << std::endl;

    for (int num : numeros)
    {
        arquivo << num << std::endl;
    }

    arquivo.close();

    std::cout << "Arquivo salvo com sucesso: " << nomeArquivo << std::endl;
}

void salvarTempo(int algoritmo, int tipo, int tamanho, std::chrono::milliseconds tempo)
{
    std::ofstream arquivo;
    std::string nomeArquivo;

    switch (algoritmo)
    {
    case 1: // Insertion-sort
        switch (tipo)
        {
        case 1: // Random
            nomeArquivo = "tempos/tempo_insertion_sort_random_" + std::to_string(tamanho) + ".txt";
            break;
        case 2: // Crescente
            nomeArquivo = "tempos/tempo_insertion_sort_crescente_" + std::to_string(tamanho) + ".txt";
            break;
        case 3: // Decrescente
            nomeArquivo = "tempos/tempo_insertion_sort_decrescente_" + std::to_string(tamanho) + ".txt";
            break;
        }
        break;
    case 2:
        break;
    }

    arquivo.open(nomeArquivo);
    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir o arquivo -> " << nomeArquivo << "." << std::endl;
        return;
    }

    switch (algoritmo)
    {
    case 1: // Insertion-sort
        arquivo << "Algoritmo: insertion-sort." << std::endl;
        switch (tipo)
        {
        case 1: // Random
            arquivo << "Entrada: " << tamanho << " elemento(s) aleatorios." << std::endl
                    << "Tempo gasto: " << tempo.count() << " milissegundos." << std::endl;
            break;
        case 2: // Crescente
            arquivo << "Entrada: " << tamanho << " elemento(s) aleatorios em ordem crescente." << std::endl
                    << "Tempo gasto: " << tempo.count() << " milissegundos." << std::endl;
            break;
        case 3: // Decrescente
            arquivo << "Entrada: " << tamanho << " elemento(s) aleatorios em ordem decrescente." << std::endl
                    << "Tempo gasto: " << tempo.count() << " milissegundos." << std::endl;
            break;
        }
        break;
    case 2:
        break;
    }

    arquivo.close();
    std::cout << "Tempo salvo em -> " << nomeArquivo << "." << std::endl;
}
#endif