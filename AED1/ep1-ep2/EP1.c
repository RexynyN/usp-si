/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   04 - Prof. Luciano Antonio Digiampietri                       **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/**   Breno da Silva Nogueira                   12400392            **/
/**                                                                 **/
/*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#define NUMTIPOS 10
#define true 1
#define false 0

typedef int bool;

typedef struct aux
{
    int id;
    int quantidade;
    int valorUnitario;
    struct aux *proxProd;
} REGISTRO, *PONT;

typedef struct
{
    PONT LISTADELISTAS[NUMTIPOS];
} LISTADEPRODUTOS, *PLISTA;

PLISTA criarLista();

int tamanho(PLISTA l);

int consultarValorUnitario(PLISTA l, int id);

PONT buscarID(PLISTA l, int id);

PONT buscarIDTipo(PLISTA l, int id, int tipo);

bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor);

bool atualizarValorDoProduto(PLISTA l, int id, int valor);

bool removerItensDeUmProduto(PLISTA l, int id, int quantidade);

PLISTA criarLista()
{
    PLISTA res = (PLISTA)malloc(sizeof(LISTADEPRODUTOS));
    int x;
    for (x = 0; x < NUMTIPOS; x++)
    {
        res->LISTADELISTAS[x] = (PONT)malloc(sizeof(REGISTRO));
        res->LISTADELISTAS[x]->id = -1;
        res->LISTADELISTAS[x]->quantidade = 0;
        res->LISTADELISTAS[x]->valorUnitario = 0;
        res->LISTADELISTAS[x]->proxProd = NULL;
    }
    return res;
}

int tamanho(PLISTA l)
{
    int tam = 0;
    int x;
    PONT atual;
    for (x = 0; x < NUMTIPOS; x++)
    {
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual)
        {
            atual = atual->proxProd;
            tam++;
        }
    }
    return tam;
}

PONT buscarID(PLISTA l, int id)
{
    int x;
    PONT atual;
    for (x = 0; x < NUMTIPOS; x++)
    {
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual)
        {
            if (atual->id == id)
                return atual;
            atual = atual->proxProd;
        }
    }
    return NULL;
}

int buscarTipo(PLISTA l, int id)
{
    int x;
    PONT atual;
    for (x = 0; x < NUMTIPOS; x++)
    {
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual)
        {
            if (atual->id == id)
                return x;
            atual = atual->proxProd;
        }
    }
    return -1;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo)
{
    if (tipo < 0 || tipo >= NUMTIPOS)
        return NULL;
    PONT atual = l->LISTADELISTAS[tipo]->proxProd;
    while (atual)
    {
        if (atual->id == id)
            return atual;
        atual = atual->proxProd;
    }
    return NULL;
}

PONT retornarNoAnterior(PLISTA l, PONT node, int tipo)
{
    PONT mid = l->LISTADELISTAS[tipo]->proxProd;
    PONT ant = l->LISTADELISTAS[tipo];
    while (mid)
    {
        if (mid == node)
            return ant;
        ant = mid;
        mid = mid->proxProd;
    }
    return NULL;
}

void exibirLog(PLISTA f)
{
    int numElementos = tamanho(f);
    printf("Log lista [elementos: %i]\n", numElementos);
    int x;
    PONT atual;
    for (x = 0; x < NUMTIPOS; x++)
    {
        printf("  #TIPO: %i -> ", x);
        atual = f->LISTADELISTAS[x]->proxProd;
        while (atual)
        {
            printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade * atual->valorUnitario);
            atual = atual->proxProd;
        }
        printf("\n");
    }
    printf("\n");
}

int consultarValorUnitario(PLISTA l, int id)
{
    int x;
    PONT atual;
    for (x = 0; x < NUMTIPOS; x++)
    {
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual)
        {
            if (atual->id == id)
                return atual->valorUnitario;
            atual = atual->proxProd;
        }
    }
    return 0;
}

bool removerNo(PLISTA l, PONT node, PONT ant, int tipo)
{
    ant->proxProd = node->proxProd;
    inserirNovoProduto(l, node->id, tipo, node->quantidade, node->valorUnitario);
    free(node);
    return true;
}

bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor)
{
    // Valida a entrada
    if (buscarID(l, id) != NULL || valor < 0 || quantidade < 0 || id < 0 || tipo < 0 || tipo > (NUMTIPOS - 1))
    {
        return false;
    }

    // Cria o novo nó e aloca as informações
    PONT novo = (PONT)malloc(sizeof(REGISTRO));
    novo->id = id;
    novo->quantidade = quantidade;
    novo->valorUnitario = valor;

    // Aloca o novo nó na lista ordenada
    PONT mid = l->LISTADELISTAS[tipo]->proxProd;
    if (mid != NULL)
    {
        int valorNovo = quantidade * valor;
        int valorTotal = 0;
        PONT ant = l->LISTADELISTAS[tipo];
        while (mid)
        {
            valorTotal = mid->quantidade * mid->valorUnitario;
            if (valorTotal >= valorNovo)
                break;
            ant = mid;
            mid = mid->proxProd;
        }

        novo->proxProd = mid;
        ant->proxProd = novo;
        return true;
    }
    else
    {
        novo->proxProd = NULL;
        l->LISTADELISTAS[tipo]->proxProd = novo;
        return true;
    }

    return false;
}

bool removerItensDeUmProduto(PLISTA l, int id, int quantidade)
{
    PONT node = buscarID(l, id);
    if (node == NULL || node->quantidade < quantidade || quantidade <= 0)
        return false;

    node->quantidade -= quantidade;

    int tipo = buscarTipo(l, id);
    PONT ant = retornarNoAnterior(l, node, tipo);

    if (node->quantidade == 0)
    {
        ant->proxProd = node->proxProd;
        free(node);
        return true;
    }
    else
    {
        PONT prox = node->proxProd;
        int valorTotal = (node->quantidade * node->valorUnitario);

        if (prox == NULL)
        {
            if ((ant->quantidade * ant->valorUnitario) > valorTotal)
            {
                removerNo(l, node, ant, tipo);
                return true;
            }
        }
        else if ((ant->quantidade * ant->valorUnitario) > valorTotal || (prox->quantidade * prox->valorUnitario) < valorTotal)
        {
            removerNo(l, node, ant, tipo);
            return true;
        }

        return true;
    }

    return false;
}

bool atualizarValorDoProduto(PLISTA l, int id, int valor)
{
    PONT node = buscarID(l, id);
    if (node == NULL || valor <= 0)
        return false;

    node->valorUnitario = valor;

    int tipo = buscarTipo(l, id);
    PONT ant = retornarNoAnterior(l, node, tipo);
    PONT prox = node->proxProd;
    int valorTotal = (node->quantidade * node->valorUnitario);

        if (prox == NULL)
        {
            if ((ant->quantidade * ant->valorUnitario) > valorTotal)
            {
                removerNo(l, node, ant, tipo);
                return true;
            }
        }
        else if ((ant->quantidade * ant->valorUnitario) > valorTotal || (prox->quantidade * prox->valorUnitario) < valorTotal)
        {
            removerNo(l, node, ant, tipo);
            return true;
        }

    return true;
}

int main()
{
    PLISTA f = criarLista();
    int id;
    int tipo;
    int quantidade;
    int valor;
    bool res;

    printf("################# INSERINDO #######################\n");

    exibirLog(f);
    res = inserirNovoProduto(f, 2, 1, 22, 23);
    if (res)
        printf("Insercao retornou true (1)\n");
    else
        printf("Insercao retornou false (1)\n");
    exibirLog(f);
    res = inserirNovoProduto(f, 4, 4, 4, 4);
    if (res)
        printf("Insercao retornou true (2)\n");
    else
        printf("Insercao retornou false (2)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 6, 1, 8, 9);
    if (res)
        printf("Insercao retornou true (3)\n");
    else
        printf("Insercao retornou false (3)\n");
    exibirLog(f);
    res = inserirNovoProduto(f, 3, 1, 22, 23);
    if (res)
        printf("Insercao retornou true (4)\n");
    else
        printf("Insercao retornou false (4)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, -5, 6, 7, 8);
    if (res)
        printf("Insercao retornou true (5)\n");
    else
        printf("Insercao retornou false (5)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 5, -6, 7, 8);
    if (res)
        printf("Insercao retornou true (6)\n");
    else
        printf("Insercao retornou false (6)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 5, 6, -7, 8);
    if (res)
        printf("Insercao retornou true (7)\n");
    else
        printf("Insercao retornou false (7)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 5, 6, 7, -8);
    if (res)
        printf("Insercao retornou true (8)\n");
    else
        printf("Insercao retornou false (8)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 3, 1, 9, 9);
    if (res)
        printf("Insercao retornou true (9)\n");
    else
        printf("Insercao retornou false (9)\n");
    exibirLog(f);

    printf("################# REMOVENDO #######################\n");
    res = removerItensDeUmProduto(f, 4, 1);
    if (res)
        printf("Remocao retornou true (1)\n");
    else
        printf("Remocao retornou false (1)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 2, 1);
    if (res)
        printf("Remocao retornou true (2)\n");
    else
        printf("Remocao retornou false (2)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 3, 22);
    if (res)
        printf("Remocao retornou true (3)\n");
    else
        printf("Remocao retornou false (3)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 20, 1);
    if (res)
        printf("Remocao retornou true (4)\n");
    else
        printf("Remocao retornou false (4)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 5, 10);
    if (res)
        printf("Remocao retornou true (5)\n");
    else
        printf("Remocao retornou false (5)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 4, 0);
    if (res)
        printf("Remocao retornou true (6)\n");
    else
        printf("Remocao retornou false (6)\n");
    exibirLog(f);

    printf("################# ATUALIZANDO VALOR #######\n");

    res = atualizarValorDoProduto(f, 6, 1);
    if (res)
        printf("Atualizacao retornou true (1)\n");
    else
        printf("Atualizacao retornou false (1)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, 600);
    if (res)
        printf("Atualizacao retornou true (2)\n");
    else
        printf("Atualizacao retornou false (2)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, 20);
    if (res)
        printf("Atualizacao retornou true (3)\n");
    else
        printf("Atualizacao retornou false (3)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, 0);
    if (res)
        printf("Atualizacao retornou true (4)\n");
    else
        printf("Atualizacao retornou false (4)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, -100);
    if (res)
        printf("Atualizacao retornou true (5)\n");
    else
        printf("Atualizacao retornou false (5)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 61, 600);
    if (res)
        printf("Atualizacao retornou true (6)\n");
    else
        printf("Atualizacao retornou false (6)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, 3);
    if (res)
        printf("Atualizacao retornou true (7)\n");
    else
        printf("Atualizacao retornou false (7)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 4, 200);
    if (res)
        printf("Atualizacao retornou true (8)\n");
    else
        printf("Atualizacao retornou false (8)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 2, 20);
    if (res)
        printf("Atualizacao retornou true (9)\n");
    else
        printf("Atualizacao retornou false (9)\n");
    exibirLog(f);

    return 0;
}