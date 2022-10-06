// Aluno: Breno da Silva Nogueira / Breno de Gonzalez Bueno
// Numero USP: 12400392 / 12543190
// Matéria: Introdução a Programação
// Atividade: EP3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// constante que define o valor maximo que um pixel pode assumir.

#define VALOR_MAXIMO 255

// constantes que definem as strings que podem ser especificadas na entrada, cada uma associada uma operacao.

#define RETA "RETA"
#define RETANGULO_CONTORNO "RETANGULO_CONTORNO"
#define RETANGULO_PREENCHIDO "RETANGULO_PREENCHIDO"
#define CLONA "CLONA"
#define CLONA_INV "CLONA_INV"
#define CLONA_HOR "CLONA_HOR"
#define CLONA_VER "CLONA_VER"
#define FIM "FIM"

// estrutura que representa uma imagem.
typedef struct
{
	int altura;	  // altura da imagem (numero de linhas)
	int largura;  // largura da imagem (numero de colunas na imagem)
	int **matriz; // ponteiro para a matriz que armazena o conteudo da imagem
} Imagem;

// estrutura que representa um Ponto no plano 2D.

typedef struct
{
	int x; // coordenada horizontal
	int y; // coordenada vertical
} Ponto2D;

// funcao que cria uma imagem vazia e a devolve. Precisar ser completada para funcionar corretamente.

Imagem *cria_imagem(int largura, int altura)
{
	Imagem *imagem = (Imagem *)malloc(sizeof(Imagem));

	imagem->altura = altura;   // isto está correto?
	imagem->largura = largura; // e isto?

	imagem->matriz = (int **)malloc(altura * sizeof(int *));

	for (int i = 0; i < altura; i++)
	{
		imagem->matriz[i] = (int *)malloc(largura * sizeof(int *));

		for (int j = 0; j < largura; j++)
		{
			imagem->matriz[i][j] = 0;
		}
	}
	return imagem;
}

// funcao (ja completa) que libera os recursos de memoria associados a uma imagem.

void libera_imagem(Imagem *imagem)
{
	int lin;
	for (lin = 0; lin < imagem->altura; lin++)
		free(imagem->matriz[lin]); // liberacao de cada linha da matriz (cada linha é um vetor de int)

	free(imagem->matriz); // liberacao da matriz (que é na realidade um vetor de linhas, ou um vetor de "vetor de int")
	free(imagem);		  // liberacao da estrutura em si
}

// funcao (ja completa) que salva uma imagem em um arquivo, no formato PGM. Programas/utilitarios que trabalham
// com imagens bitmap (como o Gimp e visualizadores de imagens normalmente instalados em ambiente Linux) em geral
// reconhecem formato. Se tiver dificuldades para visualizar os arquivos de imagem salvos por esta funcao, um visualizador
// online pode ser encontrado neste link: http://paulcuth.me.uk/netpbm-viewer/.

void salva(Imagem *imagem, char *nomeArquivo)
{
	int lin, col;
	FILE *saida = fopen(nomeArquivo, "w"); // abertura do arquivo para escrita ("w" - write)

	if (saida)
	{
		// o 'fprintf' funciona de forma igual ao 'printf', com a diferença que
		// o conteudo eh escrito em um arquivo (associado a variavel 'saida')

		fprintf(saida, "P2\n%d %d\n%d\n", imagem->largura, imagem->altura, VALOR_MAXIMO);

		for (lin = 0; lin < imagem->altura; lin++)
		{

			for (col = 0; col < imagem->largura; col++)
			{
				fprintf(saida, (col == 0 ? "%d" : " %d"), imagem->matriz[lin][col]);
			}

			fprintf(saida, "\n");
		}
	}

	fclose(saida); // fechamento do arquivo
}

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//  Funcoes que implementam as operacoes de desenho. Todas precisam ser completadas.  //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

// desenha uma reta que tem origem no ponto 'p1' e termina no ponto 'p2', na tonalidade de cinza definida em 'cor'.

