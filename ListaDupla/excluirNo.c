#include "listaDupla.h"

No *excluirNo(No **lista, int conteudo){
    No *atual = *lista;
    while(atual != NULL && atual->conteudo != conteudo)
        atual = atual->prox;
    if(atual != NULL){
        if(atual->ant != NULL)
            atual->ant->prox = atual->prox;
        else
            *lista = atual->prox;
        if(atual->prox != NULL)
            atual->prox->ant = atual->ant;
        free(atual);
    }
    return *lista;
}




