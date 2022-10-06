#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define's e estruturas para a lista
#define MAX 50

typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct
{
    // + 1 para acomodar o registro sentinela da buscaSentinela
    REGISTRO A[MAX + 1];
    int nroElem;
} LISTA;

// Funções para o uso da Lista
void inicializarLista(LISTA *l)
{
    l->nroElem = 0;
}

int tamanho(LISTA *l)
{
    return l->nroElem;
}

void imprimirLista(LISTA *l)
{
    int i;
    printf("Lista: \" ");
    for (i = 0; i < l->nroElem; i++)
        printf("%i ", l->A[i].chave);
    printf("\"\n");
}

int buscaSequencial(LISTA *l, TIPOCHAVE ch)
{
    int i = 0;
    while (i < l->nroElem)
    {
        if (ch == l->A[i].chave)
            return i;
        else
            i++;
    }
    return -1;
}

bool inserirItem(LISTA *l, REGISTRO reg, int i)
{
    int j;

    if ((l->nroElem == MAX) || (i < 0) || (i > l->nroElem))
        return false;

    for (j = l->nroElem; j > i; j--)
        l->A[j] = l->A[j - 1];

    l->A[i] = reg;
    l->nroElem++;
    return true;
}

bool excluirItem(TIPOCHAVE ch, LISTA *l)
{
    int pos, j;
    pos = buscaSequencial(l, ch);

    if (pos == -1)
        return false;

    for (j = pos; j < l->nroElem - 1; j++)
        l->A[j] = l->A[j + 1];

    l->nroElem--;
    return true;
}

void reinicializar(LISTA *l)
{
    l->nroElem = 0;
}

// Funções da segunda aula
int buscaSentinela(LISTA *l, TIPOCHAVE ch)
{
    int i = 0;
    // Elemento "sentinela"
    l->A[l->nroElem].chave = ch;

    while (l->A[i].chave != ch)
        i++;

    if (i == l->nroElem)
        return -1;
    else
        return 1;
}

bool inserirItemOrdenado(LISTA *l, REGISTRO reg)
{
    if (l->nroElem >= MAX)
        return false;

    int pos = l->nroElem;

    while (pos > 0 && l->A[pos - 1].chave > reg.chave)
    {
        l->A[pos] = l->A[pos - 1];
        pos--;
    }

    l->A[pos] = reg;
    l->nroElem++;
}

int buscaBinaria(LISTA *l, TIPOCHAVE ch)
{
    int esq, dir, meio;
    esq = 0;
    dir = l->nroElem - 1;

    while (esq <= dir)
    {
        meio = ((esq - dir) / 2);
        if (l->A[meio].chave == ch)
            return meio;
        else if (l->A[meio].chave < ch)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    return -1;
}

bool excluirItemOrdenado(TIPOCHAVE ch, LISTA *l)
{
    int pos, j;
    pos = buscaBinaria(l, ch);

    if (pos == -1)
        return false;

    for (j = pos; j < l->nroElem - 1; j++)
        l->A[j] = l->A[j + 1];

    l->nroElem--;
    return true;
}

int main()
{
    LISTA l; 
    REGISTRO regs [15];

    regs[1].chave = -43;
    regs[2].chave = 148;
    regs[3].chave = 56;
    regs[4].chave = -58;
    regs[5].chave = -137;
    regs[6].chave = 0;
    regs[7].chave = -177;
    regs[8].chave = 5;
    regs[9].chave = -23;
    regs[10].chave = 84;
    regs[11].chave = 196;
    regs[12].chave = 98;
    regs[13].chave = -118;
    regs[14].chave = 26;
    regs[15].chave = 38;

    for(int i = 0; i < 15; i++)
        inserirItem(&l, regs[i], i);
        
}