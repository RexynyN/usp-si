#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int idade1, idade2, idade3, idade4, idade5; 
int idade6, idade7, idade8, idade9, idade10;
int menu;

main()
{
setlocale (LC_ALL,"Portuguese");
while (menu != 2)	
{
system ("cls");	
printf ("Digite a idade da primeira pessoa:");
 scanf ("%i", &idade1);


system ("cls");	
printf ("Digite a idade da segunda pessoa:");
 scanf ("%i", &idade2);


system ("cls");	
printf ("Digite a idade da terceira pessoa:");
 scanf ("%i", &idade3);


system ("cls");	
printf ("Digite a idade da quarta pessoa:");
 scanf ("%i", &idade4);


system ("cls");
printf ("Digite a idade da quinta pessoa:");
 scanf ("%i", &idade5);


system ("cls");	
printf ("Digite a idade da sexta pessoa:");
 scanf ("%i", &idade6);


system ("cls");	
printf ("Digite a idade da s�tima pessoa:");
 scanf ("%i", &idade7);


system ("cls");	
printf ("Digite a idade da oitava pessoa:");
 scanf ("%i", &idade8);


system ("cls");	
printf ("Digite a idade da nona pessoa:");
 scanf ("%i", &idade9);


system ("cls");
printf ("Digite a idade da d�cima pessoa:");
 scanf ("%i", &idade10);
system ("cls"); 

if (idade1 >= 18)
  printf ("\nA primeira pessoa � maior de idade");
else;
printf ("\nA primeira pessoa n�o � maior de idade"); 

if (idade2 >= 18)
 printf ("\nA segunda pessoa � maior de idade");
else;
printf ("\nA segunda pessoa n�o � maior de idade"); 

if (idade3 >= 18)
 printf ("\nA terceira pessoa � maior de idade");
else;
printf ("\nA terceira pessoa n�o � maior de idade"); 

if (idade4 >= 18)
 printf ("\nA quarta pessoa � maior de idade");
else;
printf ("\nA quarta pessoa n�o � maior de idade"); 

if (idade5 >= 18)
 printf ("\nA quinta pessoa � maior de idade");
else;
printf ("\nA quinta pessoa n�o � maior de idade"); 

if (idade6 >= 18)
 printf ("\nA sexta pessoa � maior de idade");
else;
printf ("\nA sexta pessoa n�o � maior de idade"); 
 
if (idade7 >= 18)
 printf ("\nA s�tima pessoa � maior de idade");
else;
printf ("\nA s�tima pessoa n�o � maior de idade"); 
 
if (idade8 >= 18)
 printf ("\nA oitava pessoa � maior de idade");
else;
printf ("\nA oitava pessoa n�o � maior de idade"); 
 
if (idade9 >= 18)
 printf ("\nA nona pessoa � maior de idade");
else;;
printf ("\nA nona pessoa n�o � maior de idade"); 
 
if (idade10 >= 18)
 printf ("\nA d�cima pessoa � maior de idade");
else;
printf ("\nA d�cima pessoa n�o � maior de idade"); 

printf ("\nSe quiser continuar, digite 1 mas se quiser sair, digite 2: "); 
	scanf("%i", &menu);    	
}
}
