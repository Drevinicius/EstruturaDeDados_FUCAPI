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
//void ajustarParaCima(MaxHeap *heap, int i);
//void ajustarParaBaixo(MaxHeap *heap, int i);
void redimensionarHeap(MaxHeap *heap);
void inserir(MaxHeap *heap, int valor);
int extrairMaximo(MaxHeap *heap);
void removerElemento(MaxHeap *heap, int i);
void deletarHeap(MaxHeap *heap);
void construirHeap(MaxHeap *heap, int arr[], int n);
void imprimirHeap(MaxHeap *heap);

// 1. Criação do Heap
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

// 2. Destruir Heap (liberar memória)
void destruirHeap(MaxHeap *heap) {
    // faço apenas se meu heap tiver elementos
    if (heap){
        if (heap->arr){ // Se o array nao for vazio eu libero a memoria dele 
            free(heap->arr);
        }
        free(heap);
    }
}

// 3. Ajustar para cima (usado na inserção)
void ajustarParaCima(MaxHeap *heap, int i) {
    while (i > 0 && heap->arr[pai(i)] < heap->arr[i]) {
        // Troca pai com filho
        int temp = heap->arr[pai(i)];
        heap->arr[pai(i)] = heap->arr[i];
        heap->arr[i] = temp;
        
        // Move para o pai
        i = pai(i);
    }
}

void downHeap(MaxHeap *arvoreHeap, int index){
    int idxEsquerda = filhoEsquerdo(index);
    int idxDireita = filhoDireito(index);
    int idxMenor = arvoreHeap->arr[idxDireita] > arvoreHeap->arr[idxEsquerda] ? idxEsquerda:idxDireita;
    if(arvoreHeap->arr[index] > arvoreHeap->arr[idxMenor]){
        int temp = arvoreHeap->arr[index];
        arvoreHeap->arr[index] = arvoreHeap->arr[idxMenor];
        arvoreHeap->arr[idxMenor] = temp;
        downHeap(arvoreHeap, idxMenor);
    }
    return;
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

// 5. Redimensionar Heap quando necessário
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

// 6. INSERÇÃO de elemento
void inserir(MaxHeap *heap, int valor) {
    if (heap->tamanho == heap->capacidade) {
        // Caso eu ja tenha atingido a capacidade maxima da minha arvore
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
        // Caso eu ja tenha atingido a capacidade maxima da minha arvore
        redimensionarHeap(heap);
    }
    
    // Adiciona no final
    heap->arr[heap->tamanho] = valor;
    heap->tamanho++;
    
    // Ajusta a propriedade do heap
    upHeap(heap, heap->tamanho - 1);
    
    // O elemento sera inserido
}

// 7. REMOÇÃO do máximo (extrair raiz)
int extrairMaximo(MaxHeap *heap) {
    if (estaVazia(heap)) {
        //Heap vazio! Não é possível extrair máximo
        return -1;
    }
    
    if (heap->tamanho == 1) {
        heap->tamanho--;
        return heap->arr[0];
    }
    
    // Guarda a raiz (máximo)
    int raiz = heap->arr[0];
    
    // Move o último elemento para a raiz
    heap->arr[0] = heap->arr[heap->tamanho - 1];
    heap->tamanho--;
    
    // Ajusta a propriedade do heap
    downHeap(heap, 0);
    
    return raiz;
}

// 8. REMOÇÃO/DELETE de elemento em posição específica
void removerElemento(MaxHeap *heap, int i) {
    if (i < 0 || i >= heap->tamanho) {
        printf("Índice %d inválido\n", i);
        return;
    }
    
    printf("Removendo elemento na posição %d (valor: %d)\n", i, heap->arr[i]);
    
    // Substitui o elemento por INT_MAX e ajusta para cima
    heap->arr[i] = __INT_MAX__;
    ajustarParaCima(heap, i);
    
    // Remove a raiz (que agora contém INT_MAX)
    extrairMaximo(heap);
}

// 9. DELETE completo do heap (remove todos os elementos)
void deletarHeap(MaxHeap *heap) {
    heap->tamanho = 0;
    printf("Todos os elementos do heap foram removidos\n");
}

// 10. Construir heap a partir de array (heapify)
void construirHeap(MaxHeap *heap, int arr[], int n) {
    // Libera array atual se existir
    if (heap->arr && heap->capacidade > 0) {
        free(heap->arr);
    }
    
    // Aloca novo array
    heap->arr = (int*)malloc(n * sizeof(int));
    if (!heap->arr) {
        // Erro ao alocar memória
        return;
    }
    
    // Copia elementos
    for (int i = 0; i < n; i++) {
        heap->arr[i] = arr[i];
    }
    
    heap->tamanho = n;
    heap->capacidade = n;
    
    // Aplica heapify a partir do último nó não-folha
    for (int i = (n / 2) - 1; i >= 0; i--) {
        downHeap(heap, i);
    }
    
    printf("Heap construído a partir de array com %d elementos\n", n);
}

// 11. Imprimir heap
void imprimirHeap(MaxHeap *heap) {
    if (estaVazia(heap)) {
        printf("Heap vazio\n");
        return;
    }
    
    //printf("Heap (tamanho: %d, capacidade: %d):\n", heap->tamanho, heap->capacidade);
    
    // Imprime como array
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
    imprimirHeap(novaArvore);

    destruirHeap(primeiraArvoreHeap);
    destruirHeap(segundaArvoreHeap);
    return 0;
}