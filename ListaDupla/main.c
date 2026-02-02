#include "listaDupla.h"
#include "inserirValores.c"
#include "imprirmirValores.c"
#include "excluirNo.c"

int main() {
    No *lista = NULL;
    lista = inserirInicio(&lista, 1); // 1
    lista = inserirPosicao(&lista, 0, 1);// 2
    lista = inserirPosicao(&lista, 3, 2);// 3
    lista = inserirPosicao(&lista, 4, 1);// 4
    lista = inserirPosicao(&lista, 3, 6);// 5
    lista = inserirPosicao(&lista, 2, 3);// 6
    lista = inserirPosicao(&lista, 1, 4);// 7

    // 1 0 4 3 2 1

    imprimirValor(lista);
    free(lista);
}