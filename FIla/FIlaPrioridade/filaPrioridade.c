#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int valor;
    int prioridade;
    struct Node *next;
} Node;

// ENFILEIRAR
void enfileirar(Node **fila, int valor, int prioridade)
{
    Node *novoNo = malloc(sizeof(Node));

    if (novoNo == NULL)
    {
        return;
    }

    novoNo->valor = valor;
    novoNo->prioridade = prioridade;
    novoNo->next = NULL;

    // CASO 1: fila vazia
    if (*fila == NULL)
    {
        *fila = novoNo;
        return;
    }

    // CASO 2: prioridade menor que a do primeiro
    // entra no início
    if (prioridade < (*fila)->prioridade)
    {
        novoNo->next = *fila;
        *fila = novoNo;
        return;
    }

    // CASO 3: procurar posição no meio/final
    Node *atual = *fila;

    while (atual->next != NULL &&
           atual->next->prioridade <= prioridade)
    {
        atual = atual->next;
    }

    // Encaixa o novo nó
    novoNo->next = atual->next;
    atual->next = novoNo;
}

// DESENFILEIRAR
int desenfileirar(Node **fila)
{
    // Fila vazia
    if (*fila == NULL)
    {
        return -1;
    }

    Node *atual = *fila;
    Node *anterior = NULL;

    // Percorre até o último
    while (atual->next != NULL)
    {
        anterior = atual;
        atual = atual->next;
    }

    int valorRemovido = atual->valor;

    // Só existe um elemento
    if (anterior == NULL)
    {
        *fila = NULL;
    }
    else
    {
        anterior->next = NULL;
    }

    free(atual);

    return valorRemovido;
}

// IMPRIMIR
void imprimir(Node *fila)
{
    Node *atual = fila;

    while (atual != NULL)
    {
        printf(
            "Valor: %d | Prioridade: %d\n",
            atual->valor,
            atual->prioridade);

        atual = atual->next;
    }
}

int main()
{
    Node *fila = NULL;

    enfileirar(&fila, 40, 1);
    enfileirar(&fila, 10, 1);

    enfileirar(&fila, 20, 2);
    enfileirar(&fila, 50, 2);

    enfileirar(&fila, 30, 3);

    printf("Fila:\n");
    imprimir(fila);

    printf("\nRemovido: %d\n", desenfileirar(&fila));

    printf("\nDepois da remocao:\n");
    imprimir(fila);

    return 0;
}