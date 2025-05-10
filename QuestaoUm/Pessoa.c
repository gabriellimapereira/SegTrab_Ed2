#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"
#define preto 0
#define vermelho 1

InfoPessoa lerInfoPessoa()
{
    //preencher informações
}
Pessoa *alocarPessoa(InfoPessoa info)
{
    Pessoa *no;
    no = (Pessoa *) malloc(sizeof(Pessoa));
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
int insercaoPessoa(Pessoa **raiz, Pessoa *novoNo)
{
    int inseriu;
    inseriu = inserirPessoa(raiz, novoNo);
    if(inseriu)
    {
        (*raiz)->cor = preto;
    }
    return inseriu;
}
int inserirPessoa(Pessoa **raiz, Pessoa *novoNo)
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
            inseriu = inserirPessoa(&(*raiz)->esq, novoNo);
        }
        if((*raiz)->info.nome < novoNo->info.nome)
        {
            inseriu = inserirPessoa(&(*raiz)->dir, novoNo);
        }
        else
        {
            inseriu = 0;
        }
    }
    if(inseriu)
    {
        balanceamentoPessoa(raiz);
    }
}
void balanceamentoPessoa(Pessoa **raiz)
{
    if(corPessoa((*raiz)->esq) == preto && corPessoa((*raiz)->dir) == vermelho)
    {
        rotEsqPessoa(raiz);
    }
    if(corPessoa((*raiz)->esq) == vermelho && corPessoa((*raiz)->esq->esq) == vermelho)
    {
        rotDirPessoa(raiz);
    }
    if(corPessoa((*raiz)->esq) == vermelho && corPessoa((*raiz)->dir) == vermelho)
    {
        trocaCorPessoa(raiz);
    }
}
int corPessoa(Pessoa *raiz)
{
    int cor = preto;
    if(raiz)
    {
        cor = raiz->cor;
    }
    return cor;
}
void rotEsqPessoa(Pessoa **raiz)
{
    Pessoa *aux;
    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = vermelho;
    *raiz = aux;
}
void rotDirPessoa(Pessoa **raiz)
{
    Pessoa *aux;
    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = vermelho;
    *raiz = aux;
}
void trocaCorPessoa(Pessoa **raiz)
{
    (*raiz)->cor = !(*raiz)->cor;
    (*raiz)->esq->cor = !(*raiz)->esq->cor;
    (*raiz)->dir->cor = !(*raiz)->dir->cor;
}
void exibirPessoas(Pessoa *raiz)
{
    if(raiz)
    {
        exibirPessoas(raiz->esq);
        printf("Pessoa: %d\n", raiz->info.nome);
        exibirPessoas(raiz->dir);
    }
}
void liberarPessoas(Pessoa **raiz)
{
    if(*raiz)
    {
        liberarPessoas(&(*raiz)->esq);
        liberarPessoas(&(*raiz)->dir);
        free(*raiz);
    }
}