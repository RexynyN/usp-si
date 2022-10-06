/*
Identificação

Nome: Breno da Silva Nogueira
Número USP: 12400392
Turma: 04
*/

// Bibliotecas
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Constantes utilizadas no programa
#define MAXNUMVERTICES 100 // Máximo de Vértices na Matriz de Adjacência
#define AN -1              // Aresta Nula
#define VI -1              // Vértice Inválido
#define INFINITY INT_MAX   // Constante de "infinito" para o algoritmo de PRIM

// Definições de Tipo para as estruturas usadas
typedef struct
{
    int mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
    int numVertices;
    int numArestas;
} Grafo;

typedef struct
{
    int pai[MAXNUMVERTICES + 1];
    int custo[MAXNUMVERTICES + 1];
    bool enfileirado[MAXNUMVERTICES + 1];
    int tamanho;
} Nos;

// Inicializa um grafo para utilização
void inicializaGrafo(Grafo *grafo, int nv, int na)
{
    // Faz as verificações necessárias
    if (nv <= 0 || nv >= MAXNUMVERTICES)
    {
        fprintf(stderr, "O número de vértices não deve ser negativo, tampouco maior que %d", MAXNUMVERTICES);
        return;
    }

    // Insere os metadados no Grafo
    grafo->numArestas = na;
    grafo->numVertices = nv;

    // Inicializa o grafo com Arestas Inválidas
    for (int i = 0; i < grafo->numVertices; i++)
    {
        for (int j = 0; j < grafo->numVertices; j++)
        {
            grafo->mat[i][j] = AN;
        }
    }
}

// Insere a aresta no Grafo
bool insereAresta(Grafo *grafo, int peso, int v1, int v2)
{
    // Faz as verificações de inserção
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

    // Sendo um grafo não direcionado, existe sempre uma aresta indo e voltando de mesmo valor
    // Fiquei dois dias inteiros empacado nesse EP por causa de uma linha que esqueci de colocar pra representar a volta, ó burrice (aliás, valeu Amanda)
    grafo->mat[v1][v2] = peso;
    grafo->mat[v2][v1] = peso;

    return true;
}

// Imprime a matriz de adjacencia do grafo
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

// Exibe a fila de prioridade, usado primariamente para debugar o programa
void exibirFila(Nos *f)
{
    printf("Lista de Prioridade: \n");
    for (int i = 0; i < f->tamanho; i++)
    {
        // Verifica se está na fila
        if (f->enfileirado[i] == true)
            printf("[%d, %d, %d]", i, f->custo[i], f->pai[i]);
    }
    printf("\n");
}

// Retorna o vértice de menor custo dentro da Fila de Prioridade
int retornaMin(Nos *n)
{
    // Inicia com o maior valor possível
    int menor = INFINITY;
    int index;
    for (int i = 0; i < n->tamanho; i++)
    {
        // Se estiver enfileirado (fora da árvore mínima), e menor do que "menor", é o que procuramos
        if (n->enfileirado[i] == true && n->custo[i] < menor)
        {
            menor = n->custo[i];
            index = i;
        }
    }
    return index;
}

// Gravar a AGM no arquivo e mostrar no terminal
void gravarAGM(Grafo *g, Nos *nos, FILE *writer, int raiz)
{
    // Calcula o custo total da árvore
    int total = 0;
    for (int i = 1; i < nos->tamanho; i++)
        total += g->mat[nos->pai[i]][i];

    // Printa no terminal e no arquivo o total da arvore
    printf("Valor total = %d\n", total);
    fprintf(writer, "%d\n", total);

    // Printa no terminal e no arquivo as arestas da árvore
    printf("Aresta \tPeso\n");
    int ant = raiz;
    for (int i = 1; i < nos->tamanho; i++)
    {
        printf("%d - %d \t%d \n", nos->pai[i], i, g->mat[nos->pai[i]][i]);
        fprintf(writer, "%d %d\n", nos->pai[i], i);
    }
}

// Algoritmo de Prim no grafo não direcionado
void prim(Grafo *g, int raiz, FILE *writer)
{
    // Cria um struct que vai guardar todas as informações necessárias para o algoritmo
    Nos *nos = (Nos *)malloc(sizeof(Nos));
    nos->tamanho = g->numVertices;
    for (int i = 0; i < nos->tamanho; i++)
    {
        // Anterior ao vértice "i", inicializado com Vértice Inválido
        nos->pai[i] = -1;
        // Custo da aresta
        nos->custo[i] = INFINITY;
        // Mostra que ele está na fila de prioridade (ou alternativamente, negando que está na AGM)
        nos->enfileirado[i] = true;
    }

    // Inicializando o primeiro nó com a menor chave possível
    nos->pai[raiz] = -1;
    nos->custo[raiz] = 0;
    exibirFila(nos);

    // Loop principal
    for (int i = 0; i < g->numVertices - 1; i++)
    {
        // Recebendo a aresta de menor custo
        int u = retornaMin(nos);
        // Tira da fila de prioridade
        nos->enfileirado[u] = false;

        // Iterando sob todos os adjacentes de u
        for (int v = 0; v < g->numVertices; v++)
        {
            // Verifica se é um vértice válido
            if (g->mat[u][v] != VI)
            {
                // Se o vertice "v" estiver na fila a aresta entre ele e "u" for menor que o custo atual...
                if (nos->enfileirado[v] == true && g->mat[u][v] < nos->custo[v])
                {
                    // ...o pai de "v" vira "u", e seu custo agr é o da aresta u --> v
                    nos->pai[v] = u;
                    nos->custo[v] = g->mat[u][v];
                }
            }
        }
    }

    // Terminada todas as iterações, grava a AGM no arquivo
    gravarAGM(g, nos, writer, raiz);
}

// Função principal do programa
int main(int argc, char **argv)
{
    // Certifica de que vai ter os dois argumentos dos arquivos de texto
    if (argc < 3)
    {
        printf("Faltam argumentos para o programa funcionar!");
        return 1;
    }

    // Declara os números que vão ser lidos, e o as streams de arquivo de entrada e saida
    int num1, num2, num3;
    FILE *reader = fopen(argv[1], "r");
    FILE *writer = fopen(argv[2], "w");

    // Se der algum problema na abertura dos arquivos, aborta programa
    if (reader == NULL || writer == NULL)
    {
        printf("Houve um erro ao abrir os arquivos.");
        return 1;
    }

    // Inicializa o grafo
    Grafo g;
    fscanf(reader, "%d %d", &num1, &num2);
    // Aqui num1 = nro vértices e num2 = nro arestas
    inicializaGrafo(&g, num1, num2);

    // Loop para adicionar todas as arestas enquanto houver conteudo a se ler no arquivo
    while (!feof(reader))
    {
        fscanf(reader, "%d %d %d", &num1, &num2, &num3);
        // Aqui num1 = v1, num2 = v2, e num3 = Peso
        insereAresta(&g, num3, num1, num2);
    }
    imprimeGrafo(&g);

    // Chama o algoritmo de prim
    prim(&g, 0, writer);

    // Fecha as streams de arquivo
    fclose(reader);
    fclose(writer);

    printf("Arquivos Salvos.");

    return 0;
}
