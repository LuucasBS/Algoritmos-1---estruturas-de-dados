#include <stdio.h>
#include <stdlib.h>

typedef struct Heap
{
    int *dados;
    int tamanho;
    int capacidade;

} Heap;

Heap *criarHeap(int capacidade);
int inserir(Heap *heap, int valor);
int removerMaximo(Heap *heap, int *valor);
int consultarTopo(Heap *heap, int *valor);
int estaVazio(Heap *heap);
void imprimirHeap(Heap *heap);
void liberarHeap(Heap **heap);
void subir(int *v, int i);
void descer(int *v, int n, int i);
void heapSort(int *v, int n);

int main()
{

    Heap *heap = criarHeap(10);

    if (heap == NULL)
        return 1;

    inserir(heap, 10);
    inserir(heap, 40);
    inserir(heap, 30);
    inserir(heap, 5);
    inserir(heap, 50);
    inserir(heap, 20);

    printf("Heap (vetor): ");
    imprimirHeap(heap);

    int valor;

    if (consultarTopo(heap, &valor))
        printf("Topo: %d\n", valor);

    if (removerMaximo(heap, &valor))
        printf("Removeu: %d\n", valor);

    printf("Apos remover: ");
    imprimirHeap(heap);

    while (removerMaximo(heap, &valor))
        printf("Saiu: %d\n", valor);

    printf("Heap vazio? %s\n", estaVazio(heap) ? "Sim" : "Nao");

    liberarHeap(&heap);

    int v[] = {12, 3, 19, 7, 1, 25, 8};
    int n = sizeof(v) / sizeof(v[0]);

    heapSort(v, n);

    printf("\nHeapSort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");

    return 0;
}

Heap *criarHeap(int capacidade)
{

    Heap *heap = (Heap *)malloc(sizeof(Heap));

    if (heap == NULL)
    {
        return NULL;
    }

    heap->dados = (int *)malloc(capacidade * sizeof(int));

    if (heap->dados == NULL)
    {
        free(heap);
        return NULL;
    }

    heap->tamanho = 0;
    heap->capacidade = capacidade;

    return heap;
}

// Sobe o elemento enquanto ele for maior que o pai
void subir(int *v, int i)
{

    while (i > 0)
    {

        int pai = (i - 1) / 2;

        if (v[pai] >= v[i])
        {
            break;
        }

        int temp = v[pai];
        v[pai] = v[i];
        v[i] = temp;

        i = pai;
    }
}

// Desce o elemento enquanto algum filho for maior que ele.
// n e o tamanho considerado do heap (usado tambem no heapSort).
void descer(int *v, int n, int i)
{

    while (1)
    {

        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;
        int maior = i;

        if (esquerda < n && v[esquerda] > v[maior])
        {
            maior = esquerda;
        }

        if (direita < n && v[direita] > v[maior])
        {
            maior = direita;
        }

        if (maior == i)
        {
            break;
        }

        int temp = v[i];
        v[i] = v[maior];
        v[maior] = temp;

        i = maior;
    }
}

// Retorna 1 se inseriu, 0 se o heap estava cheio (overflow).
int inserir(Heap *heap, int valor)
{

    if (heap->tamanho == heap->capacidade)
    {
        return 0;
    }

    // Coloca no fim do vetor e sobe ate a posicao correta
    heap->dados[heap->tamanho] = valor;
    subir(heap->dados, heap->tamanho);
    heap->tamanho++;

    return 1;
}

// Remove o maior elemento (a raiz).
// Retorna 1 se removeu, 0 se o heap estava vazio.
int removerMaximo(Heap *heap, int *valor)
{

    if (heap->tamanho == 0)
    {
        return 0;
    }

    *valor = heap->dados[0];

    // O ultimo elemento vira a raiz e desce ate a posicao correta
    heap->tamanho--;
    heap->dados[0] = heap->dados[heap->tamanho];
    descer(heap->dados, heap->tamanho, 0);

    return 1;
}

// Le a raiz sem remover.
int consultarTopo(Heap *heap, int *valor)
{

    if (heap->tamanho == 0)
    {
        return 0;
    }

    *valor = heap->dados[0];

    return 1;
}

int estaVazio(Heap *heap)
{

    return heap->tamanho == 0;
}

void imprimirHeap(Heap *heap)
{

    for (int i = 0; i < heap->tamanho; i++)
        printf("%d ", heap->dados[i]);

    printf("\n");
}

void liberarHeap(Heap **heap)
{

    if (*heap == NULL)
    {
        return;
    }

    free((*heap)->dados);
    free(*heap);

    *heap = NULL;
}

void heapSort(int *v, int n)
{

    // 1) Constroi o heap maximo (de baixo para cima, comecando no ultimo pai)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        descer(v, n, i);
    }

    // 2) Troca a raiz (maior) com o ultimo e reduz o heap
    for (int fim = n - 1; fim > 0; fim--)
    {

        int temp = v[0];
        v[0] = v[fim];
        v[fim] = temp;

        descer(v, fim, 0);
    }
}