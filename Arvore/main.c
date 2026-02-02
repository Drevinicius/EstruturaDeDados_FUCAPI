#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int Bool;
typedef int TIPOCHAVE;


typedef struct aux{
    TIPOCHAVE chave;
    struct aux *esq, *dir;
} NO;

typedef NO* PONT;

/* retorna o endereco do NO que contem chave=ch ou NULL caso a
chave nao seja encontrada. Utiliza busca binaria recursiva
*/

PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
    if (raiz == NULL) return NULL;
    if (raiz->chave == ch) return raiz;
    if (raiz->chave<ch){
        return buscaBinaria(ch,raiz->dir);
    }
    return buscaBinaria(ch,raiz->esq);
}

/* cria um novo (aloca memoria e preenche valores) no com chave=ch e
retorna seu endereco */
PONT criarNovoNo(TIPOCHAVE ch){
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    return novoNo;
}
/* funcao auxiliar (recursiva) para insercao */
Bool inserirAux(PONT raiz, TIPOCHAVE ch){
    if (raiz->chave > ch) {
        if (raiz->esq == NULL) {
            raiz->esq = criarNovoNo(ch);
            return true;
        }else return inserirAux(raiz->esq, ch);
        }else{
            if (raiz->dir == NULL) {
            raiz->dir = criarNovoNo(ch);
            return true;
        }else return inserirAux(raiz->dir, ch);
    }
}

int tamanhoArvore(PONT raiz){
    if(raiz == NULL){
        return 0;
    }
    int esquerda = tamanhoArvore(raiz->esq);
    int direita = tamanhoArvore(raiz->dir);
    return 1 + esquerda + direita;
}
/* insere um novo no com chave=novaChave na arvore binaria apontada
por raiz */
Bool inserirNo(PONT * raiz, TIPOCHAVE novaChave){
    if (*raiz == NULL){
        *raiz = criarNovoNo(novaChave);
        return true;
    }
    else return inserirAux(*raiz, novaChave);
}
// Busca binária não recursiva devolvendo o nó pai
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if(atual->chave == ch) break;
        *pai = atual;
        if(ch < atual->chave) atual = atual->esq;
        else atual = atual->dir;
    }
    return *pai;
}
/* Auxilir da funcao excluirChave, procura a maior chave menor que a
chave que serah excluida */
PONT maior_esquerdo(PONT p, PONT *ant){
    *ant = p;
    p = p->esq;
    while (p->dir) {
        *ant = p;
        p = p->dir;
    }
    return(p);
}
/* exclui a chave com valor igual a ch */
Bool excluirChave(PONT *raiz, TIPOCHAVE ch){
    PONT atual, no_pai, substituto, pai_substituto;
    substituto=NULL;
    atual = buscaNo(*raiz, ch, &no_pai);
    if(atual == NULL) return false;
    if((!atual->esq)||(!atual->dir)) { // tem zero ou um filho
    if((!atual->esq)) substituto = atual->dir;
    if((!atual->dir)) substituto = atual->esq;
    if(!no_pai) {// o excluido eh raiz
        *raiz = substituto;
    }else {
        if(no_pai->chave > ch) no_pai->esq = substituto;
        else no_pai->dir = substituto;
    }
    free(atual);
    }
    else { // tem dois filhos
        substituto = maior_esquerdo(atual,&pai_substituto);
        atual->chave = substituto->chave;
    if (pai_substituto->esq == substituto){
        pai_substituto->esq = substituto->esq;
    } else {
        pai_substituto->dir = substituto->esq;
    }
    free(substituto);
    }
    return true;
}
/* Exibe arvore Em Ordem */
void exibirArvoreEmOrdem(PONT raiz){
    if (raiz == NULL) return;
    exibirArvoreEmOrdem(raiz->esq);
    printf("%d ",raiz->chave);
    exibirArvoreEmOrdem(raiz->dir);
}
/* Exibe arvore Pre Ordem */
void exibirArvorePreOrdem(PONT raiz){
    if (raiz == NULL) return;
    printf("%d ",raiz->chave);
    exibirArvorePreOrdem(raiz->esq);
    exibirArvorePreOrdem(raiz->dir);
}
/* Exibe arvore Pos Ordem */
void exibirArvorePosOrdem(PONT raiz){
    if (raiz == NULL) return;
    exibirArvorePreOrdem(raiz->esq);
    exibirArvorePreOrdem(raiz->dir);
    printf("%d ",raiz->chave);
}
/* Exibe arvore Em Ordem (com parenteses para os filhos) */
void exibirArvore(PONT raiz){
    if (raiz == NULL) return;
    printf("(");
    printf("%d",raiz->chave);
    exibirArvore(raiz->esq);
    exibirArvore(raiz->dir);
    printf(")");
}
/* funcao auxiliar na destruicao (liberacao da memoria) de uma
arvore */
void destruirAux(PONT subRaiz){
    if (subRaiz){
        destruirAux(subRaiz->esq);
        destruirAux(subRaiz->dir);
        free(subRaiz);
    }
}

/* libera toda memoria de uma arvore e coloca NULL no valor da raiz
*/
void destruirArvore(PONT * raiz){
    destruirAux(*raiz);
    *raiz = NULL;
}

/* inicializa arvore: raiz=NULL */
void inicializar(PONT * raiz){
    *raiz = NULL;
}

PONT recriarArvore(int *preOrdem, int *inOrdem){
    PONT raiz = NULL;
    inserirNo(&raiz, preOrdem[0]); 
    // A  raiz principal de uma arvore sempre e o primeiro elemento da lista PreOrdem
    

    printf("%d", preOrdem[7]);

    return raiz;
}

int main(void){
    PONT raiz = NULL;
    
    TIPOCHAVE valor[] = {5, 2, 10, 11, 1, 3};

    int listaPre[] = {5, 2, 1, 3, 10, 11};
    int listaIn[] = {1, 2, 3, 5, 10, 11};
    int tamanho = sizeof(valor) / sizeof(TIPOCHAVE);

    for(int i=0; i < tamanho;i++){
        inserirNo(&raiz, valor[i]);
    }

    recriarArvore(listaPre, listaIn);

    return 0;
}