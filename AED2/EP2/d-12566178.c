#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#define t 2
struct no
{
  int n;
  int chaves[2 * t - 1];
  struct no *filhos[2 * t];
  bool folha;
} typedef no;
no *raiz;
void splitchild(no *x, int i, no *y)
{
  no *z = (no *)malloc(sizeof(struct no));
  z->folha = y->folha;
  z->n = t - 1;
  for (int j = 0; j < t - 1; j++)
    z->chaves[j] = y->chaves[j + t];
  if (!y->folha)
    for (int j = 0; j < t; j++)
      z->filhos[j] = y->filhos[j + t];
  y->n = t - 1;
  for (int j = x->n; j >= i + 1; j--)
    x->filhos[j + 1] = x->filhos[j];
  x->filhos[i + 1] = z;
  for (int j = x->n - 1; j >= i; j--)
    x->chaves[j + 1] = x->chaves[j];
  x->chaves[i] = y->chaves[t - 1];
  x->n = x->n + 1;
}
no *find(no *x, int chave)
{
  if (x == NULL)
    return x;
  int i = 0;
  for (; i < x->n; i++)
  {
    if (chave < x->chaves[i])
      break;
    if (chave == x->chaves[i])
      return x;
  }
  return find(x->filhos[i], chave);
}
void insert_nonfull(no *x, int chave)
{
  int i = x->n - 1;
  if (x->folha)
  {
    while (i >= 0 && chave < x->chaves[i])
    {
      x->chaves[i + 1] = x->chaves[i];
      i--;
    }
    x->chaves[i + 1] = chave;
    x->n = x->n + 1;
  }
  else
  {
    while (i >= 0 && chave < x->chaves[i])
      i--;
    if (x->filhos[i + 1]->n == 2 * t - 1)
    {
      splitchild(x, i + 1, x->filhos[i + 1]);
      if (chave > x->chaves[i + 1])
        i++;
    }
    insert_nonfull(x->filhos[i + 1], chave);
  }
}
void insert(int chave)
{
  if (raiz == NULL)
  {
    raiz = (no *)malloc(sizeof(struct no));
    raiz->folha = true;
    raiz->n = 1;
    raiz->chaves[0] = chave;
  }
  else
  {
    if (raiz->n == 2 * t - 1)
    {
      no *s = (no *)malloc(sizeof(struct no));
      s->folha = false;
      s->n = 0;
      s->filhos[0] = raiz;
      splitchild(s, 0, raiz);
      int i = 0;
      if (chave > s->chaves[0])
        i++;
      insert_nonfull(s->filhos[i], chave);
      raiz = s;
    }
    else
      insert_nonfull(raiz, chave);
  }
}


