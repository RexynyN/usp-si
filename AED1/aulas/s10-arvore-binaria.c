#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef enum
{
    esquerdo,
    direito
} LADO;

typedef struct aux
{
    TIPOCHAVE chave;
    struct aux *esq, *dir;
} NO;

typedef NO *PONT;

PONT buscarChave(TIPOCHAVE ch, PONT raiz)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->chave == ch)
        return raiz;

    PONT aux = buscarChave(ch, raiz->esq);

    if (aux)
        return aux;

    return buscarChave(ch, raiz->dir);
}

PONT criarNovoNo(TIPOCHAVE ch)
{
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    return novoNo;
}

void criarRaiz(PONT *raiz, TIPOCHAVE ch)
{
    *raiz = criarNovoNo(ch);
}

bool inserirFilho(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai, LADO lado)
{
    PONT pai = buscarChave(chavePai, raiz);
    if (!pai)
        return false;

    PONT novo = criarNovoNo(novaChave);
    if(lado == esquerdo){
        // Caso já tenha algum nó
        novo->esq = pai->esq;
        pai->esq = novo;
    }else{
        // Caso já tenha algum nó
        novo->dir = pai->dir;
        pai->dir = novo;
    }
    return true;
}

int main()
{

    return 0;
}