#include <stdio.h>
#include <stdlib.h>

typedef struct aux
{
    int cpf;
    int idade;
    struct aux *conjuge;
} PESSOA;

void imprimirCPF(PESSOA p)
{
    if (p.conjuge != NULL)
    {
        printf("CPFs: %i x %i\n", p.cpf, p.conjuge->cpf);
    }
    else
    {
        printf("HAHAHAHA Não tem ninguém HAHAHAHAHA");
    }
}

void envelhecer1(PESSOA p)
{
    p.idade++;
}

void envelhecer2(PESSOA *p)
{
    p->idade++;
}

void envelhecer3(PESSOA p)
{
    p.conjuge->idade++;
}

void envelhecer4(PESSOA *p)
{
    p->conjuge->idade++;
}

int main()
{
    PESSOA p1;
    PESSOA p2;
    PESSOA solteira;

    p1.cpf = 123456789;
    p1.idade = 19;

    p2.cpf = 987654321;
    p2.idade = 21;

    p1.conjuge = &p2;
    p2.conjuge = &p1;

    solteira.cpf = 192837465;
    solteira.idade = 30;
    solteira.conjuge = NULL;

    imprimirCPF(p1);
    envelhecer1(p1);
    envelhecer2(&p1);
    envelhecer3(p1);
    envelhecer4(&p1);

    return 0;
}
