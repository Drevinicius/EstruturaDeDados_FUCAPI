#include "minHeap.h"

int main() {    
    // Cria heap
    MinHeap *primeiraArvoreHeap = criarHeap();
    MinHeap *segundaArvoreHeap = criarHeap();

    inserirMinHeap(primeiraArvoreHeap, 3);
    inserirMinHeap(primeiraArvoreHeap, 5);
    inserirMinHeap(primeiraArvoreHeap, 8);

    inserirMinHeap(segundaArvoreHeap, 2);
    inserirMinHeap(segundaArvoreHeap, 4);
    inserirMinHeap(segundaArvoreHeap, 6);

    MinHeap *novaArvore = criarHeap();
    unirArvoresHeap(novaArvore, primeiraArvoreHeap, segundaArvoreHeap, 7, 0, true);

    printf("Exibindo arvore pos sort: \n");
    imprimirHeap(novaArvore);

    //destruirHeap(primeiraArvoreHeap);
    //destruirHeap(segundaArvoreHeap);
    free(primeiraArvoreHeap);
    free(segundaArvoreHeap);
    return 0;
}