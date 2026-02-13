#include "minHeap.h"

// Funcoes auxiliares para calcular folhas e pai
int pai(int i) { return (i - 1) / 2; }
int filhoEsquerdo(int i) { return (2 * i) + 1; }
int filhoDireito(int i) { return (2 * i) + 2; }
bool estaVazia(MinHeap *heap) { return heap->tamanho == 0; }

MinHeap* criarHeap() {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) { // Se for vazia
        // Erro ao alocar memória para o heap
        return NULL;
    }
    // Faço com que o array da minha arvore receba uma capacidade Minima
    heap->arr = (int*)malloc(CAPACIDADE_INICIAL * sizeof(int));
    if (!heap->arr) {
        free(heap); // Libera a arvore heap e retorna NULL
        // Erro ao alocar memória para o array
        return NULL;
    }
    
    // Se nao termina de configurar o resto da minha arvore
    // com capacidade e o tamanho atual 0
    heap->capacidade = CAPACIDADE_INICIAL;
    heap->tamanho = 0;
    return heap; // Retorna minha locaçao de memoria
}

// Down Heap para uma Min heap
void downHeap(MinHeap *arvoreHeap, int index){
    int menor = index;
    int idxEsquerda = filhoEsquerdo(index);
    int idxDireita = filhoDireito(index);

    if (idxEsquerda < arvoreHeap->tamanho && arvoreHeap->arr[idxEsquerda] < arvoreHeap->arr[menor]) {
        menor = idxEsquerda;
    }
    if (idxDireita < arvoreHeap->tamanho && arvoreHeap->arr[idxDireita] < arvoreHeap->arr[menor]) {
        menor = idxDireita;
    }
    if(menor != index){
        int temp = arvoreHeap->arr[index];
        arvoreHeap->arr[index] = arvoreHeap->arr[menor];
        arvoreHeap->arr[menor] = temp;
        downHeap(arvoreHeap, menor);
    }
}

// Up heap para um Mim heap
void upHeap(MinHeap *arvoreHeap, int index){
    int indexPai = pai(index);
    if(arvoreHeap->arr[index] < arvoreHeap->arr[indexPai]){
        int temp = arvoreHeap->arr[index];
        arvoreHeap->arr[index] = arvoreHeap->arr[indexPai];
        arvoreHeap->arr[indexPai] = temp;
        upHeap(arvoreHeap, indexPai); 
    }
}

// Aumento a locacao do meu vetor caso eu atinja a capacidade e dobro a capacidade
void redimensionarHeap(MinHeap *heap) {
    int novaCapacidade = heap->capacidade * FATOR_CRESCIMENTO;
    int *novoArr = (int*)realloc(heap->arr, novaCapacidade * sizeof(int));
    
    if (!novoArr) {
        return;
    }
    
    heap->arr = novoArr;
    heap->capacidade = novaCapacidade;
}

// Metodo de insercao e ajuste como upHeap
void inserirMinHeap(MinHeap *heap, int valor) {
    if (heap->tamanho == heap->capacidade) {
        redimensionarHeap(heap);
    }
    
    heap->arr[heap->tamanho] = valor;
    heap->tamanho++;
    
    upHeap(heap, heap->tamanho - 1);
}

// Funcao que recebe a arvore e imprime como array e formato de arvore
void imprimirHeap(MinHeap *heap) {
    if (estaVazia(heap)) {
        printf("Heap vazio\n");
        return;
    }
    // Primeiro imprimo meu array
    printf("Array: [");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("%d", heap->arr[i]);
        if (i < heap->tamanho - 1) printf(", ");
    }
    printf("]\n");
    
    // Segundo imprimo como árvore por níveis
    printf("Estrutura de árvore:\n");
    int nivel = 0;
    int elementosNoNivel = 1;
    int contador = 0;
    
    for (int i = 0; i < heap->tamanho; i++) {
        printf("%d ", heap->arr[i]);
        contador++;
        
        if (contador == elementosNoNivel) {
            printf("\n");
            nivel++;
            elementosNoNivel *= 2;
            contador = 0;
        }
    }
    if (contador > 0) printf("\n");
}

// Funcao que pega 2 arvores heap e uni a uma terceira de forma sequencial
void unirArvoresHeap(MinHeap *novoHeap, MinHeap *primeiroHeap, MinHeap *secundoHeap, int novoElemento, int indexPai, bool verOriginal){
    if(indexPai >= primeiroHeap->tamanho && indexPai >= secundoHeap->tamanho){
        return;
    }if(novoHeap->capacidade == novoHeap->tamanho){
        redimensionarHeap(novoHeap);
    }
    if(novoHeap->tamanho == 0){
        novoHeap->arr[0] = novoElemento;
        novoHeap->tamanho++; 
    }
    if(novoHeap->tamanho == 1){
        if(primeiroHeap->tamanho > 0) {
            novoHeap->arr[novoHeap->tamanho] = primeiroHeap->arr[0];
            novoHeap->tamanho++;
        }if(secundoHeap->tamanho > 0) {
            if(novoHeap->capacidade == novoHeap->tamanho){
                redimensionarHeap(novoHeap);
            }
            novoHeap->arr[novoHeap->tamanho] = secundoHeap->arr[0];
            novoHeap->tamanho++;
        }
    }
    
    int idxEsq = filhoEsquerdo(indexPai);
    int idxDir = filhoDireito(indexPai);
    
    if(idxEsq < primeiroHeap->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = primeiroHeap->arr[idxEsq];
        novoHeap->tamanho++;
    }if(idxDir < primeiroHeap->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = primeiroHeap->arr[idxDir];
        novoHeap->tamanho++;
    }if(idxEsq < secundoHeap->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = secundoHeap->arr[idxEsq];
        novoHeap->tamanho++;
    }if(idxDir < secundoHeap->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = secundoHeap->arr[idxDir];
        novoHeap->tamanho++;
    }
    if(primeiroHeap->tamanho + secundoHeap->tamanho+1 == novoHeap->tamanho){
        if(verOriginal){
            //verOriginal = false;
            printf("Exibindo array original: \n");
            imprimirHeap(novoHeap);
        }
        downHeap(novoHeap, 0);
        return;
    }
    unirArvoresHeap(novoHeap, primeiroHeap, secundoHeap, novoElemento, indexPai + 1, verOriginal);
}

