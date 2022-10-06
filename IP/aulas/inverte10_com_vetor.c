#include <stdio.h>

int main(){

	int i, valor, total;

	int a[10]; // "a" é uma variável capaz de armazenar 10 valores inteiros nas posições: a[0], a[1], a[2], ..., a[8], a[9].

	// Laço de leitura da sequência a ser invertida, que será armazenada no vetor.

	for(i = 0; i < 10; i++){

		// Este bloco de código vai executar para valores de i indo de 0 até 9

		if(scanf("%d", &valor) && valor > 0){
		
			// se a leitura do valor inteiro for bem sucedida, 
			// e o valor for > 0, este é armazenado
			// na posição i do vetor.

			a[i] = valor;
		}
		else break; // se a leitura falha, ou o valor lido é <= 0, então provocamos a imediata 
			    // interrupçao do for através do "break".
	}

	// Na linha seguinte ao for podemos ter dois cenários:
	//
	//   1) Cenário em que a leitura termina antecipadamente. Por exemplo: quando i = 5 usuário entra com valor inválido.
	//
	//   a[0] até a[4]	: valores válidos lidos em iterações anteriores
        //   a[5] 		: não chegamos atribuir um valor nesta posição do vetor.
	//   i = 5		: valor da variável i, na linha seguinte ao fechamento do for.
	//
	//   Logo, o "valor de sáida" da variável i representa a quantidade de valores que foram atribuidos no vetor.
	//
	//   2) Cenário em que a leitura ocorre por completo (10 valores são lidos e atribuidos no vetor):
	//
	//   a[0] até a[9] = valores lidos em cada iteracao do for (valores de i entre 0 e 9).
	//  
	//   Ao final da iteração em que i = 9, há o incremento da variável i, que passa a valer 10.
	//   Neste momento, condição de manutenção do for passa a ser falsa, e o for é encerrado.
	//	
	//   Logo, o valor de saída da variável i, também representa a quantidade de valores que foram atribuidos no vetor! ;)

	total = i; 

	// Laço para exibição da saída do programa. Imprime os valores do vetor em ordem reversa (do maior índice para o zero).

	for(i = total - 1; i >= 0; i--){

		printf("%d ", a[i]);
	}

	// Valor de i ao final do for: -1

	printf("\n");

	return 0;
}

