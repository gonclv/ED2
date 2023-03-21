#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int num;
    struct no *esq;
    struct no *dir;
} TNo;

void alocaNo() {
    TNo *pno1;
    pno1 = malloc(sizeof(TNo));
    if(pno1 == NULL) return;
    pno1->num = 0;
    pno1->esq = NULL;
    pno1->esq = NULL;
}

void main() {
    TNo *raiz = malloc(sizeof(TNo));
    if(raiz) {
        TNo **rr = &raiz;
        raiz->num = 10;
        raiz->esq = NULL;
        raiz->dir = (TNo *) malloc(sizeof(TNo));
        if(raiz->dir) {
            TNo **r2 = &(raiz->dir);
            (raiz->dir)->num = 20;
            (raiz->dir)->esq = NULL;
            (raiz->dir)->dir = NULL;
        }
    }
    
    printf("%d %d\n", raiz->num, (raiz->dir)->num);
}