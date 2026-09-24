#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *prox;
} No;

typedef struct Fila
{
    struct No *frente;
    struct No *fim;
} Fila;

void enfileirar(Fila *fila, int valor);
int desenfileirar(Fila *fila, int *valor);
void imprimirFila(Fila *fila);

int main()
{
    Fila fila;

    fila.fim = NULL;
    fila.frente = NULL;

    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);

    printf("Fila: ");
    imprimirFila(&fila);

    int valor;
    while (desenfileirar(&fila, &valor))
        printf("Saiu: %d\n", valor);

    return 0;
}

void enfileirar(Fila *fila, int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
        return;

    novoNo->valor = valor;
    novoNo->prox = NULL;

    if (fila->fim == NULL)
    {
        // Fila vazia: o novo nó é frente e fim ao mesmo tempo
        fila->frente = novoNo;
        fila->fim = novoNo;
    }
    else
    {
        // Liga no final e atualiza o fim
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

// Remove o elemento da frente.
// Retorna 1 se removeu, 0 se a fila estava vazia.
int desenfileirar(Fila *fila, int *valor)
{
    if (fila->frente == NULL)
        return 0;

    No *remover = fila->frente;

    *valor = remover->valor;
    fila->frente = remover->prox;

    // Se a fila ficou vazia, o fim também precisa ser NULL
    if (fila->frente == NULL)
        fila->fim = NULL;

    free(remover);
    return 1;
}

void imprimirFila(Fila *fila)
{
    for (No *atual = fila->frente; atual != NULL; atual = atual->prox)
        printf("%d ", atual->valor);
    printf("\n");
}