#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0
#define MAX 50
#define ERRO -1
#define NP 4 //Partições da pilha (Nro de Pilhas)

typedef int bool;
typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux
{
    REGISTRO A[MAX];
    int base[NP + 1];
    int topo[NP + 1];
} PILHAS;

void inicializar(PILHAS *p)
{
    for (int i = 0; i <= NP; i++)
    {
        p->base[i] = (i * (MAX / NP)) + 1;
        p->topo[i] = p->base[i] - 1;
    }
}

int tamanhoPilha(PILHAS *p, int k)
{
    int tamanho = 0;

    for (int i = 0; i < NP; i++)
        tamanho += tamanhoPilha(p, i);

    return tamanho;
}

int tamanhoTotal(PILHAS *p, int k)
{
    if (k < 0 || k >= NP)
        return ERRO;

    return p->topo[k] - p->base[k] + 1;
}

bool pilhaCheia(PILHAS *p, int k)
{
    if (p->topo[k] == p->base[k + 1] - 1)
        return true;

    return false;
}

bool pop(PILHAS *p, TIPOCHAVE *ch, int k)
{
    if (k < 0 || k >= NP)
        return false;

    if (p->topo[k] >= p->base[k])
    {
        *ch = p->A[p->topo[k]].chave;
        p->topo[k]--;
        return true;
    }
    return false;
}

bool paraDireita(PILHAS *p, int k)
{
    if (k < 1 || k > NP - 1)
        return false;

    int i;
    if (p->topo[k] < p->base[k + 1] - 1)
    {
        for (i = p->topo[k]; i >= p->base[k]; i--)
            p->A[i + 1] = p->A[i];

        p->topo[k]++;
        p->base[k]++;
        return true;
    }
    return false;
}

bool paraEsquerda(PILHAS *p, int k)
{
    if (k < 1 || k > NP - 1)
        return false;

    int i;
    if (p->topo[k - 1] < p->base[k] - 1)
    {
        for (i = p->topo[k]; i <= p->base[k]; i++)
            p->A[i - 1] = p->A[i];

        p->topo[k]--;
        p->base[k]--;
        return true;
    }
    return false;
}

bool push(PILHAS *p, REGISTRO reg, int k)
{
    if (k < 0 || k >= NP)
        return false;

    if (pilhaCheia(p, k))
    {
        for (int j = NP - 1; j > k; j--)
            paraDireita(p, j);

        if (pilhaCheia(p, k))
        {
            for (int j = 1; j <= k; j++)
                paraEsquerda(p, j);

            if (pilhaCheia(p, k))
                return false;
        }
    }
    p->topo[k]++;
    p->A[p->topo[k]] = reg;
    return true;
}

bool reinicializar(PILHAS *p)
{
    inicializar(p);
}

int main()
{
    printf("Multiplas Pilhas Estáticas");
    return 0;
}