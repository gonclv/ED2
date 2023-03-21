#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int num;
    struct no *esq;
    struct no *dir;
} TNo;

int identificaFolha(TNo *no) {
    if(!no) return 0;
    if(!(no->esq) && !(no->dir)) return 1;
    return 0;
}

void main() {
    TNo *no = (TNo *) malloc(sizeof(TNo));
    TNo *no2 = (TNo *) malloc(sizeof(TNo));
    TNo *no3 = (TNo *) malloc(sizeof(TNo));
    no->num = 1;
    no->esq = NULL;
    no->dir = no3;
    if(identificaFolha(no) == 1)
        printf("Nó é folha\n");
    else
        printf("Nó não é folha\n");
}
