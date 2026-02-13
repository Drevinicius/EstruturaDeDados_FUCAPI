#ifndef METODO_H_INCLUDED
#define METODO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPACIDADE_INICIAL 10
#define FATOR_CRESCIMENTO 2

// Estrutura do Heap
typedef struct {
    int *arr;        // Array para armazenar os elementos
    int capacidade;  // Capacidade máxima atual
    int tamanho;     // Número atual de elementos
} MinHeap;

// Funcoes principais
MinHeap* criarHeap();
//void destruirHeap(MinHeap *heap);
void redimensionarHeap(MinHeap *heap);
void inserirMinHeap(MinHeap *heap, int valor);
void imprimirHeap(MinHeap *heap);
void unirArvoresHeap(MinHeap *novoHeap, MinHeap *primeiroHeap, MinHeap *secundoHeap, int novoElemento, int indexPai, bool verOriginal);

#endif