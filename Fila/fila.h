#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Desenvolva um programa que permita gerenciar uma pista para decolagem de aviões
    de um aeroporto privado. Para o correto funcionamento desta pista é necessário que
    sejam implementadas as seguintes funcionalidades:
        a. Número de aviões a espera de decolar
        b. Decolagem de um avião OK
        c. Entrada de um novo avião para decolar OK
        d. Listar todos os aviões a espera de decolar OK
        e. Listar as características do próximo avião a decolar OK
        */


typedef struct no{
    int codigo;
    int capacidade;
    char modelo[50];
    char destino[50];
    struct no *prox;
}no;

void limpar_buffer();
no *criarNo(int codigo, int capacidade, char *modelo, char *destino);
void inserirFila(no **inicio, no **fim, int codigo, int capacidade, char *modelo, char *destino);
void imprimirFila(no **inicio);
void decolar(no **inicio);
void contarFila(no **inicio, no **fim);
#endif