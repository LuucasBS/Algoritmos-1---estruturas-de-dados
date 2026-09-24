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
    novoNo->next = *lista;
    novoNo->prev = NULL;

    if (*lista != NULL)
    {
        (*lista)->prev = novoNo;
    }

    *lista = novoNo;
}

void adicionarNoFinal(Node **lista, int valor)
{

    Node *novoNo = (Node *)malloc(sizeof(Node));

    if (novoNo == NULL)
    {
        return;
    }

    novoNo->valor = valor;
    novoNo->next = NULL;

    if (*lista == NULL)
    {

        novoNo->prev = NULL;
        *lista = novoNo;
        return; // Estava faltando: sem isso o no apontava para si mesmo
    }

    Node *atual = *lista;

    while (atual->next != NULL)
    {
        atual = atual->next;
    }

    atual->next = novoNo;
    novoNo->prev = atual;
}

void removerNoInicio(Node **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Node *remover = *lista;

    *lista = remover->next;

    // Se sobrou algum no, ele vira a nova cabeca e nao tem anterior
    if (*lista != NULL)
    {
        (*lista)->prev = NULL;
    }

    free(remover);
}

void removerNoFinal(Node **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Node *atual = *lista;

    while (atual->next != NULL)
    {
        atual = atual->next;
    }

    // Se nao tem anterior, era o unico no da lista
    if (atual->prev == NULL)
    {
        *lista = NULL;
    }
    else
    {
        atual->prev->next = NULL;
    }

    free(atual);
}

Node *buscarValor(Node *lista, int valor)
{

    Node *atual = lista;

    while (atual != NULL)
    {

        if (atual->valor == valor)
        {
            return atual;
        }

        atual = atual->next;
    }

    return NULL;
}

void removerPorValor(Node **lista, int valor)
{

    Node *remover = buscarValor(*lista, valor);

    if (remover == NULL)
    {
        return;
    }

    // Religa o anterior (ou atualiza a cabeca)
    if (remover->prev != NULL)
    {
        remover->prev->next = remover->next;
    }
    else
    {
        *lista = remover->next;
    }

    // Religa o proximo
    if (remover->next != NULL)
    {
        remover->next->prev = remover->prev;
    }

    free(remover);
}

void percorrerParaFrente(Node *lista)
{

    Node *atual = lista;

    while (atual != NULL)
    {

        printf("%d\n", atual->valor);

        atual = atual->next;
    }
}

void percorrerParaTras(Node *lista)
{

    if (lista == NULL)
    {
        return;
    }

    Node *atual = lista;

    // Vai ate o ultimo no
    while (atual->next != NULL)
    {
        atual = atual->next;
    }

    // Volta usando o prev
    while (atual != NULL)
    {

        printf("%d\n", atual->valor);

        atual = atual->prev;
    }
}

void liberarLista(Node **lista)
{

    Node *atual = *lista;

    while (atual != NULL)
    {

        Node *proximo = atual->next;

        free(atual);

        atual = proximo;
    }

    *lista = NULL;
}