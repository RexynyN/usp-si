#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;

typedef struct aux
{
    int ordem;
    int *A;
} MTI;

void inicializarMatriz(MTI *m, int n)
{
    m->ordem = n;
    // O número de elementos válidos de um matriz triangular inferior é a soma da PA de sua ordem
    int numeroElementos = (1 + n) * (n) / 2;

    m->A = (int *)malloc(sizeof(int) * numeroElementos);

    for (int i = 0; i < numeroElementos; i++)
        m->A[i] = 0;
}

int retornaPosicao(int lin, int col)
{
    return (lin * lin - lin) / 2 + col - 1;
}

bool atribuirMatriz(int lin, int col, int val, MTI *m)
{
    if ((lin < 1) || (lin > m->ordem) || (col < 1) || (col > m->ordem) || (lin < col))
        return false;

    int posicao = retornaPosicao(lin, col);
    m->A[posicao] = val;
    return true;
}

int valorMatriz(int lin, int col, MTI *m)
{
    if ((lin < 1) || (lin > m->ordem) || (col < 1) || (col > m->ordem))
        return -1;

    if((lin < col))
        return 0;

    return m->A[retornaPosicao(lin, col)];
}



int main()
{
    // int matriz1 [2][3];

    // matriz1[0][0] = 1;
    // matriz1[0][1] = 2;
    // matriz1[1][0] = 3;
    // matriz1[1][1] = 4;
    // matriz1[0][2] = 5;
    // matriz1[1][2] = 6;

    int **M = (int **)malloc(sizeof(int *) * 2);

    for (int i = 0; i < 2; i++)
    {
        M[i] = (int *)malloc(sizeof(int) * 3);
    }
}