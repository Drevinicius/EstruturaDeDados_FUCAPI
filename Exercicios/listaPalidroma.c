#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

void listaPalindroma(nodo **listaNormal){
    nodo *atual = *listaNormal, *listaReversa = NULL;
    bool verificar = true;
    // Inserindo minha lista de modo inverso
    while(atual != NULL){
        listaReversa = inserirInicio(&listaReversa, atual->conteudo);
        atual = atual->prox;
    }

    nodo *reverso = listaReversa;
    atual = *listaNormal;

    while(atual != NULL){
        if(reverso->conteudo != atual->conteudo){
            verificar = false;
            break;
        }
        atual = atual->prox;
        reverso = reverso->prox;
    }
    if(verificar)
        printf("Sao palindromos");
    else
        printf("nao sao palindromos");

}

int main(){
    nodo *lista = NULL;

    lista = inserirNo(&lista, 4);
    lista = inserirNo(&lista, 7);
    lista = inserirNo(&lista, 8);
    lista = inserirNo(&lista, 7);
    lista = inserirNo(&lista, 1);

    imprimirLista(lista);
    printf("\n");
    listaPalindroma(&lista);

    free(lista);
}