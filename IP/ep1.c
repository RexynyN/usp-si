// Aluno: Breno da Silva Nogueira
// Numero USP: 12400392
// Matéria: Introdução a Programação
// Atividade: EP1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Decide qual o tipo de triângulo quanto ao ângulo
void quantoAngulo(float l1, float l2, float l3, float maior)
{
    // Variavel de pitagoras
    float pit;

    if (l1 == maior)
        pit = pow(l2, 2) + pow(l3, 2);
    else if (l2 == maior)
        pit = pow(l1, 2) + pow(l3, 2);
    else
        pit = pow(l1, 2) + pow(l2, 2);

    maior = pow(maior, 2);

    if (pit == maior)
        printf("Classificacao em funcao dos angulos: RETO\n");
    else if (pit < maior)
        printf("Classificacao em funcao dos angulos: OBTUSO\n");
    else
        printf("Classificacao em funcao dos angulos: AGUDO\n");
}



// Programa principal
int main()
{
    // Declaração de váriaveis
    float l1, l2, l3, maior;

    // Inputs do usuário
    printf("Insira o lado 1: ");
    scanf("%f", &l1);

    printf("Insira o lado 2: ");
    scanf("%f", &l2);

    printf("Insira o lado 3: ");
    scanf("%f", &l3);

    // Limpa tela
    system("cls");

    // Verificação do conteudo dos Inputs
    if (l1 <= 0 || l2 <= 0 || l3 <= 0)
        printf("Entrada invalida, rode novamente e coloque valores maiores que 0");
    else
    {
        // Verifica qual o maior lado
        if (l1 > l2)
            maior = l1;
        else
            maior = l2;

        if (l3 > maior)
            maior = l3;

        float soma = (l1 + l2 + l3) - maior;

        // Se o maior lado for maior que a soma dos dois outros, não é um triângulo.
        if (maior > soma)
            printf("Medidas dos lados formam um triangulo: INVALIDO\n");
        else
        {
            printf("Medidas dos lados formam um triangulo: VALIDO\n");

            float area;

            // Verifica a classificação do triangulo e o trata
            if (l1 == l2 && l2 == l3)
            {
                printf("Classificacao em funcao dos lados: EQUILATERO\n");
                // Todo equilatero é agudo
                printf("Classificacao em funcao dos angulos: AGUDO\n");
                // Formula do equilateros para a area
                area = pow(l1, 2) * (sqrt(3) / 4);

                printf("Area do Triangulo: %f", area);
            }
            else if (l1 == l2 || l2 == l3 || l3 == l1)
            {
                printf("Classificacao em funcao dos lados: ISOSCELES\n");

                quantoAngulo(l1, l2, l3, maior);

                float base, altura, cateto;

                if (l1 == l2)
                {
                    base = l3;
                    cateto = l1;
                }
                else if (l2 == l3)
                {
                    base = l1;
                    cateto = l2;
                }
                else
                {
                    base = l2;
                    cateto = l1;
                }

                // Descobrir a altura do triângulo com base em pitágoras
                base = base / 2;
                altura = sqrt(pow(cateto, 2) - pow(base, 2));

                // Cálculo da área
                area = (base * altura);

                printf("Area do Triangulo: %f", area);
            }
            else
            {
                printf("Classificacao em funcao dos lados: ESCALENO\n");

                quantoAngulo(l1, l2, l3, maior);

                // Cálculo da área pela fórmula de Heron
                float semi = (l1 + l2 + l3) / 2;

                area = sqrt(semi * (semi - l1) * (semi - l2) * (semi - l3));

                printf("Area do Triangulo: %f", area);
            }
        }
    }
    system("pause");
    return 0;
}

// Final do programa
// Bom dia/tarde/noite professor :D