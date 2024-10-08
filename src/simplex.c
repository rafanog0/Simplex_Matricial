#include <stdio.h>
#include <stdlib.h>
#include "/home/rafanog/desktop/otimiza/Simplex_Matricial/inc/matrizes.h"

#define INFINITO 999999999999

void libera_memoria_simplex(float **matriz_base, float **matriz_base_inversa, float **matriz_nao_base, float **matriz_nao_base_resultante, float *vetor_solucao, float *custos_relativos, int num_restricoes)
{
    for (int i = 0; i < num_restricoes; i++)
        free(matriz_base[i]);
    free(matriz_base);
    for (int i = 0; i < num_restricoes; i++)
        free(matriz_base_inversa[i]);
    free(matriz_base_inversa);
    for (int i = 0; i < num_restricoes; i++)
        free(matriz_nao_base[i]);
    free(matriz_nao_base);
    for (int i = 0; i < num_restricoes; i++)
        free(matriz_nao_base_resultante[i]);
    free(matriz_nao_base_resultante);
    free(vetor_solucao);
    free(custos_relativos);
}

int contem_positivo(float *vetor, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (vetor[i] > 0)
            return 1;
    }
    return 0;
}

float *copiar_coluna_vetor(float **matriz, int coluna, int tam)
{
    float *vetor = (float *)malloc(tam * sizeof(float));
    for (int i = 0; i < tam; i++)
    {
        vetor[i] = matriz[i][coluna];
    }
    return vetor;
}

int contem_valor(int tam, int *vetor, int valor)
{
    for (int i = 0; i < tam; i++)
    {
        if (vetor[i] == valor)
            return 1;
    }
    return 0;
}

int verifica_factividade(float *vetor_solucao, int num_restricoes)
{
    for (int i = 0; i < num_restricoes; i++)
    {
        if (vetor_solucao[i] < 0)
            return 0;
    }
    return 1;
}

void insere_vetor_coordenadas(float *vetor_coordenadas, float *vetor_solucao, int *colunas_base, int *colunas_nao_base, int num_variaveis, int num_restricoes)
{
    for (int i = 0; i < num_variaveis; i++)
        vetor_coordenadas[colunas_nao_base[i]] = 0;

    for (int i = 0; i < num_restricoes; i++)
        vetor_coordenadas[colunas_base[i]] = vetor_solucao[i];
}

float calcula_solucao(float *funcao_objetivo, float *vetor_coordenadas, int num_variaveis)
{
    float solucao = 0;

    for (int i = 0; i < num_variaveis; i++)
        solucao += funcao_objetivo[i] * vetor_coordenadas[i];

    return solucao;
}

int busca_indice_maior_valor_vetor(float *funcao_objetivo, int num_variaveis)
{
    float maior_valor = -INFINITO;
    int indice_maior_valor;
    for (int i = 0; i < num_variaveis; i++)
    {
        if (funcao_objetivo[i] > maior_valor)
        {
            maior_valor = funcao_objetivo[i];
            indice_maior_valor = i;
        }
    }
    return indice_maior_valor;
}

int busca_indice_menor_valor_vetor(float *funcao_objetivo, int num_variaveis)
{
    float menor_valor = INFINITO;
    int indice_menor_valor;
    for (int i = 0; i < num_variaveis; i++)
    {
        if (funcao_objetivo[i] < menor_valor)
        {
            menor_valor = funcao_objetivo[i];
            indice_menor_valor = i;
        }
    }
    return indice_menor_valor;
}


float *calcular_custo_relativo(float *funcao_objetivo, float **matriz_variaveis_folga,
                               float **matriz_base_inversa, int num_variaveis, int num_restricoes,
                               int *colunas_base, int *colunas_nao_base)
{
    float *vetor_calculo = (float *)malloc(num_restricoes * sizeof(float));

    for (int i = 0; i < num_restricoes; i++)
    {
        if (colunas_base[i] < num_variaveis)
            vetor_calculo[i] = funcao_objetivo[colunas_base[i]];
        else
            vetor_calculo[i] = 0;
    }
    float *temp = vetor_calculo;
    vetor_calculo = multiplica_vetor_t_por_matriz(matriz_base_inversa, vetor_calculo, num_restricoes, num_restricoes);
    free(temp);
    float *custo_relativo = (float *)malloc(num_variaveis * sizeof(float));

    for (int i = 0; i < num_variaveis; i++)
    {
        float *coluna_selecionada = copiar_coluna_vetor(matriz_variaveis_folga, colunas_nao_base[i], num_restricoes);

        if (colunas_nao_base[i] < num_variaveis)
            custo_relativo[i] = funcao_objetivo[colunas_nao_base[i]] - multiplicacao_vetor(num_restricoes, vetor_calculo, coluna_selecionada);
        else
            custo_relativo[i] = -(multiplicacao_vetor(num_restricoes, vetor_calculo, coluna_selecionada));

        free(coluna_selecionada);
    }

    return custo_relativo;
}

