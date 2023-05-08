#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *esq, *dir;
} TNoABP;

//Completar
void insereABP(TNoABP **raiz, int i) {
    if(*raiz == NULL) {
        *raiz = (TNoABP *) malloc(sizeof(TNoABP));
        (*raiz)->chave = i;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        return;
    }
    if(i < (*raiz)->chave) insereABP(&(*raiz)->esq, i);
    else insereABP(&(*raiz)->dir, i);
}

void emOrdemOrdena(TNoABP *raiz, int v[], int *indice) {
    if(raiz == NULL) return;
    emOrdemOrdena(raiz->esq, v, indice);
    //O primeiro nó a ser visitado é o menor de todos, então será gravado na posição 0 do vetor.
    v[*indice] = raiz->chave;
    *indice = (*indice) + 1;
    emOrdemOrdena(raiz->dir, v, indice);
}

void imprime(TNoABP *raiz) {
    if(raiz == NULL) return;
    imprime(raiz->esq);
    printf("%d\n", raiz->chave);
    imprime(raiz->dir);
}

void ordena(int v[], int n) {
    if((v == NULL) || (n <= 1)) return;
    TNoABP *raiz = NULL;
    int indice = 0;
    for(int i = 0; i < n; i++) {
        insereABP(&raiz, v[i]);
    }
    emOrdemOrdena(raiz, v, &indice);
    imprime(raiz);

    //Desalocar todos os nós da árvore temporária (usando pós ordem):
}

int main()
{
    int v[10] = {7,6,4,3,0,2,1,8,5,9};
    ordena(v, 10);

    return 0;
}