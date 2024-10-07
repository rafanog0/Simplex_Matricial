#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <stdbool.h>
#include <stddef.h>

// Declarações das funções adicionais

float *copia_coluna_vetor(float **matriz, int coluna, int tam);

int contem_valor(int tam, int *vetor, int valor);

int verifica_factividade(float *vetor_solucao, int num_restricoes);

void insere_vetor_coordenadas(float *vetor_coordenadas, float *vetor_solucao, int *colunas_base, int *colunas_nao_base, int num_variaveis, int num_restricoes);

float calcula_solucao(float *funcao_objetivo, float *vetor_coordenadas, int num_variaveis);

int busca_indice_maior_valor_vetor(float *vetor, int tamanho);

int busca_indice_menor_valor_vetor(float *vetor, int tamanho);

float *calcular_custo_relativo(float *funcao_objetivo, float **matriz_variaveis_folga,
                               float **matriz_base_inversa, int num_variaveis, int num_restricoes,
                               int *colunas_base, int *colunas_nao_base);

int teste_da_razao(float **matriz_base_inversa, int coluna_entra_base, float **matriz_variaveis_folga, float *vetor_solucao, int num_restricoes);

int contem_positivo(float *vetor, int tam);

void simplex(float *funcao_objetivo, float **matriz_variaveis_folga, float *vetor_independente, int num_variaveis, int num_restricoes);

#endif // SIMPLEX_H
