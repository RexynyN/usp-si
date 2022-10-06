#include<stdio.h>
#include<math.h>

// Alteração das função para que elas possam calcular a área de regiões de mesmo tipo,
// mas com dimensões diferentes. Para isso, as funções foram modificadas para receberem 
// as dimensões relevantes cada tipo de área como parâmetro. Com estas alterações as 
// funções se tornam mais úteis, pois podem ser usadas para resolver uma maior variedade
// de problemas. Para que elas possam ser genéricas, trocamos o tipo de retorno das funções
// que calculam a área do retângulo e do triângulo de int para double (ponto-flutuante).

double areaRetangulo(double l1, double l2){

	return l1 * l2;
}

double areaTriangulo(double b, double h){

	return b * h / 2;
}

double areaCirculo(double r){

	// De um modo geral, esta função se torna mais útil 
	// se calcular a área do circulo completo. Quem usa
	// a função, pode dividir o resultado depois para
	// obter a fração da área desejada.

	return M_PI * pow(r, 2);
}

int main(){

	double ret;
	double tri;
	double circ;

	// Chamada das funções que calculam a área de cada parte, 
	// e atribuição dos resultados nas variáveis. Note que as 
	// chamadas agora passam as informações necessárias para
	// que a área de cada parte possa ser devidamente calculada.
	ret = areaRetangulo(10, 7);
	tri = areaTriangulo(5, 4);
	circ = areaCirculo(4) / 4;

	// Exibição das "boas vindas".
	printf("Programa para calculo da area de uma forma geometrica.\n\n");

	// Exibição da área referente a cada parte.	
	printf("Area do retangulo = %f\n", ret);
	printf("Area do triangulo = %f\n", tri);
	printf("Area do 1/4 de circulo = %f\n", circ);

	// Exibição da área total. 
	printf("\nArea Total = %f\n", ret + tri - circ);

	// return zero sinaliza que a execução foi bem sucedida.
	return 0;
}