int teste_da_razao(float **matriz_base_inversa, int coluna_entra_base, float **matriz_variaveis_folga, float *vetor_solucao, int num_restricoes)
{
    // Multiplica a matriz inversa pela coluna da variável que entra na base
    float *vetor_calculo = (float *)malloc(num_restricoes * sizeof(float));
    float *coluna_selecionada = copiar_coluna_vetor(matriz_variaveis_folga, coluna_entra_base, num_restricoes);
    float *temp = vetor_calculo;
    vetor_calculo = multiplica_vetor_por_matriz(matriz_base_inversa, coluna_selecionada, num_restricoes, num_restricoes);
    free(temp);

    for (int i = 0; i < num_restricoes; i++)
        vetor_calculo[i] = vetor_solucao[i] / vetor_calculo[i];

    int indice_menor_valor = busca_indice_menor_valor_vetor(vetor_calculo, num_restricoes);
    free(vetor_calculo);
    free(coluna_selecionada);
    return indice_menor_valor; // retorna o índice da variável que sai da base
}

void simplex(float *funcao_objetivo, float **matriz_variaveis_folga, float *vetor_independente, int num_variaveis, int num_restricoes)
{
    int iteracoes = 0;
    // começando pelo caso trivial
    float melhor_solucao = -INFINITO;
    float *melhor_solucao_coordenadas = (float *)malloc((num_variaveis + num_restricoes) * sizeof(float));

    float solucao_encontrada;

    float *vetor_coordenadas = (float *)malloc((num_variaveis + num_restricoes) * sizeof(float));

    int *colunas_base = (int *)malloc(num_restricoes * sizeof(int));
    for (int i = num_variaveis, j = 0; i < num_variaveis + num_restricoes; i++, j++)
        colunas_base[j] = i;

    int *colunas_nao_base = (int *)malloc(num_variaveis * sizeof(int));
    for (int i = 0; i < num_variaveis; i++)
        colunas_nao_base[i] = i;

    while (1)
    {
        iteracoes++;
        float **matriz_base = seleciona_colunas_matriz(matriz_variaveis_folga, colunas_base, num_restricoes);
        // printf("\n----------------- MATRIZ BASE -----------------\n");
        // mostra_matriz(matriz_base, num_restricoes, num_restricoes);

        float **matriz_base_inversa = calcula_matriz_inversa(num_restricoes, matriz_base);
        if(matriz_base_inversa == NULL)
        {
            printf("Matriz singular\n");
            break;
        }
        float **matriz_nao_base = seleciona_colunas_matriz(matriz_variaveis_folga, colunas_nao_base, num_restricoes);

        float **matriz_nao_base_resultante = multiplica_matrizes(num_restricoes, matriz_base_inversa, matriz_nao_base);

        float *vetor_solucao = multiplica_vetor_por_matriz(matriz_base_inversa, vetor_independente, num_restricoes, num_restricoes);

        insere_vetor_coordenadas(vetor_coordenadas, vetor_solucao, colunas_base, colunas_nao_base, num_variaveis, num_restricoes);

        solucao_encontrada = calcula_solucao(funcao_objetivo, vetor_coordenadas, num_variaveis);

        if (verifica_factividade(vetor_coordenadas, num_restricoes))
        {
            if (solucao_encontrada > melhor_solucao)
            {
                melhor_solucao = solucao_encontrada;
                for (int i = 0; i < num_variaveis + num_restricoes; i++)
                    melhor_solucao_coordenadas[i] = vetor_coordenadas[i];
            }
        }
        // calcular custo relativo

        float *custos_relativos = calcular_custo_relativo(funcao_objetivo, matriz_variaveis_folga,
                                                          matriz_base_inversa, num_variaveis, num_restricoes, colunas_base, colunas_nao_base);

        if (!contem_positivo(custos_relativos, num_variaveis))
            break;

        int variavel_entra_base = busca_indice_maior_valor_vetor(custos_relativos, num_variaveis);
        int variavel_sai_base = teste_da_razao(matriz_base_inversa, variavel_entra_base, matriz_variaveis_folga, vetor_solucao, num_restricoes);

        colunas_base[variavel_sai_base] = variavel_entra_base;
        colunas_nao_base[variavel_entra_base] = variavel_sai_base;
        libera_memoria_simplex(matriz_base, matriz_base_inversa, matriz_nao_base, matriz_nao_base_resultante, vetor_solucao, custos_relativos, num_restricoes);
    }

    printf("Melhor solucao encontrada: %.2f\n", melhor_solucao);
    printf("Coordenadas da melhor solucao: \n( ");
    for (int i = 0; i < num_variaveis + num_restricoes; i++)
        printf("%.2f ", melhor_solucao_coordenadas[i]);
    printf(")\nNúmero de iterações: %d\n", iteracoes);
    free(melhor_solucao_coordenadas);
    free(vetor_coordenadas);
    free(colunas_base);
    free(colunas_nao_base);

}



