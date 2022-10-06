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
printf ("Digite a idade da sétima pessoa:");
 scanf ("%i", &idade7);


system ("cls");	
printf ("Digite a idade da oitava pessoa:");
 scanf ("%i", &idade8);


system ("cls");	
printf ("Digite a idade da nona pessoa:");
 scanf ("%i", &idade9);


system ("cls");
printf ("Digite a idade da décima pessoa:");
 scanf ("%i", &idade10);
system ("cls"); 

if (idade1 >= 18)
  printf ("\nA primeira pessoa é maior de idade");
else;
printf ("\nA primeira pessoa não é maior de idade"); 

if (idade2 >= 18)
 printf ("\nA segunda pessoa é maior de idade");
else;
printf ("\nA segunda pessoa não é maior de idade"); 

if (idade3 >= 18)
 printf ("\nA terceira pessoa é maior de idade");
else;
printf ("\nA terceira pessoa não é maior de idade"); 

if (idade4 >= 18)
 printf ("\nA quarta pessoa é maior de idade");
else;
printf ("\nA quarta pessoa não é maior de idade"); 

if (idade5 >= 18)
 printf ("\nA quinta pessoa é maior de idade");
else;
printf ("\nA quinta pessoa não é maior de idade"); 

if (idade6 >= 18)
 printf ("\nA sexta pessoa é maior de idade");
else;
printf ("\nA sexta pessoa não é maior de idade"); 
 
if (idade7 >= 18)
 printf ("\nA sétima pessoa é maior de idade");
else;
printf ("\nA sétima pessoa não é maior de idade"); 
 
if (idade8 >= 18)
 printf ("\nA oitava pessoa é maior de idade");
else;
printf ("\nA oitava pessoa não é maior de idade"); 
 
if (idade9 >= 18)
 printf ("\nA nona pessoa é maior de idade");
else;;
printf ("\nA nona pessoa não é maior de idade"); 
 
if (idade10 >= 18)
 printf ("\nA décima pessoa é maior de idade");
else;
printf ("\nA décima pessoa não é maior de idade"); 

printf ("\nSe quiser continuar, digite 1 mas se quiser sair, digite 2: "); 
	scanf("%i", &menu);    	
}
}
