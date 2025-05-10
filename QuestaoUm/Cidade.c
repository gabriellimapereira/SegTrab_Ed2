#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"
#define preto 0
#define vermelho 1

InfoCidade lerInfoCidade()
{
    //preencher informações
}
Cidade *alocarCidade(InfoCidade info)
{
    Cidade *no;
    no = (Cidade *) malloc(sizeof(Cidade));
    if(no == NULL)
    {
        printf("Erro de alocacao.\n");
        exit(1);
    }
    no->dir = NULL;
    no->esq = NULL;
    no->cor = vermelho;
    no->info = info;
    return no;
}
int insercaoCidade(Cidade **raiz, Cidade *novoNo)
{
    int inseriu;
    inseriu = inserirCidade(raiz, novoNo);
    if(inseriu)
    {
        (*raiz)->cor = preto;
    }
    return inseriu;
}
int inserirCidade(Cidade **raiz, Cidade *novoNo)
{
    int inseriu = 1;
    if(*raiz == NULL)
    {
        (*raiz) = novoNo;
    }
    else
    {
        if((*raiz)->info.nome > novoNo->info.nome)
        {
            inseriu = inserirCidade(&(*raiz)->esq, novoNo);
        }
        if((*raiz)->info.nome < novoNo->info.nome)
        {
            inseriu = inserirCidade(&(*raiz)->dir, novoNo);
        }
        else
        {
            inseriu = 0;
        }
    }
    if(inseriu)
    {
        balanceamentoCidade(raiz);
    }
}
void balanceamentoCidade(Cidade **raiz)
{
    if(corCidade((*raiz)->esq) == preto && corCidade((*raiz)->dir) == vermelho)
    {
        rotEsqCidade(raiz);
    }
    if(corCidade((*raiz)->esq) == vermelho && corCidade((*raiz)->esq->esq) == vermelho)
    {
        rotDirCidade(raiz);
    }
    if(corCidade((*raiz)->esq) == vermelho && corCidade((*raiz)->dir) == vermelho)
    {
        trocaCorCidade(raiz);
    }
}
int corCidade(Cidade *raiz)
{
    int cor = preto;
    if(raiz)
    {
        cor = raiz->cor;
    }
    return cor;
}
void rotEsqCidade(Cidade **raiz)
{
    Cidade *aux;
    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = vermelho;
    *raiz = aux;
}
void rotDirCidade(Cidade **raiz)
{
    Cidade *aux;
    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = vermelho;
    *raiz = aux;
}
void trocaCorCidade(Cidade **raiz)
{
    (*raiz)->cor = !(*raiz)->cor;
    (*raiz)->esq->cor = !(*raiz)->esq->cor;
    (*raiz)->dir->cor = !(*raiz)->dir->cor;
}
void exibirCidades(Cidade *raiz)
{
    if(raiz)
    {
        exibirCidades(raiz->esq);
        printf("Cidade: %d\n", raiz->info.nome);
        exibirCidades(raiz->dir);
    }
}
void liberarCidades(Cidade **raiz)
{
    if(*raiz)
    {
        liberarCidades(&(*raiz)->esq);
        liberarCidades(&(*raiz)->dir);
        free(*raiz);
    }
}