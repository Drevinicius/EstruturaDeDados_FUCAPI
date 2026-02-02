#include "lista.h"


no * criarNo(int conteudo){
    no *novo = (no *) malloc(sizeof(no));
    novo->conteudo = conteudo;
    novo->prox = NULL;
    return novo;
}

int busca(no *prim, int chave){
    while (prim!=NULL){
        if (prim->conteudo==chave)
            return 1;
        prim = prim->prox;
    }
    return 0;
}
