
#include "grafo-lista.h"

void inicializaGrafo(Grafo *grafo, int nv, int na)
{
    if (nv <= 0 || nv >= MAXNUMVERTICES)
    {
        fprintf(stderr, "O número de vértices não deve ser negativo, tampouco maior que %d", MAXNUMVERTICES);
        return;
    }
    grafo->numVertices = nv;
    grafo->numVertices = na;

    for (int i = 0; i < nv; i++)
    {
        grafo->listaAdj[i] = NULL;
    }
}

bool insereAresta(int v1, int v2, Peso peso, Grafo *grafo)
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

    Aresta a;
    a.vdest = v2;
    a.peso = peso;
    a.prox = NULL;

    Apontador atual = grafo->listaAdj[v1];
    if (atual == NULL)
    {
        atual = &a;
    }
    else
    {
        while (atual->prox != NULL)
        {
            atual = grafo->listaAdj[v1]->prox;
        }

        atual->prox = &a;
    }

    return true;
}

bool existeAresta(int v1, int v2, Grafo *grafo)
{
    if (v1 > grafo->numVertices || v2 > grafo->numVertices)
        return false;

    bool sentinela = false;
    Apontador atual = grafo->listaAdj[v1];
    while (atual->prox != NULL)
    {
        if (atual->vdest == v2)
        {
            sentinela = true;
            break;
        }
        atual = grafo->listaAdj[v1]->prox;
    }

    return sentinela;
}

bool removeAresta(int v1, int v2, Peso *peso, Grafo *grafo)
{
    if (!existeAresta(v1, v2, grafo))
        return false;

    Apontador atual = grafo->listaAdj[v1];
    Apontador ant = NULL;
    while (atual->prox != NULL)
    {
        ant = atual;
        atual = grafo->listaAdj[v1]->prox;
    }

    ant->prox = atual->prox;
    atual->prox = NULL;
    free(atual);

    return true;
}

bool listAdjVazia(int v, Grafo *grafo)
{
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "O vértice \"%d\" não existe.", v);
        return false;
    }

    return grafo->listaAdj[v] = NULL;
}

Apontador primeiroListAdj(int v, Grafo *grafo)
{
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "O vértice \"%d\" não existe.", v);
        return false;
    }

    return grafo->listaAdj[v];
}

Apontador proxListaAdj(int v, Grafo *grafo, Apontador atual)
{
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "O vértice \"%d\" não existe.", v);
        return false;
    }

    return atual->prox;
}

void imprimeGrafo(Grafo *grafo)
{
    printf("Matriz de Adjacencia do Grafo: \n\n");
    for (int i = 0; i < grafo->numVertices; i++)
    {
        for (int j = 0; j < grafo->numVertices; j++)
        {
            if (grafo->mat[i][j] / 10 == 0 && grafo->mat[i][j] > 0)
            {
                printf("0%d ", grafo->mat[i][j]);
            }
            else
            {
                printf("%d ", grafo->mat[i][j]);
            }
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

void importaMatriz(Peso **matriz, Grafo *grafo, int tamanho)
{
    grafo->numVertices = tamanho;
    memcpy(&(grafo->numVertices), matriz, tamanho * tamanho * sizeof(Peso));

    // for (int i = 0; i < tamanho; i++)
    // {
    //     for (int j = 0; j < tamanho; j++)
    //     {
    //             printf("Sexo");
    //             grafo->mat[i][j] = *(matriz+i)+j;
    //     }
    // }
}