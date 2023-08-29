import random

quantidade_numeros = 10
def gerar_numero_aleatorio():
    return random.randint(-1000000, 1000000)

# Gerar a quantidade especificada de numeros
numeros_aleatorios = [gerar_numero_aleatorio() for _ in range(quantidade_numeros)]

# Escrever os números no arquivo
nome_arquivo = f"numeros_aleatorios_{quantidade_numeros}.txt"
with open(nome_arquivo, 'w') as arquivo:
    for numero in numeros_aleatorios:
        arquivo.write(str(numero) + '\n')

print(f"Arquivo {nome_arquivo} gerado com sucesso!")
