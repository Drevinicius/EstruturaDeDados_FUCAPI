#include "fila.h"


no *criarNo(int codigo, int capacidade, char *modelo, char *destino){
    no *novoNo = (no*)malloc(sizeof(no));
    if (novoNo == NULL) {
        return NULL;
    }
    novoNo->codigo = codigo;
    novoNo->capacidade = capacidade;
    strcpy(novoNo->modelo, modelo);
    strcpy(novoNo->destino, destino);
    novoNo->prox = NULL;

    return novoNo;
}

void inserirFila(no **inicio, no **fim, int codigo, int capacidade, char *modelo, char *destino){

    no *novoNo = criarNo(codigo, capacidade, modelo, destino);
    if (*inicio == NULL) {
        *inicio = novoNo;
        *fim = *inicio;
    }else{
        (*fim)->prox = novoNo;
        *fim = novoNo;
    }
}

void decolar(no **inicio){
    no *aux = (*inicio)->prox, *atual = *inicio;
    atual->prox = NULL;
    *inicio = aux;

    printf("Decolando o aviao para: %s\n", atual->destino);

    free(atual);
}

void imprimirFila(no **inicio){
    no *atual = *inicio;
    while(atual != NULL){
        printf("Codigo: %d\n", atual->codigo);
        printf("Destino: %s\n\n", atual->destino);
        atual = atual->prox;
    }
}

void contarFila(no **inicio, no **fim){
    no *aux = (*inicio)->prox, *atual = *inicio, *auxInicio = *inicio;
    int cont = 0;
    if(*inicio == NULL){
        printf("Lista vazia");
    }else{
        do{
            auxInicio = aux;
            aux = auxInicio->prox;
            atual->prox = NULL;
            (*fim)->prox = atual;
            *fim = atual;
            cont ++;
        }while(auxInicio != aux);
        printf("Quatidade no patio: %d\n", cont);
    }
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}