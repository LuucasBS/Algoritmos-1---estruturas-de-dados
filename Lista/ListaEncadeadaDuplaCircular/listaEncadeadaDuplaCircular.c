#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{

    struct Node *prev;
    struct Node *next;
    int valor;

} Node;

void adicionarNoInicio(Node **lista, int valor);

void adicionarNoFinal(Node **lista, int valor);

void removerNoInicio(Node **lista);

void removerNoFinal(Node **lista);

Node *buscarValor(Node *lista, int valor);

void removerPorValor(Node **lista, int valor);

void percorrerParaFrente(Node *lista);

void percorrerParaTras(Node *lista);

void liberarLista(Node **lista);

int main()
{

    Node *lista = NULL;

    adicionarNoInicio(&lista, 20);
    adicionarNoInicio(&lista, 10);
    adicionarNoInicio(&lista, 90);
    adicionarNoFinal(&lista, 1000);

    printf("Lista inicial (frente):\n");
    percorrerParaFrente(lista);

    printf("\nLista inicial (tras):\n");
    percorrerParaTras(lista);

    removerNoInicio(&lista);
    printf("\nApos removerNoInicio:\n");
    percorrerParaFrente(lista);

    removerNoFinal(&lista);
    printf("\nApos removerNoFinal:\n");
    percorrerParaFrente(lista);

    adicionarNoFinal(&lista, 30);
    adicionarNoFinal(&lista, 40);
    printf("\nApos adicionar 30 e 40 no final:\n");
    percorrerParaFrente(lista);

    Node *encontrado = buscarValor(lista, 30);
    if (encontrado != NULL)
        printf("\nValor %d encontrado\n", encontrado->valor);
    else
        printf("\nValor 30 nao encontrado\n");

    removerPorValor(&lista, 30);
    printf("\nApos removerPorValor(30) (frente):\n");
    percorrerParaFrente(lista);

    printf("\nApos removerPorValor(30) (tras):\n");
    percorrerParaTras(lista);

    liberarLista(&lista);

    return 0;
}

void adicionarNoInicio(Node **lista, int valor)
{

    Node *novoNo = (Node *)malloc(sizeof(Node));

    if (novoNo == NULL)
    {
        return;
    }

    novoNo->valor = valor;

    // Lista vazia: o no aponta para si mesmo nos dois sentidos
    if (*lista == NULL)
    {

        novoNo->next = novoNo;
        novoNo->prev = novoNo;
        *lista = novoNo;
        return;
    }

    Node *ultimo = (*lista)->prev; // em lista circular, o ultimo e o prev da cabeca

    novoNo->next = *lista;
    novoNo->prev = ultimo;

    ultimo->next = novoNo;
    (*lista)->prev = novoNo;

    *lista = novoNo; // o novo no vira a cabeca
}

void adicionarNoFinal(Node **lista, int valor)
{

    Node *novoNo = (Node *)malloc(sizeof(Node));

    if (novoNo == NULL)
    {
        return;
    }

    novoNo->valor = valor;

    if (*lista == NULL)
    {

        novoNo->next = novoNo;
        novoNo->prev = novoNo;
        *lista = novoNo;
        return;
    }

    Node *ultimo = (*lista)->prev;

    novoNo->next = *lista;
    novoNo->prev = ultimo;

    ultimo->next = novoNo;
    (*lista)->prev = novoNo;

    // Diferente do inicio: a cabeca continua a mesma
}

void removerNoInicio(Node **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Node *remover = *lista;

    // Unico no da lista
    if (remover->next == remover)
    {
        free(remover);
        *lista = NULL;
        return;
    }

    Node *ultimo = remover->prev;

    *lista = remover->next;
    (*lista)->prev = ultimo;
    ultimo->next = *lista;

    free(remover);
}

void removerNoFinal(Node **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Node *ultimo = (*lista)->prev;

    // Unico no da lista
    if (ultimo == *lista)
    {
        free(ultimo);
        *lista = NULL;
        return;
    }

    Node *penultimo = ultimo->prev;

    penultimo->next = *lista;
    (*lista)->prev = penultimo;

    free(ultimo);
}

Node *buscarValor(Node *lista, int valor)
{

    if (lista == NULL)
    {
        return NULL;
    }

    Node *atual = lista;

    // do-while: como a lista e circular, o criterio de parada
    // e voltar para a cabeca, e nao chegar em NULL
    do
    {

        if (atual->valor == valor)
        {
            return atual;
        }

        atual = atual->next;

    } while (atual != lista);

    return NULL;
}

void removerPorValor(Node **lista, int valor)
{

    Node *remover = buscarValor(*lista, valor);

    if (remover == NULL)
    {
        return;
    }

    // Unico no da lista
    if (remover->next == remover)
    {
        free(remover);
        *lista = NULL;
        return;
    }

    remover->prev->next = remover->next;
    remover->next->prev = remover->prev;

    // Se removeu a cabeca, a proxima vira a nova cabeca
    if (remover == *lista)
    {
        *lista = remover->next;
    }

    free(remover);
}

void percorrerParaFrente(Node *lista)
{

    if (lista == NULL)
    {
        return;
    }

    Node *atual = lista;

    do
    {

        printf("%d\n", atual->valor);

        atual = atual->next;

    } while (atual != lista);
}

void percorrerParaTras(Node *lista)
{

    if (lista == NULL)
    {
        return;
    }

    Node *ultimo = lista->prev; // nao precisa varrer ate o fim, o prev da cabeca ja e o ultimo

    Node *atual = ultimo;

    do
    {

        printf("%d\n", atual->valor);

        atual = atual->prev;

    } while (atual != ultimo);
}

void liberarLista(Node **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Node *atual = (*lista)->next;

    // Libera todos menos a cabeca
    while (atual != *lista)
    {

        Node *proximo = atual->next;

        free(atual);

        atual = proximo;
    }

    free(*lista);

    *lista = NULL;
}