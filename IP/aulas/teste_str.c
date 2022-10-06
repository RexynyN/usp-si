#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao que imprime uma string (vetor de char com caractere nulo representando o final da string)
// caractere a caractere (apenas para fins didaticos, na pratica, usamos o printf com o marcador %s).

void imprime(char * s){ 

	int i;

	for(i = 0; s[i]; i++){

		printf("%c", s[i]);
	}
}

// Versao alternativa da funcao que imprime uma quebra de linha apos a string.

void imprime_ln(char * s){

	imprime(s);
	imprime("\n");
}

// Funcao que recebe duas strings: uma frase e uma palavra e verifica se a palavra ocorre na frase.
// Ilustra o uso das funções strncmp (uma variação do strcmp) e strlen.

void busca_palavra(char * frase, char * palavra){

	int i;
	char * substring;

	for(i = 0; i < strlen(frase); i++){
		
		// usamos aritmetica de ponteiros para definir a substring  
		// que tem inicio no caractere de indice i:  
		substring = frase + i; 

		printf("iteracao %3d: comparando os primeiros %ld caracteres de '%s' com '%s'\n", i, strlen(palavra), substring, palavra);
	
		// para cada substring, verificamos se os primeiros 
		// caracteres sao os mesmos da string palavra:
		if(strncmp(substring, palavra, strlen(palavra)) == 0) {

			printf("Palavra '%s' ocorre na frase no indice %d.\n", palavra, i);
			break;
		}
	}

	// se nenhuma substring bate com a string palavra entao esta nao ocorre na frase:
	if(i == strlen(frase)) printf("A palavra '%s' NAO ocorre na frase.\n", palavra);
}


// Funcao que atribui o caractere c no indice i da string a:

void altera(char * a, int i, char c){

	a[i] = c; // atribuicao de c no endereco de memoria (a + i * sizeof(char))
}

// Funcao que concatena duas strings em uma unica string, separadas 
// pelo caractere espaco. Exemplo de uso da funcao strcpy:

char * junta(char * a, char * b){

	// alocacao da memoria para armazenamento da string resultante. O '+ 2'
	// serve para acomodar os caracteres espaco e nulo, nao contabilizados 
	// na expressao 'strlen(a) + strlen(b)':
	char * c = (char *) malloc ( (strlen(a) + strlen(b) + 2) * sizeof(char) );

	strcpy(c, a);
	altera(c, strlen(a), ' ');
	strcpy(c + strlen(c), b);

	return c;
}

int main(){

	char * a = "o rato roeu a roupa";
	char * b = "do rei de roma.";
	char * frase;
	char palavra[20];

	imprime("Frase (1.a parte): '");
	imprime(a);
	imprime_ln("'");

	imprime("Frase (2.a parte): '");
	imprime(b);
	imprime_ln("'");

	frase = junta(a, b);

	imprime("Frase (completa): '");
	imprime(frase);
	imprime_ln("'");

	imprime("Digite a palavra a ser buscada: ");	
	scanf("%s", palavra);

	busca_palavra(frase, palavra);

	return 0;
}
