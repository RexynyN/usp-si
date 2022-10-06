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


PONT inicializa (){
    return(NULL);
}

PONT criaNovoNo(TIPOCHAVE ch){
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;

    return novoNo;
}

PONT adiciona (PONT raiz, PONT no){
    if(raiz == NULL)
        return no;
    
    if(no->chave < raiz->chave)
        raiz->esq = adiciona(raiz->esq, no);
    else
        raiz->dir = adiciona(raiz->dir, no);

    return raiz;
}

PONT contem (TIPOCHAVE ch, PONT raiz){
    if (raiz == NULL)
        return NULL;

    if(raiz->chave == ch)
        return raiz;

    if(raiz->chave > ch)
        return contem(ch, raiz->esq);

    return contem(ch, raiz->dir);
}

int numeroNos (PONT raiz){
    if(!raiz)
        return 0;

    return (numeroNos(raiz->esq) + 1 + numeroNos(raiz->dir));
}


PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
    PONT atual = raiz;

    *pai = NULL;
    while(atual){
        if(atual->chave == ch)
            return atual;
        
        *pai = atual;
        if(ch < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    return NULL;
}

PONT removeNo (PONT raiz, TIPOCHAVE ch)
{
    PONT pai, no, p, q;
    no = buscaNo(raiz, ch, &pai);
    if(no == NULL)
        return raiz;
    
    if(!no->esq || !no->dir){
        if(!no->esq)
            q = no->dir;
        else
            q = no->esq;
    }else{
        p = no;
        q = no->esq;
        while(q->dir){
            p = q;
            q = q->dir;
        }
        if(p != no){
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }

    if(!pai){
        free(no);
        return(q);
    }

    if(ch < pai->chave)
        pai->esq = q;
    else 
        pai->dir = q;

    free(no);
    return raiz;
}

void exibirArvore(PONT raiz){
    if(raiz != NULL){
        printf("%i", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

void exibirPreOrdem (PONT raiz){
    if(raiz == NULL)
        return ;

    printf("%i ", raiz->chave);
    exibirPreOrdem(raiz->esq);
    exibirPreOrdem(raiz->dir);
}

void exibirEmOrdem (PONT raiz){
    if(raiz == NULL)
        return;

    exibirEmOrdem(raiz->esq);
    printf("%i ", raiz->chave);
    exibirEmOrdem(raiz->dir);
}

void exibirPosOrdem (PONT raiz){
    if(raiz == NULL)
        return;
    
    exibirPosOrdem(raiz->esq);
    exibirPosOrdem(raiz->dir);
    printf("%i ", raiz->chave);
}

// Versões alternativas de inserção e exclusão

bool inserirNo(PONT * raiz,  TIPOCHAVE ch){
    if(*raiz == NULL){
        *raiz = criaNovoNo(ch);
        return true;
    }else{
        if((*raiz)->chave >= ch)
            return inserirNo(&(*raiz)->esq, ch);
        else 
            return inserirNo(&(*raiz)->dir, ch);
    }

}

PONT maiorAEsquerda(PONT p, PONT *ant){
  *ant = p;
  p = p->esq;
  while (p->dir) {
    *ant = p;
    p = p->dir;
  }
  return(p);
}

bool excluirNo (PONT * raiz, TIPOCHAVE ch){
    PONT atual = *raiz;
    if(!atual)
        return false;
    
    if(atual->chave == ch){
        PONT substituto, pai_substituto;

        if(!atual->esq || !atual->dir){
            if(atual->esq)
                substituto = atual->esq;
            else
                substituto = atual->dir;
            
            *raiz = substituto;
            free(atual);
            return true;
        }else{
            substituto = maiorAEsquerda(atual, &pai_substituto);
            atual->chave = substituto->chave;
            ch = substituto->chave;
        }
    }

    if(ch > atual->chave)
        return excluirNo(&(atual->dir), ch);
    else 
        return excluirNo(&(atual->esq), ch);

}


int main (){
    PONT r = inicializa();

    PONT no = criaNovoNo(23);
    r = adiciona(r,no);

    no = criaNovoNo(12);
    r = adiciona(r,no);

    no = criaNovoNo(15);
    r = adiciona(r,no);

    no = criaNovoNo(25);
    r = adiciona(r,no);

    no = criaNovoNo(8);
    r = adiciona(r,no);

    inserirNo(&r, 37);
    inserirNo(&r, 2);
    inserirNo(&r, 17);
    inserirNo(&r, 42);


    PONT p = contem(12, r);

    printf("%d\n", numeroNos(r));
    exibirArvore(r);
    printf("\n");

    exibirPreOrdem(r);
    printf("\n");

    exibirEmOrdem(r);
    printf("\n");

    exibirPosOrdem(r);
    printf("\n");

}