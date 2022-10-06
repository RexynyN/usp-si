#include<stdio.h>
#include<math.h>

// Melhorando a versão anterior, através do uso de variáveis para armazenar as áreas
// das partes menores que são relevantes para o cálculo da área total.

int main(){

	int ret;	// variável para armazenar a área da região retangular.
	int tri;	// variável para armazenar a área da região triângular.
	double circ;	// variável para armazenar a área da região referente ao 1/4 de círculo.

	// Cálculo a atribuição dos resultados nas variáveis.
	ret = 10 * 7;			
	tri = 5 * 4 / 2;
	circ = M_PI * 4 * 4 / 4;

	// Exibição das boas vindas.
	printf("Programa para calculo da area de uma forma geometrica.\n\n");

	// Exibição da área referente a cada parte.	
	printf("Area do retangulo = %d\n", ret);
	printf("Area do triangulo = %d\n", tri);
	printf("Area do 1/4 de circulo = %f\n", circ);

	// Exibição da área total. Note como, além de evitar a repetição do cálculo da área 
	// de cada parte, a expressão que determina o valor da área total está muito mais compreensível.	
	printf("\nArea Total = %f\n", ret + tri - circ);

	// return zero sinaliza que a execução foi bem sucedida.
	return 0;
}

