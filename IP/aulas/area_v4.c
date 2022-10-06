#include <stdio.h>
#include <math.h>

// Melhorias finais.

double areaRetangulo(double l1, double l2){

	return l1 * l2;
}

double areaTriangulo(double b, double h){

	// Uso da função areaRetangulo para calcular a área do triângulo.
	// Evitamos a implementação duplicada da mesma funcionalidade. Ao
	// invés disso, usamos uma funcionalidade já pronta, para crir uma
	// nova.

	return areaRetangulo(b, h) / 2;
}

double areaCirculo(double r){
	
	return M_PI * pow(r, 2);
}

// Nova função para exibir todas as áreas parciais e a área total.
// Note que, com esta função não precisa devolver nada para quem
// a chama, seu tipo de retorno é void. 

void imprimeArea(double ret, double tri, double circ){

	printf("Area do retangulo = %f\n", ret);
	printf("Area do triangulo = %f\n", tri);
	printf("Area do 1/4 de circulo = %f\n", circ);
	printf("\nArea Total = %f\n", ret + tri - circ);
}

int main(){

	// Nesta versão do programa, foram feitas modificações para que seja mais
	// fácil adaptar o programa para o cálculo da área de formas geométricas
	// que possuam as mesmas proporções da forma considerada inicialmente, mas
	// com dimensões diferentes (ou seja, versões aumentadas ou diminuídas da 
	// mesma forma).

	double ret, tri, circ; 		// variáveis para armazenar as áreas parciais.
	double x, l1, l2, b, h, r; 	// variáveis para armazenar as dimensões referentes à cada parte.

	// Exibição das "boas vindas".
	printf("Programa para calculo da area de uma forma geometrica.\n\n");

	// leitura do comprimento do maior lado da forma geométrica, que é usado
	// para determinar as demais dimensões. Usamos a função scanf para fazer
	// a leitura a de dados a partir da entrada padrão (terminal).	
	printf("Qual o comprimento do maior lado? ");
	if(scanf("%lf", &x) != 1){
	
		printf("Erro na leitura da dimensão maior!\n");
		return 1;	
	}

	// Para calcular a área de uma forma de dimensões diferentes, 
	// basta fornecer valores diferentes para a variável x. Todos 
	// os demais valores são determinados a partir de x.

	l1 = 2 * x / 3;		// lado maior do retângulo
	l2 = 7 * x / 15;	// lado menor do retângulo
	b = x - l1;		// base do triângulo
	h = 4 * l2 / 7;		// altura do triângulo
	r = h;			// raio do circulo

	ret = areaRetangulo(l1, l2);
	tri = areaTriangulo(b, h);
	circ = areaCirculo(r) / 4;
		
	// Chamada da função que exibe as áreas parciais e total.
	imprimeArea(ret, tri, circ);

	// return zero sinaliza que a execução foi bem sucedida.
	return 0;
}

