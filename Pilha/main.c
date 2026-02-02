#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *prox;
} no;

no *criarP(int cont){
    no *novoNo = (no*)malloc(sizeof(no));
    novoNo->conteudo = cont;
    novoNo->prox = NULL;

    return novoNo;
}


no *inserirNormal(no **topo, int cont){
    no *p = criarP(cont);
    if(!*topo)
        *topo = p;
    else{
        p->prox = *topo;
        *topo = p;
    }
    return *topo;
}

no *inserir(no **topo, no *p){
    //no *p = criarP(cont);
    if(!*topo)
        *topo = p;
    else{
        p->prox = *topo;
        *topo = p;
    }
    return *topo;
}

no *remover(no **topo){
    no *p = NULL;
    if(*topo){
        p = *topo;
        *topo = (*topo)->prox;
        p->prox = NULL;
    }
    return p;
}

void imprimir(no *topo){
    no *p_tmp = NULL;
    while(topo){
        printf("%d :", remover(&topo)->conteudo);
        p_tmp = inserir(&topo, remover(&topo));
    }
    printf("\n");
    topo = p_tmp;

    while(topo){
        //printf("%d :", remover(&topo)->conteudo);
        p_tmp = inserir(&topo, remover(&topo));
    }
    //p_tmp = NULL;
    //free(p_tmp);
}

int main(){
    no *pilha = NULL;

    pilha = inserirNormal(&pilha, 4);
    pilha = inserirNormal(&pilha, 3);
    pilha = inserirNormal(&pilha, 2);
    pilha = inserirNormal(&pilha, 1);

    imprimir(pilha);
    //imprimir(pilha);
    imprimir(pilha);

    free(pilha);
}