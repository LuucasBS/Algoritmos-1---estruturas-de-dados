#include <stdio.h>
#include <stdlib.h>

typedef struct Item
{
    int valor;
    int prioridade;

} Item;

typedef struct FilaPrioridade
{
    Item *dados;
    int tamanho;
    int capacidade;

} FilaPrioridade;

FilaPrioridade *criarFila(int capacidade);
int enfileirar(FilaPrioridade *fila, int valor, int prioridade);
int desenfileirar(FilaPrioridade *fila, int *valor, int *prioridade);
int consultarFrente(FilaPrioridade *fila, int *valor, int *prioridade);
int estaVazia(FilaPrioridade *fila);
void imprimirFila(FilaPrioridade *fila);
void liberarFila(FilaPrioridade **fila);
void subir(Item *v, int i);
void descer(Item *v, int n, int i);

int main()
{

    FilaPrioridade *fila = criarFila(10);

    if (fila == NULL)
        return 1;

    enfileirar(fila, 10, 2);
    enfileirar(fila, 20, 5);
    enfileirar(fila, 30, 1);
    enfileirar(fila, 40, 5);

    printf("Fila (vetor do heap): ");
    imprimirFila(fila);

    int valor, prioridade;

    if (consultarFrente(fila, &valor, &prioridade))
        printf("Frente: valor=%d, prioridade=%d\n", valor, prioridade);

    while (desenfileirar(fila, &valor, &prioridade))
        printf("Saiu: valor=%d, prioridade=%d\n", valor, prioridade);

    printf("Fila vazia? %s\n", estaVazia(fila) ? "Sim" : "Nao");

    liberarFila(&fila);

    return 0;
}

FilaPrioridade *criarFila(int capacidade)
{

    FilaPrioridade *fila = (FilaPrioridade *)malloc(sizeof(FilaPrioridade));

    if (fila == NULL)
    {
        return NULL;
    }

    fila->dados = (Item *)malloc(capacidade * sizeof(Item));

    if (fila->dados == NULL)
    {
        free(fila);
        return NULL;
    }

    fila->tamanho = 0;
    fila->capacidade = capacidade;

    return fila;
}

// Sobe o item enquanto a prioridade dele for maior que a do pai
void subir(Item *v, int i)
{

    while (i > 0)
    {

        int pai = (i - 1) / 2;

        if (v[pai].prioridade >= v[i].prioridade)
        {
            break;
        }

        Item temp = v[pai];
        v[pai] = v[i];
        v[i] = temp;

        i = pai;
    }
}

// Desce o item enquanto algum filho tiver prioridade maior que a dele.
// n e o tamanho considerado do heap.
void descer(Item *v, int n, int i)
{

    while (1)
    {

        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;
        int maior = i;

        if (esquerda < n && v[esquerda].prioridade > v[maior].prioridade)
        {
            maior = esquerda;
        }

        if (direita < n && v[direita].prioridade > v[maior].prioridade)
        {
            maior = direita;
        }

        if (maior == i)
        {
            break;
        }

        Item temp = v[i];
        v[i] = v[maior];
        v[maior] = temp;

        i = maior;
    }
}

// Retorna 1 se enfileirou, 0 se a fila estava cheia (overflow).
int enfileirar(FilaPrioridade *fila, int valor, int prioridade)
{

    if (fila->tamanho == fila->capacidade)
    {
        return 0;
    }

    // Coloca no fim do vetor e sobe ate a posicao correta
    fila->dados[fila->tamanho].valor = valor;
    fila->dados[fila->tamanho].prioridade = prioridade;
    subir(fila->dados, fila->tamanho);
    fila->tamanho++;

    return 1;
}

// Remove o item de maior prioridade (a raiz).
// Retorna 1 se removeu, 0 se a fila estava vazia (underflow).
int desenfileirar(FilaPrioridade *fila, int *valor, int *prioridade)
{

    if (fila->tamanho == 0)
    {
        return 0;
    }

    *valor = fila->dados[0].valor;
    *prioridade = fila->dados[0].prioridade;

    // O ultimo item vira a raiz e desce ate a posicao correta
    fila->tamanho--;
    fila->dados[0] = fila->dados[fila->tamanho];
    descer(fila->dados, fila->tamanho, 0);

    return 1;
}

// Le a raiz sem remover.
int consultarFrente(FilaPrioridade *fila, int *valor, int *prioridade)
{

    if (fila->tamanho == 0)
    {
        return 0;
    }

    *valor = fila->dados[0].valor;
    *prioridade = fila->dados[0].prioridade;

    return 1;
}

int estaVazia(FilaPrioridade *fila)
{

    return fila->tamanho == 0;
}

void imprimirFila(FilaPrioridade *fila)
{

    for (int i = 0; i < fila->tamanho; i++)
        printf("(valor=%d, prioridade=%d) ", fila->dados[i].valor, fila->dados[i].prioridade);

    printf("\n");
}

void liberarFila(FilaPrioridade **fila)
{

    if (*fila == NULL)
    {
        return;
    }

    free((*fila)->dados);
    free(*fila);

    *fila = NULL;
}