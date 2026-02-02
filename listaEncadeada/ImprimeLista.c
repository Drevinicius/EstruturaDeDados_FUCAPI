#include "lista.h"


void imprimirLista(no *lista){
    while (lista!=NULL){
        printf(" : %d", lista->conteudo);
        lista = lista->prox;
    }
}

int somarLista(no *lista){
    int soma=0;
    while (lista!=NULL){
        soma = soma + lista->conteudo;
        lista = lista->prox;
    }
    return soma;
}

void imprimeListaRecursiva(no *lista)
{
    if (lista != NULL)   {
        printf(" : %d", lista->conteudo);
        imprimeListaRecursiva(lista->prox);
    }
}

void imprimirReverse(no *lista){
    if (lista!=NULL){
        imprimirReverse(lista->prox);
        printf(" : %d", lista->conteudo);
    }
}
