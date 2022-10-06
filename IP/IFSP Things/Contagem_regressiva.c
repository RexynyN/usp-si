#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int liti, litf, menu;

main()
{
while (menu != 2)
{
system ("cls");	
printf ("Escreva o limite inicial:");
   scanf ("%i", &liti);
printf ("Escreva o limite final:");
   scanf ("%i", &litf);
while (liti >= litf) 
 {
    system ("cls");
    printf ("%i", liti);
    liti = liti - 1;
}
printf ("\nSe quiser fazer a operacao de novo, digite 1, se quiser sair, digite 2: ");
  scanf ("%i", &menu);
}
}

