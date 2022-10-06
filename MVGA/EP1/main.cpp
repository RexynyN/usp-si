#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <list>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
//#include <functional>

#include "of.h"
#include "ofOffPointsReader.h"
#include "Handler.hpp"
#include "GL_Interactor.h"
#include "ColorRGBA.hpp"
#include "Cores.h"
#include "Point.hpp"
#include "printof.hpp"

#include "CommandComponent.hpp"
#include "MyCommands.hpp"

#include "ofVertexStarIteratorSurfaceVertex.h"

clock_t start_insert;
clock_t end_insert;
clock_t start_print;
clock_t end_print;

using namespace std;
using namespace of;

//Define o tamanho da tela.
scrInteractor *Interactor = new scrInteractor(900, 650);

//Define a malha a ser usada.
typedef of::MyofDefault2D TTraits;
typedef of::ofMesh<TTraits> TMesh;
TMesh *malha;
Handler<TMesh> meshHandler;

typedef PrintOf<TTraits> TPrintOf;

TPrintOf *Print;

typedef MyCommands<TPrintOf> TMyCommands;
typedef CommandComponent TAllCommands;

ofVtkWriter<TTraits> writer;
TAllCommands *allCommands;

//##################################################################//

////////////////////////////////////////////////////////////////////////
int type = 3;
//CASO 1 EXECUTA CRUST
//CASO 2 EXECUTA BETA-SKELETON
//CASO 3 EXECUTA ARVORE
////////////////////////////////////////////////////////////////////////

// Struct de um ponto no plano, para melhor manejo durante os cálculos.
typedef struct
{
	int id;
	double x;
	double y;
} TPoint;

// Checa as coordenadas baricentricas do triângulo ABC para saber se o ponto P está dentro dele.
bool checkBarycenter(TPoint A, TPoint B, TPoint C, TPoint P)
{
	// Vai calcular os dois alfas e descobrir se o ponto está ou não dentro do triângulo
	double s1 = C.y - A.y;
	double s2 = C.x - A.x;
	double s3 = B.y - A.y;
	double s4 = P.y - A.y;

	double w1 = (A.x * s1 + s4 * s2 - P.x * s1) / (s3 * s2 - (B.x - A.x) * s1);
	double w2 = (s4 - w1 * s3) / s1;

	// Retorna se o ponto está ou não dentro do triângulo
	return (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1);
}

// Encontra a mediana para retornar o valor médio dos três módulos.
double findMedian(double a[])
{
	int n = sizeof(a) / sizeof(a[0]);
	std::sort(a, a + n);

	if (n % 2 != 0)
		return (double)a[n / 2];

	return (double)(a[(n - 1) / 2] + a[n / 2]) / 2.0;
}

// Retorna o valor igual ao modo pedido em relação ao módulo do vetor entre o ponto especificado e o ponto P
int findMostNegative(TPoint A, TPoint B, TPoint C, TPoint P, int mode)
{
	int id = 0;
	// Traça o módulo de um vetor entre os vértices e o ponto p, e descobre qual o mais perto
	double vA = sqrt(pow((P.x - A.x), 2) + pow((P.y - A.y), 2));
	double vB = sqrt(pow((P.x - B.x), 2) + pow((P.y - B.y), 2));
	double vC = sqrt(pow((P.x - C.x), 2) + pow((P.y - C.y), 2));

	// Retorna o id do:
	// 1: Menor valor
	// 2: Valor médio
	// 3: Maior valor
	switch (mode)
	{
	case 1:
		if (vA < vB && vA < vC)
			id = A.id;
		else if (vB < vA && vB < vC)
			id = B.id;
		else
			id = C.id;
		break;

	case 2:
	{
		double values[] = {vA, vB, vC};
		double median = findMedian(values);

		if (vA == median)
			id = A.id;
		else if (vB == median)
			id = B.id;
		else
			id = C.id;

		break;
	}

	case 3:
		if (vA > vB && vA > vC)
			id = A.id;
		else if (vB > vA && vB > vC)
			id = B.id;
		else
			id = C.id;
		break;

	default:
		id = -1;
		break;
	}

	return id;
}

