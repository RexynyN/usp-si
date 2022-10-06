#include<stdio.h>

// Programa "completo" que calcula e informa a area de uma forma geométrica específica.
// Dizemos "completo", pois várias melhorias ainda são possíveis.

int main(){

	// Programa exibe as "boas vindas".
	printf("Programa para calculo da area de uma forma geometrica.\n\n");

	// Cálculo e exibição da área das partes relevantes para o cálculo da área total.
	// Pontos de atenção: 
	// 	1) Uso do %d (valores inteiros) e %f (ponto-flutuante) para sinalizar a inserção de valores numéricos na mensagem.
	// 	2) Precedência dos operadores aritméticos, e uso de parênteses para formar a expressão matemática adequada.

	printf("Area do retangulo = %d\n", 10 * 7);
	printf("Area do triangulo = %d\n", (15 - 10) * (7 - 3) / 2);
	printf("Area do 1/4 de circulo = %f\n", 3.14159 * 4 * 4 / 4);

	// Cálculo e exibição da área total. Note o uso dos parênteses para tornar mais clara a expressão.
	// Ou seja, que a área total é composta pela soma dois valores e a subtração de um terceiro.
	// Perceba também que a área de cada parte da figura é calculada duas vezes durante a execução do 
	// programa, algo que pode ser melhorado.

	printf("\nArea Total = %f\n", (10 * 7) + ((15 - 10) * (7 - 3) / 2) - (3.14159 * 4 * 4 / 4));

	// return zero sinaliza que a execução foi bem sucedida.
	return 0;
}

