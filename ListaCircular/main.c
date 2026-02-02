#include "listaCircular.h"
#include "listaCircular.c"

int main(){
    No *lista = NULL;
    int valorInicial, elementos, valor;

    printf("\t=*=*=*=*=*=*=*=*=*=*=\n");
    printf("\t Desafio de Josephus\n");
    printf("\t=*=*=*=*=*=*=*=*=*=*=\n");

    printf("\tQuantos elementos deseja inserir? ");
    scanf("%d", &elementos);

    printf("\tQual o valor de passos inicial? ");
    scanf("%d", &valorInicial);

    for(int i = 1; i <= elementos; i++){
        printf("\t%dº elemento: ", i);
        scanf("%d", &valor);

        lista = inserirFinal(&lista, valor);
    }
    printf("\n");

    lista = excluirPosicao(&lista, valorInicial);
    imprimirListaCircular(lista);

    free(lista);
    return 0;
}
