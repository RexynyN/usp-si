/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   04 - Prof. Luciano Antonio Digiampietri                       **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   Breno da Silva Nogueira                   12400392            **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila()
{
	PFILA res = (PFILA)malloc(sizeof(FILAPREFERENCIAL));
	res->cabeca = (PONT)malloc(sizeof(ELEMENTO));
	res->inicioNaoPref = res->cabeca;
	res->cabeca->id = -1;
	res->cabeca->ehPreferencial = false;
	res->cabeca->ant = res->cabeca;
	res->cabeca->prox = res->cabeca;
	return res;
}

int tamanho(PFILA f)
{
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca)
	{
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id)
{
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca)
	{
		if (atual->id == id)
			return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}

bool consultarPreferencial(PFILA f, int id)
{
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca)
	{
		if (atual->id == id)
			return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}

bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial)
{
	// Validando as coisas aqui
	if (id <= 0 || buscarID(f, id) != NULL)
		return false;

	// Criando novo elemento
	PONT novo = (PONT)malloc(sizeof(ELEMENTO));
	novo->id = id;
	novo->ehPreferencial = ehPreferencial;

	if (ehPreferencial == true)
	{
		novo->ant = f->inicioNaoPref->ant;
		novo->prox = f->inicioNaoPref;

		f->inicioNaoPref->ant->prox = novo;
		f->inicioNaoPref->ant = novo;

		return true;
	}
	else
	{
		// Caso não seja preferencial
		novo->ant = f->cabeca->ant;
		novo->prox = f->cabeca;
		f->cabeca->ant->prox = novo;
		f->cabeca->ant = novo;

		// Caso seja o primeiro a não ter direito a preferencial
		if (f->inicioNaoPref == f->cabeca)
			f->inicioNaoPref = novo;

		return true;
	}

	return false;
}

bool atenderPrimeiraDaFila(PFILA f, int *id)
{
	// Validando :)
	if (f->cabeca->prox == f->cabeca)
		return false;

	// Colocando em uma variável para manipular com mais facilidade
	PONT node = f->cabeca->prox;

	// Colocando o ID no ponteiro
	*id = node->id;

	// Arrumando os ponteiros
	node->prox->ant = f->cabeca;
	f->cabeca->prox = node->prox;


	if (node->ehPreferencial == false || node->prox == f->cabeca)
		f->inicioNaoPref = node->prox;

	// Libertando nossa memória para ela seguir seus sonhos como floriculturista
	free(node);

	return true;
}

bool desistirDaFila(PFILA f, int id)
{
	// Validando as bagaça
	PONT node = buscarID(f, id);
	if (id <= 0 || node == NULL)
		return false;

	if (f->inicioNaoPref == node)
		f->inicioNaoPref = node->prox;

	// Arrumando os ponteiros
	node->prox->ant = node->ant;
	node->ant->prox = node->prox;

	// Libertando nossa memória para ela seguir seus sonhos (essa aqui quer ser atriz)
	free(node);

	return true;
}
