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

nodo *inserirInicio(nodo **lista, int conteudo){
    nodo *novoNo = criarNo(conteudo);
    if(*lista == NULL)
        *lista = novoNo;
    else{
        nodo *atual = *lista;
        novoNo->prox = atual;
        atual->ant = novoNo;
        *lista = novoNo;
    }
    return *lista;
}

void imprimirLista(nodo *lista){
    if(lista != NULL){
        printf(" %d ", lista->conteudo);
        imprimirLista(lista->prox);
    }
}

void parImpar(nodo **lista, nodo **par, nodo **impar){
    nodo *atual, *fim;
    atual = fim  = *lista; 
    while(fim != NULL)
        fim = fim->prox;

    while(atual != NULL){
        if(atual->conteudo % 2 ==0){
            *par = inserirNo(par, atual->conteudo);
        }
        if(fim->conteudo % 2 != 0){
            *impar = inserirNo(impar, atual->conteudo);
        }
        atual = atual->prox;
        fim = fim->ant;
    }
}

int main(){
    nodo *lista = NULL, *par = NULL, *impar = NULL;

    lista = inserirNo(&lista, 4);
    lista = inserirNo(&lista, 7);
    lista = inserirNo(&lista, 2);
    lista = inserirNo(&lista, 9);
    lista = inserirNo(&lista, 6);

    parImpar(&lista, &par, &impar);

    imprimirLista(par);

    printf("\n");

    imprimirLista(impar);

    free(lista);
}