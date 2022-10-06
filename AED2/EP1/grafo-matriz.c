// Bibliotecas
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// Constantes utilizadas no programa
#define MAXNUMVERTICES 100 // Máximo de Vértices na Matriz de Adjacência
#define AN -1              // Aresta Nula
#define VI -1              // Vértice Inválido
#define INFINITY INT_MAX

// Definições de Tipo para as estruturas usadas
typedef int Peso;

typedef struct
{
    Peso mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
    int numVertices;
    int numArestas;
} Grafo;

typedef int Apontador;

typedef struct no
{
    int vertice;
    int custo;
    int ant;
    struct no *prox;
} No;

typedef struct
{
    No *cabeca;
} AGM;

typedef struct
{
    No *cabeca;
} FilaPrioridade;

// ================================= IMPLEMENTAÇÃO DA FILA DE PRIORIDADE ==================

void exibirFila(FilaPrioridade *f)
{
    if(f->cabeca == NULL)
        return;

    printf("Lista de Prioridade: \n");
    No *aux = f->cabeca;
    while (aux)
    {
        printf("[%d, %d, %d]", aux->vertice, aux->custo, aux->ant);
        aux = aux->prox;
    }
    printf("\n");
}

// Atualiza o custo e vértice anterior do nó, organiza na fila
void atualizaNo(FilaPrioridade *f, int vertice, int ant, int custo)
{
    // Esse while busca o Nó com o vértice especificado, assim como seu anterior
    No *vert = f->cabeca;
    No *last = vert;
    while (vert)
    {
        if (vert->vertice == vertice)
        {
            break;
        }

        last = vert;
        vert = vert->prox;
    }

    // Atualiza com a nova informação
    vert->ant = ant;
    vert->custo = custo;

    // Se ele já estiver ordenado, deixa como está
    if (vert->custo < vert->prox->custo && vert->custo > last->custo)
    {
        return;
    }
    // Esse é caso seja o primeiro da lista
    else if(last == vert && vert->custo < vert->prox->custo ){
        return;
    }

    last->prox = vert->prox;

    // Se ele for menor que a cabeça da fila, coloca ele como a cabeça e arruma os ponteiros
    No *v = f->cabeca;
    if (v == NULL){
        printf("Sexo1\n");
        f->cabeca = vert;
    }
    // else if (vert->custo < v->custo)
    // {
    //     No *aux = f->cabeca;
    //     printf("Sexo2\n");
    //     printf("%d %d %d\n" , vert->prox->vertice, vert->vertice, last->vertice);
    //     f->cabeca = vert;
    //     f->cabeca->prox = aux;
    // }
    else
    {
        printf("Sexo3\n");
        // Senão, procura o nó que seja maior ou igual em custo, e coloca entre ele e seu anterior
        No *aux = f->cabeca; // Nó que vamos substituir
        No *antes = f->cabeca; // Nó anterior ao que vamos substituir
        while (aux)
        {
            if(vert->custo <= aux->custo && vert != aux)
                break; 

            antes = aux;
            aux = last->prox;
        }
        
        antes->prox = vert;
        vert->prox = aux;
    }

}

FilaPrioridade * criarFila(Grafo *g, int raiz)
{
    FilaPrioridade *f = (FilaPrioridade *)malloc(sizeof(FilaPrioridade));

    No *ant = NULL;
    for (int i = 0; i < g->numVertices; i++)
    {
        No *new = (No *)malloc(sizeof(No));
        new->vertice = i;
        new->custo = INFINITY;
        new->ant = -1;
        new->prox = NULL;

        if (ant != NULL)
            ant->prox = new;
        else
            f->cabeca = new;
        
        // if (ant != NULL)
        //     printf("[%d, %d, %d]\n", ant->vertice, new->vertice, f->cabeca->vertice);

        ant = new;
    }
    exibirFila(f);

    atualizaNo(f, raiz, -1, 0);

    return f;
}

bool estaVazia(FilaPrioridade *f)
{
    return f->cabeca == NULL;
}

No *retornarMin(FilaPrioridade *fila)
{
    if (fila->cabeca == NULL)
    {
        printf("Lista Vazia");
        return NULL;
    }

    No *aux = fila->cabeca;

    // free(fila->cabeca);

    if (fila->cabeca != NULL)
    {
        fila->cabeca = aux->prox;
        aux->prox = NULL;
    }
    else
    {
        fila->cabeca = NULL;
    }

    return aux;
}

bool estaFila(FilaPrioridade *f, int vertice)
{
    No *aux = f->cabeca;
    while (aux->prox != NULL)
    {
        if (aux->vertice == vertice)
        {
            return true;
        }
        aux = aux->prox;
    }
    return false;
}

No retornaNo(FilaPrioridade *f, int vertice)
{
    No *aux = f->cabeca;
    while (aux)
    {
        if (aux->vertice == vertice)
        {
            return *aux;
        }
        aux = aux->prox;
    }

    return;
}


// ================================= IMPLEMENTAÇÃO DE GRAFOS E PRIM ==================

void adicionaAGM(AGM *agm, No *no)
{
    no->prox = NULL;
    if (agm->cabeca == NULL)
    {
        agm->cabeca = no;
        return;
    }

    No *aux = agm->cabeca;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    aux->prox = no;
}

