#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo;
    struct no *prox;
} no;



no* criarNo(int conteudo) {
    no* novo = (no*)malloc(sizeof(no));
    novo->conteudo = conteudo;
    novo->prox = NULL;
    return novo;
}

no* inserirNoMeioCircular(no **lista, int conteudo, int posicao) {
    no *novo, *atual, *anterior;
    int pos = 1;

    novo = criarNo(conteudo);

    if (*lista == NULL) {
        novo->prox = novo;
        *lista = novo;
        return *lista;
    }

    atual = *lista;

    if (posicao == 1) {
        while (atual->prox != *lista) {
            atual = atual->prox;
        }
        novo->prox = *lista;
        atual->prox = novo;
        *lista = novo;
        return *lista;
    }

    anterior = *lista;
    atual = (*lista)->prox;
    pos = 2;

    while (atual != *lista && pos < posicao) {
        anterior = atual;
        atual = atual->prox;
        pos++;
    }

    anterior->prox = novo;
    novo->prox = atual;

    return *lista;
}

void imprimirListaCircular(no *lista) {
    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    no *atual = lista;
    do {
        printf("%d -> ", atual->conteudo);
        atual = atual->prox;
    } while (atual != lista);


}

int main(){
    no *lista1;
    lista1 = NULL;

    lista1 = inserirNoMeioCircular(&lista1, 32, 1);
    lista1 = inserirNoMeioCircular(&lista1, 12, 2);
    lista1 = inserirNoMeioCircular(&lista1, 42, 3);
    lista1 = inserirNoMeioCircular(&lista1, 50, 2);

    imprimirListaCircular(lista1);

    free(lista1);
    return 0;
}
