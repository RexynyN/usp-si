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
setlocale (LC_ALL,"Portuguese");
do{
printf("Escolha um modo de jogo");
printf("\n(1) para adição");
printf("\n(2) para subtração");
printf("\n(3) para multiplicação");
printf("\n(4) para sair");
printf("\nSua escolha: ");
    scanf("%i", &mdj);
    switch(mdj){
    case 1:
do{
system("cls");	
srand(time(NULL));
num = (rand() % 11);
num2 = (rand() % 11);
while(num == 0)
num = (rand() % 11);
while(num2 == 0)
num2 = (rand() % 11);
	printf("\t\nQuanto é %i mais %i? ", num, num2);
	 scanf("%i", &resp);
if(resp == num + num2)
printf("\t\nParabéns, você acertou!");
else 
printf("\t\nQue pena! Você errou...");
printf("\t\nSe você quiser continuar, pressione 1, para sair, pressione qualquer outro botão");
  scanf("%i", &batata);
}while(batata == 1);
break;

case 2:
	do{
system("cls");	
srand(time(NULL));
num = (rand() % 11);
num2 = (rand() % 11);
while(num == 0)
num = (rand() % 11);
while(num2 == 0)
num2 = (rand() % 11);
	printf("\t\nQuanto é %i menos %i? ", num, num2);
	 scanf("%i", &resp);
if(resp == num - num2)
printf("\t\nParabéns, você acertou!");
else 
printf("\t\nQue pena! Você errou...");
printf("\t\nSe você quiser continuar, pressione 1, para sair, pressione qualquer outro botão");
  scanf("%i", &batata);
}while(batata == 1);
break;

case 3:
	do{
system("cls");	
srand(time(NULL));
num = (rand() % 11);
num2 = (rand() % 11);
while(num == 0)
num = (rand() % 11);
while(num2 == 0)
num2 = (rand() % 11);
	printf("\t\nQuanto é %i vezes %i? ", num, num2);
	 scanf("%i", &resp);
if(resp == num * num2)
printf("\t\nParabéns, você acertou!");
else 
printf("\t\nQue pena! Você errou...");
printf("\t\nSe você quiser continuar, pressione 1, para sair, pressione qualquer outro botão");
  scanf("%i", &batata);
}while(batata == 1);
break; 
}
}while(mdj != 4);
}
