#include <stdio.h>
#include <stdlib.h>

typedef struct Nodec
{
    int valor;
    struct Nodec *prox;

} Nodec;

void inserirInicio(Nodec **lista, int valor);
void removerPorValor(Nodec **lista, int valor);
void inserirNoFim(Nodec **lista, int valor);
void removerPorPosicao(Nodec **lista, int posicao);
void percorrerLista(Nodec *lista);
void liberarLista(Nodec **lista);

int main()
{

    Nodec *lista = NULL;

    inserirInicio(&lista, 20);
    inserirInicio(&lista, 10);
    inserirInicio(&lista, 90);
    inserirNoFim(&lista, 1000);

    printf("Lista inicial:\n");
    percorrerLista(lista);

    removerPorValor(&lista, 10);
    printf("\nApos removerPorValor(10):\n");
    percorrerLista(lista);

    removerPorPosicao(&lista, 0);
    printf("\nApos removerPorPosicao(0):\n");
    percorrerLista(lista);

    inserirNoFim(&lista, 30);
    inserirNoFim(&lista, 40);
    printf("\nApos inserir 30 e 40 no fim:\n");
    percorrerLista(lista);

    removerPorPosicao(&lista, 2);
    printf("\nApos removerPorPosicao(2):\n");
    percorrerLista(lista);

    removerPorPosicao(&lista, 10);
    printf("\nApos removerPorPosicao(10), fora do limite:\n");
    percorrerLista(lista);

    liberarLista(&lista);

    return 0;
}

void inserirInicio(Nodec **lista, int valor)
{

    Nodec *novoNo = malloc(sizeof(Nodec));

    if (novoNo == NULL)
        return;

    novoNo->valor = valor;

    if (*lista == NULL)
    {

        novoNo->prox = novoNo;
        *lista = novoNo;
        return;
    }

    novoNo->prox = *lista;

    Nodec *atual = *lista;

    while (atual->prox != *lista)
    {

        atual = atual->prox;
    }

    atual->prox = novoNo;
    *lista = novoNo;
}

void removerPorValor(Nodec **lista, int valor)
{
    if (lista == NULL || *lista == NULL)
    {
        return;
    }

    Nodec *atual = *lista;
    Nodec *anterior = *lista;

    /* Localiza o ultimo no, que e o anterior do primeiro. */
    while (anterior->prox != *lista)
    {
        anterior = anterior->prox;
    }

    do
    {
        if (atual->valor == valor)
        {
            if (atual->prox == atual)
            {
                *lista = NULL;
            }
            else
            {
                anterior->prox = atual->prox;

                if (atual == *lista)
                {
                    *lista = atual->prox;
                }
            }

            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    } while (atual != *lista);
}

void inserirNoFim(Nodec **lista, int valor)
{

    Nodec *novoNo = malloc(sizeof(Nodec));

    if (novoNo == NULL)
        return;

    novoNo->valor = valor;

    if (*lista == NULL)
    {

        novoNo->prox = novoNo;
        *lista = novoNo;
        return;
    }

    Nodec *atual = *lista;

    while (atual->prox != *lista)
    {
        atual = atual->prox;
    }

    novoNo->prox = *lista;
    atual->prox = novoNo;
}

void removerPorPosicao(Nodec **lista, int posicao)
{

    if (lista == NULL || *lista == NULL || posicao < 0)
    {
        return;
    }

    Nodec *atual = *lista;
    Nodec *anterior = *lista;

    /* Localiza o ultimo no, que e o anterior do primeiro. */
    while (anterior->prox != *lista)
    {
        anterior = anterior->prox;
    }

    for (int i = 0; i < posicao; i++)
    {

        anterior = atual;
        atual = atual->prox;

        /* Deu a volta completa: a posicao nao existe */
        if (atual == *lista)
        {
            return;
        }
    }

    if (atual->prox == atual)
    {
        *lista = NULL;
    }
    else
    {
        anterior->prox = atual->prox;

        if (atual == *lista)
        {
            *lista = atual->prox;
        }
    }

    free(atual);
}

void percorrerLista(Nodec *lista)
{

    if (lista == NULL)
    {
        return;
    }

    Nodec *atual = lista;

    do
    {

        printf("%d\n", atual->valor);

        atual = atual->prox;

    } while (atual != lista);
}

void liberarLista(Nodec **lista)
{

    if (*lista == NULL)
    {
        return;
    }

    Nodec *atual = (*lista)->prox;

    /* Libera todos menos a cabeca */
    while (atual != *lista)
    {

        Nodec *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    free(*lista);

    *lista = NULL;
}