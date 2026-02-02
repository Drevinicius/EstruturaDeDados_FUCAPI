#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
    no *lista1, *lista2, *lista3;
    char op;
    int valor, quantidade;

    lista1 = NULL;
    //printf("%p\n",lista1);
    //printf("%p\n",&lista1);
    //printf("%p\n",lista2);
    //printf("%p\n",lista3);
    //scanf("%d",&valor);

    lista1 = inserirNodos(&lista1);//e04
    lista1 = inserirNodosFinal(&lista1,7);
    lista1 = inserirNodosInicio(&lista1,9);
    //lista1 = inserirNodosPosicao(&lista1,12,20);
    //imprimirLista(lista1);
    //lista_pares_impares(lista1);


    return 0;
}
