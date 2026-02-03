#include "metodo.h"

// Faz a locacao dinamica para cada raiz/ folha da minha arvore
Raiz criarNo(CHAVE vlr){
    Raiz novo = (Raiz) malloc(sizeof(NO));  /* novo: nó alocado na memória */
    novo->chave = vlr;   /* guarda o valor no nó */
    novo->esq = NULL;    /* ainda não tem filho à esquerda */
    novo->dir = NULL;    /* ainda não tem filho à direita */

    return novo;
}

boolean inserirAux(Raiz raiz,CHAVE ch){
    /* se a chave a inserir é menor que a do nó atual, vai para a esquerda */
    if(raiz->chave > ch){
        /* se não tem filho à esquerda, cria o nó aqui */
        if(raiz->esq == NULL){
            raiz->esq = criarNo(ch);
            return true;
        }else{
            /* senão, desce na subárvore esquerda */
            return inserirAux(raiz->esq, ch);
        }
    }else{
        /* chave >= raiz: vai para a direita */
        if(raiz->dir == NULL){
            raiz->dir = criarNo(ch);
            return true;
        }else{
            return inserirAux(raiz->dir, ch);
        }
    }
}

boolean inserirNo(Raiz *raiz, CHAVE ch){
    /* se a árvore está vazia, o primeiro nó é a raiz */
    if(*raiz == NULL){
        *raiz = criarNo(ch);
        return true;
    }else{
        /* senão, procura o lugar certo na árvore (ordem BST) */
        return inserirAux(*raiz, ch);
    }
}

void criarListaInOrdem(Raiz raiz, no **lista){
    /* caso base: árvore vazia, não adiciona nada */
    if(raiz == NULL){
        return;
    }
    /* InOrdem: esquerda -> raiz -> direita */
    criarListaInOrdem(raiz->esq, lista);
    inserirNoLista(&(*lista), raiz->chave);
    criarListaInOrdem(raiz->dir, lista);
}

void criarListaPreOrdem(Raiz raiz, no **lista){
    if(raiz == NULL){
        return;
    }
    /* PreOrdem: raiz -> esquerda -> direita */
    inserirNoLista(&(*lista), raiz->chave);
    criarListaPreOrdem(raiz->esq, lista);
    criarListaPreOrdem(raiz->dir, lista);
}

void exibirInOrdem(Raiz raiz){
    if (raiz == NULL){
        return;
    }
    /* InOrdem: esquerda -> raiz -> direita */
    exibirInOrdem(raiz->esq);
    printf("%d ",raiz->chave);
    exibirInOrdem(raiz->dir);
}

void exibirPreOrdem(Raiz raiz){
    if(raiz == NULL){
        return;
    }
    /* PreOrdem: raiz -> esquerda -> direita */
    printf("%d ", raiz->chave);
    exibirPreOrdem(raiz->esq);
    exibirPreOrdem(raiz->dir);
}

void exibirPosOrdem(Raiz raiz){
    if(raiz == NULL){
        return;
    }
    /* PósOrdem: esquerda -> direita -> raiz */
    exibirPosOrdem(raiz->esq);
    exibirPosOrdem(raiz->dir);
    printf("%d ", raiz->chave);
}

boolean validador(Raiz raiz, int menor, int maior){
    /* árvore vazia é considerada válida (BST) */
    if(raiz == NULL){
        return true;
    }
    /* em uma BST, o nó deve estar entre menor e maior (limites do intervalo permitido) */
    if(raiz->chave < menor || raiz->chave > maior){
        return false;
    }
    /* esquerda: mesmo menor, limite superior vira a chave do nó; direita: limite inferior vira a chave do nó */
    return validador(raiz->esq, menor, raiz->chave) && validador(raiz->dir, raiz->chave, maior);
}

int maior(Raiz raiz){
    if(raiz == NULL){
        return 0;
    }
    /* em BST, o maior valor está no nó mais à direita */
    if(raiz->dir != NULL){
        return maior(raiz->dir);
    }else{
        return raiz->chave;
    }
}

int menor(Raiz raiz){
    if(raiz == NULL){
        return 0;
    }
    /* em BST, o menor valor está no nó mais à esquerda */
    if(raiz->esq != NULL){
        return menor(raiz->esq);
    }else{
        return raiz->chave;
    }
}

/* Copia os valores da lista para o vetor (vetor já alocado com tamanho n). */
void listaParaVetor(no *lista, int *vet, int n){
    for(int i = 0; i < n && lista != NULL; i++, lista = lista->prx){
        vet[i] = lista->valor;
    }
}

/* Constrói a árvore a partir dos segmentos de PreOrdem e InOrdem (por índices). */
Raiz construirDePreIn(int *pre, int *in, int preInicio, int preFim, int inInicio, int inFim){
    /* pre: vetor PreOrdem; in: vetor InOrdem; preInicio/preFim: intervalo em pre[]; inInicio/inFim: intervalo em in[] */
    /* se o intervalo está vazio, não há subárvore */
    if(preInicio > preFim || inInicio > inFim){
        return NULL;
    }
    CHAVE chaveRaiz = pre[preInicio];  /* em PreOrdem o primeiro elemento do intervalo é sempre a raiz */
    Raiz r = criarNo(chaveRaiz);
    int posIn = inInicio;   /* procura onde a raiz está no InOrdem (divide esquerda e direita) */
    while(in[posIn] != chaveRaiz){
        posIn++;
    }
    int tamEsq = posIn - inInicio;   /* quantidade de nós na subárvore esquerda */
    /* subárvore esquerda: em pre[] vem logo após a raiz; em in[] vai de inInicio até posIn-1 */
    r->esq = construirDePreIn(pre, in, preInicio + 1, preInicio + tamEsq, inInicio, posIn - 1);
    /* subárvore direita: resto de pre[] e de in[] após a raiz */
    r->dir = construirDePreIn(pre, in, preInicio + tamEsq + 1, preFim, posIn + 1, inFim);
    return r;
}

/* Recebe apenas as listas InOrdem e PreOrdem e devolve a árvore reconstruída (ou NULL). */
Raiz recriarArvore(no *listaInOrdem, no *listaPreOrdem){
    /* se alguma lista é nula, não dá para reconstruir */
    if(!listaPreOrdem || !listaInOrdem){
        return NULL;
    }
    int n = tamanhoLista(listaInOrdem);   /* número de nós (as duas listas devem ter o mesmo tamanho) */
    /* listas com tamanhos diferentes ou vazias: dados inválidos */
    if(n != tamanhoLista(listaPreOrdem) || n == 0){
        return NULL;
    }
    int *pre = (int *) malloc((size_t)n * sizeof(int));   /* vetor com a sequência PreOrdem */
    int *in  = (int *) malloc((size_t)n * sizeof(int));   /* vetor com a sequência InOrdem */
    /* se a alocação falhou, libera o que foi alocado e retorna NULL */
    if(!pre || !in){
        free(pre);
        free(in);
        return NULL;
    }
    listaParaVetor(listaPreOrdem, pre, n);
    listaParaVetor(listaInOrdem, in, n);
    Raiz raiz = construirDePreIn(pre, in, 0, n - 1, 0, n - 1);   /* reconstrói a árvore usando os vetores */
    free(pre);
    free(in);
    return raiz;
}