#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int valor;
    int prioridade;
    struct Node *next;
} Node;

void inserirNaLista(Node **lista, int valor, int prioridade)
{
    Node *novoNo = (Node *)malloc(sizeof(Node));
    if (novoNo == NULL)
        return;

    novoNo->valor = valor;
    novoNo->prioridade = prioridade;
    novoNo->next = NULL;

    // Lista vazia ou prioridade maior que a do primeiro: entra na cabeça
    if (*lista == NULL || prioridade > (*lista)->prioridade)
    {
        novoNo->next = *lista;
        *lista = novoNo;
        return;
    }

    Node *atual = *lista;

    // >= mantém a ordem de chegada entre prioridades iguais (FIFO)
    while (atual->next != NULL && atual->next->prioridade >= novoNo->prioridade)
        atual = atual->next;

    // Estava faltando: liga o novo nó na posição encontrada
    novoNo->next = atual->next;
    atual->next = novoNo;
}

// Remove o elemento de maior prioridade (sempre o primeiro da lista).
// Retorna 1 se removeu, 0 se a fila estava vazia.
int desinfileirar(Node **lista, int *valor, int *prioridade)
{
    if (*lista == NULL)
        return 0;

    Node *remover = *lista;

    *valor = remover->valor;
    *prioridade = remover->prioridade;

    *lista = remover->next;
    free(remover);

    return 1;
}

void imprimirLista(Node *lista)
{
    for (Node *atual = lista; atual != NULL; atual = atual->next)
        printf("(valor=%d, prioridade=%d) ", atual->valor, atual->prioridade);
    printf("\n");
}

int main()
{
    Node *fila = NULL;

    inserirNaLista(&fila, 10, 2);
    inserirNaLista(&fila, 20, 5);
    inserirNaLista(&fila, 30, 1);
    inserirNaLista(&fila, 40, 5); // mesma prioridade do 20, fica depois dele

    printf("Fila: ");
    imprimirLista(fila);

    int valor, prioridade;
    while (desinfileirar(&fila, &valor, &prioridade))
        printf("Saiu: valor=%d, prioridade=%d\n", valor, prioridade);

    return 0;
}