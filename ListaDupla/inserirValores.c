#include "listaDupla.h"
#include "criarNo.c"

No *inserirInicio(No **lista, int conteudo){
    No *novoNo = criarNo(conteudo);
    if(*lista == NULL)
        *lista = novoNo;
    else{
        No *atual = *lista;
        novoNo->prox = atual;
        atual->ant = novoNo;
        *lista = novoNo;
    }
    return *lista;
}

No *inserirFinal(No **lista, int conteudo){
    No *novoNo = criarNo(conteudo);
    if(*lista == NULL)
        *lista = novoNo;
    else{
        No *atual = *lista;
        while(atual->prox != NULL)
            atual = atual->prox;
        atual->prox = novoNo;
        novoNo->ant = atual;
    }
    return *lista;
}

No *inserirPosicao(No **lista, int conteudo, int posicao){
    No *novoNo = criarNo(conteudo);
    if(*lista ==NULL)
        *lista = novoNo;
    else{
        if(posicao == 1)
            *lista = inserirInicio(*(&lista), conteudo);
        else{
            int pos = 2;
            No *atual = (*lista)->prox, *anterior = *lista;
            while(atual != NULL && pos < posicao){
                atual = atual->prox;
                anterior = anterior->prox;
                pos++;
            }
            if(atual == NULL)
                *lista = inserirFinal(*(&lista), conteudo);
            else{
                atual->ant = novoNo;
                anterior->prox = novoNo;
                novoNo->ant = anterior;
                novoNo->prox = atual;
            }
        }
    }
    return *lista;
}