void delete (no *x, int chave)
{
  if (x == NULL)
    return;
  int i = x->n - 1, j;
  while (i >= 0 && chave < x->chaves[i])
    i--;
  if (x->folha && i >= 0 && x->chaves[i] == chave)
  { // 1:k⊂x->chaves&x->folha
    while (i < x->n - 1)
    {
      x->chaves[i] = x->chaves[i + 1];
      i++;
    }
    x->n--;
    return;
  }
  else if (!(x->folha) && i >= 0 && x->chaves[i] == chave)
  { // 2:k⊂x->chaves&!x->folha
    no *y = x->filhos[i];
    no *z = x->filhos[i + 1];
    if (y->n >= t)
    { // 2a:y->n>=t
      x->chaves[i] = y->chaves[y->n - 1];
      y->n--;
    }
    else if (z->n >= t)
    { // 2b:y->n<t<=z->n
      x->chaves[i] = z->chaves[0];
      for (j = 0; j < z->n - 1; j++)
        z->chaves[j] = z->chaves[j + 1];
      z->n--;
    }
    else
    { // 2c:[y,z]->n<t
      y->chaves[y->n] = x->chaves[i];
      y->n++;
      for (j = i; j < x->n - 1; j++)
      {
        x->chaves[j] = x->chaves[j + 1];
        if (j > i)
          x->filhos[j] = x->filhos[j + 1];
      }
      x->filhos[j] = x->filhos[j + 1];
      x->n--;
      for (j = 0; j < z->n; j++)
      {
        y->chaves[y->n] = z->chaves[j];
        y->filhos[y->n] = z->filhos[j];
        y->n++;
      }
      y->filhos[y->n] = z->filhos[j];
      free(z);
      delete (y, chave);
    }
    return;
  }
  if (x->folha)
    return;
  i++;
  no *filho = x->filhos[i];
  if (filho->n == t - 1)
  { // 3:k⊄x->chaves
    if (i <= x->n && x->filhos[i + 1]->n >= t)
    { // 3a:irmao_dir->n>=t
      no *irmao_dir = x->filhos[i + 1];
      filho->chaves[filho->n] = x->chaves[i];
      filho->n++;
      x->chaves[i] = irmao_dir->chaves[0];
      filho->filhos[filho->n] = irmao_dir->filhos[0];
      irmao_dir->n--;
      for (j = 0; j < irmao_dir->n; j++)
      {
        irmao_dir->chaves[j] = irmao_dir->chaves[j + 1];
        irmao_dir->filhos[j] = irmao_dir->filhos[j + 1];
      }
      irmao_dir->filhos[irmao_dir->n] = irmao_dir->filhos[irmao_dir->n + 1];
    }
    else if (i > 0 && x->filhos[i - 1]->n >= t)
    { // 3a:irmao_dir->n<t&irmao_esq->n>=t
      no *irmao_esq = x->filhos[i - 1];
      filho->chaves[filho->n] = x->chaves[i];
      filho->n++;
      x->chaves[i] = x->chaves[i - 1];
      x->chaves[i - 1] = irmao_esq->chaves[irmao_esq->n - 1];
      filho->filhos[0] = irmao_esq->filhos[irmao_esq->n];
      irmao_esq->n--;
    }
    else if (i <= x->n)
    { // 3b:[irmao_esq,irmao_dir]->n<t&i<=x->n
      no *irmao_dir = x->filhos[i + 1];
      filho->chaves[filho->n] = x->chaves[i];
      filho->n++;
      for (j = 0; j < irmao_dir->n; j++, filho->n++)
      {
        filho->chaves[filho->n] = irmao_dir->chaves[j];
        filho->filhos[filho->n] = irmao_dir->filhos[j];
      }
      filho->filhos[filho->n] = irmao_dir->filhos[j];
      for (j = x->n - 1; j > i; j--)
      {
        x->chaves[j - 1] = x->chaves[j];
        x->filhos[j] = x->filhos[j + 1];
      }
      x->n--;
      free(irmao_dir);
    }
    else
    { // 3b:[irmao_esq,irmao_dir]->n<t&i>x->n
      no *irmao_esq = x->filhos[i - 1];
      filho->chaves[filho->n] = x->chaves[i];
      filho->n++;
      for (j = 0; j < filho->n; j++, irmao_esq->n++)
      {
        irmao_esq->chaves[irmao_esq->n] = filho->chaves[j];
        irmao_esq->filhos[irmao_esq->n] = filho->filhos[j];
      }
      irmao_esq->filhos[irmao_esq->n] = filho->filhos[j];
      for (j = x->n - 1; j > i; j--)
      {
        x->chaves[j - 1] = x->chaves[j];
        x->filhos[j] = x->filhos[j + 1];
      }
      x->n--;
      free(irmao_esq);
    }
  }
  delete (x->filhos[i], chave);
}


void traverse(no *base, bool fileout, FILE *fp)
{
  int i = 0;
  for (; i < base->n; i++)
  {
    if (!base->folha)
      traverse(base->filhos[i], fileout, fp);
    if (!fileout)
      printf("%d ", base->chaves[i]);
    else
      fprintf(fp, "%d ", base->chaves[i]);
  }
  if (!base->folha)
    traverse(base->filhos[i], fileout, fp);
}

int main(int argc, char **argv)
{
  char cmd[8] = "";
  int chave;
  FILE *fp;
  raiz = NULL;
  fp = fopen(argv[1], "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);
  while (strcmp(cmd, "fim") != 0)
  {
    fscanf(fp, "%s", cmd);
    if (strcmp(cmd, "insere") == 0)
    {
      fscanf(fp, "%d", &chave);
      insert(chave);
    }
    else if (strcmp(cmd, "remove") == 0)
    {
      fscanf(fp, "%d", &chave);
      delete (find(raiz, chave), chave);
    }
    else if (strcmp(cmd, "imprime") == 0)
    {
      traverse(raiz, false, fp);
      printf("\n");
    }
  }
  fclose(fp);
  fp = fopen("saida.txt", "w");
  if (fp == NULL)
    exit(EXIT_FAILURE);
  traverse(raiz, true, fp);
  fclose(fp);
  return 0;
}
