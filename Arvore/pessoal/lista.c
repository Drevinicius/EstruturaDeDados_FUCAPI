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

void excluirValor(no **lista, int valor){
    if(!(*lista)){
        return;
    }
    no *atual = *lista;
    no *anterior = atual;
    while(atual && atual->valor != valor){
        anterior = atual;
        atual = atual->prx;
    }
    if(atual->prx == NULL){
        anterior->prx = NULL;
    }else if(atual == anterior){
        *lista = atual->prx;
        atual->prx = NULL;
        anterior->prx = NULL;
    }else{
        anterior->prx = atual->prx;
        atual->prx = NULL;
    }
    printf("Valor %d excluido.\n", atual->valor);
    free(atual);
}

int tamanhoLista(no *lista){
    no *atual = lista;
    int tamanho = 0;
    while(atual){
        tamanho++;
        atual = atual->prx;
    }
    return tamanho;
}