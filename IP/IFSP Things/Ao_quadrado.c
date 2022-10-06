#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int number, number2, number3, number4, number5; 
int result, result2, result3, result4, result5;
int menu ;

main ()
{
setlocale (LC_ALL, "Portuguese");
while (menu !=  2)
{
system ("cls");	
printf ("Digite um número para ser elevado ao quadrado: ");
  scanf ("%i", &number);

system ("cls"); 
printf ("Digite outro número para ser elevado ao quadrado: ");
  scanf ("%i", &number2);

system ("cls");
printf ("Digite outro número para ser elevado ao quadrado: ");
  scanf ("%i", &number3);

system ("cls");  
printf ("Digite outro número para ser elevado ao quadrado: ");
  scanf ("%i", &number4);

system ("cls");  
printf ("Digite outro número para ser elevado ao quadrado: ");
  scanf ("%i", &number5);      	  

result= number * number; 

result2= number2 * number2; 

result3= number3 * number3; 

result4= number4 * number4; 

result5= number5 * number5;
 
system ("cls");
printf ("\nO quadrado de %i é %i", number, result);
printf ("\nO quadrado de %i é %i", number2, result2);
printf ("\nO quadrado de %i é %i", number3, result3);
printf ("\nO quadrado de %i é %i", number4, result4);
printf ("\nO quadrado de %i é %i", number5, result5);
printf ("\nSe quiser fazer outra operação digite 1, mas se quiser sair, digite 2: ");
 scanf ("%i", &menu);
}
	
}
