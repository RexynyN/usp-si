#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

unsigned long long int total = 1; 
int equ = 1;
unsigned long long int grao = 1;  

main()
{
/*Programador: Breno Nogueira*/	
/*Nome do Programa: Extrapoint*/
/*N�mero do Aluno: 21*/	
setlocale(LC_ALL, "Portuguese");
printf("Aprenda a verdade, meu pequeno padawan...");
  getch(); 
system("cls");
for (grao = 1, equ = 1, total = 1; equ != 65; equ++, grao = grao*2, total = total + grao)
{
   printf("\nCasa: %i , N�mero de Gr�os: %llu, Total: %llu", equ, grao, total);  
}
   printf("\nO total totalit�rio �: %llu", total); 
   getch();
}
