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
printf("\n(1) para Adi��o");
printf("\n(2) para Subtra��o");
printf("\n(3) para Multiplica��o");
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
    printf("Sua pontua��o: %i", point);
	printf("\t\nQuanto � %i mais %i? ", num, num2);
	 scanf("%i", &resp);
	 system("cls");
if(resp == num + num2){
++point;
printf("\t\nParab�ns, voc� acertou!");
printf("\n\nSua pontua��o: %i", point);}
else{
printf("\t\nQue pena! Voc� errou...");
printf("\n\nSua pontua��o: %i", point);
point = point;}
printf("\t\n\nSe voc� quiser continuar, pressione 1, para sair, pressione qualquer outro bot�o");
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
	printf("Sua pontua��o: %i", point);
	printf("\t\nQuanto � %i menos %i? ", num, num2);
	 scanf("%i", &resp);
	 system("cls");
if(resp == num - num2){
++point;
printf("\t\nParab�ns, voc� acertou!");
printf("\n\nSua pontua��o: %i", point);
}
else{
printf("\t\nQue pena! Voc� errou...");
printf("\n\nSua pontua��o: %i", point);
point = point;}
printf("\t\n\nSe voc� quiser continuar, pressione 1, para sair, pressione qualquer outro bot�o");
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
    printf("Sua pontua��o: %i", point);
	printf("\t\nQuanto � %i vezes %i? ", num, num2);
	 scanf("%i", &resp);
	 system("cls");
if(resp == num * num2){
++point;
printf("\t\nParab�ns, voc� acertou!");
printf("\n\nSua pontua��o: %i", point);}
else{
printf("\t\nQue pena! Voc� errou...");
printf("\n\nSua pontua��o: %i", point);
point = point;}
printf("\t\n\nSe voc� quiser continuar, pressione 1, para sair, pressione qualquer outro bot�o");
  scanf("%i", &batata);
}while(batata == 1);
break;
}
}
}

