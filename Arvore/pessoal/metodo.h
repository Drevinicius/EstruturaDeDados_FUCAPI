#ifndef METODO_H
#define METODO_H
#define true 1
#define false 0

#include<stdio.h>
#include<stdlib.h>


typedef int CHAVE; // Armazenar inteiros
typedef int boolean;
typedef struct aux{
    CHAVE chave; // Conteudo que as folhas e a raiz vai ter
    struct aux *esq, *dir; // Ponteiro das proximas folhas pela esquerda e direta
}NO;
typedef NO *Raiz;
typedef struct no{
    int valor;
    struct no *prx;
}no;

no *criarNoLista(int vlr);
void inserirNoLista(no **lista, int vlr);
Raiz criarNo(CHAVE vlr);
boolean inserirAux(Raiz raiz,CHAVE ch);
boolean inserirNo(Raiz *raiz, CHAVE ch);
boolean validador(Raiz raiz, int menor, int maior);
void criarListaInOrdem(Raiz raiz, no **lista);
void criarListaPreOrdem(Raiz raiz, no **lista);
void exibirInOrdem(Raiz raiz);
void exibirPreOrdem(Raiz raiz);
void exibirPosOrdem(Raiz raiz);
void exibirLista(no *lista);
Raiz recriarArvore(no *listaInOrdem, no *listaPreOrdem);
void excluirValor(no **lista, int valor);
int maior(Raiz raiz);
int menor(Raiz raiz);
int tamanhoLista(no *lista);

#endif