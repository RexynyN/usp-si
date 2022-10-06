/*
Identificação

Nome: Breno da Silva Nogueira
Número USP: 12400392
Turma: 04
*/

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes de Controle da Árvore
#define T 3
#define MINIMO 2

// Struct que define um Nó
typedef struct node
{
    int chaves[T + 1];
    int numChaves;
    struct node *filhos[T + 1];
} No;

// Nó raiz da Árvore B (variavel global)
No *raiz;

// Remove um valor de dentro de um nó
void removerValor(No *no, int index)
{
    int i = index + 1;
    while (i <= no->numChaves)
    {
        no->chaves[i - 1] = no->chaves[i];
        no->filhos[i - 1] = no->filhos[i];
        i++;
    }
    no->numChaves--;
}

// Junta os nos numa operação de remoção
void juntarNos(No *no, int index)
{
    int i = 1;
    No *shu1 = no->filhos[index];
    No *shu2 = no->filhos[index - 1];

    shu2->numChaves++;
    shu2->chaves[shu2->numChaves] = no->chaves[index];
    shu2->filhos[shu2->numChaves] = no->filhos[0];

    while (i <= shu1->numChaves)
    {
        shu2->numChaves++;
        shu2->chaves[shu2->numChaves] = shu1->chaves[i];
        shu2->filhos[shu2->numChaves] = shu1->filhos[i];
        i++;
    }

    i = index;
    while (i < no->numChaves)
    {
        no->chaves[i] = no->chaves[i + 1];
        no->filhos[i] = no->filhos[i + 1];
        i++;
    }
    no->numChaves--;
    free(shu1);
}

// Move todos os valores do nó para a direita
void moverDireita(No *no, int index)
{
    No *shu = no->filhos[index];
    int i = shu->numChaves;

    while (i > 0)
    {
        shu->chaves[i + 1] = shu->chaves[i];
        shu->filhos[i + 1] = shu->filhos[i];
        i--;
    }
    shu->chaves[1] = no->chaves[index];
    shu->filhos[1] = shu->filhos[0];
    shu->numChaves++;

    shu = no->filhos[index - 1];
    no->chaves[index] = shu->chaves[shu->numChaves];
    no->filhos[index] = shu->filhos[shu->numChaves];
    shu->numChaves--;
}

// Move todos os valores do nó para a esquerda
void moverEsquerda(No *no, int index)
{
    int i = 1;
    No *shu = no->filhos[index - 1];

    shu->numChaves++;
    shu->chaves[shu->numChaves] = no->chaves[index];
    shu->filhos[shu->numChaves] = no->filhos[index]->filhos[0];

    shu = no->filhos[index];
    no->chaves[index] = shu->chaves[1];
    shu->filhos[0] = shu->filhos[1];
    shu->numChaves--;

    while (i <= shu->numChaves)
    {
        shu->chaves[i] = shu->chaves[i + 1];
        shu->filhos[i] = shu->filhos[i + 1];
        i++;
    }
}

// Ajusta as posições do No
void ajustarNo(No *no, int index)
{
    if (!index)
    {
        if (no->filhos[1]->numChaves > MINIMO)
            moverEsquerda(no, 1);
        else
            juntarNos(no, 1);
    }
    else
    {
        if (no->numChaves != index)
        {
            if (no->filhos[index - 1]->numChaves > MINIMO)
                moverDireita(no, index);
            else
            {
                if (no->filhos[index + 1]->numChaves > MINIMO)
                    moverEsquerda(no, index + 1);
                else
                    juntarNos(no, index);
            }
        }
        else
        {
            if (no->filhos[index - 1]->numChaves > MINIMO)
                moverDireita(no, index);
            else
                juntarNos(no, index);
        }
    }
}

// Copia o sucessor
void copiarSucessor(No *no, int index)
{
    No *aux;
    aux = no->filhos[index];

    while (aux->filhos[0] != NULL)
        aux = aux->filhos[0];

    no->chaves[index] = aux->chaves[1];
}

// Remove o valor da chave do No
int removerValorNo(int chave, No *no)
{
    int index;
    int flag = 0;
    if (no)
    {
        if (chave < no->chaves[1])
        {
            index = 0;
            flag = 0;
        }
        else
        {
            index = no->numChaves;
            while (chave < no->chaves[index] && index > 1)
                index--;

            if (chave == no->chaves[index])
                flag = 1;
            else
                flag = 0;
        }
        if (flag)
        {
            if (no->filhos[index - 1])
            {
                copiarSucessor(no, index);
                flag = removerValorNo(no->chaves[index], no->filhos[index]);
                if (flag == 0)
                    return 1;
            }
            else
                removerValor(no, index);
        }
        else
            flag = removerValorNo(chave, no->filhos[index]);

        if (no->filhos[index])
        {
            if (no->filhos[index]->numChaves < MINIMO)
                ajustarNo(no, index);
        }
    }
    return flag;
}

