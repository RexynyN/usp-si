#include <stdio.h>
#include <stdlib.h>

int main(){

	int i, valor, total, n;
	int * a;

	printf("Qual o tamanho maximo da sequencia? ");
	scanf("%d", &n);
	
	a = (int *) malloc(n * sizeof(int));

	printf("Digite a sequencia com no maximo %d valores:\n", n);

	for(i = 0; i < n; i++){

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

