#include <stdio.h>
#include <stdlib.h>

#define USE_REALLOC 0 // mude o valor da constante para 1 para usar a funca realloc da stdlib

// nossa propria versao do realloc:
int * realoca(int * v, int n_antigo, int n_novo){

	int i;
	int * novo;

	printf("realoca: aumentando capacidade de %d para %d\n", n_antigo, n_novo);
	
	// alocacao do novo vetor
	novo = (int *) malloc (n_novo * sizeof(int));
	
	// copia dos valores do vetor antigo para o vetor novo
	for(i = 0; i < n_antigo; i++){
	
		novo[i] = v[i]; 
	}

	// liberacao da memoria ocupada pelo vetor antigo
	free(v); 

	// devolucao do endereco do novo vetor
	return novo;
}

int main(){

	int i, valor, total, n;
	int * a;
	
	n = 1;
	a = (int *) malloc(n * sizeof(int));

	printf("Endereco inicial do vetor: %p\n", a);
	printf("Digite os valores da sequencia:\n");

	for(i = 0; ; i++){

		// na i-esima iteracao, o valor de i corresponde a quantidade de valores
		// jah armazenados no vetor. Quando i == n, quer dizer que o vetor ja esta
		// todo ocupado. Logo precisamos realocar o vetor, aumentando seu tamanho.
		// Definir o novo tamanho como o dobro do tamanho atual eh uma boa politica
		// de realocacao: o desperdicio de memoria (memoria alocada, mas nao usada)
		// nunca serah maior do que n / 2 (este cenario acontece quando logo apos a
		// realocacao nao armazenamos mais nenhum valor no vetor), e a quantidade
		// total de realocacoes necessarias ateh atingir a uma certa capacidade
		// serah pequena (o que dilui o eventual custo de copiar os valores do vetor 
		// antigo para o vetor novo).

		if(i == n){

			n = n * 2;

			if(USE_REALLOC) a = (int *) realloc(a, sizeof(int) * n);
			else a = realoca(a, n / 2, n);

			printf("Endereco após realocacao do vetor: %p\n", a);
		}

		if(scanf("%d", &valor) && valor > 0){

			a[i] = valor;
		}
		else break;
	}

	total = i;

	printf("Sequencia invertida:\n");

	for(i = total - 1; i >= 0; i--){

		printf("%d\n", a[i]);
	}

	free(a);
	return 0;
}

