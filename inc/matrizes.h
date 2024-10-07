#ifndef MATRIZES_H
#define MATRIZES_H

#include <stddef.h>


float *multiplica_vetor_t_por_matriz(float **matriz, float *vetor, int tamanho_matriz, int tamanho_vetor);

float *multiplica_vetor_por_matriz(float **matriz, float *vetor, int tamanho_matriz, int tamanho_vetor);

float **multiplica_matrizes(int tam, float **matriz1, float **matriz2);

void insere_identidade(int tam, float **matriz);

float **calcula_matriz_inversa(size_t tamanho, float **matrizSistema);

float **seleciona_colunas_matriz(float **matriz_com_variaveis_folga, int *colunas_escolhidas, int numero_restricoes);

float **cria_matriz_com_variaveis_de_folga(float **matriz_original, int num_variaveis, int num_restricoes);

void mostra_matriz(float **matriz, int num_linhas, int num_colunas);

float multiplicacao_vetor(int tam, float *vetor1, float *vetor2);

float modulo(float x);

#endif // MATRIZES_H
