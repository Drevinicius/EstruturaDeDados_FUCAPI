#include "metodo.h"

int main(){
    Raiz raiz = NULL;
    //CHAVE chave; Tipo de inteiro

    inserirNo(&raiz, 4);
    inserirNo(&raiz, 5);
    inserirNo(&raiz, 2);
    inserirNo(&raiz, 0);

    no *listaInOrdem = NULL;
    no *listaPreOrdem = NULL;
    criarListaInOrdem(raiz, &listaInOrdem); // Criacao da lista em ordem
    criarListaPreOrdem(raiz, &listaPreOrdem); // Criacao da lista pre-ordem

    //TESTES
    
    //Verificacao de criacao de listas
    //exibirLista(listaInOrdem);
    //exibirInOrdem(raiz);
    //exibirLista(listaPreOrdem);
    //exibirPreOrdem(raiz);

    // Medir menor e maior valores e validador de arvore
    //printf("Maior: %d\n", maior(raiz));
    //printf("Menor: %d\n", menor(raiz));
    //printf("Valido: %s", validador(raiz, menor(raiz), maior(raiz)) ? "SIM" : "NAO");


    // Reconstruir árvore apenas com as listas InOrdem e PreOrdem
    Raiz arvoreReconstruida = recriarArvore(listaInOrdem, listaPreOrdem);
    if(arvoreReconstruida){
        printf("Arvore reconstruida - InOrdem: ");
        exibirInOrdem(arvoreReconstruida);
        printf("\nArvore reconstruida - PreOrdem: ");
        exibirPreOrdem(arvoreReconstruida);
        printf("\n");
    }

    return 0;
}