// Remove o valor da árvore
void removeC(int chave, No *no)
{
    No *aux;
    if (!removerValorNo(chave, no))
        return;
    else
    {
        if (no->numChaves == 0)
        {
            aux = no;
            no = no->filhos[0];
            free(aux);
        }
    }
    raiz = no;
    return;
}

// Cria um novo Nó
No *criarNo(int chave, No *filho)
{
    No *novoNo;
    novoNo = (No *)malloc(sizeof(No));
    novoNo->chaves[1] = chave;
    novoNo->numChaves = 1;
    novoNo->filhos[0] = raiz;
    novoNo->filhos[1] = filho;
    return novoNo;
}

void adicionaChaveNo(int chave, int index, No *no, No *filho)
{
    int i = no->numChaves;
    while (i > index)
    {
        no->chaves[i + 1] = no->chaves[i];
        no->filhos[i + 1] = no->filhos[i];
        i--;
    }
    no->chaves[i + 1] = chave;
    no->filhos[i + 1] = filho;
    no->numChaves++;
}

// Divide um nó cheio em dois
void dividirNo(int chave, int *p, int index, No *no, No *filho, No **novo)
{
    int meio;
    int i;

    if (index > MINIMO)
        meio = MINIMO + 1;
    else
        meio = MINIMO;

    *novo = (No *)malloc(sizeof(No));
    i = meio + 1;
    while (i <= T)
    {
        (*novo)->chaves[i - meio] = no->chaves[i];
        (*novo)->filhos[i - meio] = no->filhos[i];
        i++;
    }
    no->numChaves = meio;
    (*novo)->numChaves = T - meio;

    if (index <= MINIMO)
    {
        adicionaChaveNo(chave, index, no, filho);
    }
    else
    {
        adicionaChaveNo(chave, index - meio, *novo, filho);
    }
    *p = no->chaves[no->numChaves];
    (*novo)->filhos[0] = no->filhos[no->numChaves];
    no->numChaves--;
}

// Insere o valor da chave no nó
int colocarValorNo(int chave, int *p, No *no, No **filho)
{
    int index;
    if (!no)
    {
        *p = chave;
        *filho = NULL;
        return 1;
    }

    if (chave < no->chaves[1])
        index = 0;
    else
    {
        index = no->numChaves;
        while (chave < no->chaves[index] && index > 1)
            index--;

        if (chave == no->chaves[index])
            return 0;
    }
    if (colocarValorNo(chave, p, no->filhos[index], filho))
    {
        if (no->numChaves < T)
            adicionaChaveNo(*p, index, no, *filho);
        else
        {
            dividirNo(*p, p, index, no, *filho, filho);
            return 1;
        }
    }
    return 0;
}

// Insere uma chave nova na árvore
void insere(int chave)
{
    int flag;
    int i;
    No *filho;

    flag = colocarValorNo(chave, &i, raiz, &filho);
    if (flag)
        raiz = criarNo(i, filho);
}


// Procura um nó com base na sua chave
No *procurar(int chave, No *no)
{
    if (!no)
        return NULL;

    int index;
    if (chave < no->chaves[1])
        index = 0;
    else
    {
        index = no->numChaves;
        while (chave < no->chaves[index] && index > 1)
            index--;

        if (chave == no->chaves[index])
            return no;
    }

    procurar(chave, no->filhos[index]);
}

// Imprime a árvore
void imprime(No *no, FILE *writer)
{
    int i;
    if (no)
    {
        for (i = 0; i < no->numChaves; i++)
        {
            imprime(no->filhos[i], writer);
            printf("%d ", no->chaves[i + 1]);
            fprintf(writer, "%d ", no->chaves[i + 1]);
        }
        imprime(no->filhos[i], writer);
    }
}

// Função principal do programa
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Faltam argumentos para o programa funcionar!");
        return 1;
    }

    int num;
    char ins[20];
    FILE *reader = fopen(argv[1], "r");
    FILE *writer = fopen(argv[2], "w");

    if (reader == NULL || writer == NULL)
    {
        printf("Houve um erro ao abrir os arquivos.");
        return 1;
    }

    // Funções auxiliares
    No *rem;
    int index;

    // Loop de avaliação dos comandos
    while (!feof(reader))
    {
        fscanf(reader, "%s %d", &ins, &num);
        printf("\n%d - ", num);
        puts(ins);

        if (strcmp(ins, "insere") == 0)
        {
            insere(num);
        }
        else if (strcmp(ins, "remove") == 0)
        {
            rem = procurar(num, raiz);
            removeC(num, rem);
        }
        else if (strcmp(ins, "imprime") == 0)
        {
            imprime(raiz, writer);
            fprintf(writer, "\n");
        }
        else if (strcmp(ins, "fim") == 0)
        {
            break;
        }
        imprime(raiz, writer);
        fprintf(writer, "\n");
    }

    // Fecha as streams de arquivo
    fclose(reader);
    fclose(writer);
    printf("Arquivos Salvos.");

    return 0;
}