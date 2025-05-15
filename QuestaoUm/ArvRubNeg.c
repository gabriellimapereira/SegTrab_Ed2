#include <stdlib.h>
#include <stdio.h>
#include "prototipos.h"

ArvDoisTres* criarNo(Dados dado) {
    ArvDoisTres *novoNo = (ArvDoisTres*) malloc(sizeof(ArvDoisTres));
    if (novoNo != NULL) {
        novoNo->info = dado;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->cor = vermelho;
    }
    return novoNo;
}

void imprimirArvore(ArvDoisTres *r, int espaco) {
    if (r == NULL) return;

    const int DISTANCIA = 5;
    espaco += DISTANCIA;

    imprimirArvore(r->dir, espaco);

    printf("\n");
    for (int i = DISTANCIA; i < espaco; i++)
        printf(" ");
    
    printf("%d (%s)\n", r->info.cep, r->cor == 0 ? "P" : "V");

    imprimirArvore(r->esq, espaco);
}

void liberarArvore(ArvDoisTres *r) {
    if (r) {
        liberarArvore(r->esq);
        liberarArvore(r->dir);
        free(r);
    }
}

ArvDoisTres* buscaNo(ArvDoisTres *r, int valor) 
{
    ArvDoisTres *no;

    if (r->info.cep == valor) 
        no = r;
    else if (r->info.cep > valor)
        no = buscaNo(r->esq, valor);
    else if (r->info.cep < valor)
        no = buscaNo(r->dir, valor);
    else 
        no = NULL;
    
    return no;
}

int cor(ArvDoisTres *raiz) {
    int cor = preto;

    if (raiz) {
        cor = (*raiz).cor;
    }

    return cor;
}

void rotEsq(ArvDoisTres **raiz) {
    ArvDoisTres *aux = (**raiz).dir;

    (**raiz).dir = (*aux).esq;
    (*aux).esq = *raiz;
    (*aux).cor = (**raiz).cor;
    (**raiz).cor = vermelho;
    (*raiz) = aux;
}

void rotDir(ArvDoisTres **raiz) {
    ArvDoisTres *aux = (**raiz).esq;

    (**raiz).esq = (*aux).dir;
    (*aux).dir = *raiz;
    (*aux).cor = (**raiz).cor;
    (**raiz).cor = vermelho;
    (*raiz) = aux;
}

void trocaCor(ArvDoisTres **raiz) {
    (**raiz).cor = !((**raiz).cor);
    (**raiz).esq->cor = !((**raiz).esq->cor);
    (**raiz).dir->cor = !((**raiz).dir->cor);
}

void balanceamento(ArvDoisTres **raiz) 
{
    if (cor((**raiz).esq) == preto && cor((**raiz).dir) == vermelho)
    {
        rotEsq(raiz);
    } 

    if (cor((**raiz).esq) == vermelho) if (cor((**raiz).esq->esq) == vermelho)
    {
        rotDir(raiz);
    } 

    if (cor((**raiz).esq) == vermelho && cor((**raiz).dir) == vermelho)
    {
        trocaCor(raiz); 
    } 
}

int insereNo(ArvDoisTres **raiz, ArvDoisTres *novoNo) {
    int inseriu = 1;

    if (*raiz == NULL) 
        *raiz = novoNo;
    else if ((**raiz).info.cep > (*novoNo).info.cep) 
        inseriu = insereNo(&((**raiz).esq), novoNo);
    else if ((**raiz).info.cep < (*novoNo).info.cep) 
        inseriu = insereNo(&((**raiz).dir), novoNo);
    else 
        inseriu = 0;
    
    if (*raiz && inseriu) balanceamento(raiz);

    return inseriu;
}

int  insercao(ArvDoisTres **raiz, ArvDoisTres *novoNo) {
    int inseriu = insereNo(raiz, novoNo);

    if (inseriu) (**raiz).cor = preto;

    return inseriu;
}

ArvDoisTres* moveTwoEsqRed(ArvDoisTres *raiz) {
    trocaCor(&raiz);

    if (cor((*raiz).dir->esq) == vermelho) {
        rotDir(&((*raiz).dir));
        rotEsq(&raiz);
        trocaCor(&raiz);
    }

    return raiz;
}

ArvDoisTres* moveTwoDirRed(ArvDoisTres *raiz) {
    trocaCor(&raiz);

    if (cor((*raiz).esq->esq) == vermelho) {
        rotDir(&raiz);
        trocaCor(&raiz);
    }

    return raiz;
}

ArvDoisTres *removeMenor(ArvDoisTres *raiz) {
    if ((*raiz).esq == NULL) {
        free (raiz);
        return NULL;
    }

    if (cor((*raiz).esq) == preto && cor((*raiz).esq->esq) == preto) raiz =  moveTwoEsqRed((*raiz).esq);

    (*raiz).esq = removeMenor((*raiz).esq);
    balanceamento(&raiz);

    return raiz;
}

ArvDoisTres* procuraMenor(ArvDoisTres *raiz) {
    ArvDoisTres *aux = raiz;

    while (aux->esq != NULL) aux = aux->esq;

    return aux;
}

ArvDoisTres* removeNo(ArvDoisTres *raiz, int valor) {
    if (valor < (*raiz).info.cep) {
        if (cor((*raiz).esq) == preto && cor((*raiz).dir) == preto) raiz = moveTwoEsqRed(raiz);
        
        (*raiz).esq = removeNo((*raiz).esq, valor);

    } else {
        if (cor((*raiz).esq) == vermelho) rotDir(&raiz);

        if (valor == (*raiz).info.cep && ((*raiz).dir) == NULL) {
            free(raiz);
            return NULL;
        }

        if (cor((*raiz).dir) == preto && cor((*raiz).dir->esq) == preto) raiz = moveTwoDirRed(raiz);

        if (valor == (*raiz).info.cep) {
            ArvDoisTres *menor = procuraMenor((*raiz).dir);
            (*raiz).info = (*menor).info;
            (*raiz).dir = removeMenor((*raiz).dir);
        } else 
            (*raiz).dir = removeNo((*raiz).dir, valor);
    }

    balanceamento(&raiz);

    return raiz;
} 

void exibirCeps(ArvDoisTres *raiz) 
{
    if (raiz) 
    {
        exibirCeps(raiz->esq);
        printf("Cep: %d\n", raiz->info.cep);
        exibirCeps(raiz->dir);
    }
}

void exibirCidades(ArvDoisTres *raiz) 
{
    if (raiz) 
    {
        exibirCidades(raiz->esq);
        printf("Cidade: %d\n", raiz->info.cidade.nome);
        exibirCeps(raiz->info.cidade.ceps);
        exibirCidades(raiz->dir);
    }
}

void exibirPessoas(ArvDoisTres *raiz) 
{
    if (raiz) 
    {
        exibirPessoas(raiz->esq);
        printf("CPF: %d\n", raiz->info.pessoa.cpf);
        exibirPessoas(raiz->dir);
    }
}