void reta(Imagem *imagem, Ponto2D p1, Ponto2D p2, int cor)
{
	// Distância de x do pixel
	int dx = abs(p1.x - p2.x), sx = p1.x < p2.x ? 1 : -1;
	// Distância de y do pixel
	int dy = -abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
	int err = dx + dy, e2;

	for (;;)
	{
		imagem->matriz[p1.y][p1.x] = cor;
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			p1.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

// desenha o contorno de um retangulo com cantos opostos em 'p1' e 'p2', na tonalidade de cinza definida em 'cor'.
// Você não pode assumir nada em relacao a posicao dos cantos 'p1' e 'p2', apenas que tratam-se de cantos opostos.

void retangulo_contorno(Imagem *imagem, Ponto2D p1, Ponto2D p2, int cor)
{
	// Pontos faltantes para completar o retangulo
	Ponto2D pq;
	pq.x = p2.x;
	pq.y = p1.y;

	Ponto2D pr;
	pr.x = p1.x;
	pr.y = p2.y;

	// Primeira reta
	reta(imagem, p1, pq, cor);
	// Segunda reta
	reta(imagem, p1, pr, cor);
	// Terceira reta
	reta(imagem, p2, pq, cor);
	// Quarta reta
	reta(imagem, p2, pr, cor);
}

// desenha um retangulo preenchido com cantos opostos em 'p1' e 'p2', na tonalidade de cinza definida em 'cor'.
// Você não pode assumir nada em relacao a posicao dos cantos 'p1' e 'p2', apenas que tratam-se de cantos opostos.

void retangulo_preenchido(Imagem *imagem, Ponto2D p1, Ponto2D p2, int cor)
{
	Ponto2D maior = p1.x > p2.x ? p1 : p2;
	Ponto2D menor = p1.x < p2.x ? p1 : p2;

	// Ponto Auxiliares
	Ponto2D pr;
	pr.x = menor.x;
	pr.y = maior.y;

	Ponto2D pq;
	pq.x = menor.x;
	pq.y = menor.y;

	for (;;)
	{
		reta(imagem, pq, pr, cor);
		if (pq.x == maior.x)
		{
			reta(imagem, pq, pr, cor);
			break;
		}
		pq.x++;
		pr.x++;
	}
}

// copia o conteudo da area compreendida no retangulo delimitado pelos cantos opostos 'p1' e 'p2' para uma região destino
// na imagem. Para esta funcao, voce pode assumir que 'p1' representa o canto superior esquerdo da area a ser copiada,
// 'p2' o canto inferior direito desta mesma area, e 'p3' o canto superior esquerdo da regiao que receberá a copia.

void clona(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
	// Distância de x entre os dois pontos
	int dx = p1.x > p2.x ? p1.x - p2.x : p2.x - p1.x;
	// Distância de y entre os dois pontos
	int dy = p1.y > p2.y ? p1.y - p2.y : p2.y - p1.y;

	for (int i = 0; i <= dx; i++)
	{
		for (int j = 0; j <= dy; j++)
		{
			imagem->matriz[p3.y + j][p3.x + i] = imagem->matriz[j][i];
		}
	}
}

// similar a funcao acima, mas invertendo o valor dos pixels copiados para a região destino. Isto é, pixels brancos devem
// se tornar pretos, pixels pretos se tornar brancos, e pixels em tons de cinza devem assumir o valor complementar (aquele
// que somado ao valor original resulta no valor definido na constante VALOR_MAXIMO).

void clona_inverte_cor(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
	// Distância de x entre os dois pontos
	int dx = p1.x > p2.x ? p1.x - p2.x : p2.x - p1.x;
	// Distância de y entre os dois pontos
	int dy = p1.y > p2.y ? p1.y - p2.y : p2.y - p1.y;

	int cor = 0;
	for (int i = 0; i <= dx; i++)
	{
		for (int j = 0; j <= dy; j++)
		{
			cor = VALOR_MAXIMO - imagem->matriz[j][i];
			imagem->matriz[p3.y + j][p3.x + i] = cor;
		}
	}
}

// similar a funcao 'clona', mas espelhando horizontalmente a região copiada.

void clona_espelha_horizontal(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
	// Distância de x entre os dois pontos
	int dx = p1.x > p2.x ? p1.x - p2.x : p2.x - p1.x;
	// Distância de y entre os dois pontos
	int dy = p1.y > p2.y ? p1.y - p2.y : p2.y - p1.y;

	int xc = p3.x + dx;
	int yc = p3.y;

	for (int i = 0; i <= dx; i++)
	{
		for (int j = 0; j <= dy; j++)
		{
			imagem->matriz[yc + j][xc - i] = imagem->matriz[p1.y + j][p1.x + i];
		}
	}
}

// similar a funcao 'clona', mas espelhando verticalmente a região copiada.

void clona_espelha_vertical(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
	// Distância de x entre os dois pontos
	int dx = p1.x > p2.x ? p1.x - p2.x : p2.x - p1.x;
	// Distância de y entre os dois pontos
	int dy = p1.y > p2.y ? p1.y - p2.y : p2.y - p1.y;

	int xc = p3.x;
	int yc = p3.y + dy;

	for (int i = 0; i <= dy; i++)
	{
		for (int j = 0; j <= dx; j++)
		{
			imagem->matriz[yc - i][xc + j] = imagem->matriz[p1.y + i][p1.x + j];
		}
	}
}

/////////////////////////////////////////////////////////
//                                                     //
//  Programa principal. Também precisa ser completado. //
//                                                     //
/////////////////////////////////////////////////////////

int main()
{
	int largura, altura, cor;
	char operacao[32], nome_arquivo[256];
	Imagem *img;
	Ponto2D p1;
	Ponto2D p2;
	Ponto2D p3;

	scanf("%s %d %d", nome_arquivo, &largura, &altura);
	img = cria_imagem(largura, altura);

	while (scanf("%s", operacao) == 1 && strcmp(operacao, "FIM") != 0)
	{
		p1.x = 0;
		p1.y = 0;

		p2.x = 0;
		p2.y = 0;

		cor = 0;

		if (strcmp(operacao, RETA) == 0)
		{
			scanf("%d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &cor);
			reta(img, p1, p2, cor);
		}
		else if (strcmp(operacao, RETANGULO_CONTORNO) == 0)
		{
			scanf("%d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &cor);
			retangulo_contorno(img, p1, p2, cor);
		}
		else if (strcmp(operacao, RETANGULO_PREENCHIDO) == 0)
		{
			scanf("%d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &cor);
			retangulo_preenchido(img, p1, p2, cor);
		}
		else
		{
			p3.x = 0;
			p3.y = 0;

			if (strcmp(operacao, CLONA) == 0)
			{
				scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
				clona(img, p1, p2, p3);
			}
			else if (strcmp(operacao, CLONA_HOR) == 0)
			{
				scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
				clona_espelha_horizontal(img, p1, p2, p3);
			}
			else if (strcmp(operacao, CLONA_INV) == 0)
			{
				scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
				clona_inverte_cor(img, p1, p2, p3);
			}
			else if (strcmp(operacao, CLONA_VER) == 0)
			{
				scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
				clona_espelha_vertical(img, p1, p2, p3);
			}
			else
				continue;
		}
	}
	salva(img, nome_arquivo);
	libera_imagem(img);

	return 0;
}