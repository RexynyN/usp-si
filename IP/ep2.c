// Aluno: Breno da Silva Nogueira
// Numero USP: 12400392
// Matéria: Introdução a Programação
// Atividade: EP2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double e, n;

    printf("Insira o numero para fazer a raiz (maior que 1): ");
    scanf("%lf", &n);
    printf("Insira a precisao do calculo: ");
    scanf("%lf", &e);

    if (n < 1)
    {
        printf("Entrada Invalida, digite um numero maior que 1");
    }
    else
    {

        double diff, dupe, x;
        int cont = 0;
        double range[2] = {0, n};

        while ((n = n))
        {
            x = ((range[0] + range[1]) / 2);
            dupe = x * x;
            diff = fabs((dupe - n));

            if (diff <= e)
            {
                printf("%d: intervalo = [ %lf, %lf ]  x = %lf\n", cont, range[0], range[1], x);
                printf("Numero de iteracoes: %d\n", (cont + 1));
                printf("Diferenca absoluta: %lf\n", diff);
                printf("Raiz quadrada: %lf\n", x);
                break;
            }
            else if (dupe > n)
            {
                printf("%d: intervalo = [ %lf, %lf ]  x = %lf\n", cont, range[0], range[1], x);
                range[1] = x;
                cont++;
            }
            else if (dupe < n)
            {
                printf("%d: intervalo = [ %lf, %lf ]  x = %lf\n", cont, range[0], range[1], x);
                range[0] = x;
                cont++;
            }
        }
    }
    return 0;
}

// Bom dia / Boa tarde / Boa Noite Professor :D