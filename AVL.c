#include <stdio.h>
#include <stdlib.h>

typedef struct noAVL {
    int chave;
    int bal;
    struct noAVL *esq;
    struct noAVL *dir;
} TNoAVL;

int rot_esq(TNoAVL **no) {
    TNoAVL *p, *aux;

    if((*no) == NULL) return 1;
    p = (*no)->dir;
    aux = p->esq;
    p->esq = (*no);
    (*no)->dir = aux;
    (*no) = p;

    return 0;
}

int rot_dir(TNoAVL **no) {
    TNoAVL *p, *aux;
    if((*no) == NULL) return 1;

    p = (*no)->esq;
    aux = p->dir;
    p->dir = (*no);
    (*no)->esq = aux;
    (*no) = p;

    return 0;
}

int bal_esq(TNoAVL **no) {
    TNoAVL *p1, *p2;

    if((*no) == NULL) {
        //Pesquisar
    }

    if((*no)->bal == -1) {
        //Pesquisar
    }
    else if((*no)->bal == 0) {
        (*no)->bal = 0;
        return 1;
    }
    else {
        p1 = (*no)->dir;

        if(p1->bal >= 0) {
            //Pesquisar
        }
        else {
            p2 = p1->esq;
            p1->esq = p2->dir;
            p2->dir = p1;
            (*no)->dir = p2->esq;
            p2->esq = (*no);

            if(p2->bal == 1) (*no)->bal = -1;
            else (*no)->bal = 0;

            if(p2->bal == -1) p1->bal = 1;
            else p1->bal = 0;

            (*no) = p2;
            p2->bal = 0;

            return 1;
        }
    }
}

int insere(TNoAVL **no, int k) {
    int cresceu;

    if(*no == NULL) { 
        *no = (TNoAVL *) malloc(sizeof(TNoAVL));
        (*no)->chave = k;
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        (*no)->bal = 0;

        cresceu = 1;
    }

    else if((*no)->chave >= k) {
    //Pesquisar
    }

    else if((*no)->chave < k) {
        cresceu = insere(&(*no)->dir, k);
        if(cresceu) {
            switch((*no)->bal) {
                case -1: //Pesquisar
                case 0: {
                    (*no)->bal = 1;
                    cresceu = 1;
                    break;
                }
                case 1: {
                    if((*no)->dir->bal == 1) {
                        rot_esq(no);
                        (*no)->bal = 0;
                        (*no)->esq->bal = 0;
                    }
                }
            }
        }
    }

    else cresceu = 0;

    return cresceu;
}

void imprime(TNoAVL *raiz) {
    if(raiz == NULL) return;
    imprime(raiz->esq);
    printf("%d\n", raiz->chave);
    imprime(raiz->dir);
}

void deletaArvore(TNoAVL **raiz) {
    if((*raiz) == NULL) return;
    if((*raiz)->esq != NULL) deletaArvore(&(*raiz)->esq);
    if((*raiz)->dir != NULL) deletaArvore(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
}

TNoAVL **busca(TNoAVL **raiz, int k) {
    if((*raiz) == NULL) return NULL;
    while((*raiz) != NULL) {
        if(k == (*raiz)->chave) return raiz;
        if(k < (*raiz)->chave) raiz = &(*raiz)->esq;
        else raiz = &(*raiz)->dir;
    }
    printf("Erro: no n esta na arvore\n");
    return NULL;
}

int removeNo(TNoAVL **no, int k) {
    TNoAVL *p, *aux;
    int flag = 0;

    if(*no == NULL) {/*Pesquisar*/}
    
    else if((*no)->chave > k) {
        flag = removeNo(&(*no)->esq, k);

        if(flag) {
            bal_esq(&(*no));
            return 1;
        }
    } 
    else if((*no)->chave < k) {
        //Pesquisar
    }
    else {
        p = (*no);

        if(p->dir == NULL) {
            (*no) = p->esq;
            return 1;
        }
        else if(p->esq == NULL) {
            //Pesquisar
        }
        else {
            //Pesquisar
        }
    }
}

int main() {
    TNoAVL *raiz = NULL;
    int num;
    do {
      printf("1 - Inserir numero, 0 - Continuar: ");
      //scanf("%d", &op);
      //if(op == 1) {
        scanf("%d", &num);
        insere(&raiz, num);
    //}
    } while(num != 0);

    imprime(raiz);

    int k;
    scanf("%d", &k);
    TNoAVL **buscar = busca(&raiz, k);
    if(buscar != NULL) removeNo(&raiz, buscar);

    //deletaArvore(&raiz);
    if(raiz == NULL) printf("Arvore vazia\n");
    else imprime(raiz);

    return 0;
}