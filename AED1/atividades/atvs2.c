#include <stdio.h>
#include <stdlib.h>

// Exercício 1:
typedef struct aux
{
    int id;
    struct aux *mae;
    struct aux *pai;
} PESSOA;

// Exercício 2:
PESSOA *inicializar(int id)
{
    PESSOA *pessoa = (PESSOA *)malloc(sizeof(PESSOA));
    pessoa->id = id;
    pessoa->pai = NULL;
    pessoa->mae = NULL;

    return pessoa;
}

// Exercício 3
void registrar(PESSOA *filho, PESSOA *mae, PESSOA *pai)
{
    filho->pai = pai;
    filho->mae = mae;
}

int main()
{
    PESSOA p;
    PESSOA p2;
    PESSOA p3;

    p.id = 42;
    p2.id = 123;
    p3.id = 321;

    registrar(&p, &p2, &p3);
    printf("%i %i %i %i", p.mae->id, p2.id, p.pai->id, p3.id);
    return 0;
}