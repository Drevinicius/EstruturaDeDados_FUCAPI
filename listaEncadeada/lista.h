#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int conteudo;
    struct nodo *prox;
}no;

no * criarNo(int conteudo);
no * inserirNodos(no **lista);
no * inserirNodosFinal(no **lista, int conteudo);
no * inserirNodosInicio(no **lista, int conteudo);
no * removerNodos(no **lista, int conteudo);
int busca(no *prim, int chave);
void imprimirLista(no *lista);
void imprimirReverse(no *lista);
void imprimeListaRecursiva(no *lista);

#endif // LISTA_H_INCLUDED
