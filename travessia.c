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

void totalFolhas(TNoABP *raiz, int *cont) {
    /* Assume que há uma variável contadora na main, inicializada com valor 0
    e cujo endereço é passado como parâmetro para a função. */
    if(raiz == NULL) return;
    if((raiz->esq == NULL) && (raiz->dir == NULL)) {
        *cont = *cont + 1;
        return;
    }
    totalFolhas(raiz->esq, cont);
    totalFolhas(raiz->dir, cont);
}

TNoABP **menorNo(TNoABP **raiz) {
    if(*raiz == NULL) return NULL;
    while((*raiz)->esq != NULL) raiz = &((*raiz)->esq);
    return raiz;
}

void deletaArvore(TNoABP **raiz) {
    if((*raiz) == NULL) return;
    if((*raiz)->esq != NULL) deletaArvore(&(*raiz)->esq);
    if((*raiz)->dir != NULL) deletaArvore(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
}

int soma(TNoABP *raiz, int *cont) {
    /* Assume que há uma variável contadora na main, inicializada com valor 0
    e cujo endereço é passado como parâmetro para a função. */
    if(raiz == NULL) return 0;
    (*cont)++;
    return raiz->chave + soma(raiz->esq, cont) + soma(raiz->dir, cont);
}

TNoABP **busca(TNoABP **raiz, int k) {
    if((*raiz) == NULL) return NULL;
    while((*raiz) != NULL) {
        if(k == (*raiz)->chave) return raiz;
        if(k < (*raiz)->chave) raiz = &(*raiz)->esq;
        else raiz = &(*raiz)->dir;
    }
    printf("Erro: no n esta na arvore\n");
    return NULL;
}

void removeNo(TNoABP **raiz, TNoABP **no) {
    if(*raiz == NULL) return;
    if((*no)->chave == (*raiz)->chave) {
        if((*raiz)->esq == NULL) {
            TNoABP *aux = *raiz;
            *raiz = (*raiz)->dir;
            free(aux);
        }
        else if((*raiz)->dir == NULL) {
            TNoABP *aux = *raiz;
            *raiz = (*raiz)->esq;
            free(aux);
        }
        else {
            TNoABP *aux = (*raiz)->dir;
            while (aux->esq != NULL) aux = aux->esq;
            (*raiz)->chave = aux->chave;
            removeNo(&(*raiz)->dir, &aux);
        }
    }
    else if((*no)->chave < (*raiz)->chave) removeNo(&(*raiz)->esq, no);
    else removeNo(&(*raiz)->dir, no);
}

void removeQuaseFolha(TNoABP **raiz, TNoABP **no) {
    if(*raiz == NULL) return;
    if((*raiz)->chave == (*no)->chave) {
        TNoABP *aux = *raiz;
        if((*raiz)->esq != NULL) *raiz = (*raiz)->esq;
        else *raiz = (*raiz)->dir;
        free(aux);
    }
    else if((*no)->chave < (*raiz)->chave) removeQuaseFolha(&(*raiz)->esq, no);
    else removeQuaseFolha(&(*raiz)->dir, no);
}

void main() {
    TNoABP *raiz = NULL;
    int num, op, cont = 0, cont2 = 0;
    do {
      printf("1 - Inserir número, 0 - Continuar: ");
      //scanf("%d", &op);
      //if(op == 1) {
        scanf("%d", &num);
        insere(&raiz, num);
    //}
    } while(num != 0);

    imprime(raiz);
    totalFolhas(raiz, &cont);
    printf("Cont: %d\n", cont);

    TNoABP **menor;
    menor = menorNo(&raiz);
    if(menor) printf("Menor: %d\n", (*menor)->chave);

    float media = (float) soma(raiz, &cont2) / cont2;
    printf("Media: %f\n", media);

    int k;
    scanf("%d", &k);
    TNoABP **buscar = busca(&raiz, k);
    if(buscar != NULL) removeNo(&raiz, buscar);

    //deletaArvore(&raiz);
    if(raiz == NULL) printf("Árvore vazia\n");
    else imprime(raiz);
}