#include "metodo.h"

no *criarNoLista(int vlr){
    no *novo = (no *) malloc(sizeof(no));
    novo->valor = vlr;
    novo->prx = NULL;
    return novo;
}

void inserirNoLista(no **lista, int vlr){
    if(!(*lista)){
        *lista = criarNoLista(vlr);
        return;
    }
    no *novo = criarNoLista(vlr);
    no *atual = *lista;
    while(atual->prx != NULL){
        atual = atual->prx;
    }
    atual->prx = novo;
}

void exibirLista(no *lista){
    if(!lista){
        return;
    }
    no *atual = lista;
    while(atual){
        printf("%d ", atual->valor);
        atual = atual->prx;
    }
    printf("\n");
}
