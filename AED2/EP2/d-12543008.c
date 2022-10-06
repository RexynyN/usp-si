#include <stdio.h>
#include <stdlib.h>
#define MAXNUMVERTICES 100
#define AN -1 // Aresta Nula
#define VI -1 // Vértice Inválido
#define INFINITO 10000

typedef int tipoPeso;
typedef int tipoCusto;
typedef struct TipoGrafo
{
    tipoPeso mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
    int numVertices;
    int numArestas;
    int custoTotal;
    tipoCusto custo[MAXNUMVERTICES + 1];
} TipoGrafo;

void lerEInserir(TipoGrafo *grafo, int argc, char *argv[])
{
    int origem, destino, peso, i, j, a, b;
    char str[60];
    FILE *f = fopen(_argv[1], "r");
    // le a primeira linha (numero de vertices e arestas) e passa pra int
    fgets(str, sizeof(str), f);
    sscanf(str, "%d %d", &grafo->numVertices, &grafo->numArestas);
    if (grafo->numVertices < 0 || grafo->numArestas < 0)
        exit(1);
    // le o restante das linhas e armazena os pesos na matriz de adjacencia
    // obs: grafo nao-direcionado
    while (i < grafo->numArestas)
    {
        fgets(str, sizeof(str) * 3, f);
        sscanf(str, "%d %d %d", &origem, &destino, &peso);
        if (peso < 0)
            exit(1);
        grafo->mat[origem][destino] = peso;
        grafo->mat[destino][origem] = peso;
        i++;
    }
}

void prim(TipoGrafo *grafo)
{
    int i, j, k, indiceMinimo, custo[grafo->numVertices], agm[grafo->numVertices][2], ant[grafo->numVertices], custoMinimo;
    // prepara os arrays de custo e anterior
    for (i = 0; i < grafo->numVertices; i++)
    {
        custo[i] = INFINITO;
        ant[i] = -1;
    }
    // inicializa o custo do primeiro indice como 0
    custo[0] = 0;
    custoMinimo = custo[0];
    indiceMinimo = 0;
    grafo->custoTotal = 0;

    for (i = 0; i < grafo->numVertices; i++)
    {
        // reseta o custoMinimo a cada iteracao para o mesmo nao ficar preso em 0
        custoMinimo = INFINITO;
        // dentro do array de custos, escolhe o minimo
        for (j = 0; j < grafo->numVertices; j++)
        {
            if (custo[j] < 0)
                j++; // pula para o proximo item em custo[] se o elemento atual for invalido (-1)
            if (custoMinimo > custo[j] && custo[j] > 0 && custoMinimo > 0)
            {
                custoMinimo = custo[j];
                indiceMinimo = j;
                continue;
            }
            else
                continue;
        }
        // acumula o custo total
        grafo->custoTotal = grafo->custoTotal + custo[indiceMinimo];
        // coloca o custo dos indices "retirados" como -1
        custo[indiceMinimo] = -1;
        puts("");
        // ajusta os custos e anteriores dos vizinhos do vertice "retirado"
        for (k = 0; k < grafo->numVertices; k++)
        {
            if (grafo->mat[indiceMinimo][k] < custo[k] && grafo->mat[indiceMinimo][k] > 0 && custo[k] > 0)
            {
                custo[k] = grafo->mat[k][indiceMinimo];
                ant[k] = indiceMinimo;
            }
        }
        // coloca as arestas (par de vertices) em um array
        agm[i][0] = ant[indiceMinimo];
        agm[i][1] = indiceMinimo;
    }

    // colocando a saida no arquivo
    freopen(_argv[2], "w", stdout);
    printf("%d\n", grafo->custoTotal);
    for (i = 1; i < grafo->numVertices; i++)
    {
        printf("%d %d", agm[i][0], agm[i][1]);
        puts("");
    }
}

int main()
{
    TipoGrafo grafo;
    lerEInserir(&grafo, _argc, _argv);
    prim(&grafo);
    return 0;
}