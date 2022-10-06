#include<stdio.h>
#include<math.h>

// Melhorando ainda mais a versão anterior com a declaração de funções (subrotinas) 
// que calculam a área de cada parte. A criação das funções ajuda a orgnizar melhor 
// o código e realça a abordagem de dividir um problema maior em problemas menores
// empregada para elaborar o algoritmo.

// Cada função delimita um bloco de código que executa apenas quando cada função é 
// chamada no programa principal. Ao final da execução de cada chamda de função, o 
// valor calculado é devolvido. Uma declaração de função é composta pelo nome que 
// queremos dar à subrotina (o qual é usado para chamar a função no programa principal), 
// pelo tipo daquilo que será devolvido pela função, e também por um conjunto de 
// parâmetros que podem ser passados à chamada da função (isso não é explorado neste 
// exemplo, mas será no próximo).

int areaRetangulo(){

	int a = 10 * 7;
	return a;
}

int areaTriangulo(){

	int a = 5 * 4 / 2;
	return a;
}

double areaQuartoDeCirculo(){

	// Aqui também há uma melhoria em relação ao cálculo da área da
	// região correspondente a 1/4 de circulo com o uso da constante PI
	// e função de exponenciação disponibilizadas na biblioteca <math.h>.

	return M_PI * pow(4, 2) / 4; 
}

int main(){

	// variáveis para armazenar as áreas de cada parte.
	int ret;
	int tri;
	double circ;

	// Chamada das funções que calculam a área de cada parte, 
	// e atribuição dos resultados nas variáveis.
	ret = areaRetangulo();
	tri = areaTriangulo();
	circ = areaQuartoDeCirculo();

	// Exibição das boas vindas.
	printf("Programa para calculo da area de uma forma geometrica.\n\n");

	// Exibição da área referente a cada parte.	
	printf("Area do retangulo = %d\n", ret);
	printf("Area do triangulo = %d\n", tri);
	printf("Area do 1/4 de circulo = %f\n", circ);
	
	// Exibição da área total. 
	printf("\nArea Total = %f\n", ret + tri - circ);

	// return zero sinaliza que a execução foi bem sucedida.
	return 0;
}

