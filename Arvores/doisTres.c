#pragma once
#include <stdlib.h>

// CÓDIGO DO DIABO

typedef struct DoisTres {
    int infoUm, infoDois, quantInfo;
    DoisTres *esq, *cen, *dir;
} DoisTres;

DoisTres* criaNo(int info, DoisTres *fEsq, DoisTres *fCen)
{
    DoisTres *no;
    no = (DoisTres*) malloc(sizeof(DoisTres));

    if (no != NULL)
    {
        no->infoUm = info;
        no->esq = fEsq;
        no->cen = fCen;
        no->dir = NULL;
        no->quantInfo = 1;
    }

    return no;
}

void adicionaInfo(DoisTres **no, int info, DoisTres *subArvInfo)
{
    if (info > (*no)->infoUm)
    {
        (*no)->infoDois = info;
        (*no)->dir = subArvInfo;
    }
    else 
    {
        (*no)->infoDois = (*no)->infoUm;
        (*no)->infoUm = info;
        (*no)->dir = (*no)->cen;
        (*no)->cen = subArvInfo;
    }

    (*no)->quantInfo = 2;
}

DoisTres* quebraNo(DoisTres **no, int info, int *sobe, DoisTres *filhoDir)
{
    DoisTres *maior;

    if (info > (*no)->infoDois)
    {
        *sobe = (*no)->infoDois;
        maior = criaNo(info, (*no)->dir, filhoDir);
        (*no)->quantInfo = 1;
    }
    else if (info > (*no)->infoUm) 
    {
        *sobe = info;
        maior = criaNo((*no)->infoDois, filhoDir, (*no)->dir);
        (*no)->quantInfo = 1;
    }
    else 
    {
        *sobe = (*no)->infoUm;
        maior = criaNo((*no)->infoDois, (*no)->cen, (*no)->dir);
        (*no)->infoUm = info;
        (*no)->cen = filhoDir;
        (*no)->quantInfo = 1;
    }

    return maior;
}

DoisTres* insere(DoisTres **raiz, DoisTres *pai, int info, int *sobe) 
{
    if (*raiz == NULL)
    {
        *raiz = criaNo(info, NULL, NULL);
    }
    else 
    {
        DoisTres *maiorNo;
        if (ehFolha(*raiz))
        {
            if ((**raiz).quantInfo == 1)
            {
                adicionaInfo(raiz, info, NULL);
            }
            else 
            {
                maiorNo = quebraNo(raiz, info, sobe, NULL);
                if (pai == NULL)
                {
                    *raiz = criaNo(*sobe, *raiz, maiorNo);
                    maiorNo = NULL;
                }
                else 
                {
                    if (info < (*raiz)->infoUm)
                        maiorNo = insere(&((*raiz)->esq), info, *raiz, sobe);
                    else if ((*raiz)->quantInfo == 1 || info < (*raiz)->infoDois)
                        maiorNo = insere(&((*raiz)->cen), info, *raiz, sobe);
                    else if (info > (*raiz)->infoDois)
                        maiorNo = insere(&((*raiz)->dir), info, *raiz, sobe);
                }
            }
        }
        else  
        {

        }
    }
}