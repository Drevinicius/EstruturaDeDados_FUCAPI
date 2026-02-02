#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int CHAVE; // Armazenar inteiros
typedef int boolean;
typedef struct aux{
    CHAVE chave; // Conteudo que as folhas e a raiz vai ter
    struct aux *esq, *dir; // Ponteiro das proximas folhas pela esquerda e direta
}NO;

typedef NO *Raiz;

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

boolean validador(Raiz raiz, int min, int max){
    if(!raiz) return true;

    if(raiz->chave < min || raiz->chave > max) return false;
    
    return validador(raiz->esq, min, raiz->chave) && validador(raiz->dir, raiz->chave, max);
}

int main(){
    Raiz raiz = NULL;
    CHAVE ch = 4;

    inserirNo(&raiz, ch);
    ch = 5;
    inserirNo(&raiz, ch);
    ch = 2;
    inserirNo(&raiz, ch);
    ch = 0;
    inserirNo(&raiz, ch);

    printf("%d", validador(raiz, 0, 5));

    return 0;
}