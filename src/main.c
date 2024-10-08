#include <stdio.h>
#include <stdlib.h>
#include "/home/rafanog/desktop/otimiza/Simplex_Matricial/inc/simplex.h"
#include "/home/rafanog/desktop/otimiza/Simplex_Matricial/inc/matrizes.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#elif defined(__linux__)
#define CLEAR_COMMAND "clear"
#else
#define CLEAR_COMMAND ""
#endif

void limpa_terminal()
{
    if (CLEAR_COMMAND[0] != '\0')
        system(CLEAR_COMMAND);
}

int main()
{
    int num_variaveis;
    int num_restricoes;

    printf("Digite o numero de variaveis e restricoes\n");
    scanf("%d %d", &num_variaveis, &num_restricoes);
    printf("Digite os coeficientes das variaveis da funcao objetivo\n");

    float *vetor_independente = (float *)malloc(num_restricoes * sizeof(float));
    float **matriz_restricoes = (float **)malloc(num_restricoes * sizeof(float *));
    for (int i = 0; i < num_restricoes; i++)
        matriz_restricoes[i] = (float *)malloc(num_variaveis * sizeof(float));

    float *funcao_objetivo = (float *)malloc(num_variaveis * sizeof(float));
    for (int i = 0; i < num_variaveis; i++)
    {
        scanf("%f", &funcao_objetivo[i]);
    }
    for (int i = 0; i < num_restricoes; i++)
    {
        printf("Digite os coeficientes das variaveis da restricao %d\n", i + 1);
        for (int j = 0; j < num_variaveis; j++)
        {
            scanf("%f", &matriz_restricoes[i][j]);
        }
        printf("Digite o valor do lado direito da restricao %d\n", i + 1);
        scanf("%f", &vetor_independente[i]);
    }
    limpa_terminal();

    float **matriz_variaveis_folga = cria_matriz_com_variaveis_de_folga(matriz_restricoes, num_variaveis, num_restricoes);

    simplex(funcao_objetivo, matriz_variaveis_folga, vetor_independente, num_variaveis, num_restricoes);

    for (int i = 0; i < num_restricoes; i++)
        free(matriz_restricoes[i]);
    free(matriz_restricoes);
    for (int i = 0; i < num_restricoes; i++)
        free(matriz_variaveis_folga[i]);
    free(matriz_variaveis_folga);
    free(vetor_independente);
    free(funcao_objetivo);

    return 0;
}
