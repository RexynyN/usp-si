/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   Breno da Silva Nogueira                   12400392            **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"
#define MAX 5

PFILA criarFila()
{
  PFILA res = (PFILA)malloc(sizeof(FILADEPRIORIDADE));
  res->referencias = (PONT *)malloc(sizeof(PONT) * MAX);
  res->heap = (PONT *)malloc(sizeof(PONT) * MAX);
  int i;
  for (i = 0; i < MAX; i++)
  {
    res->referencias[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}

bool exibirLog(PFILA f)
{
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i = 0; i < f->elementosNoHeap; i++)
  {
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f)
{
  return f->elementosNoHeap;
}

void trocarHeap(PONT *a, PONT *b)
{
  int pos = (*a)->posicao;
  (*a)->posicao = (*b)->posicao;
  (*b)->posicao = pos;

  PONT aux = *a;
  *a = *b;
  *b = aux;
}

void heapUp(PFILA f, int i)
{
  int nodePai = (i - 1) / 2;

  while (i != 0 && f->heap[nodePai]->prioridade < f->heap[i]->prioridade)
  {
    trocarHeap(&f->heap[nodePai], &f->heap[i]);
    i = nodePai;
    nodePai = (i - 1) / 2;
  }
}

void maxHeapify(PFILA f, int n, int i)
{
  i += 1;
  int esq = 2 * i;
  int dir = (2 * i) + 1;
  int maior = -1;

  if (esq <= n && f->heap[esq - 1]->prioridade > f->heap[i - 1]->prioridade)
    maior = esq;
  else
    maior = i;

  if (dir <= n && f->heap[dir - 1]->prioridade > f->heap[maior - 1]->prioridade)
    maior = dir;

  if (maior != i)
  {
    trocarHeap(&f->heap[maior - 1], &f->heap[i - 1]);
    maxHeapify(f, n, maior - 1);
  }
}

bool inserirElemento(PFILA f, int id, float prioridade)
{
  if (id < 0 || id >= MAX || f->referencias[id] != NULL || f->elementosNoHeap >= MAX)
    return false;

  PONT newNode = (PONT)malloc(sizeof(ELEMENTO));
  newNode->id = id;
  newNode->prioridade = prioridade;
  newNode->posicao = f->elementosNoHeap;

  f->heap[f->elementosNoHeap] = newNode;
  f->referencias[id] = newNode;
  f->elementosNoHeap += 1;

  int i = f->elementosNoHeap - 1;

  heapUp(f, f->elementosNoHeap - 1);

  return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
  if (id < 0 || id >= MAX || f->referencias[id] == NULL || novaPrioridade <= f->referencias[id]->prioridade)
    return false;

  PONT node = f->referencias[id];
  node->prioridade = novaPrioridade;

  heapUp(f, node->posicao);

  return true;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
  if (id < 0 || id >= MAX || f->referencias[id] == NULL || novaPrioridade >= f->referencias[id]->prioridade)
    return false;

  PONT node = f->referencias[id];
  node->prioridade = novaPrioridade;

  maxHeapify(f, f->elementosNoHeap, node->posicao);

  return true;
}

PONT removerElemento(PFILA f)
{
  if (f->heap[0] == NULL)
    return NULL;

  PONT res = f->heap[0];
  if (tamanho(f) > 1)
  {
    f->heap[0] = f->heap[f->elementosNoHeap - 1];
    f->heap[f->elementosNoHeap - 1] = NULL;
    f->heap[0]->posicao = 0;

    f->elementosNoHeap -= 1;
    f->referencias[res->id] = NULL;

    maxHeapify(f, f->elementosNoHeap, 0);
  }
  else
  {
    f->heap[0] = NULL;
    f->elementosNoHeap -= 1;
    f->referencias[res->id] = NULL;
  }

  return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{
  if (id < 0 || id >= MAX || f->referencias[id] == NULL)
    return false;

  *resposta = f->referencias[id]->prioridade;

  return true;
}
