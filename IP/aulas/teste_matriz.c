#include <stdio.h>
#include <stdlib.h>

// funcao que imprime uma matriz alocada estaticamente com um
// numero arbitrario de linhas, mas necessariamente 4 colunas.

void imprimeMatrizEstatica(int m[][4], int nLin){

	int lin, col;

	printf("\nConteudo da matriz com %d linhas e %d colunas:\n", nLin, 4);

	for(lin = 0; lin < nLin; lin++){

		for(col = 0; col < 4; col++){

			printf("%3d ", m[lin][col]);
		}
	
		printf("\n");
	}
}

// funcao de teste que ilustra a criacao e manipulacao 
// basica de uma matriz alocada estaticamente.

void teste_alocacao_estatica(){

	int i;
	int m[3][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };

	// inversao do sinal dos valores que possuem coordenadas da linha e coluna iguais.
	for(i = 0; i < 3; i++) m[i][i] = m[i][i] * (-1);

	imprimeMatrizEstatica(m, 3);

	printf("\n");
	printf("Endereco armazenado em m:\t%p\n", m);
	printf("Endereco armazenado em m[0]:\t%p\n", m[0]);
	printf("Endereco armazenado em m[1]:\t%p\n", m[1]);
	printf("Endereco armazenado em m[2]:\t%p\n", m[2]);
}

// funcao que imprime uma matriz alocada dinamicamente,
// com um numero arbitrario de linhas e colunas.

void imprimeMatrizDinamica(int ** m, int nLin, int nCol){

	int lin, col;

	printf("\nConteudo da matriz com %d linhas e %d colunas:\n", nLin, nCol);

	for(lin = 0; lin < nLin; lin++){

		for(col = 0; col < nCol; col++){

			printf("%3d ", m[lin][col]);
		}
	
		printf("\n");
	}
}

// funcao de teste que ilustra a criacao e manipulacao
// basica de uma matriz alocada de forma dinamica.

void teste_alocacao_dinamica(){

	int i, j;

	int nLin = 12;
	int nCol = 14;

	int ** m; // declaracao da variavel m que é um vetor de enderecos

	// alocacao da matriz: vetor de enderecos

	m = (int **) malloc (nLin * sizeof(int *));

	// alocacao das matriz: alocacao individual de cada linha 

	for(i = 0; i < nLin; i++){

		m[i] = (int *) malloc (nCol * sizeof(int));
	}

	// atribuicao de valores na matriz	
	
	for(i = 0; i < nLin; i++){

		for(j = 0; j < nCol; j++){

			m[i][j] = (i * nCol + j);
		}
	}

	imprimeMatrizDinamica(m, nLin, nCol);

	printf("\n");
	printf("Endereco armazenado em m:\t%p\n", m);
	printf("Endereco armazenado em m[0]:\t%p\n", m[0]);
	printf("Endereco armazenado em m[1]:\t%p\n", m[1]);
	printf("Endereco armazenado em m[2]:\t%p\n", m[2]);
}

int main(){

	teste_alocacao_estatica();
	printf("\n--------------------------------------------------\n");
	teste_alocacao_dinamica();

	return 0;
}
