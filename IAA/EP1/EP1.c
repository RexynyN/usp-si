#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int * arrayTeste(size)
{
  //int size = atoi(size * 10000);
  int *array = (int *)malloc(sizeof(int) * size);

  srand(time(NULL));

  for (int i = 0; i < size; i++)
  {
    array[i] = rand();
    printf("%i ", array[i]);
  }

  return array;
}

int *subArray(int *array, int com, int fim)
{
  int size = (fim - com) + 1;
  int *sub = (int *)malloc(sizeof(int) * size);

  for (int i = 0; i < size; i++)
  {
    sub[i] = array[i];
  }

  return sub;
}

void troca(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int particao(int *array, int i)
{
  int size = (int)sizeof(array) / sizeof(int);
  int pivot = array[size - 1];
  i = -1;
  int j;

  for (j = 0; j < size - 1; j++)
    if (array[j] <= pivot)
      troca(&array[++i], &array[j]);

  troca(&array[i + 1], &array[j]);

  return i + 1;
}

int selecao1(int *array, int i)
{

  int size = (int)sizeof(array) / sizeof(int);

  int q;
  if (size > 0)
  {
    q = particao(array, size);

    selecao1(array, q);
    selecao1(&array[q + 1], size - (q + 1));
  }

  return array[i - 1];
}

int selecao2(int *array, int i)
{
  int size = (int)sizeof(array) / sizeof(array[0]);
  int q = particao(array, size);

  if (size == 1)
    return array[0];

  if (i < q)
  {
    array = subArray(&array, 0, q - 1);
    return selecao2(array, i);
  }
  else if (i > q)
  {
    array = subArray(&array, q, size);
    return selecao2(array, i - (q));
  }
  else
    return array[q - 1];
}

int main()
{
  int *array = arrayTeste(10);
  // Isso é pra medir o tempo
  clock_t start, end;
  double tempo;

  start = clock();
  /* Coloca a função aqui no meio */
  end = clock();
  tempo = ((double)(end - start)) / CLOCKS_PER_SEC;

  int * a = subArray(array,0,4);
    printf("\n\n%i \n\n", sizeof(array) / sizeof(array[0]));

  for (int i = 0; i < 10; i++)
  {
    printf("%i ", a[i]);
  }

  // Implementa essas funções
  // printf("\n\n\n%i", selecao1(array, 1));

  printf("\n\n\n%i", selecao2(array, 1));

  return 0;
}