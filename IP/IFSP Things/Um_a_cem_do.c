#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int valor = 100;

main ()
{
do 
{
	printf("\n %d", valor);    
	valor = (valor - 1);
	}
while (valor != 0);	
getche ();
			
}
