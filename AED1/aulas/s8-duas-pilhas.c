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
    int topo1;
    int topo2;
} PILHAS;

void inicializar(PILHAS *p)
{
    p->topo1 = -1;
    p->topo2 = MAX;
}

int tamanhoPilhas(PILHAS *p)
{
    int tamanho = p->topo1 + 1;
    tamanho = MAX - p->topo2;

    return tamanho;
}

bool exibirUmaPilha(PILHAS *p, int pilha)
{
    if (pilha < 1 || pilha > 2)
        return false;

    printf("Pilha: %i \"", pilha);
    int i;
    if (pilha == 1)
        for (i = p->topo1; i >= 0; i--)
            printf("%i ", p->A[i].chave);
    else
        for (i = p->topo2; i < MAX; i++)
            printf("%i ", p->A[i].chave);

    printf("\"\n");
    return true;
}

bool inserirElemento(PILHAS *p, REGISTRO reg, int pilha)
{
    if (pilha < 1 || pilha > 2)
        return false;

    if(p->topo1 + 1 == p->topo2)
        return false;

    if(pilha == 1){
        p->topo1 = p->topo1 + 1;
        p->A[p->topo1] = reg;
    }else{
        p->topo2 = p->topo2 - 1;
        p->A[p->topo2] = reg;
    }
}

bool excluirElemento(PILHAS *p, REGISTRO * reg, int pilha)
{
    if (pilha < 1 || pilha > 2)
        return false;

    if(pilha == 1){
        if(p->topo1 == -1)
            return false;
        *reg = p->A[p->topo1];
        p->topo1 = p->topo1 - 1;
    }else{
        if(p->topo2 == MAX)
            return false;
        *reg = p->A[p->topo2];
        p->topo2 = p->topo2 + 1;
    }
    return true;
}

bool reinicializar (PILHAS *p){
    inicializar(p);
}

int main (){
    printf("Duas Pilhas Estáticas");
    return 0;
}