#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux
{
    TIPOCHAVE chave;
    struct aux *primFilho, *proxIrmao;
} NO;

typedef NO *PONT;

PONT criaNovoNo(TIPOCHAVE ch){
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo->primFilho = NULL;
    novoNo->proxIrmao = NULL;
    novoNo->chave = ch;

    return novoNo;
}


PONT inicializa (TIPOCHAVE ch){ 
    return criaNovoNo(ch);
}

bool insere(PONT raiz, TIPOCHAVE ch, TIPOCHAVE chavePai){
    PONT pai = buscaChave(chavePai, raiz);
    if(!pai)
        return false;

    PONT filho = pai->primFilho;
    PONT p = pai->primFilho;

    if(!p)
        pai->primFilho = filho;
    else{
        while(p->proxIrmao)
            p = p->proxIrmao;
        p->proxIrmao = filho;
    }

    return true;
}

void exibirArvore(PONT raiz){
    if(raiz == NULL)
        return;
    print("%d(", raiz->chave);
    PONT p = raiz->primFilho;
    while(p){
        exibirArvore(p);
        p = p->proxIrmao;
    }
    printf(")");
}

PONT buscaChave (TIPOCHAVE ch, PONT raiz){
    if(raiz == NULL)
        return NULL;
    
    if(raiz->chave == ch)
        return raiz;

    PONT p = raiz->primFilho;
    while(p){
        PONT resp = buscaChave(ch, p);
        if(resp)
            return resp;
        p = p->proxIrmao;
    }
    return NULL;
}

int main(){
    PONT r = inicializa(8);
}