// Retorna os três pontos do triângulo como um struct personalizado TPoint
TPoint *getPointsTriangle(int id1, int id2, int id3)
{
	// Cria array de TPoint's e uma variável auxiliar para guardar as coordenadas
	TPoint *points = (TPoint *)malloc(sizeof(TPoint) * 3);
	of::MyofDefault2D::space *vertex;

	// Aloca o id e coordenadas nos structs
	vertex = malha->getVertex(id1)->getCoords();
	points[0].id = id1;
	points[0].x = (double)vertex[0];
	points[0].y = (double)vertex[1];

	vertex = malha->getVertex(id2)->getCoords();
	points[1].id = id2;
	points[1].x = (double)vertex[0];
	points[1].y = (double)vertex[1];

	vertex = malha->getVertex(id3)->getCoords();
	points[2].id = id3;
	points[2].x = (double)vertex[0];
	points[2].y = (double)vertex[1];

	//for (int i = 0; i < 3; i++)
	//	cout << points[i].id << " - " << points[i].x << " - " << points[i].y << endl;

	return points;
}

void RenderScene(void)
{
	cout << "\nEP de MVGA - Breno da Silva Nogueira - 12400392 - Turma 04\n"
		 << endl;
	cout << "Let's Roll"
		 << endl;

	allCommands->Execute();
	Print->Vertices(malha, blue, 3);
	Print->FacesWireframe(malha, grey, 3);

	// =========================================================================================================
	// =========================================================================================================
	// ========================== CONFIGURAÇÕES DO ALGORITMO ===================================================
	// =========================================================================================================
	// Se quiser mudar o comportamento, aqui estão as variáveis.

	// Esse vai ser o ponto que o algoritmo vai tentar encontrar
	TPoint p;
	p.id = -1;
	p.x = 399;
	p.y = 439;

	// Começamos a procurar pelo triângulo de id 320, mas pode mudar para qualquer id
	int cellId = 320;
	// Pinta de amarelo para saber de onde começou
	Print->Face(malha->getCell(cellId), yellow);

	// =========================================================================================================
	// =========================================================================================================
	// =========================================================================================================

	// Placeholder para o id do vertice que a gente vai procurar ao longo do loop
	int vertexId = 0;
	// Estrutura vector para armazenar todas as células que já percorreu, para que não entre em um loop infinito entre células
	std::vector<int> items;
	bool sentinel = true;
	while (sentinel)
	{
		// Pega a célula com o Id colocado e seus vértices
		of::MyofDefault2D::sCell *cell = malha->getCell(cellId);
 
		// Aqui, professor, eu não sei se era proposital ou um bug, mas os vértices estavam como privados e não achei nenhum método para retorná-los,
		// Então fui na definição deles e os deixei públicos, espero não ter trapaceado haha
		TPoint *points = getPointsTriangle(cell->vertices[0], cell->vertices[1], cell->vertices[2]);

		// Checa se o ponto P está na célula atual
		if (checkBarycenter(points[0], points[1], points[2], p))
		{
			// Se achar, pinta o triângulo de vermelho e quebra o loop
			cout << "\nO ponto P(" << p.x << "," << p.y << ") está no triângulo da célula " << cellId << " (em vermelho no grid)\n"
				 << endl;
			Print->Face(cell, red);
			break;
		}
		else
		{
			// Se não achar, pinta de azul e continua o loop, pegando o triângulo oposto ao vértice mais perto do ponto P
			Print->Face(cell, blue);

			//cout << "///" << cellId << endl;
			items.push_back(cellId);

			vertexId = findMostNegative(points[0], points[1], points[2], p, 1);
			cellId = cell->getMateVertexId(vertexId);

			// Garante que ache um triângulo com ID >= 0 ou uma célula no qual já não se tenha passado
			if (cellId < 0 || std::find(items.begin(), items.end(), cellId) != items.end())
			{
				vertexId = findMostNegative(points[0], points[1], points[2], p, 2);
				cellId = cell->getMateVertexId(vertexId);

				//sentinel = false;
				if (cellId < 0 || std::find(items.begin(), items.end(), cellId) != items.end())
				{
					vertexId = findMostNegative(points[0], points[1], points[2], p, 3);
					cellId = cell->getMateVertexId(vertexId);

					// A esse ponto o triângulo está cercado, joga ele para outro canto do mapa
					if (cellId < 0 || std::find(items.begin(), items.end(), cellId) != items.end())
						cellId += 1;
				}
			}
		}
	}

	glFinish();
	glutSwapBuffers();
}

