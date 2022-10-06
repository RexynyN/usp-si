#include <stdio.h>

/*
	Parecido com os demais, mas a sequência pode ter até 10 valores.
	Ou seja, o programa funcionará para sequencias menores. Um valor
	menor ou igual a zero sinaliza o término da sequência, e este último
	valor não chega a fazer parte da sequência.

	Apesar de funcionar, observe como a abordagem utilizada até aqui
	se torna inviável quando o tamanho máximo da sequência cresce. Note
	também as diversas linhas de código praticamente identicas, nas quais
	a variável envolvida é o único elemento que varia.  
*/

int main(){

	int a, b, c, d, e, f, g, h, i, j;

	a = 0;
	b = 0;
	c = 0;
	d = 0;
	e = 0;
	f = 0;
	g = 0;
	h = 0;
	i = 0;
	j = 0;

	scanf("%d", &a);
	if(a > 0) scanf("%d", &b);
	if(b > 0) scanf("%d", &c);
	if(c > 0) scanf("%d", &d);
	if(d > 0) scanf("%d", &e);
	if(e > 0) scanf("%d", &f);
	if(f > 0) scanf("%d", &g);
	if(g > 0) scanf("%d", &h);
	if(h > 0) scanf("%d", &i);
	if(i > 0) scanf("%d", &j);

	if(j > 0) printf("%d ", j);
	if(i > 0) printf("%d ", i);
	if(h > 0) printf("%d ", h);
	if(g > 0) printf("%d ", g);
	if(f > 0) printf("%d ", f);
	if(e > 0) printf("%d ", e);
	if(d > 0) printf("%d ", d);
	if(c > 0) printf("%d ", c);
	if(b > 0) printf("%d ", b);
	if(a > 0) printf("%d ", a);

	printf("\n");

	return 0;
}
