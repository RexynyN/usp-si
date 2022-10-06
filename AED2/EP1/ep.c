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
} No;

typedef struct
{
    No nos[MAXNUMVERTICES + 1];
    int tamanho;
} AGM;

typedef struct
{
    No *nos[MAXNUMVERTICES + 1];
    int tamanho;
} FilaPrioridade;

// ================================= IMPLEMENTAÇÃO DA FILA DE PRIORIDADE ==================

void exibirFila(FilaPrioridade *f)
{
    printf("Lista de Prioridade: \n");
    No *aux = NULL;
    for (int i = 0; i < f->tamanho; i++)
    {
        aux = f->nos[i];
        if(aux->vertice != -1)
            printf("[%d, %d, %d]", aux->vertice, aux->custo, aux->ant);
    }
    printf("\n");
}

// Atualiza o custo e vértice anterior do nó, organiza na fila
void atualizaNo(FilaPrioridade *f, int vertice, int ant, int custo)
{
    if (f->tamanho == 0)
        return 0;

    for (int i = 0; i < f->tamanho; i++)
    {
        if (f->nos[i]->vertice == vertice)
        {
            f->nos[i]->ant = ant;
            f->nos[i]->custo = custo;
        }
    }
}

FilaPrioridade *criarFila(Grafo *g, int raiz)
{
    FilaPrioridade *f = (FilaPrioridade *)malloc(sizeof(FilaPrioridade));
    f->tamanho = 0;

    for (int i = 0; i < g->numVertices; i++)
    {
        No *new = (No *)malloc(sizeof(No));
        new->vertice = i;
        new->ant = -1;
        new->custo = INFINITY;

        f->nos[i] = new;
        f->tamanho++;
    }
    exibirFila(f);

    atualizaNo(f, raiz, -1, 0);

    return f;
}

bool estaVazia(FilaPrioridade *f)
{
    return f->tamanho == 0;
}

No retornarMin(FilaPrioridade *fila)
{
    if (fila->tamanho == 0)
    {
        printf("Lista Vazia");
        return;
    }

    int menor = 0;
    int valorMenor = INFINITY;
    for (int i = 0; i < fila->tamanho; i++)
    {
        if(fila->nos[i]->custo < valorMenor){
            valorMenor = fila->nos[i]->custo;
            menor = i;
        }
    }

    No aux = *fila->nos[menor];

    fila->tamanho--;
    for (int i = menor; i < fila->tamanho; i++)  
    {  
        fila->nos[i] = fila->nos[i+1];
    }  

    // // Invalida o nó sem ter que tirar ele do array
    // fila->nos[menor]->vertice = -1;
    // fila->nos[menor]->custo = INFINITY;
    // fila->nos[menor]->ant = -1;

    return aux;
}

bool estaFila(FilaPrioridade *f, int vertice)
{
    if(vertice == -1)
        return false; 

    for (int i = 0; i < f->tamanho; i++)
    {
        if (f->nos[i]->vertice == vertice)
            return true;
    }

    return false;
}

No retornaNo(FilaPrioridade *f, int vertice)
{
    No aux;
    for (int i = 0; i < f->tamanho; i++)
    {
        if (f->nos[i]->vertice == vertice)
            return (*f->nos[i]);
    }

    return;
}

// ================================= IMPLEMENTAÇÃO DE GRAFOS E PRIM ==================

void adicionaAGM(AGM *agm, No no)
{
    agm->nos[agm->tamanho] = no;
    agm->tamanho++;

}

void gravarAGM(AGM *agm)
{
    printf("Árvore Geradora Mínima: \n");
    No aux;
    for (int i = 0; i < agm->tamanho; i++)
    {
        aux = agm->nos[i];
        printf("[%d, %d, %d]", aux.vertice, aux.custo, aux.ant);
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
    printf("Passou 1 %d\n", fila->tamanho);

    AGM *caminho = (AGM*) malloc(sizeof(AGM));

    No u;
    No noV;

    while (!estaVazia(fila))
    {
        printf("Passou 2\n");
        u = retornarMin(fila);
        printf("[%d, %d, %d]\n", u.vertice, u.custo, u.ant);

        printf("Passou 3\n");
        adicionaAGM(caminho, u);
        // gravarAGM(caminho);

        printf("Passou 4\n");
        exibirFila(fila);

        for (int v = 0; v < grafo->numVertices; v++)
        {
            if (grafo->mat[u.vertice][v] != VI)
            {
                printf("Passou 5\n");

                // printf("Passou 1\n");
                noV = retornaNo(fila, v);
                // printf("Passou 2\n");
                if (estaFila(fila, v) && grafo->mat[u.vertice][v] < noV.custo)
                    atualizaNo(fila, v, u.vertice, grafo->mat[u.vertice][v]);
                    exibirFila(fila);

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
    fptr = fopen("grafo02.txt", "r");
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
