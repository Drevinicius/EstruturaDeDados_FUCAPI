#include "listaCircular.h"

No *criarNo(int conteudo){
    No *novo = (No *)malloc(sizeof(No));
    novo->posicao = 1;
    novo->valorInicial = conteudo;
    novo->prox = novo;
    return novo;
}

No *inserirFinal(No **lista, int valorInicial){
    No *novoNo = criarNo(valorInicial);
    if(*lista == NULL){
        novoNo->posicao = 1;
        *lista = novoNo;
    }else{
        No *atual = *lista;
        do{
            novoNo->posicao += 1;
            atual = atual->prox;
        }while(atual->prox != *lista);
        if(novoNo->posicao == atual->posicao){
            novoNo->posicao += 1;
        }
        atual->prox = novoNo;
        novoNo->prox = *lista;
    }
    return *lista;
}

void imprimirListaCircular(No *lista) {
if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    printf("\nSobrevivente: %d na posicao: %d\n", lista->valorInicial, lista->posicao);
}

No *excluirPosicao(No **lista, int valorInicial) {
    if (*lista == NULL || (*lista)->prox == *lista)return *lista;

    No *atual = *lista;
    No *anterior = NULL;

    while (atual->prox != atual) {
        for (int i = 1; i < valorInicial; i++) {
            anterior = atual;
            atual = atual->prox;
        }
        valorInicial = atual->valorInicial;

        printf("\tEliminado: %d na posicao: %d\n", atual->valorInicial, atual->posicao);
        anterior->prox = atual->prox;

        if (atual == *lista) {
            *lista = atual->prox;
        }

        free(atual);
        atual = anterior->prox;
    }
    return *lista;
}