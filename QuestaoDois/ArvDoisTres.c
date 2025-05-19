#include <stdio.h>
#include <stdlib.h>
#include "prototiposDois.h"

ArvRubNeg* criarNo(Dados info, ArvRubNeg *fEsq, ArvRubNeg *fCen) {
    ArvRubNeg *no = malloc(sizeof(ArvRubNeg));
    if (no) {
        no->infoUm.cep = info.cep;
        no->quantInfo = 1;
        no->esq = fEsq;
        no->cen = fCen;
        no->dir = NULL;
    }
    return no;
}

void imprimirArv(ArvRubNeg *raiz, int nivel) {
    if (raiz == NULL) return;

    imprimirArv(raiz->dir, nivel + 1);

    for (int i = 0; i < nivel; i++)
        printf("   ");

    if (raiz->quantInfo == 1)
        printf("[%d]\n", raiz->infoUm.cep);
    else
        printf("[%d|%d]\n", raiz->infoUm.cep, raiz->infoDois.cep);

    imprimirArv(raiz->cen, nivel + 1);
    imprimirArv(raiz->esq, nivel + 1);
}

void liberarArv(ArvRubNeg **raiz) {
    if (*raiz) {
        liberarArv(&(*raiz)->esq);
        liberarArv(&(*raiz)->cen);
        if ((*raiz)->quantInfo == 2)
            liberarArv(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }
}

void adicionarInfo(ArvRubNeg **no, Dados info, ArvRubNeg *subArvInfo) {
    if (info.cep > (*no)->infoUm.cep) {
        (*no)->infoDois = info;
        (*no)->dir = subArvInfo;
    } else {
        (*no)->infoDois = (*no)->infoUm;
        (*no)->infoUm = info;
        (*no)->dir = (*no)->cen;
        (*no)->cen = subArvInfo;
    }
    (*no)->quantInfo = 2;
}

ArvRubNeg* quebrarNo(ArvRubNeg **no, Dados info, Dados *sobe, ArvRubNeg *filhoDir) {
    ArvRubNeg *maior;

    if (info.cep > (*no)->infoDois.cep) {
        *sobe = (*no)->infoDois;
        maior = criarNo(info, (*no)->dir, filhoDir);
        (*no)->quantInfo = 1;
    } else if (info.cep > (*no)->infoUm.cep) {
        *sobe = info;
        maior = criarNo((*no)->infoDois, filhoDir, (*no)->dir);
        (*no)->quantInfo = 1;
    } else {
        *sobe = (*no)->infoUm;
        maior = criarNo((*no)->infoDois, (*no)->cen, (*no)->dir);
        (*no)->infoUm = info;
        (*no)->cen = filhoDir;
        (*no)->quantInfo = 1;
    }

    return maior;
}

ArvRubNeg* inserirNo(ArvRubNeg **raiz, ArvRubNeg *pai, Dados info, Dados *sobe) {
    ArvRubNeg *maiorNo = NULL;

    if (*raiz == NULL) {
        *raiz = criarNo(info, NULL, NULL);
    } else {
        if ((*raiz)->esq == NULL) {
            if ((*raiz)->quantInfo == 1) {
                adicionarInfo(raiz, info, NULL);
            } else {
                maiorNo = quebrarNo(raiz, info, sobe, NULL);
                if (pai == NULL) {
                    *raiz = criarNo(*sobe, *raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        } else {
            if (info.cep < (*raiz)->infoUm.cep) {
                maiorNo = inserirNo(&(*raiz)->esq, *raiz, info, sobe);
            } else if ((*raiz)->quantInfo == 1 || info.cep < (*raiz)->infoDois.cep) {
                maiorNo = inserirNo(&(*raiz)->cen, *raiz, info, sobe);
            } else {
                maiorNo = inserirNo(&(*raiz)->dir, *raiz, info, sobe);
            }

            if (maiorNo != NULL) {
                if ((*raiz)->quantInfo == 1) {
                    adicionarInfo(raiz, *sobe, maiorNo);
                    maiorNo = NULL;
                } else {
                    maiorNo = quebrarNo(raiz, *sobe, sobe, maiorNo);
                    if (pai == NULL) {
                        *raiz = criarNo(*sobe, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }

    return maiorNo;
}

void exibirCeps(ArvRubNeg *raiz) 
{
    if (raiz) 
    {
        exibirCeps(raiz->esq);
        printf("Cep: %d\n", raiz->infoUm.cep);
        exibirCeps(raiz->cen);
        if (raiz->quantInfo == 2) {
            printf("Cep: %d\n", raiz->infoDois.cep);
            exibirCeps(raiz->dir);
        }
    }
}

void exibirCidades(ArvRubNeg *raiz) 
{
    if (raiz) 
    {
        exibirCidades(raiz->esq);
        printf("Cidade: %d\n", raiz->infoUm.cidade.nome);
        exibirCeps(raiz->infoUm.cidade.ceps);
        exibirCeps(raiz->cen);
        if (raiz->quantInfo == 2) {
            printf("Cidade: %d\n", raiz->infoDois.cidade.nome);    
            exibirCeps(raiz->infoDois.cidade.ceps);
            exibirCidades(raiz->dir);
        }
    }
}

void exibirPessoas(ArvRubNeg *raiz) 
{
    if (raiz) 
    {
        exibirPessoas(raiz->esq);
        printf("CPF: %d\n", raiz->infoUm.pessoa.cpf);
        exibirPessoas(raiz->cen);
        if (raiz->quantInfo == 2) {
            printf("CPF: %d\n", raiz->infoDois.pessoa.cpf);
            exibirPessoas(raiz->dir);
        }
    }
}