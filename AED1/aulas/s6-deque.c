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
    struct aux * ant;
} ELEMENTO;

typedef ELEMENTO * PONT;

typedef struct 
{
    PONT cabeca;
} DEQUE;

void inicializar(DEQUE * d)
{
    d->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

int tamanho (DEQUE * d){
    PONT end = d->cabeca->prox;
    int tam = 0;

    while(end != d->cabeca){
        tam++;
        end = end->prox;
    }

    return tam;
}

void exibirDequeFim (DEQUE * d){
    PONT end = d->cabeca->ant;
    printf("Deque partindo do fim: \"");
    while(end != d->cabeca){
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

bool inserirFim (DEQUE * d, REGISTRO reg){
    PONT novo = (PONT) malloc (sizeof (ELEMENTO));
    novo->reg = reg;

    // Ajustando um monte de ponteiros
    novo->prox = d->cabeca;
    novo->ant = d->cabeca->ant;
    d->cabeca->ant = novo;
    novo->ant->prox = novo;

    return true;
}

bool excluirInicio (DEQUE * d, REGISTRO * reg){
    if(d->cabeca->prox == d->cabeca)
        return false;

    PONT apagar = d->cabeca->prox;
    *reg = apagar->reg;

    d->cabeca->prox = apagar->prox;
    apagar->prox->ant = d->cabeca;
    free(apagar);
    return true;
}

void reinicializarDeque (DEQUE * d){
    PONT end = d->cabeca->prox;
    while(end != d->cabeca){
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }

    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}



int main (){
    printf("Deque");
    return 0;
}