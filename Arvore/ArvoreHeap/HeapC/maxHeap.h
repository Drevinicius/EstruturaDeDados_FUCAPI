#ifndef MAXHEAP_H_INCLUDED
#define MAXHEAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPACIDADE_INICIAL 10
#define FATOR_CRESCIMENTO 2

typedef struct{
    int *array;
    int capacidade;
    int tamanho;
}MaxHeap;

MaxHeap *criarHeap();

#endif