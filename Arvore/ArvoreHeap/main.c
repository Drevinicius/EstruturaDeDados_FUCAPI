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
} MaxHeap;

int pai(int i) { return (i - 1) / 2; }
int filhoEsquerdo(int i) { return (2 * i) + 1; }
int filhoDireito(int i) { return (2 * i) + 2; }
bool estaVazia(MaxHeap *heap) { return heap->tamanho == 0; }

MaxHeap* criarHeap();
void destruirHeap(MaxHeap *heap);
void redimensionarHeap(MaxHeap *heap);
void inserir(MaxHeap *heap, int valor);
int extrairMaximo(MaxHeap *heap);
void removerElemento(MaxHeap *heap, int i);
void deletarHeap(MaxHeap *heap);
void construirHeap(MaxHeap *heap, int arr[], int n);
void imprimirHeap(MaxHeap *heap);

MaxHeap* criarHeap() {
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (!heap) { // Se for vazia
        // Erro ao alocar memória para o heap
        return NULL;
    }
    
    // Faço com que o array da minha arvore receba uma capacidade maxima
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




void downHeap(MaxHeap *arvoreHeap, int index){
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

void upHeap(MaxHeap *arvoreHeap, int index){
    int indexPai = pai(index);
    if(arvoreHeap->arr[index] < arvoreHeap->arr[indexPai]){
        int temp = arvoreHeap->arr[index];
        arvoreHeap->arr[index] = arvoreHeap->arr[indexPai];
        arvoreHeap->arr[indexPai] = temp;
        upHeap(arvoreHeap, indexPai); 
    }
}

void redimensionarHeap(MaxHeap *heap) {
    int novaCapacidade = heap->capacidade * FATOR_CRESCIMENTO;
    int *novoArr = (int*)realloc(heap->arr, novaCapacidade * sizeof(int));
    
    if (!novoArr) {
        //Erro ao redimensionar o heap
        return;
    }
    
    heap->arr = novoArr;
    heap->capacidade = novaCapacidade;
    printf("Heap redimensionado para capacidade %d\n", novaCapacidade);
}


void inserir(MaxHeap *heap, int valor) {
    if (heap->tamanho == heap->capacidade) {
        redimensionarHeap(heap);
    }
    
    // Adiciona no final
    heap->arr[heap->tamanho] = valor;
    heap->tamanho++;
    
    // Ajusta a propriedade do heap
    downHeap(heap, heap->tamanho - 1);
    
    // O elemento sera inserido
}

void inserirRaizMenor(MaxHeap *heap, int valor) {
    if (heap->tamanho == heap->capacidade) {
        redimensionarHeap(heap);
    }
    
    // Adiciona no final
    heap->arr[heap->tamanho] = valor;
    heap->tamanho++;
    
    // Ajusta a propriedade do heap
    upHeap(heap, heap->tamanho - 1);
    
    // O elemento sera inserido
}




// 11. Imprimir heap
void imprimirHeap(MaxHeap *heap) {
    if (estaVazia(heap)) {
        printf("Heap vazio\n");
        return;
    }

    printf("Array: [");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("%d", heap->arr[i]);
        if (i < heap->tamanho - 1) printf(", ");
    }
    printf("]\n");
    
    // Imprime como árvore (níveis)
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

/*Criar uma funcao que receba 2 arvores HEAP e um elemento
 *A funçao deve unir a 2 arvores numa nova e re-odenar seus elementos
 *de modo correto
 
 3 - 8 - 5
 2 - 4 - 6
 */

 void inserirParaRecriar(MaxHeap *novoHeap, MaxHeap *pr, MaxHeap *sc, int indexPai){
    if(indexPai >= pr->tamanho && indexPai >= sc->tamanho){
        return;
    }if(novoHeap->capacidade == novoHeap->tamanho){
        redimensionarHeap(novoHeap);
    }
    if(novoHeap->tamanho == 1){
        if(pr->tamanho > 0) {
            novoHeap->arr[novoHeap->tamanho] = pr->arr[0];
            novoHeap->tamanho++;
        }if(sc->tamanho > 0) {
            if(novoHeap->capacidade == novoHeap->tamanho){
                redimensionarHeap(novoHeap);
            }
            novoHeap->arr[novoHeap->tamanho] = sc->arr[0];
            novoHeap->tamanho++;
        }
    }
    
    int idxEsq = filhoEsquerdo(indexPai);
    int idxDir = filhoDireito(indexPai);
    
    if(idxEsq < pr->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = pr->arr[idxEsq];
        novoHeap->tamanho++;
    }if(idxDir < pr->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = pr->arr[idxDir];
        novoHeap->tamanho++;
    }if(idxEsq < sc->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = sc->arr[idxEsq];
        novoHeap->tamanho++;
    }if(idxDir < sc->tamanho){
        if(novoHeap->capacidade == novoHeap->tamanho){
            redimensionarHeap(novoHeap);
        }
        novoHeap->arr[novoHeap->tamanho] = sc->arr[idxDir];
        novoHeap->tamanho++;
    }
    inserirParaRecriar(novoHeap, pr, sc, indexPai + 1);
}

 MaxHeap *recriarHeap(MaxHeap *primeiraArvore, MaxHeap *segundaArvore, int novoElemento){
    MaxHeap *heapAgrupado = criarHeap();
    heapAgrupado->arr[0] = novoElemento;
    heapAgrupado->tamanho++;
    inserirParaRecriar(heapAgrupado,primeiraArvore, segundaArvore, 0);
    
    printf("Exibindo arvore antes do sort: \n");
    imprimirHeap(heapAgrupado);

    downHeap(heapAgrupado, 0);
    
    return heapAgrupado;
 }

int main() {    
    // Cria heap
    MaxHeap *primeiraArvoreHeap = criarHeap();
    MaxHeap *segundaArvoreHeap = criarHeap();

    inserirRaizMenor(primeiraArvoreHeap, 3);
    inserirRaizMenor(primeiraArvoreHeap, 5);
    inserirRaizMenor(primeiraArvoreHeap, 8);

    inserirRaizMenor(segundaArvoreHeap, 2);
    inserirRaizMenor(segundaArvoreHeap, 4);
    inserirRaizMenor(segundaArvoreHeap, 6);

    MaxHeap *novaArvore = recriarHeap(primeiraArvoreHeap, segundaArvoreHeap, 7);
    printf("Exibindo arvore pos sort: \n");
    imprimirHeap(novaArvore);

    destruirHeap(primeiraArvoreHeap);
    destruirHeap(segundaArvoreHeap);
    return 0;
}