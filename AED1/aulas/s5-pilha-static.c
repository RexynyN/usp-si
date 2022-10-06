#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0
#define MAX 50

typedef int bool;
typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux
{
    REGISTRO A[MAX];
    int topo;
} PILHA;

void inicializar(PILHA *p)
{
    p->topo = -1;
}

int tamanhoPilha(PILHA *p)
{
    return p->topo + 1;
}

void exibirPilha(PILHA *p)
{
    printf("Pilha: \" ");
    int i;
    for (i = p->topo; i >= 0; i--)
    {
        printf("%i ", p->A[i].chave);
    }
    printf("\"\n");
}

bool inserirElemento(PILHA *p, REGISTRO reg)
{
    if (p->topo >= MAX - 1)
        return false;

    p->topo = p->topo + 1;
    p->A[p->topo] = reg;

    return true;
}


bool excluirElemento(PILHA *p, REGISTRO * reg)
{
    if (p->topo >= -1)
        return false;

    *reg = p->A[p->topo];
    p->topo = p->topo - 1;

    return true;
}

void reinicializarPilha (PILHA * p){
    p->topo = -1;
}

int main (){
    printf("Pilha Static");
    return 0;
}