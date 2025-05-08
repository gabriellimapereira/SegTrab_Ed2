#include "prototipos.h"
#include <stdio.h>
#include <stdlib.h>

int lerCep() 
{
    //dispensável por hora
}

CEP* alocarCep(int numCep) 
{
    CEP *aux = (CEP*) malloc (sizeof(CEP));
    aux->dir = NULL;
    aux->esq = NULL;
    aux->info = numCep;
    aux->cor = vermelho;

    return aux;
}

CEP* buscaCep(CEP *raiz, int valor) 
{
    CEP *no;

    if (raiz->info == valor) 
        no = raiz;
    else if (raiz->info > valor)
        no = buscaCep(raiz->esq, valor);
    else if (raiz->info < valor)
        no = buscaCep(raiz->dir, valor);
    else 
        no = NULL;
    
    return no;
}

int corCep(CEP *raiz)
{
    int cor = preto;

    if (raiz) cor = (*raiz).cor;

    return cor;
}

void rotEsqCep(CEP **raiz)
{
    CEP *aux = (**raiz).dir;

    (**raiz).dir = (*aux).esq;
    (*aux).esq = *raiz;
    (*aux).cor = (**raiz).cor;
    (**raiz).cor = vermelho;
    (*raiz) = aux;
}

void rotDirCep(CEP **raiz)
{
    CEP *aux = (**raiz).esq;

    (**raiz).esq = (*aux).dir;
    (*aux).dir = *raiz;
    (*aux).cor = (**raiz).cor;
    (**raiz).cor = vermelho;
    (*raiz) = aux;
}

void trocaCorCep(CEP **raiz)
{
    (**raiz).cor = !((**raiz).cor);
    (**raiz).esq->cor = !((**raiz).esq->cor);
    (**raiz).dir->cor = !((**raiz).dir->cor);
}

void balanceamentoCep(CEP **raiz) 
{
    if (corCep((**raiz).esq) == preto && corCep((**raiz).dir) == vermelho) rotEsqCep(raiz);

    if (corCep((**raiz).esq) == vermelho) if (corCep((**raiz).esq->esq) == vermelho) rotDirCep(raiz);

    if (corCep((**raiz).esq) == vermelho && corCep((**raiz).dir) == vermelho) trocaCorCep(raiz); 
}

int inserirCep(CEP **raiz, CEP *novoNo)
{
    int inseriu = 1;
    if (*raiz == NULL)
        *raiz = novoNo;
    else if ((*raiz)->info > novoNo->info)
        inseriu = inserirCep(&((*raiz)->esq), novoNo);
    else if ((*raiz)->info < novoNo->info)
        inseriu = inserirCep(&((*raiz)->dir), novoNo);
    else 
        inseriu = 0;

    if (*raiz && inseriu) balanceamentoCep(raiz);
}

int insercaoCep(CEP **raiz, CEP *novoNo) 
{
    int inseriu = inserirCep(raiz, novoNo);

    if (inseriu) (**raiz).cor = preto;

    return inseriu;
}

int removerCep(CEP **raiz, int numCep) 
{
    //quero verificar melhor se a remoção está efetivamente funcionando
}

void exibirCeps(CEP *raiz)
{
    if (raiz)
    {
        exibirCeps(raiz->esq);
        printf("Cep: %d", raiz->info);
        exibirCeps(raiz->dir);
    }
}

void liberarCeps(CEP **raiz)
{
    if (*raiz)
    {
        liberarCeps(&((*raiz)->esq));
        liberarCeps(&((*raiz)->dir));
        free(*raiz);
    }
}