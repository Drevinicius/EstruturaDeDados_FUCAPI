#ifndef LISTADUPLA_H_INCLUDED
#define LISTADUPLA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    int conteudo;
    struct no* prox;
    struct no* ant;
} No;

No *criarNo(int valor);
No *inserirInicio(No **lista, int conteudo);
No *excluirNo(No **lista, int conteudo);
No *inserirPosicao(No **lista, int conteudo, int posicao);

void imprimirValor(No *lista);
void imprimirValorReverse(No *lista);

#endif