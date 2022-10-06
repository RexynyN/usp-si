#define MAXNUMVERTICES 100
// Aresta Nula
#define AN -1 
// Vértice Inválido ou ausente
#define VERTICE_INVALIDO -1 

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int Peso;
typedef struct taresta {
    int vdest;
    Peso peso;
    struct taresta * prox;
} Aresta;

typedef Aresta * Apontador;

typedef struct Grafo {
    Apontador * listaAdj; // É um vetor de apontadores, não esquece!
    int numVertices;
    int numArestas;
} Grafo;


void inicializaGrafo(Grafo *grafo, int nv, int na);

bool insereAresta(int v1, int v2, Peso peso, Grafo * grafo);

bool existeAresta(int v1, int v2, Grafo * grafo);

bool retiraAresta(int v1, int v2, Grafo * grafo);

bool listAdjVazia (int v, Grafo * grafo);

// void liberaGrafo(Grafo * grafo);

void imprimeGrafo(Grafo * grafo);

void grafoTransposto(Grafo * grafo, Grafo * grafoT);

void retiraMin(int a);

Apontador proxListaAdj(int v, Grafo *grafo, Apontador atual);

Apontador primeiroListAdj(int v, Grafo *grafo);
