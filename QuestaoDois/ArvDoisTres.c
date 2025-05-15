#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"

ArvDoisTres* criarNo(int cep, ArvDoisTres *fEsq, ArvDoisTres *fCen) {
    ArvDoisTres *no = malloc(sizeof(ArvDoisTres));
    if (no) {
        no->infoUm.cep = cep;
        no->quantInfo = 1;
        no->infoDois.cep = 0;
        no->esq = fEsq;
        no->cen = fCen;
        no->dir = NULL;
    }
    return no;
}

void imprimirArv(ArvDoisTres *raiz, int nivel) {
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

void liberarArv(ArvDoisTres **raiz) {
    if (*raiz) {
        liberarArv(&(*raiz)->esq);
        liberarArv(&(*raiz)->cen);
        if ((*raiz)->quantInfo == 2)
            liberarArv(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }
}

void adicionarInfo(ArvDoisTres **no, Dados info, ArvDoisTres *subArvInfo) {
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

ArvDoisTres* quebrarNo(ArvDoisTres **no, Dados info, Dados *sobe, ArvDoisTres *filhoDir) {
    ArvDoisTres *maior;

    if (info.cep > (*no)->infoDois.cep) {
        *sobe = (*no)->infoDois;
        maior = criarNo(info.cep, (*no)->dir, filhoDir);
        (*no)->quantInfo = 1;
    } else if (info.cep > (*no)->infoUm.cep) {
        *sobe = info;
        maior = criarNo((*no)->infoDois.cep, filhoDir, (*no)->dir);
        (*no)->quantInfo = 1;
    } else {
        *sobe = (*no)->infoUm;
        maior = criarNo((*no)->infoDois.cep, (*no)->cen, (*no)->dir);
        (*no)->infoUm = info;
        (*no)->cen = filhoDir;
        (*no)->quantInfo = 1;
    }

    return maior;
}

ArvDoisTres* inserirNo(ArvDoisTres **raiz, ArvDoisTres *pai, Dados info, Dados *sobe) {
    ArvDoisTres *maiorNo = NULL;

    if (*raiz == NULL) {
        *raiz = criarNo(info.cep, NULL, NULL);
    } else {
        if ((*raiz)->esq == NULL) {
            if ((*raiz)->quantInfo == 1) {
                adicionarInfo(raiz, info, NULL);
            } else {
                maiorNo = quebrarNo(raiz, info, sobe, NULL);
                if (pai == NULL) {
                    *raiz = criarNo(sobe->cep, *raiz, maiorNo);
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
                        *raiz = criarNo(sobe->cep, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }

    return maiorNo;
}
