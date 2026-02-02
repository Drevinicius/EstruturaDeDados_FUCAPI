#include "fila.h"
#include "inserirFila.c"
#include "criarNo.c"

int main(){
    no *inicio = NULL, *fim = NULL;
    inserirFila(&inicio, &fim, 123, 300, "BOING", "SAO PAULO");
    inserirFila(&inicio, &fim, 432, 35, "BOING", "SAO LUIS");
    inserirFila(&inicio, &fim, 113, 120, "BOING", "SAO JOSE DOS CAMPOS");
    
    contarFila(&inicio, &fim);

    decolar(&inicio);
    decolar(&inicio);

    //imprimirFila(&inicio);

    free(inicio);
}