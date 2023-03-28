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
        (*rr)->num = 10;
        (*rr)->esq = NULL;
        (*rr)->dir = (TNo *) malloc(sizeof(TNo));
        if((*rr)->dir) {
            TNo **r2 = &(raiz->dir);
            (*r2)->num = 20;
            (*r2)->esq = NULL;
            (*r2)->dir = NULL;
        }
    }
    
    printf("%d %d\n", raiz->num, (raiz->dir)->num);
}