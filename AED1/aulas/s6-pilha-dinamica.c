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

typedef struct aux {
    REGISTRO reg;
    struct aux * prox;
} ELEMENTO;

typedef ELEMENTO * PONT;

typedef struct 
{
    PONT topo;
} PILHA;

void inicializar(PILHA *p)
{
    p->topo = NULL;
}

int tamanhoPilha(PILHA *p)
{
    PONT end = p->topo;
    int tam = 0;

    while(end != NULL){
        tam++;
        end = end->prox;
    }

    return tam;
}

bool estaVazia(PILHA * p){
    if(p->topo == NULL)
        return true;

    return false;
}

void exibirPilha(PILHA *p)
{
    printf("Pilha: \" ");
    PONT end = p->topo;
    while (end != NULL)
    {
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

bool inserirElemento(PILHA *p, REGISTRO reg)
{
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;

    return true;
}


bool excluirElemento(PILHA *p, REGISTRO * reg)
{
    if(p->topo == NULL) 
        return false;

    PONT apagar = p->topo;
    *reg = p->topo->reg;
    p->topo = p->topo->prox;
    free(apagar);

    return true;
}

void reinicializarPilha (PILHA * p){
    PONT apagar;
    PONT end = p->topo;
    while(end != NULL){
        apagar = end;
        end = end->prox;
        free(apagar);
    }
    p->topo = NULL;
}

int main (){
    printf("Pilha Dinamic");
    return 0;
}