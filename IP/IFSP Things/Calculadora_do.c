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
printf ("\n(1) para Adi��o");
printf ("\n(2) para Subtra��o");
printf ("\n(3) para Multiplica��o");
printf ("\n(4) para Divis�o");
printf ("\n(5) para Sair");
printf ("\nEscoha uma das op��es: ");
   scanf ("%i", &opc);
   
switch (opc)
{
case 1:
{	
system ("cls");	
printf ("Digite o primeiro n�mero da opera��o: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo n�mero da opera��o: ");
  scanf ("%d", &num2);
resul = (num1 + num2);
printf ("O resultado �: %d", resul);
break;
}

case 2:
{	
system ("cls");	
printf ("Digite o primeiro n�mero da opera��o: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo n�mero da opera��o: ");
  scanf ("%d", &num2);
resul = (num1 - num2);
printf ("O resultado �: %d", resul);
break;
}

case 3:
{	
system ("cls");	
printf ("Digite o primeiro n�mero da opera��o: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo n�mero da opera��o: ");
  scanf ("%d", &num2);
resul = (num1 * num2);
printf ("O resultado �: %d", resul);
break;
}

case 4:
{	
system ("cls");	
printf ("Digite o primeiro n�mero da opera��o: ");	
  scanf ("%d", &num1);
system ("cls");	  
printf ("Digite o segundo n�mero da opera��o: ");
  scanf ("%d", &num2);
resul = (num1 / num2);
printf ("O resultado �: %d", resul);
break;
}
}
printf ("\nSe voc� deseja fazer outra opera��o digite 1 se deseja sair, digite 5: ");
  scanf ("%i", &menu);
}
while(menu != 5);
}

