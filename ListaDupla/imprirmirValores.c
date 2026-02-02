#include "listaDupla.h"

void imprimirValor(No *lista){
    if(lista != NULL){
        printf("%d ", lista->conteudo);
        imprimirValor(lista->prox);
    }
}

void imprimirValorReverse(No *lista){
    if(lista != NULL){
        imprimirValorReverse(lista->prox);
        printf("%d ", lista->conteudo);
    }
}