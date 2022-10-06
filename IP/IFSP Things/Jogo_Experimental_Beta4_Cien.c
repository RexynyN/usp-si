#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

void respostas()
{
	if (respostacien == "A" || "a")
	{
		++pontuacao;
		printf("\nVoc� acertou! \nSua pontua��o: %i \nTentativas Restantes: %i \nPressione ENTER para continuar...", pontuacao, tentativas);
		getch();
	}
	else
	{
		--tentativas;
		printf("\nVoc� errou... \nSua Pontua��o: %i \nTentativas Restantes: %i \nAperte ENTER para continuar...", pontuacao, tentativas);
		getch();
	}
}

void gameover()
{
	if (tentativas == 0)
	{
		printf("GAME OVER! \nSua pontua��o: %i \nAperte ENTER para voltar para o menu principal...", pontuacao);
		getch();
		control = 42;
	}
}

void facil()
{
	system("cls");
	num1 = (rand() % 101);
	num2 = (rand() % 101);
	printf("Quanto �: %i + %i?", num1, num2);
	printf("\nSua Resposta: ");
	scanf("%i", &resultadosoma);
}

void medio()
{
	system("cls");
	num1 = (rand() % 101);
	num2 = (rand() % 101);
	num3 = (rand() % 11);
	printf("Quanto �: (%i - %i) * %i?", num1, num2, num3);
	printf("\nSua Resposta: ");
	scanf("%i", &resultadoexp);
}

void dificil()
{
	system("cls");
	num1 = (rand() % 11);
	num2 = (rand() % 11);
	num3 = (rand() % 11);
	printf("Quanto �: (%i x %i) x %i?", num1, num2, num3);
	printf("\nSua Resposta: ");
	scanf("%i", &resultadoexp);
}

int mdjmat = 0;
tentativas = 0, pontuacao = 0, operacao = 0, control = 0;
int num1 = 0, num2 = 0, num3 = 0, resultadosoma = 0, resultadosub = 0, resultadomult = 0, resultadoexp = 0;
srand(time(NULL));
setlocale(LC_ALL, "Portuguese");

while (control = 42)
{
	tentativas = 5;
	pontuacao = 0;
	system("cls");

	printf("Escolha uma dificuldade:");
	printf("\n(1) para F�cil");
	printf("\n(2) para M�dio");
	printf("\n(3) para D�ficil");
	printf("\n(4) para Modo Pesadelo");
	printf("\nSua escolha: ");
	scanf("%i", &mdjmat);
	switch (mdjmat)
	{
	case 1:
		void facil();

		break;

	case 2:
		void medio();
		break case 3 : void dificil();
	}
}