void gravarAGM(AGM *agm)
{
    printf("Árvore Geradora Mínima: \n");
    No *aux = agm->cabeca;
    while (aux->prox != NULL)
    {
        printf("[%d, %d, %d]", aux->vertice, aux->custo, aux->ant);
        aux = aux->prox;
    }
    printf("\n");
}



void inicializaGrafo(Grafo *grafo, int nv, int na)
{
    if (nv <= 0 || nv >= MAXNUMVERTICES)
    {
        fprintf(stderr, "O número de vértices não deve ser negativo, tampouco maior que %d", MAXNUMVERTICES);
        return;
    }

    grafo->numArestas = na;
    grafo->numVertices = nv;
    for (int i = 0; i < grafo->numVertices; i++)
    {
        for (int j = 0; j < grafo->numVertices; j++)
        {
            grafo->mat[i][j] = AN;
        }
    }
}

bool insereAresta(Grafo *grafo, Peso peso, int v1, int v2)
{
    if (v1 > grafo->numVertices)
    {
        fprintf(stderr, "O vértice 1 \"%d\" não existe.", v1);
        return false;
    }

    if (v1 > grafo->numVertices)
    {
        fprintf(stderr, "O vértice 2 \"%d\" não existe.", v2);
        return false;
    }

    if (peso < 0)
    {
        fprintf(stderr, "O peso não deve ser menor que 0.");
        return false;
    }

    grafo->mat[v1][v2] = peso;

    return true;
}

bool existeAresta(Grafo *grafo, int v1, int v2)
{
    if (v1 > grafo->numVertices || v2 > grafo->numVertices)
        return false;

    return grafo->mat[v1][v2] != AN;
}

bool removeAresta(Grafo *grafo, Peso *peso, int v1, int v2)
{
    if (!existeAresta(grafo, v1, v2))
        return false;

    (*peso) = grafo->mat[v1][v2];
    grafo->mat[v1][v2] = AN;

    return true;
}

bool listAdjVazia(Grafo *grafo, int v)
{
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "O vértice \"%d\" não existe.", v);
        return false;
    }

    bool sentinela = true;
    for (int i = 0; i <= grafo->numVertices; i++)
    {
        if (grafo->mat[v][i] != AN)
        {
            sentinela = false;
            break;
        }
    }

    return sentinela;
}

Apontador primeiroListAdj(Grafo *grafo, int v)
{
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "O vértice \"%d\" não existe.", v);
        return false;
    }

    Apontador a = AN;
    for (int i = 0; i <= grafo->numVertices; i++)
    {
        if (grafo->mat[v][i] != AN)
        {
            a = i;
            break;
        }
    }
    return a;
}

Apontador proxListAdj(Grafo *grafo, Apontador atual, int v)
{
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "O vértice \"%d\" não existe.", v);
        return false;
    }

    Apontador a = AN;
    for (int i = (atual + 1); i <= grafo->numVertices; i++)
    {
        if (grafo->mat[v][i] != AN)
        {
            a = i;
            break;
        }
    }

    return a;
}

void imprimeGrafo(Grafo *grafo)
{
    printf("Matriz de Adjacencia do Grafo: \n\n");
    for (int i = 0; i < grafo->numVertices; i++)
    {
        for (int j = 0; j < grafo->numVertices; j++)
        {

            printf("%d ", grafo->mat[i][j]);
        }
        printf("\n");
    }
}

Grafo liberaGrafo(Grafo *grafo)
{
    free(grafo);
    Grafo g;
    return g;
}

AGM *prim(Grafo *grafo, int raiz)
{
    FilaPrioridade *fila = criarFila(grafo, raiz);
    exibirFila(fila);

    AGM *caminho;
    caminho->cabeca = NULL;

    No *u = NULL;
    No noV;

    while (!estaVazia(fila))
    {
        u = retornarMin(fila);
        adicionaAGM(caminho, u);
        exibirFila(fila);

        for (int v = 0; v < grafo->numVertices; v++)
        {
            if (grafo->mat[u->vertice][v] != VI)
            {
                // printf("Passou 1\n");
                noV = retornaNo(fila, v);
                // printf("Passou 2\n");  
                if (estaFila(fila, v) && grafo->mat[u->vertice][v] < noV.custo)
                    atualizaNo(fila, v, u->vertice, grafo->mat[u->vertice][v]);
                    // printf("Passou 3\n");
            }
        }
    }

    return caminho;
}

int main()
{
    int num1, num2, num3;
    FILE *fptr;

    // Aqui num1 = nro vértices e num2 = nro arestas
    fptr = fopen("grafo01.txt", "r");
    fscanf(fptr, "%d %d", &num1, &num2);

    Grafo g;
    inicializaGrafo(&g, num1, num2);

    // Aqui num1 = v1, num2 = v2, e num3 = Peso
    while (!feof(fptr))
    {
        fscanf(fptr, "%d %d %d", &num1, &num2, &num3);
        insereAresta(&g, num3, num1, num2);
    }

    imprimeGrafo(&g);

    AGM *caminho = prim(&g, 0);
    gravarAGM(caminho);
    printf("Sexo");

    fclose(fptr);
}
