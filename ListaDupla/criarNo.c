#include "listaDupla.h"

No *criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->conteudo = valor;
        novoNo->prox = NULL;
        novoNo->ant = NULL;
    }else
        printf("Erro ao alocar memoria para o novo no.\n");
    return novoNo;
}