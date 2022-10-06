#include <stdio.h>

/*
	Este programa lê, a partir da entrada padrão, uma sequência de
	3 valores inteiros, e os imprime na ordem reversa à ordem em que
	foram fornecidos.
*/

int main(){

	int a, b, c;

	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	printf("%d %d %d\n", c, b, a);

	return 0;
}
