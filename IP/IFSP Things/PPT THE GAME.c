#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int op1;
int op2;
int mdj;
int menu;
int menu2;
int idiom;

main()
{ 
printf ("Digite 1 para jogar em portugues");	
printf ("\nType 2 to play in english");
printf ("\nEscolha/Choice: ");
  scanf ("%d", &idiom);
  switch(idiom)	
  {
  case 1:
  {
system ("cls");
printf ("\n---------------------------------------------------------------------");
printf ("\n                  Jogo do Pedra, Papel, Tesoura                      ");
printf ("\n---------------------------------------------------------------------");
printf ("\n                    Bem-Vindo(s) Jogador(es)!                         ");
printf ("\n---------------------------------------------------------------------");
printf ("\nDigite \"1\" para jogar de um pessoa e \"2\" para jogar de duas pessoas: ");
  scanf("%d", &mdj);
  
switch (mdj) 
{
 case 1:
 {
 	while (menu != 2)
{
srand (time(NULL));
system ("cls"); 	
printf ("Jogador, escolha entre");
printf ("\n(1) para Pedra");  
printf ("\n(2) para Papel");  
printf ("\n(3) para Tesoura");  
printf ("\nDigite sua escolha: ");    
  scanf ("%d", &op1); 
   system ("cls");
while(op2 = 0)
op2 = (rand () % 3); 

        if ((op1 == 2) && (op2 == 3))
        {
		
		    printf ("\nO computador escolheu: 3 (Tesoura)");
            printf ("\nO computador ganhou!");
        }
        else
         if ((op1 == 1) && (op2 == 1)) 
         {
            printf ("\nO computador escolheu: 1 (Pedra)");
            printf ("\nEmpate!");
         }
         else
         if ((op1 == 2) && (op2 == 2))
         {
            printf ("\nO computador escolheu: 2 (Papel)");
            printf ("\nEmpate!");
         }
         else
         if ((op1 == 3) && (op2 == 3))
         {
            printf ("\nO computador escolheu: 3 (Tesoura)");
            printf ("\nEmpate!");
         }
        else
         if ((op1 == 1) && (op2 == 2))
         {
            printf ("\nO computador escolheu: 2 (Papel)");
            printf ("\nO computador ganhou!");
         }
         else
         if ((op1 == 3) && (op2 == 1))
          {
		    printf ("\nO computador escolheu: 1 (Pedra)");
            printf ("\nO computador ganhou!");
          }
         else
         if ((op1 == 1) && (op2 == 3))
         {
            printf ("\nO computador escolheu: 3 (Tesoura)");
            printf ("\nO jogador ganhou!");
         }
         else
         if ((op1 == 2) && (op2 == 1))
         {
            printf ("\nO computador escolheu: 1 (Pedra)");
            printf ("\nO jogador ganhou!");
         }
         else 
         if ((op1 == 3) && (op2 == 2))
         {
            printf ("\nO computador escolheu: 2 (Papel)");
            printf ("\nO jogador ganhou!");
         }   
printf ("\nSe quiser jogar de novo digite \"1\", se quiser sair, digite \"2\": "); 
   scanf ("%d", &menu);
}
}

case 2: 
 {
while (menu != 2)
{		
system ("cls");
printf ("Jogador 1, escolha entre");
printf ("\n(1) para Pedra");  
printf ("\n(2) para Papel");  
printf ("\n(3) para Tesoura");  
printf ("\nDigite sua escolha: ");    
  scanf ("%d", &op1); 

system ("cls");
printf ("Jogador 2, escolha entre");
printf ("\n(1) para Pedra");  
printf ("\n(2) para Papel");  
printf ("\n(3) para Tesoura");  
printf ("\nDigite sua escolha: ");    
  scanf ("%d", &op2); 
  system ("cls");  
  
         if ((op1 == 2) && (op2 == 3))
            printf ("O jogador 2 ganhou!");
         else 
          if ((op1 == 1) && (op2 == 1))
            printf ("Empate!");
         else
         if ((op1 == 2) && (op2 == 2))
            printf ("Empate!"); 
       	else 
         if ((op1 == 3) && (op2 == 3))
            printf ("Empate!");
        else 
         if ((op1 == 1) && (op2 == 2))
            printf ("O jogador 2 ganhou!");      
        else 
         if ((op1 == 3) && (op2 == 1))
            printf ("O jogador 2 ganhou!");
        else 
         if ((op1 == 1) && (op2 == 3))
            printf ("O jogador 1 ganhou!");
        else 
         if ((op1 == 2) && (op2 == 1))
            printf ("O jogador 1 ganhou!");
        else    
         if ((op1 == 3) && (op2 == 2))
            printf ("O jogador 1 ganhou!");
printf ("\nSe quiser jogar de novo digite \"1\", se quiser sair, digite \"2\": "); 
   scanf ("%d", &menu);            
}
}
}



case 2: 
{
system ("cls");
printf ("\n---------------------------------------------------------------------");
printf ("\n                  The Rock, Paper, Scissors Game                     ");
printf ("\n---------------------------------------------------------------------");
printf ("\n                     Welcome Player(s)!                         ");
printf ("\n---------------------------------------------------------------------");
printf ("\nType \"1\" to play in one person or \"2\" to play in two people: ");
  scanf("%d", &mdj);
  
switch (mdj) 
{
 case 1:
 {
 while (menu2 != 2)
 {
system ("cls"); 	
printf ("Player, choose between: ");
printf ("\n(1) for Rock");  
printf ("\n(2) for Paper");  
printf ("\n(3) for Scissors");  
printf ("\nType your choice: ");    
  scanf ("%d", &op1); 
   system ("cls");
   while(op2 = 0)
op2 = (rand () % 3);  

        if ((op1 == 2) && (op2 == 3))
        {
		
		    printf ("\nThe computer chose: 3 (Scissors)");
            printf ("\nThe computer won!");
        }
        else
         if ((op1 == 1) && (op2 == 1)) 
         {
            printf ("\nThe computer chose: 1 (Rock)");
            printf ("\nDraw!");
         }
         else
         if ((op1 == 2) && (op2 == 2))
         {
            printf ("\nThe computer chose: 2 (Paper)");
            printf ("\nDraw!");
         }
         else
         if ((op1 == 3) && (op2 == 3))
         {
            printf ("\nThe computer chose: 3 (Scissors)");
            printf ("\nDraw!");
         }
        else
         if ((op1 == 1) && (op2 == 2))
         {
            printf ("\nThe computer chose: 2 (Paper)");
            printf ("\nThe computer won!");
         }
         else
         if ((op1 == 3) && (op2 == 1))
          {
		    printf ("\nThe computer chose: 1 (Rock)");
            printf ("\nThe computer won!");
          }
         else
         if ((op1 == 1) && (op2 == 3))
         {
            printf ("\nThe computer chose: 3 (Scissors)");
            printf ("\nThe player won!");
         }
         else
         if ((op1 == 2) && (op2 == 1))
         {
            printf ("\nThe computer chose: 1 (Rock)");
            printf ("\nThe player won!");
         }
         else 
         if ((op1 == 3) && (op2 == 2))
         {
            printf ("\nThe computer chose: 2 (Paper)");
            printf ("\nThe player won!");
         }   
printf ("\nIf you want to play again type \"1\", if you want to quit \"2\": "); 
   scanf ("%d", &menu2);
}
}


case 2:
{
	while (menu2 != 2)
	{
system ("cls");
printf ("Player 1, choose between: ");
printf ("\n(1) for Rock");  
printf ("\n(2) for Paper");  
printf ("\n(3) for Scissors");  
printf ("\nType your choice: ");        
  scanf ("%d", &op1); 

system ("cls");
printf ("Player, choose between: ");
printf ("\n(1) for Rock");  
printf ("\n(2) for Paper");  
printf ("\n(3) for Scissors");  
printf ("\nType your choice: ");       
  scanf ("%d", &op2); 
  system ("cls");  
  
         if ((op1 == 2) && (op2 == 3))
            printf ("Player 2 won!");
         else 
          if ((op1 == 1) && (op2 == 1))
            printf ("Draw!");
         else
         if ((op1 == 2) && (op2 == 2))
            printf ("Draw!"); 
       	else 
         if ((op1 == 3) && (op2 == 3))
            printf ("Draw!");
        else 
         if ((op1 == 1) && (op2 == 2))
            printf ("Player 2 won!");      
        else 
         if ((op1 == 3) && (op2 == 1))
            printf ("Player 2 won!");
        else 
         if ((op1 == 1) && (op2 == 3))
            printf ("Player 1 won!");
        else 
         if ((op1 == 2) && (op2 == 1))
            printf ("Player 1 won!");
        else    
         if ((op1 == 3) && (op2 == 2))
            printf ("Player 1 won!");
printf ("\nIf you want to play again type \"1\", if you want to quit \"2\": "); 
   scanf ("%d", &menu2);            
}
}
}
}
}
}
}
