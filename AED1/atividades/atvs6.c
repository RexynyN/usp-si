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
    struct aux *ant;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
    PONT cabeca;
} DEQUE;

void inicializar(DEQUE *d)
{
    d->cabeca = (PONT)malloc(sizeof(ELEMENTO));
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

int tamanho(DEQUE *d)
{
    PONT end = d->cabeca->prox;
    int tam = 0;

    while (end != d->cabeca)
    {
        tam++;
        end = end->prox;
    }

    return tam;
}

void exibirDequeFim(DEQUE *d)
{
    PONT end = d->cabeca->ant;
    printf("Deque partindo do fim: \"");
    while (end != d->cabeca)
    {
        printf("%i ", end->reg.chave);
        end = end->ant;
    }
    printf("\"\n");
}

bool inserirFim(DEQUE *d, REGISTRO reg)
{
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->reg = reg;

    // Ajustando um monte de ponteiros
    novo->prox = d->cabeca;
    novo->ant = d->cabeca->ant;
    d->cabeca->ant = novo;
    novo->ant->prox = novo;

    return true;
}

bool excluirInicio(DEQUE *d, REGISTRO *reg)
{
    if (d->cabeca->prox == d->cabeca)
        return false;

    PONT apagar = d->cabeca->prox;
    *reg = apagar->reg;

    d->cabeca->prox = apagar->prox;
    apagar->prox->ant = d->cabeca;
    free(apagar);
    return true;
}

void reinicializarDeque(DEQUE *d)
{
    PONT end = d->cabeca->prox;
    while (end != d->cabeca)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }

    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

bool encontrarMax(DEQUE *d, int *max)
{
    bool resposta = false;

    if(d->cabeca->prox == d->cabeca)
        return resposta;

    PONT end = d->cabeca->prox;
    int maior = end->reg.chave; 
    while (end != d->cabeca)
    {
        if(end->reg.chave > maior)
            maior = end->reg.chave;

        end = end->prox;        
    }

    resposta = true;
    *max = maior;
    return resposta;
}

int main()
{
    DEQUE d;
    inicializar(&d);
    REGISTRO r;

    r.chave = 20;
    inserirFim(&d, r);
    
    r.chave = 2;
    inserirFim(&d, r);
    r.chave = 3;
    inserirFim(&d, r);
    r.chave = 4;
    inserirFim(&d, r);
    r.chave = 5;
    inserirFim(&d, r);
    r.chave = 60;
    inserirFim(&d, r);
    r.chave = 7;
    inserirFim(&d, r);
    r.chave = 8;
    inserirFim(&d, r);
    r.chave = 9;
    inserirFim(&d, r);
    r.chave = 10;
    inserirFim(&d, r);

    exibirDequeFim(&d);

    int max ;
    encontrarMax(&d, &max);

    printf("O maior eh: %i \n", max);

    return 0;
}