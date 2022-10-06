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

void exibirPilhaInvertida(PILHA *p)
{
    printf("Pilha: (da base para o topo) \" ");
    for (int i = 0; i <= p->topo; i++)
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
    PILHA pil;
    REGISTRO r;
    inicializar(&pil);

    r.chave = 1;
    inserirElemento(&pil, r);
    r.chave = 2;
    inserirElemento(&pil, r);
    r.chave = 3;
    inserirElemento(&pil, r);
    r.chave = 4;
    inserirElemento(&pil, r);
    r.chave = 5;
    inserirElemento(&pil, r);
    r.chave = 6;
    inserirElemento(&pil, r);
    r.chave = 7;
    inserirElemento(&pil, r);
    r.chave = 8;
    inserirElemento(&pil, r);
    r.chave = 9;
    inserirElemento(&pil, r);
    r.chave = 10;
    inserirElemento(&pil, r);

    exibirPilha (&pil);
    exibirPilhaInvertida(&pil);

    return 0;
}