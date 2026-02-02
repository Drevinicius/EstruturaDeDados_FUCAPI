#include "lista.h"

no * inserirNodos(no **lista){
    no *inicio, *p;
    int n[11] = {8,1,2,3,4,5,6}, i;
    //printf("%p\n",&p);
    for (i=0;i<7;i++){
        if (*lista==NULL){
            p = criarNo(n[i]);
            //printf("%p\n",p);
            inicio = *lista = p;
        } else {
            p = criarNo(n[i]);
            //printf("%p\n",p);
            (*lista)->prox = p;
            (*lista) = (*lista)->prox;
        }
    }
    //printf("%p\n",inicio);
    return inicio;
}

no * inserirNodosFinal(no **lista, int conteudo){
    no *inicio, *p;

    if (*lista==NULL){
        p = criarNo(conteudo);
        inicio = *lista = p;
    } else {
        inicio = *lista;
        while ((*lista)->prox!=NULL){
            *lista = (*lista)->prox;
        }

        p = criarNo(conteudo);
        (*lista)->prox = p;
    }
    return inicio;
}

no * inserirNodosInicio(no **lista, int conteudo){
    no *inicio, *p;

    if (*lista==NULL){
        p = criarNo(conteudo);
        inicio = *lista = p;
    } else {
        p = criarNo(conteudo);
        p->prox = *lista;
        inicio = p;
    }
    return inicio;
}

no * inserirNodosPosicao(no **lista, int conteudo, int posicao){
    no *inicio, *p, *ant;
    ant = *lista;
    int pos=1;
    if (*lista==NULL){
        p = criarNo(conteudo);
        inicio = *lista = p;
        p->prox = p;
    } else {
        if (posicao==1){
            p = criarNo(conteudo);
            p->prox = *lista;
            inicio = p;
        } else {
            while (pos != (posicao-1) && ant->prox !=NULL){
                ant = ant->prox;
                pos++;
            }
            p = criarNo(conteudo);
            if (ant->prox==NULL){
                ant->prox = p;
            } else {
                p->prox = ant->prox;
                ant->prox = p;
            }
        }
    }
    return inicio;
}
