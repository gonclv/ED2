#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *esq;
    struct no *dir;
} TNoABP;

void insere(TNoABP **raiz, int k) {
    if(*raiz == NULL) { 
        *raiz = (TNoABP *) malloc(sizeof(TNoABP));
        (*raiz)->chave = k;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        return;
    }
    if(k < (*raiz)->chave) insere(&((*raiz)->esq), k);
    else insere(&((*raiz)->dir), k);
}

void imprime(TNoABP *raiz) {
    if(raiz == NULL) return;
    imprime(raiz->esq);
    printf("%d\n", raiz->chave);
    imprime(raiz->dir);
}

void nosUmFilho(TNoABP *raiz, int *cont) {
    if(raiz == NULL) return;
    if((raiz->esq == NULL) && (raiz->dir != NULL)) {
        (*cont)++;
    }
    if((raiz->esq != NULL) && (raiz->dir == NULL)) {
        (*cont)++;
    }
    nosUmFilho(raiz->esq, cont);
    nosUmFilho(raiz->dir, cont);
}

void main() {
    TNoABP *raiz = NULL;
    int N, i, chave, cont = 0, nivel = 0;
    scanf("%d", &N);
    for(i = 0; i < N; i++) {
        scanf("%d", &chave);
        insere(&raiz, chave);
    }

    imprime(raiz);
    nosUmFilho(raiz, &cont);
    printf("Nos que tem um filho: %d\n", cont);

    TNoABP **aux = &raiz;
    while((*aux)->dir != NULL) {
        nivel++;
        aux = &((*aux)->dir);
    }
    TNoABP *aux2 = *aux;
    while(aux2->esq != NULL) {
        nivel++;
        aux2 = aux2->esq;
    }
    *aux = (*aux)->esq;
    nivel--;
    if((*aux)->esq == NULL) nivel = -1;
    free(*aux);
    printf("%d\n", nivel);
}