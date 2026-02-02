#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
    int conteudo;
    struct  nodo *prox;
    struct nodo *ant;
}nodo;

nodo *criarNo(int conteudo){
    nodo *novo = (nodo*)malloc(sizeof(nodo));
    if(novo !=NULL){
        novo->conteudo = conteudo;
        novo->prox = NULL;
        novo->ant = NULL;
    }
    else
        printf("Erro de locacao");
    return novo;
}

nodo *inserirNo(nodo **lista, int conteudo){
    nodo *novo = criarNo(conteudo);
    if(*lista == NULL)
        *lista = novo;
    else{
        nodo *atual = *lista;
        while(atual->prox != NULL)
            atual = atual->prox;
        atual->prox = novo;
        novo->ant = atual;
    }
    return *lista;
}

void imprimirLista(nodo *lista){
    if(lista != NULL){
        printf(" %d ", lista->conteudo);
        imprimirLista(lista->prox);
    }
}

nodo *trocarListaParImpar(nodo **lista){
    if (lista == NULL || *lista == NULL || (*lista)->prox == NULL)
        return *lista;

    nodo *atual = *lista;
    nodo *inicio = atual->prox; // após a primeira troca, o segundo vira a nova cabeça

    while (atual != NULL && atual->prox != NULL) {
        nodo *first = atual;
        nodo *second = atual->prox;
        nodo *next = second->prox;

        // conectar second ao anterior de first
        second->ant = first->ant;
        second->prox = first;
        if (second->ant != NULL)
            second->ant->prox = second;

        // conectar first após second
        first->ant = second;
        first->prox = next;
        if (next != NULL)
            next->ant = first;

        // avançar dois nós
        atual = next;
    }

    return inicio != NULL ? inicio : *lista;
}

int main(){
    nodo *lista = NULL;

    lista = inserirNo(&lista, 9);
    lista = inserirNo(&lista, 3);
    lista = inserirNo(&lista, 6);
    lista = inserirNo(&lista, 5);
    lista = inserirNo(&lista, 2);
    lista = inserirNo(&lista, 1);

    imprimirLista(lista);
    printf("\n\n");

    lista = trocarListaParImpar(&lista);
    
    imprimirLista(lista);

    free(lista);
}