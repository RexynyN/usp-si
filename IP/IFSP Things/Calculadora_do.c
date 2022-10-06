#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>


int num1, num2, resul;
int opc, menu; 

main ()
{
setlocale (LC_ALL, "Portuguese");
do
{
system ("cls");	
printf ("Calculadora");
printf ("\n(1) para Adição");
printf ("\n(2) para Subtração");
printf ("\n(3) para Multiplicação");
printf ("\n(4) para Divisão");
printf ("\n(5) para Sair");
printf ("\nEscoha uma das opções: ");
   scanf ("%i", &opc);
   
switch (opc)
{
case 1:
{	
system ("cls");	
printf ("Digite o primeiro número da operação: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo número da operação: ");
  scanf ("%d", &num2);
resul = (num1 + num2);
printf ("O resultado é: %d", resul);
break;
}

case 2:
{	
system ("cls");	
printf ("Digite o primeiro número da operação: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo número da operação: ");
  scanf ("%d", &num2);
resul = (num1 - num2);
printf ("O resultado é: %d", resul);
break;
}

case 3:
{	
system ("cls");	
printf ("Digite o primeiro número da operação: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo número da operação: ");
  scanf ("%d", &num2);
resul = (num1 * num2);
printf ("O resultado é: %d", resul);
break;
}

case 4:
{	
system ("cls");	
printf ("Digite o primeiro número da operação: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo número da operação: ");
  scanf ("%d", &num2);
resul = (num1 / num2);
printf ("O resultado é: %d", resul);
break;
}
}
printf ("\nSe você deseja fazer outra operação digite 1 se deseja sair, digite 5: ");
  scanf ("%i", &menu);
}
while(menu != 5);
}

