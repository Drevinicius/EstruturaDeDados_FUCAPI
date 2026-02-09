#include "maxHeap.h"
#include <stdlib.h>



int pai(int i) { return (i - 1) / 2; }
int filhoEsquerdo(int i) { return (2 * i) + 1; }
int filhoDireito(int i) { return (2 * i) + 2; }
bool estaVazia(MaxHeap *heap) { return heap->tamanho == 0; }

MaxHeap *iniciarlizarHeap(){
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));

    if(!heap){
        return NULL;
    }
    heap->array = (int*)malloc(CAPACIDADE_INICIAL * sizeof(int));
    if(!heap->array){
        free(heap);
        return NULL;
    }

    heap->capacidade = CAPACIDADE_INICIAL;
    heap->tamanho = 0;

    return heap;
}

void redimensionarHeap(MaxHeap *heap){
    int novaCapacidade = heap->capacidade * FATOR_CRESCIMENTO;
    int *novoArray = (int*)realloc(heap->array, novaCapacidade * sizeof(int));

    if(!novoArray){
        return;
    }

    heap->array = novoArray;
    heap->capacidade = novaCapacidade;
}

void upHeadMaxHeap(MaxHeap *heap, int indexFilho){
    int indexPai = pai(indexFilho);
    if(heap->array[indexFilho] > heap->array[indexPai]){
        int temp = heap->array[indexPai];
        heap->array[indexPai] = heap->array[indexFilho];
        heap->array[indexFilho] = temp;
        upHeadMaxHeap(heap, indexPai);
    }
}

void downHeapMazxHeap(MaxHeap *heap, int indexPai){
    /*----- Logica de down heap -----*/
}

void inserieMaxHeap(MaxHeap *heap, int valor){
    if(heap->capacidade == heap->tamanho){
        redimensionarHeap(heap);
    }
    int indexPosicao = heap->tamanho;
    heap->array[indexPosicao] = valor;
    heap->tamanho ++;

    upHeadMaxHeap(heap, indexPosicao+1);
}