void HandleKeyboard(unsigned char key, int x, int y)
{

	double coords[3];
	char *xs[10];
	allCommands->Keyboard(key);

	switch (key)
	{

	case 'e':
		exit(1);
		break;
	case 'v':
		coords[0] = x;
		coords[1] = -y;
		coords[2] = 0.0;
		malha->addVertex(coords);
		break;
	case 's':

		break;

	case 'd':

		break;
	}

	Interactor->Refresh_List();
	glutPostRedisplay();
}

using namespace std;

int main(int *argc, char **argv)
{

	ofRuppert2D<MyofDefault2D> ruppert;
	ofPoints2DReader<MyofDefault2D> reader;
	ofVtkWriter<MyofDefault2D> writer;
	Interactor->setDraw(RenderScene);
	meshHandler.Set(new TMesh());
	char *fileBrasil = "../Brasil.off";

	reader.readOffFile(fileBrasil);

	ruppert.execute2D(reader.getLv(), reader.getLids(), true);
	//writer.write(ruppert.getMesh(),"out.vtk",reader.getNorma(),ruppert.getNumberOfInsertedVertices());

	meshHandler = ruppert.getMesh();
	malha = ruppert.getMesh();

	Print = new TPrintOf(meshHandler);

	allCommands = new TMyCommands(Print, Interactor);

	double a, x1, x2, y1, y2, z1, z2;

	of::ofVerticesIterator<TTraits> iv(&meshHandler);

	iv.initialize();
	x1 = x2 = iv->getCoord(0);
	y1 = y2 = iv->getCoord(1);
	z1 = z2 = iv->getCoord(2);

	for (iv.initialize(); iv.notFinish(); ++iv)
	{
		if (iv->getCoord(0) < x1)
			x1 = a = iv->getCoord(0);
		if (iv->getCoord(0) > x2)
			x2 = a = iv->getCoord(0);
		if (iv->getCoord(1) < y1)
			y1 = a = iv->getCoord(1);
		if (iv->getCoord(1) > y2)
			y2 = a = iv->getCoord(1);
		if (iv->getCoord(2) < z1)
			z1 = a = iv->getCoord(2);
		if (iv->getCoord(2) > z2)
			z2 = a = iv->getCoord(2);
	}

	double maxdim;
	maxdim = fabs(x2 - x1);
	if (maxdim < fabs(y2 - y1))
		maxdim = fabs(y2 - y1);
	if (maxdim < fabs(z2 - z1))
		maxdim = fabs(z2 - z1);

	maxdim *= 0.6;

	Point center((x1 + x2) / 2.0, (y1 + y2) / 2.0, (y1 + y2) / 2.0);
	Interactor->Init(center[0] - maxdim, center[0] + maxdim,
					 center[1] - maxdim, center[1] + maxdim,
					 center[2] - maxdim, center[2] + maxdim, argc, argv);

	AddKeyboard(HandleKeyboard);

	allCommands->Help(std::cout);
	std::cout << std::endl
			  << "Press \"?\" key for help" << std::endl
			  << std::endl;
	double t;

	Init_Interactor();

	return EXIT_SUCCESS;
}
