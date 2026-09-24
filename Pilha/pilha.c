#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *prox;

} No;

typedef struct Pilha
{
    struct No *topo;

} Pilha;

void empilhar(Pilha *pilha, int valor);
int desempilhar(Pilha *pilha, int *valor);
int consultarTopo(Pilha *pilha, int *valor);
int estaVazia(Pilha *pilha);
void imprimirPilha(Pilha *pilha);
void liberarPilha(Pilha *pilha);

int main()
{

    Pilha pilha;

    pilha.topo = NULL;

    empilhar(&pilha, 10);
    empilhar(&pilha, 20);
    empilhar(&pilha, 30);

    printf("Pilha (topo -> base): ");
    imprimirPilha(&pilha);

    int valor;

    if (consultarTopo(&pilha, &valor))
        printf("Topo: %d\n", valor);

    if (desempilhar(&pilha, &valor))
        printf("Desempilhou: %d\n", valor);

    empilhar(&pilha, 40);
    printf("Apos empilhar 40: ");
    imprimirPilha(&pilha);

    while (desempilhar(&pilha, &valor))
        printf("Saiu: %d\n", valor);

    printf("Pilha vazia? %s\n", estaVazia(&pilha) ? "Sim" : "Nao");

    liberarPilha(&pilha);

    return 0;
}

void empilhar(Pilha *pilha, int valor)
{

    No *novoNo = (No *)malloc(sizeof(No));

    if (novoNo == NULL)
    {
        return;
    }

    novoNo->valor = valor;

    // Insere no inicio da lista: o novo no vira o topo
    novoNo->prox = pilha->topo;
    pilha->topo = novoNo;
}

// Remove o elemento do topo.
// Retorna 1 se removeu, 0 se a pilha estava vazia.
int desempilhar(Pilha *pilha, int *valor)
{

    if (pilha->topo == NULL)
    {
        return 0;
    }

    No *remover = pilha->topo;

    *valor = remover->valor;
    pilha->topo = remover->prox;

    free(remover);

    return 1;
}

// Le o topo sem remover.
// Retorna 1 se leu, 0 se a pilha estava vazia.
int consultarTopo(Pilha *pilha, int *valor)
{

    if (pilha->topo == NULL)
    {
        return 0;
    }

    *valor = pilha->topo->valor;

    return 1;
}

int estaVazia(Pilha *pilha)
{

    return pilha->topo == NULL;
}

void imprimirPilha(Pilha *pilha)
{

    for (No *atual = pilha->topo; atual != NULL; atual = atual->prox)
        printf("%d ", atual->valor);

    printf("\n");
}

void liberarPilha(Pilha *pilha)
{

    No *atual = pilha->topo;

    while (atual != NULL)
    {

        No *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    pilha->topo = NULL;
}