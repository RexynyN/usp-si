#include<stdio.h>
#include<math.h>

/*
	Versão final com o uso de condicionais e laços mais elaborados.
	Permite que o usuário do programa realize o cálculo repetidas vezes, 
	enquanto um valor válido (> 0) para a dimensão maior da figura geométrica
	for fornecido.
*/


// alguns defines para "criar" o tipo de variável booleano.
// Torna mais claras as situações em que valores do tipo int
// estão sendo usados com o propósito de representar valores
// booleanos (que podem ser apenas verdadeiro ou falso).

#define BOOLEAN int
#define TRUE 1
#define FALSE 0 

double areaRetangulo(double l1, double l2) {

	return (l1 * l2);
}

double areaTriangulo(double b, double h) {

	return (areaRetangulo(b, h) / 2);
}

double areaCirculo(double r) {

	// Também é possível utilizar a função areaRetangulo
	// para calcular o termo "raio elevado ao quadrado",
	// no cálculo da area do circulo.

	return (M_PI * areaRetangulo(r, r));
}

void imprimeResultado(double aRet, double aTri, double aFatia){

	printf("\n");
	printf("Area do retangulo = %g\n", aRet);
	printf("Area do triangulo = %g\n", aTri);
	printf("Area de 1/4 de circulo = %g\n", aFatia);
	printf("Area total = %g\n", aRet + aTri - aFatia);
	printf("\n");
}

int main(){

	double ret, tri, circ;
	double x, l1, l2, b, h, r;

	char ch;
	int contador;		// variável que conta quantas vezes o cálculo de área foi realizado.
	BOOLEAN terminou;	// variável booleana indica se o processo de repetição do cálculo terminou ou não.

	printf("Programa para calculo da area de uma forma geometrica.\n\n");

	contador = 0;		// inicialmente não fizemos nenhum cálculo de área.
	terminou = FALSE;	// inicialmente deve haver repetição do cálculo da área, ou seja NÃO terminamos.

	do {

		printf("contador = %d\n", contador);
		printf("Digite o valor de x: ");
		
		if( scanf("%lf", &x) == 0 ){

			printf("\nFalha na leitura do valor double, ignorando restante da linha.\n\n");
			
			// Se a tentativa de leitura de um valor double falha, nenhum caractere é consumido
			// da fila de caracteres disponíveis na entrada padrão (stdin). Logo, qualquer nova
			// tentativa de leitura de um valor double usando o scanf iria processar a mesma
			// sequência de caracteres, gerando nova falhar de leitura. Para dar a chance de
			// o usuário fornecer ao programa um valor double válido na próxima tentativa
			// devemos "gastar" estes caracteres da fila que não foram processados. Fazemos
			// isto com o laço abaixo, que le um caractere por vez da fila até encontrar o
			// caractere que representa a quebra de linha ('\n'). Ao executarmos este laço, 
			// tudo o que foi digitado pelo usuário até a quebra de linha é "descartado".

			do{
				scanf("%c", &ch);

			} while(ch != '\n');


			// O "continue" termina imediatamente a iteração atual referente ao laço do/while
			// mais externo, e o fluxo de execução do programa retoma a partir do início deste
			// laço (se a condição de manutenção do laço ainda for verdadeira). Ou seja, a iteração 
			// atual termina antecipadamente (sem que nenhum cálculo seja feito), e iniciamos 
			// imediatamente uma nova iteração para que o usuário possa fornecer ao programa um
			// valor adequado (isto é, uma sequencia de caracteres que seja adequadamente interpretada
			// com um valor double.

			continue; 		 
		}

		// Se chegamos até aqui na iteração atual, então o valor fornecido pelo usuário é um valor
		// double válido. Mas ainda assim pode ser uma dimensão que não faça sentido em relação ao
		// cálculo da área. Assumiremos que se o usuário fornece um valor zero ou negativo, ele deseja
		// interromper o processo de repetição do cálculo da área.
	
		if(x <= 0) {

			terminou = TRUE; // atribuição para indicar que o processo de repetição do cálculo terminou
			
			// O "continue" impede o cálculo da área para o valor atual de x (que é negativo ou zero). 
			// A iteração atual é encerrada antecipamente, e a condição de manutenção do laço que será 
			// verificada logo em seguida será falsa, uma vez que acabamos de atribuir o valor verdadeiro
			// à variável "terminou". Isso irá acarretar no encerramento do laço do/while  
			continue;
		}

		// Se chegamos até aqui, o valor fornecido pelo usuário é um valor double válido, e também é
		// um valor que faz sentido para o cálculo da área (ou seja, x > 0). Logo o cálculo será feito
		// e o resultado exibido:
	
		l1 = (2 * x) / 3;
		l2 = (7 * x) / 15;
		b = x / 3;
		h = (4 * x) / 15;
		r = h;

		ret = areaRetangulo(l1, l2);
		tri = areaTriangulo(b, h);
		circ = areaCirculo(r) / 4;

		imprimeResultado(ret, tri, circ);
		
		contador++; // incrementamos o contados que indica quantas vezes o cálculo foi realizado com sucesso!
	
	} while (!terminou); // se terminou == FALSE ---> !terminou == TRUE,  logo haverá uma nova execução do bloco. 
			     // se terminou == TRUE  ---> !terminou == FALSE, logo NÃO haverá nova execução do bloco.

	printf("valor final do contador = %d\n", contador);
	
	return 0;
}

