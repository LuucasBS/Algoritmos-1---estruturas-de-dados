#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int valor;
    struct Node *prox;

} Node;

void inserirNoInicio(Node **head, int valor);

void percorrerLista(Node *lista);

void inserirNoFim(Node **lista, int valor);

void removerNoInicio(Node **lista);

void removerNoFim(Node **lista);

Node *buscarValor(Node *lista, int valor);

void removerPorValor(Node **lista, int valor);

void liberarLista(Node **lista);

int main()
{

    Node *head = NULL;

    inserirNoInicio(&head, 20);
    inserirNoInicio(&head, 10);
    inserirNoInicio(&head, 90);
    inserirNoFim(&head, 1000);

    printf("Lista inicial:\n");
    percorrerLista(head);

    removerNoInicio(&head);
    printf("\nApos removerNoInicio:\n");
    percorrerLista(head);

    removerNoFim(&head);
    printf("\nApos removerNoFim:\n");
    percorrerLista(head);

    inserirNoFim(&head, 30);
    inserirNoFim(&head, 40);
    printf("\nApos inserir 30 e 40 no fim:\n");
    percorrerLista(head);

    Node *encontrado = buscarValor(head, 30);
    if (encontrado != NULL)
        printf("\nValor %d encontrado\n", encontrado->valor);
    else
        printf("\nValor 30 nao encontrado\n");

    removerPorValor(&head, 30);
    printf("\nApos removerPorValor(30):\n");
    percorrerLista(head);

    liberarLista(&head);

    return 0;
}

void inserirNoInicio(Node **head, int valor)
{

    Node *novoNo = (Node *)malloc(sizeof(Node));

    if (novoNo == NULL)
    {
        return;
    }

    novoNo->valor = valor;

    novoNo->prox = *head;
    *head = novoNo;
}

void percorrerLista(Node *lista)
{

    Node *atual = lista;

    while (atual != NULL)
    {

        printf("%d\n", atual->valor);

        atual = atual->prox;
    }
}

void inserirNoFim(Node **lista, int valor)
{

    Node *novoNo = malloc(sizeof(Node));

    if (novoNo == NULL)
    {
        return;
    }

    novoNo->valor = valor;
    novoNo->prox = NULL;

    Node *atual = *lista;

    if (*lista == NULL)
    {

        *lista = novoNo;
        return;
    }

    while (atual->prox != NULL)
    {

        atual = atual->prox;
    }

    atual->prox = novoNo;
}

void removerNoInicio(Node **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Node *atual = *lista;

    *lista = atual->prox;

    free(atual);
}

void removerNoFim(Node **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Node *atual = *lista;

    if (atual->prox == NULL)
    {
        free(atual);
        *lista = NULL;
        return;
    }

    while (atual->prox && atual->prox->prox) // se tiver proximo e for o penultimo.
    {
        atual = atual->prox;
    }

    Node *temp = atual->prox;

    free(temp);

    atual->prox = NULL;
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

        atual = atual->prox;
    }

    return NULL;
}

void removerPorValor(Node **lista, int valor)
{

    if (*lista == NULL)
        return;

    Node *atual = *lista;
    Node *anterior = NULL;

    while (atual != NULL)
    {

        if (atual->valor == valor)
        {

            if (atual == *lista)
            {

                *lista = atual->prox;

                free(atual);
                return;
            }

            anterior->prox = atual->prox;
            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return;
}

void liberarLista(Node **lista)
{

    Node *atual = *lista;

    while (atual != NULL)
    {

        Node *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    *lista = NULL;
}