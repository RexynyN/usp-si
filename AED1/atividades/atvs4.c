#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

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
    PONT inicio;
} LISTA;

void inicializar(LISTA *l)
{
    l->inicio = NULL;
}

int tamanho(LISTA *l)
{
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

void exibirLista(LISTA *l)
{
    PONT end = l->inicio;
    printf("Lista: \" ");
    while (end != NULL)
    {
        printf(" %i ", end->reg.chave);
        end = end->prox;
    }
    printf(" \"\n");
}

PONT buscaSequencialOrd(LISTA *l, TIPOCHAVE ch)
{
    PONT pos = l->inicio;
    while (pos != NULL && pos->reg.chave < ch)
    {
        pos = pos->prox;
    }
    if (pos != NULL && pos->reg.chave == ch)
        return pos;

    return NULL;
}

PONT buscaSequencialExc(LISTA *l, TIPOCHAVE ch, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while (atual != NULL && atual->reg.chave < ch)
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->reg.chave == ch))
        return atual;
    return NULL;
}

bool inserirListaOrd(LISTA *l, REGISTRO reg)
{
    TIPOCHAVE ch = reg.chave;
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);
    if (i != NULL)
        return false;

    i = (PONT)malloc(sizeof(ELEMENTO));
    i->reg = reg;

    if (ant == NULL)
    // Está no começo da lista
    {
        i->ant = 0;
        i->prox = l->inicio;
        l->inicio = i;
    }
    else
    // Está no meio ou no finalxx
    {
        i->prox = ant->prox;
        ant->prox = i;
        i->ant = ant;
    }

    if (i->prox != NULL)
        i->prox->ant = i;

    return true;
}

bool excluirItem(LISTA *l, TIPOCHAVE ch)
{
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);
    if (i == NULL)
        return false;

    if (ant == NULL)
        l->inicio = i->prox;
    else
        ant->prox = i->prox;

    if (i->prox)
        i->prox->ant = ant;

    free(i);
    return true;
}

void reinicializar(LISTA *l)
{
    PONT end = l->inicio;

    while (end != NULL)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

/* Verifica consistencia da lista duplamente ligada */
bool verificarListaDuplamenteLigada(LISTA *l)
{
    bool res = true;
    if (!l->inicio)
        return res;
    PONT ant;
    PONT pos = l->inicio;
    if (pos->ant)
    {
        res = false;
        printf("Problema na verificacao (1): endereco anterior do primeiro elemento difere de NULL.\n");
    }
    while (pos != NULL)
    {
        ant = pos;
        pos = pos->prox;
        if (pos && pos->ant != ant)
        {
            printf("TESTE %p x %p.\n", pos->ant, ant);
            printf("Problema na verificacao (1): endereco anterior do elemento %i difere do endereco de %i: %p x %p.\n", pos->reg.chave, ant->reg.chave, pos->ant, ant);
            res = false;
        }
    }
    return res;
} /* verificarListaDuplamenteLigada */

int main(void)
{
    REGISTRO r1, r2, r3, r4, r5, r6;
    LISTA l;

    inicializar(&l);
    printf("Inserindo elementos... \n");

    r1.chave = 13;
    inserirListaOrd(&l, r1);
    r2.chave = 4;
    inserirListaOrd(&l, r2);
    r3.chave = 7;
    inserirListaOrd(&l, r3);
    r4.chave = 10;
    inserirListaOrd(&l, r4);
    r5.chave = 2;
    inserirListaOrd(&l, r5);
    r6.chave = 12;
    inserirListaOrd(&l, r6);

    exibirLista(&l);
    printf("Verificando a lista: \n");
    printf(" %i \n", verificarListaDuplamenteLigada(&l));

    printf("Excluindo no comeco da lista e verificando: \n");
    excluirItem(&l, 2);
    exibirLista(&l);
    printf(" %i \n", verificarListaDuplamenteLigada(&l));

    printf("Excluindo no meio da lista e verificando: \n");
    excluirItem(&l, 10);
    exibirLista(&l);
    printf(" %i \n", verificarListaDuplamenteLigada(&l));

    printf("Excluindo no final da lista e verificando: \n");
    excluirItem(&l, 13);
    exibirLista(&l);
    printf(" %i \n", verificarListaDuplamenteLigada(&l));

    return 0;
}