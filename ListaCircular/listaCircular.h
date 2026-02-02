#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>


typedef struct no{
    int posicao;
    int valorInicial;
    struct no *prox;
} No;

No *criarNo(int conteudo);
No *inserirFinal(No **lista, int valorInicial);
void imprimirListaCircular(No *lista);
No *excluirPosicao(No **lista, int valorInicial);

#endif