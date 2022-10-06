#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

main()
{
int num;
int num2;
int resp;
int batata = 0;
int mdj;
int point = 0;

while(batata != 1)
system("cls");
setlocale(LC_ALL, "Portuguese");
printf("Joguinho bem legal");
printf("\n(1) para Adição");
printf("\n(2) para Subtração");
printf("\n(3) para Multiplicação");
printf("\nSua escolha: ");
   scanf("%i", &mdj);
switch(mdj)
{
    case 1:
{do{
system("cls");
srand(time(NULL));
num = (rand() % 11);
num2 = (rand() % 11);
while(num == 0)
num = (rand() % 11);
while(num2 == 0)
num2 = (rand() % 11);
    printf("Sua pontuação: %i", point);
	printf("\t\nQuanto é %i mais %i? ", num, num2);
	 scanf("%i", &resp);
	 system("cls");
if(resp == num + num2){
++point;
printf("\t\nParabéns, você acertou!");
printf("\n\nSua pontuação: %i", point);}
else{
printf("\t\nQue pena! Você errou...");
printf("\n\nSua pontuação: %i", point);
point = point;}
printf("\t\n\nSe você quiser continuar, pressione 1, para sair, pressione qualquer outro botão");
  scanf("%i", &batata);
}while(batata == 1);
break;
}
    case 2:
{do{
system("cls");
srand(time(NULL));
num = (rand() % 11);
num2 = (rand() % 11);
while(num == 0)
num = (rand() % 11);
while(num2 == 0)
num2 = (rand() % 11);
	printf("Sua pontuação: %i", point);
	printf("\t\nQuanto é %i menos %i? ", num, num2);
	 scanf("%i", &resp);
	 system("cls");
if(resp == num - num2){
++point;
printf("\t\nParabéns, você acertou!");
printf("\n\nSua pontuação: %i", point);
}
else{
printf("\t\nQue pena! Você errou...");
printf("\n\nSua pontuação: %i", point);
point = point;}
printf("\t\n\nSe você quiser continuar, pressione 1, para sair, pressione qualquer outro botão");
  scanf("%i", &batata);
}while(batata == 1);
break;
}

    case 3:
{do{
system("cls");
srand(time(NULL));
num = (rand() % 11);
num2 = (rand() % 11);
while(num == 0)
num = (rand() % 11);
while(num2 == 0)
num2 = (rand() % 11);
    printf("Sua pontuação: %i", point);
	printf("\t\nQuanto é %i vezes %i? ", num, num2);
	 scanf("%i", &resp);
	 system("cls");
if(resp == num * num2){
++point;
printf("\t\nParabéns, você acertou!");
printf("\n\nSua pontuação: %i", point);}
else{
printf("\t\nQue pena! Você errou...");
printf("\n\nSua pontuação: %i", point);
point = point;}
printf("\t\n\nSe você quiser continuar, pressione 1, para sair, pressione qualquer outro botão");
  scanf("%i", &batata);
}while(batata == 1);
break;
}
}
}

