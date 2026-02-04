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

// Funções auxiliares
int pai(int i) { return (i - 1) / 2; }
int filhoEsquerdo(int i) { return (2 * i) + 1; }
int filhoDireito(int i) { return (2 * i) + 2; }
bool estaVazia(MaxHeap *heap) { return heap->tamanho == 0; }

// Protótipos das funções
MaxHeap* criarHeap();
void destruirHeap(MaxHeap *heap);
void ajustarParaCima(MaxHeap *heap, int i);
void ajustarParaBaixo(MaxHeap *heap, int i);
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
    if (!heap) {
        printf("Erro ao alocar memória para o heap\n");
        return NULL;
    }
    
    heap->arr = (int*)malloc(CAPACIDADE_INICIAL * sizeof(int));
    if (!heap->arr) {
        free(heap);
        printf("Erro ao alocar memória para o array\n");
        return NULL;
    }
    
    heap->capacidade = CAPACIDADE_INICIAL;
    heap->tamanho = 0;
    return heap;
}

// 2. Destruir Heap (liberar memória)
void destruirHeap(MaxHeap *heap) {
    if (heap) {
        if (heap->arr) {
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

// 4. Ajustar para baixo (usado na remoção)
void ajustarParaBaixo(MaxHeap *heap, int i) {
    int maior = i;
    int esquerdo = filhoEsquerdo(i);
    int direito = filhoDireito(i);
    
    // Encontra o maior entre pai e filhos
    if (esquerdo < heap->tamanho && heap->arr[esquerdo] > heap->arr[maior]) {
        maior = esquerdo;
    }
    
    if (direito < heap->tamanho && heap->arr[direito] > heap->arr[maior]) {
        maior = direito;
    }
    
    // Se o maior não for o pai, troca e continua ajustando
    if (maior != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[maior];
        heap->arr[maior] = temp;
        
        ajustarParaBaixo(heap, maior);
    }
}

// 5. Redimensionar Heap quando necessário
void redimensionarHeap(MaxHeap *heap) {
    int novaCapacidade = heap->capacidade * FATOR_CRESCIMENTO;
    int *novoArr = (int*)realloc(heap->arr, novaCapacidade * sizeof(int));
    
    if (!novoArr) {
        printf("Erro ao redimensionar o heap\n");
        return;
    }
    
    heap->arr = novoArr;
    heap->capacidade = novaCapacidade;
    printf("Heap redimensionado para capacidade %d\n", novaCapacidade);
}

// 6. INSERÇÃO de elemento
void inserir(MaxHeap *heap, int valor) {
    if (heap->tamanho == heap->capacidade) {
        redimensionarHeap(heap);
    }
    
    // Adiciona no final
    heap->arr[heap->tamanho] = valor;
    heap->tamanho++;
    
    // Ajusta a propriedade do heap
    ajustarParaCima(heap, heap->tamanho - 1);
    
    printf("Elemento %d inserido com sucesso\n", valor);
}

// 7. REMOÇÃO do máximo (extrair raiz)
int extrairMaximo(MaxHeap *heap) {
    if (estaVazia(heap)) {
        printf("Heap vazio! Não é possível extrair máximo\n");
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
    ajustarParaBaixo(heap, 0);
    
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
        printf("Erro ao alocar memória\n");
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
        ajustarParaBaixo(heap, i);
    }
    
    printf("Heap construído a partir de array com %d elementos\n", n);
}

// 11. Imprimir heap
void imprimirHeap(MaxHeap *heap) {
    if (estaVazia(heap)) {
        printf("Heap vazio\n");
        return;
    }
    
    printf("Heap (tamanho: %d, capacidade: %d):\n", heap->tamanho, heap->capacidade);
    
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

// 12. Função principal para demonstrar o uso
int main() {
    printf("=== DEMONSTRAÇÃO ===\n\n");
    
    // Cria heap
    MaxHeap *heap = criarHeap();
    
    // 1. Teste de inserção
    printf("1. INSERINDO ELEMENTOS:\n");
    inserir(heap, 10);
    inserir(heap, 20);
    inserir(heap, 15);
    inserir(heap, 30);
    inserir(heap, 40);
    inserir(heap, 5);
    inserir(heap, 50);
    imprimirHeap(heap);
    printf("\n");
    
    // 2. Teste de remoção do máximo
    printf("2. REMOVENDO MÁXIMOS:\n");
    int max = extrairMaximo(heap);
    printf("Máximo extraído: %d\n", max);
    imprimirHeap(heap);
    
    max = extrairMaximo(heap);
    printf("Máximo extraído: %d\n", max);
    imprimirHeap(heap);
    printf("\n");
    
    // 3. Teste de remoção de elemento específico
    printf("3. REMOVENDO ELEMENTO ESPECÍFICO:\n");
    printf("Antes da remoção:\n");
    inserir(heap, 25);
    inserir(heap, 35);
    imprimirHeap(heap);
    
    // Remove o elemento na posição 2 (terceiro elemento)
    removerElemento(heap, 2);
    printf("Após remoção:\n");
    imprimirHeap(heap);
    printf("\n");
    
    // 4. Teste de delete completo
    printf("4. DELETE COMPLETO DO HEAP:\n");
    deletarHeap(heap);
    imprimirHeap(heap);
    printf("\n");
    
    // 5. Teste de construção a partir de array
    printf("5. CONSTRUÇÃO A PARTIR DE ARRAY:\n");
    int arr[] = {4, 10, 3, 5, 1, 8, 7, 2, 9, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    construirHeap(heap, arr, n);
    imprimirHeap(heap);
    
    // Limpeza
    destruirHeap(heap);
    
    return 0;
}