#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MOVIMENTACOES 20

typedef struct{
    int id;
    double saldo;
    char *nome;
    //int *registroDeMovimentacoes;
    //double *valorMovimentado;
} contaBancaria;

contaBancaria *iniciarConta(char *nome){
    contaBancaria *novaConta = (contaBancaria*)malloc(sizeof(contaBancaria));
    novaConta->id = rand()%(1000+1);
    novaConta->saldo = 0;
    novaConta->nome = (char*)malloc(sizeof(nome));
    novaConta->nome = nome;
    //novaConta->registroDeMovimentacoes = (int*)malloc(MOVIMENTACOES * sizeof(int));
    //novaConta->valorMovimentado = (double*)malloc(MOVIMENTACOES * sizeof(double));
    if(!novaConta || !novaConta->nome){
        return NULL;
    }
    //printf("Ola, %s\nConta registrada com sucesso\nSeu numero de conta e: %d\n", novaConta->nome,novaConta->id);
    return novaConta;
}

void deposito(contaBancaria *minhaConta, double valor){
    minhaConta->saldo += valor;
    printf("Valor depositado!\n");
}

int main(void){
    srand(time(NULL));
    contaBancaria *minhaConta = iniciarConta("Andre");

    deposito(minhaConta, 150.36);

    printf("%.2f", minhaConta->saldo);

    free(minhaConta);
    return 0;
}