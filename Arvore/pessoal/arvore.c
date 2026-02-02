#include "metodo.h"

Raiz criarNo(CHAVE vlr){
    Raiz novo = (Raiz) malloc(sizeof(NO));
    novo->chave = vlr;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}
boolean inserirAux(Raiz raiz,CHAVE ch){
    if(raiz->chave > ch){
        if(raiz->esq == NULL){
            raiz->esq = criarNo(ch);
            return true;
        }else{
            return inserirAux(raiz->esq, ch);
        }
    }else{
        if(raiz->dir == NULL){
            raiz->dir = criarNo(ch);
            return true;
        }else{
            return inserirAux(raiz->dir, ch);
        }
    }
}
boolean inserirNo(Raiz *raiz, CHAVE ch){
    if(*raiz == NULL){
        *raiz = criarNo(ch);
        return true;
    }else{
        return inserirAux(*raiz, ch);
    }
}
void criarListaInOrdem(Raiz raiz, no **lista){
    if(raiz == NULL){
        return;
    }
    criarListaInOrdem(raiz->esq, lista);
    inserirNoLista(&(*lista), raiz->chave);
    criarListaInOrdem(raiz->dir, lista);
}
void criarListaPreOrdem(Raiz raiz, no **lista){
    if(raiz == NULL){
        return;
    }
    inserirNoLista(&(*lista), raiz->chave);
    criarListaPreOrdem(raiz->esq, lista);
    criarListaPreOrdem(raiz->dir, lista);
}
void exibirInOrdem(Raiz raiz){
    if (raiz == NULL){
        return;
    }
    exibirInOrdem(raiz->esq);
    printf("%d ",raiz->chave);
    exibirInOrdem(raiz->dir);
}
void exibirPreOrdem(Raiz raiz){
    if(raiz == NULL){
        return;
    }
    printf("%d ", raiz->chave);
    exibirPreOrdem(raiz->esq);
    exibirPreOrdem(raiz->dir);
}
void exibirPosOrdem(Raiz raiz){
    if(raiz == NULL){
        return;
    }
    exibirPosOrdem(raiz->esq);
    exibirPosOrdem(raiz->dir);
    printf("%d ", raiz->chave);
}
boolean validador(Raiz raiz, int menor, int maior){
    if(raiz == NULL){
        return true;
    }
    if(raiz->chave < menor || raiz->chave > maior){
        return false;
    }
    return validador(raiz->esq, menor, raiz->chave) && validador(raiz->dir, raiz->chave, maior);
}
int maior(Raiz raiz){
    if(raiz == NULL){
        return 0;
    }
    if(raiz->dir != NULL){
        return maior(raiz->dir);
    }else{
        return raiz->chave;
    }
}
int menor(Raiz raiz){
    if(raiz == NULL){
        return 0;
    }
    if(raiz->esq != NULL){
        return menor(raiz->esq);
    }else{
        return raiz->chave;
    }
}

void recriarArvore(no *listaInOrdem, no *listaPreOrdem){
    Raiz raiz = NULL;
    inserirNo(&raiz, listaPreOrdem->valor);
    
    printf("Teste");

}