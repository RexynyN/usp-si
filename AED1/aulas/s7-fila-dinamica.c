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
    REGISTRO reg;
    struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
    PONT inicio;
    PONT fim;
} FILA;

void inicializar(FILA *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}

int tamanhoPilha(FILA *f)
{
    PONT end = f->inicio;
    int tam = 0;

    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }

    return tam;
}

void exibirFila(FILA *f)
{
    PONT end = f->inicio;
    printf("FILA: \" ");

    while (end != NULL)
    {
        printf("%i", end->reg.chave);
        end = end->prox;
    }
    printf(" \"\n");
}

bool inserirElemento(FILA *f, REGISTRO *reg)
{
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->reg = *reg;
    novo->prox = NULL;

    if (f->inicio == NULL)
        f->inicio = novo;
    else
        f->fim->prox = novo;
    f->fim = novo;
    return true;
}

bool excluirElemento(FILA *f, REGISTRO *reg)
{
    if (f->inicio == NULL)
        return false;

    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if (f->inicio == NULL)
        f->fim == NULL;
    return true;
}

void reinicializar(FILA *f)
{
    PONT end = f->inicio;

    while(end != NULL) {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
}

int main(){
    printf("Fila Dinamica");
    return 0;
}