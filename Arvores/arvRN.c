#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define preto 0
#define vermelho 1

typedef struct ArvRN {
    int info;
    int cor;
    struct ArvRN *esq, *dir;
} ArvRN;

ArvRN* criarNo(int dado) {
    ArvRN *novoNo = (ArvRN*) malloc(sizeof(ArvRN));
    if (novoNo != NULL) {
        novoNo->info = dado;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
    }
    return novoNo;
}

ArvRN* inserirNo(ArvRN *r, int dado) {
    if (r == NULL) 
        return criarNo(dado);
    
    if (dado < r->info) 
        r->esq = inserirNo(r->esq, dado);
    else if (dado > r->info) 
        r->dir = inserirNo(r->dir, dado);
    
    return r;
}

void imprimirEmOrdem(ArvRN *r) {
    if (r != NULL) {
        imprimirEmOrdem(r->esq);
        printf("%d ", r->info);
        imprimirEmOrdem(r->dir);
    }
}

void liberarArvore(ArvRN *r) {
    if (r != NULL) {
        liberarArvore(r->esq);
        liberarArvore(r->dir);
        free(r);
    }
}

int cor(ArvRN *r) {
    int cor = preto;

    if (r) {
        cor = (*r).cor;
    }

    return cor;
}

void rotEsq(ArvRN **r) {
    ArvRN *aux = (**r).dir;

    (**r).esq = (*aux).dir;
    (*aux).dir = *r;
    (*aux).cor = (**r).cor;
    (**r).cor = vermelho;
    (*r) = aux;
}

void rotDir(ArvRN **r) {
    ArvRN *aux = (**r).esq;

    (**r).dir = (*aux).esq;
    (*aux).esq = *r;
    (*aux).cor = (**r).cor;
    (**r).cor = vermelho;
    (*r) = aux;
}

void trocaCor(ArvRN **r) {
    (**r).cor = !((**r).cor);
    (**r).esq->cor = !((**r).esq->cor);
    (**r).dir->cor = !((**r).dir->cor);
}

void balanceamento(ArvRN **r) 
{
    if (cor((**r).esq) == preto && cor((**r).dir) == vermelho) rotEsq(r);

    if (cor((**r).esq) == vermelho) if (cor((**r).esq->esq) == vermelho) rotDir(&((**r).dir));

    if (cor((**r).esq) == vermelho && cor((**r).dir) == vermelho) trocaCor(r);
}

int insereNo(ArvRN **r, ArvRN *novoNo) {
    int inseriu = 1;

    if (*r == NULL) 
        *r = novoNo;
    else if ((**r).info > (*novoNo).info) 
        inseriu = insereNo(&((**r).esq), novoNo);
    else if ((**r).info < (*novoNo).info) 
        inseriu = insereNo(&((**r).dir), novoNo);
    else 
        inseriu = 0;
    
    if (*r && inseriu) balanceamento(r);
}

void insercao(ArvRN **r, ArvRN *novoNo) {
    int inseriu = insereNo(r, novoNo);

    if (inseriu) (**r).cor = preto;
}

ArvRN* moveTwoEsqRed(ArvRN *r) {
    trocaCor(&r);

    if (cor((*r).dir->esq) == vermelho) {
        rotDir(&((*r).dir));
        rotEsq(&r);
        trocaCor(&r);
    }

    return r;
}

ArvRN* moveTwoDirRed(ArvRN *r) {
    trocaCor(&r);

    if (cor((*r).esq->esq) == vermelho) {
        rotDir(&r);
        trocaCor(&r);
    }

    return r;
}

ArvRN *removeMenor(ArvRN *r) {
    if ((*r).esq == NULL) {
        free (r);
        return NULL;
    }

    if (cor((*r).esq) == preto && cor((*r).esq->esq) == preto) r =  moveTwoEsqRed((*r).esq);

    (*r).esq = removeMenor((*r).esq);
    balanceamento(&r);

    return r;
}

ArvRN* removeNo(ArvRN *r, int valor) {
    if (valor < (*r).info) {
        if (cor((*r).esq) == preto && cor((*r).dir) == preto) r = moveTwoEsqRed(r);
        
        (*r).esq = removeNo((*r).esq, valor);

    } else {
        if (cor((*r).esq) == vermelho) rotDir(&r);

        if (valor == (*r).info && ((*r).dir) == NULL) {
            free(r);
            return NULL;
        }

        if (cor((*r).dir) == preto && cor((*r).dir->esq) == preto) r = moveTwoDirRed(r);

        if (valor == (*r).info) {
            ArvRN *menor = procuraMenor((*r).dir);
            (*r).info = (*menor).info;
            (*r).dir = removeMenor((*r).dir);
        } else 
            (*r).dir = removeNo((*r).dir, valor);
    }

    balanceamento(&r);

    return r;
}

int main() {
    printf("inicializando a main...\n");

    ArvRN *raiz = NULL;

    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        raiz = inserirNo(raiz, valores[i]);
    }

    printf("\nárvore em ordem antes da remoção:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}