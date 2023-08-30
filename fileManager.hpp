#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

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

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 1000000);

    // Escrever o tamanho na primeira linha do txt
    arquivo << tamanho << std::endl;

    std::vector<int> numeros;

    switch (tipo)
    {
    case 1: // Números aleatorios
        for (int i = 0; i < tamanho; ++i)
        {
            numeros.push_back(distribution(generator));
        }
        break;

    case 2: // Números aleatorios em ordem crescente
        for (int i = 0; i < tamanho; ++i)
        {
            numeros.push_back(distribution(generator));
        }
        std::sort(numeros.begin(), numeros.end());
        break;

    case 3: // Números aleatorios em ordem decrescente
        for (int i = 0; i < tamanho; ++i)
        {
            numeros.push_back(distribution(generator));
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
        std::cerr << "Erro ao abrir o arquivo -> " << nomeArquivo << "." << std::endl;
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
        std::cerr << "Tipo de entrada inválido." << std::endl;
        return;
    }

    arquivo.open(nomeArquivo);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir o arquivo para escrita." << std::endl;
        return;
    }

    for (int num : numeros)
    {
        arquivo << num << std::endl;
    }

    arquivo.close();

    std::cout << "Arquivo salvo com sucesso: " << nomeArquivo << std::endl;
}
#endif