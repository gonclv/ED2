#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *esq;
    struct no *dir;
} TNoABP;

void emOrdem(TNoABP *raiz) {
  if (raiz == NULL) return;
  emOrdem(raiz->esq);
  printf("%d\n", raiz->chave);
  emOrdem(raiz->dir);
}

/*Mudar para ponteiro de ponteiro*/
TNoABP *menorNo(TNoABP *raiz) {
    if(raiz == NULL) return NULL;
    while(raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}

/*Mudar para ponteiro de ponteiro*/
TNoABP *maiorNo(TNoABP *raiz) {
    if(raiz == NULL) return NULL;
    while(raiz->dir != NULL) raiz = raiz->dir;
    return raiz;
}

/*acho q pronto se eu entendi certo o enunciado*/
TNoABP *insere(TNoABP *raiz, int chave) {
  TNoABP *novo = (TNoABP *) malloc(sizeof(TNoABP));
  if(novo == NULL) return raiz;
  novo->chave = chave;
  novo->esq = NULL;
  novo->dir = NULL;

  TNoABP *aux = raiz;
  while(aux != NULL) {
    if(chave < aux->chave) {
      if(aux->esq == NULL) {
        aux->esq = novo;
        return raiz;
      }
      aux = aux->esq;
    }
    else {
      if(aux->dir == NULL) {
        aux->dir = novo;
        return raiz;
      }
      aux = aux->dir;
    }
  }
  return novo;
}

void main() {
    TNoABP *raiz, **r;

    //No 7
    raiz = (TNoABP *) malloc(sizeof(TNoABP));
    r = &raiz;
    raiz->chave = 7;
    raiz->esq = NULL;
    raiz->dir = NULL;

    //No 5
    raiz->esq = (TNoABP *) malloc(sizeof(TNoABP));
    (raiz->esq)->chave = 5;
    (raiz->esq)->esq = NULL;
    (raiz->esq)->dir = NULL;

    //No 2
    (raiz->esq)->esq = (TNoABP *) malloc(sizeof(TNoABP));
    ((raiz->esq)->esq)->chave = 2;
    ((raiz->esq)->esq)->esq = NULL;
    ((raiz->esq)->esq)->dir = NULL;

    //No 6
    (raiz->esq)->dir = (TNoABP *) malloc(sizeof(TNoABP));
    ((raiz->esq)->dir)->chave = 6;
    ((raiz->esq)->dir)->esq = NULL;
    ((raiz->esq)->dir)->dir = NULL;

    //No 9
    raiz->dir = (TNoABP *) malloc(sizeof(TNoABP));
    (raiz->dir)->chave = 9;
    (raiz->dir)->esq = NULL;
    (raiz->dir)->dir = NULL;

    //No 8
    (raiz->dir)->esq = (TNoABP *) malloc(sizeof(TNoABP));
    ((raiz->dir)->esq)->chave = 8;
    ((raiz->dir)->esq)->esq = NULL;
    ((raiz->dir)->esq)->dir = NULL;

    emOrdem(raiz);

    printf("Endereco do no raiz: %p, endereco da variavel raiz: %p\n", raiz, &raiz);
    printf("Endereco do no raiz: %p, endereco da variavel raiz: %p\n", *r, &(*r));
    printf("Valor chave usando 'raiz': %d, valor chave usando 'r': %d\n", raiz->chave, (*r)->chave);
    printf("Valor campo esq: %p, endereco campo dir: %p\n", raiz->esq, &(raiz->dir));
    printf("Valor campo esq: %p, endereco campo dir: %p\n", (*r)->esq, &((*r)->dir));
    /*
    free((raiz->dir)->esq);
    (raiz->dir)->esq = NULL;
    */

    free(((*r)->dir)->esq);
    ((*r)->dir)->esq = NULL;

    TNoABP *resposta = menorNo(raiz);
    printf("Menor: %d\n",resposta->chave);

    resposta = maiorNo(raiz);
    printf("Maior: %d\n",resposta->chave);

  int num;
  do {
    scanf("%d", &num);
    raiz = insere(raiz, num);
  } while(num != 0);

    emOrdem(raiz);
}