#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct aux
{
    REGISTRO reg;
    struct aux *ant, *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
    PONT cabeca;
} LISTA;

void inicializar(LISTA *l)
{
    l->cabeca = (PONT)malloc(sizeof(ELEMENTO));
    l->cabeca->prox = l->cabeca;
}

int tamanho(LISTA *l)
{
    PONT end = l->cabeca->prox;
    int tam = 0;

    while (end != l->cabeca)
    {
        tam++;
        end = end->prox;
    }

    return tam;
}

void exibirLista(LISTA *l)
{
    PONT end = l->cabeca->prox;
    printf("Lista: \" ");

    while (end != l->cabeca)
    {
        printf("Lista: \" ");
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("Lista: \"\n");
}

void buscaSentinela(LISTA *l, TIPOCHAVE ch)
{
    PONT pos = l->cabeca->prox;
    l->cabeca->reg.chave = ch;

    while (pos->reg.chave != ch)
        pos = pos->prox;

    if (pos != l->cabeca)
        return pos;

    return NULL;
}

void buscaOrdenada(LISTA *l, TIPOCHAVE ch)
{
    PONT pos = l->cabeca->prox;
    l->cabeca->reg.chave = ch;

    while (pos->reg.chave < ch)
        pos = pos->prox;

    if (pos != l->cabeca && pos->reg.chave == ch)
        return pos;

    return NULL;
}

PONT buscaSeqExc(LISTA *l, TIPOCHAVE ch, PONT *ant)
{
    *ant = l->cabeca;
    PONT atual = l->cabeca->prox;
    // Sentinela
    l->cabeca->reg.chave = ch;

    while (atual->reg.chave < ch)
    {
        *ant = atual;
        atual = atual->prox;
    }

    if ((atual != l->cabeca) && (atual->reg.chave == ch))
        return atual;

    return NULL;
}

bool inserirElemento(LISTA *l, REGISTRO reg)
{
    PONT ant, i;
    i = buscaSeqExc(l, reg.chave, &ant);

    if(i != NULL)
        return false;

    i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    i->prox = ant->prox;
    ant->prox = i;

    return true;
}

bool excluirElemento (LISTA * l, TIPOCHAVE ch){
    PONT ant, i;
    i = buscaSeqExc(l, ch, &ant);

    if(i == NULL)
        return false;

    ant->prox = i->prox;
    free(i);
    return true;
}

void reinicializar (LISTA * l){
    PONT end = l->cabeca->prox;

    while(end != l->cabeca){
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->cabeca->prox = l->cabeca;
}

int main (){
    printf("Lista Circular");
    return 0;
}