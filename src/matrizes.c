#include <stdio.h>
#include <stdlib.h>
#include "simplex.h"

float modulo(float x)
{
    if (x < 0)
        x = -x;
    return x;
}

void mostra_matriz(float **matriz, int num_linhas, int num_colunas)
{
    for (int i = 0; i < num_linhas; i++)
    {
        for (int j = 0; j < num_colunas; j++)
        {
            printf("%.2f\t", matriz[i][j]);
        }
        printf("\n");
    }
}


float *multiplica_vetor_t_por_matriz(float **matriz, float *vetor, int tamanho_matriz, int tamanho_vetor)
{
    float *resultado = (float *)malloc(tamanho_vetor * sizeof(float));
    for (int i = 0; i < tamanho_matriz; i++)
    {
        resultado[i] = 0;
        for (int j = 0; j < tamanho_vetor; j++)
        {
            resultado[i] += matriz[j][i] * vetor[j];
        }
    }
    return resultado;
}

float *multiplica_vetor_por_matriz(float **matriz, float *vetor, int tamanho_matriz, int tamanho_vetor)
{
    float *resultado = (float *)malloc(tamanho_vetor * sizeof(float));
    for (int i = 0; i < tamanho_matriz; i++)
    {
        resultado[i] = 0;
        for (int j = 0; j < tamanho_vetor; j++)
        {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }
    return resultado;
}

float **multiplica_matrizes(int tam, float **matriz1, float **matriz2)
{
    float **resultado = (float **)malloc(tam * sizeof(float *));
    for (int i = 0; i < tam; i++)
    {
        resultado[i] = (float *)malloc(tam * sizeof(float));
    }

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            resultado[i][j] = 0;
            for (int k = 0; k < tam; k++)
            {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    return resultado;
}

void insere_identidade(int tam, float **matriz)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (i == j)
            {
                matriz[i][j] = 1;
            }
            else
            {
                matriz[i][j] = 0;
            }
        }
    }
}

float **calcula_matriz_inversa(size_t tamanho, float **matrizSistema)
{
    float **matriz = (float **)malloc(tamanho * sizeof(float *));
    for (int i = 0; i < tamanho; i++)
        matriz[i] = (float *)malloc(tamanho * sizeof(float));

    float **inversa = (float **)malloc(tamanho * sizeof(float *));
    for (int i = 0; i < tamanho; i++)
        inversa[i] = (float *)malloc(tamanho * sizeof(float));
    insere_identidade(tamanho, inversa);

    // Copiar a matriz de coeficientes para não alterar a original
    for (int linha = 0; linha < tamanho; linha++)
    {
        for (int coluna = 0; coluna < tamanho; coluna++)
        {
            matriz[linha][coluna] = matrizSistema[linha][coluna];
        }
    }

    // Eliminação Gaussiana com Pivoteamento Parcial para escalonar a matriz até a identidade
    for (int etapa = 0; etapa < tamanho; etapa++)
    {
        // Pivoteamento parcial: encontrar o maior elemento na coluna atual
        int linhaPivo = etapa;
        for (int linha = etapa + 1; linha < tamanho; linha++)
        {
            if (modulo(matriz[linha][etapa]) > modulo(matriz[linhaPivo][etapa]))
            {
                linhaPivo = linha;
            }
        }

        // Se o maior pivô for zero, a matriz é singular e não possui inversa
        if (modulo(matriz[linhaPivo][etapa]) == 0)
        {
            // Liberar memória antes de retornar
            for (int i = 0; i < tamanho; i++)
            {
                free(matriz[i]);
                free(inversa[i]);
            }
            free(matriz);
            free(inversa);
            return NULL;
        }

        // Trocar a linha atual pela linha com o maior pivô, se necessário
        if (linhaPivo != etapa)
        {
            for (int coluna = 0; coluna < tamanho; coluna++)
            {
                float temp = matriz[etapa][coluna];
                matriz[etapa][coluna] = matriz[linhaPivo][coluna];
                matriz[linhaPivo][coluna] = temp;

                temp = inversa[etapa][coluna];
                inversa[etapa][coluna] = inversa[linhaPivo][coluna];
                inversa[linhaPivo][coluna] = temp;
            }
        }

        // Normalizar a linha do pivô para que o elemento pivô seja 1
        float fatorPivo = matriz[etapa][etapa];
        for (int coluna = 0; coluna < tamanho; coluna++)
        {
            matriz[etapa][coluna] /= fatorPivo;
            inversa[etapa][coluna] /= fatorPivo;
        }

        // Tornar todos os elementos acima e abaixo do pivô zero
        for (int linha = 0; linha < tamanho; linha++)
        {
            if (linha != etapa)
            {
                float fatorMultiplicador = matriz[linha][etapa];

                for (int coluna = 0; coluna < tamanho; coluna++)
                {
                    matriz[linha][coluna] -= fatorMultiplicador * matriz[etapa][coluna];
                    inversa[linha][coluna] -= fatorMultiplicador * inversa[etapa][coluna];
                }
            }
        }
    }

    // Liberar a matriz auxiliar, já que não é mais necessária
    for (int i = 0; i < tamanho; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    return inversa;
}

float **seleciona_colunas_matriz(float **matriz_com_variaveis_folga, int *colunas_escolhidas, int numero_restricoes)
{
    float **matriz_selecionada = (float **)malloc(numero_restricoes * sizeof(float *));
    for (int i = 0; i < numero_restricoes; i++)
        matriz_selecionada[i] = (float *)malloc(numero_restricoes * sizeof(float));

    for (int i = 0; i < numero_restricoes; i++)
    {
        int coluna_selecionada = colunas_escolhidas[i]; // Pega o índice da coluna a ser copiada
        for (int j = 0; j < numero_restricoes; j++)
        {
            matriz_selecionada[j][i] = matriz_com_variaveis_folga[j][coluna_selecionada];
        }
    }
    // printf("\n ------------ Matriz selecionada ------------ \n");
    // mostra_matriz(matriz_selecionada, numero_restricoes, numero_restricoes);

    return matriz_selecionada;
}

float **cria_matriz_com_variaveis_de_folga(float **matriz_original, int num_variaveis, int num_restricoes)
{
    int colMatriz = num_variaveis + num_restricoes;
    float **matriz_com_variaveis_folga = (float **)malloc(num_restricoes * sizeof(float *));
    for (int i = 0; i < num_restricoes; i++)
        matriz_com_variaveis_folga[i] = (float *)malloc(colMatriz * sizeof(float));

    for (int i = 0; i < num_restricoes; i++)
    {
        for (int j = 0; j < num_variaveis; j++)
        {
            matriz_com_variaveis_folga[i][j] = matriz_original[i][j];
        }
        for (int j = num_variaveis; j < colMatriz; j++)
        {
            if (j == num_variaveis + i)
            {
                matriz_com_variaveis_folga[i][j] = 1; // Elemento da identidade
            }
            else
            {
                matriz_com_variaveis_folga[i][j] = 0; // Outros elementos são zero
            }
        }
    }

    return matriz_com_variaveis_folga;
}

float multiplicacao_vetor(int tam, float *vetor1, float *vetor2)
{
    float resultado = 0;
    for (int i = 0; i < tam; i++)
    {
        resultado += vetor1[i] * vetor2[i];
    }
    return resultado;
}

