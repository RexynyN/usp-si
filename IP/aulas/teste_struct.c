#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _ponto_ {

	int x;	// 4 bytes
	int y;	// 4 bytes

} Ponto;


void calc_e_imprime_distancia1(Ponto p){

	double d = sqrt(p.x * p.x + p.y * p.y);

	printf("distancia do ponto (%d, %d) a origem: %f\n", p.x, p.y, d);
}

void calc_e_imprime_distancia2(Ponto * p){

	double d = sqrt(p->x * p->x + p->y * p->y);

	printf("distancia do ponto (%d, %d) a origem: %f\n", p->x, p->y, d);
}

void atualiza_coordenadas(Ponto * p, int novo_x, int novo_y){

	p->x = novo_x;
	p->y = novo_y;
}


int main(){

	Ponto p1;

	// alocacao dinamica de um ponto. A variavel p2 guarda o endereco do ponto alocado.	
	Ponto * p2 = (Ponto *) malloc(sizeof(Ponto));

	p1.x = 4;
	p1.y = 3;

	printf("\nponto p1: (%d, %d)\n", p1.x, p1.y);
	calc_e_imprime_distancia1(p1);
	atualiza_coordenadas(&p1, 3, 4);
	printf("ponto p1: (%d, %d)\n", p1.x, p1.y);
	calc_e_imprime_distancia2(&p1);

	printf("\n------------------------------------------------------\n\n");
	
	p2->x = 10;
	p2->y = 3;

	printf("ponto p2: (%d, %d)\n", p2->x, p2->y);
	calc_e_imprime_distancia1(*p2);
	atualiza_coordenadas(p2, 3, 10);
	printf("ponto p2: (%d, %d)\n", p2->x, p2->y);
	calc_e_imprime_distancia2(p2);
	printf("\n");

	return 0;
}

