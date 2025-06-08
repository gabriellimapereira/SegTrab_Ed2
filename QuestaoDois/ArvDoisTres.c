#include <stdio.h>
#include <stdlib.h>
#include "prototiposDois.h"

ArvDoisTres* criarNo(Dados info, ArvDoisTres *fEsq, ArvDoisTres *fCen) 
{
    ArvDoisTres *no = malloc(sizeof(ArvDoisTres));
    if(no) 
    {
        no->infoUm.cep = info.cep;
        no->quantInfo = 1;
        no->esq = fEsq;
        no->cen = fCen;
        no->dir = NULL;
    }
    return no;
}

InfoCidade lerInfoCidade()
{
    InfoCidade info;
    printf("Digite o nome da cidade: "); scanf("%d", &info.nome);
    printf("Digite a populacao da cidade: "); scanf("%d", &info.populacao);
    info.ceps = NULL;
    return info;
}

int lerCep() 
{
    int info;
    printf("Digite o CEP: \n"); scanf("%d", &info);
    return info;
}

int verificaCep(ArvDoisTres *raiz, int cep) 
{
    int existe = 0;
    if (raiz != NULL) 
    {
        if (cep == raiz->infoUm.cep || (raiz->quantInfo == 2 && cep == raiz->infoDois.cep))
        {
            existe = 1;
        } 
        else 
        {
            if (cep < raiz->infoUm.cep) 
            {
                existe = verificaCep(raiz->esq, cep);
            } 
            else if (raiz->quantInfo == 1 || cep < raiz->infoDois.cep) 
            {
                existe = verificaCep(raiz->cen, cep);
            } 
            else
            {
                existe = verificaCep(raiz->dir, cep);
            }
        }
    }
    return existe;
}

int verificaCepCidade(ArvDoisTres *cidades, int cep) 
{
    int existe = 0;
    if (cidades != NULL) 
    {
        if (verificaCep(cidades->infoUm.cidade.ceps, cep)) 
        {
            existe = 1;
        } 
        else if (cidades->quantInfo == 2 && verificaCep(cidades->infoDois.cidade.ceps, cep)) 
        {
            existe = 1;
        } 
        else 
        {
            existe = verificaCepCidade(cidades->esq, cep);
            if (existe == 0)
                existe = verificaCepCidade(cidades->cen, cep);
            if (existe == 0)
                existe = verificaCepCidade(cidades->dir, cep);
        }
    }
    return existe;
}

int verificaCepEstado(Estado *inicio, int cep) 
{
    int existe = 0;
    if(inicio) 
    {
        existe = verificaCepCidade(inicio->info.cidades, cep);
        if(existe == 0)
        {
           existe = verificaCepEstado(inicio->prox, cep);
        }
    } 
    return existe;
}

InfoPessoa lerInfoPessoa(Estado *raiz) 
{
    InfoPessoa info;
    int valido = 0;
    printf("Digite o nome da pessoa:\n"); scanf("%d", &info.nome);
    printf("Digite o CPF:\n"); scanf("%d", &info.cpf);
    printf("Digite a data de nascimento:\n"); scanf("%d", &info.dataNasc);
    do {
        printf("Digite o CEP atual:\n"); scanf("%d", &info.cepAtual);
        valido = (verificaCepEstado(raiz, info.cepAtual));
        if(!valido) 
        {
            printf("Digite um CEP válido!\n");
        }
    } while (!valido);
    do {
        printf("Digite o CEP natal:\n"); scanf("%d", &info.cepNatal);
        valido = (verificaCepEstado(raiz, info.cepNatal));
        if(!valido)
        {
            printf("Digite um CEP válido!\n");
        }
    } while (!valido);
    return info;
}

void imprimirArv(ArvDoisTres *raiz, int nivel) 
{
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

void liberarArv(ArvDoisTres **raiz) 
{
    if(*raiz) 
    {
        liberarArv(&(*raiz)->esq);
        liberarArv(&(*raiz)->cen);
        if((*raiz)->quantInfo == 2)
        {
            liberarArv(&(*raiz)->dir);
        }
        free(*raiz);
        *raiz = NULL;
    }
}

void adicionarInfo(ArvDoisTres **no, Dados info, ArvDoisTres *subArvInfo) 
{
    if (info.cep > (*no)->infoUm.cep) 
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

ArvDoisTres* quebrarNo(ArvDoisTres **no, Dados info, Dados *sobe, ArvDoisTres *filhoDir) 
{
    ArvDoisTres *maior;
    if (info.cep > (*no)->infoDois.cep) 
    {
        *sobe = (*no)->infoDois;
        maior = criarNo(info, (*no)->dir, filhoDir);
        (*no)->quantInfo = 1;
    } 
    else if (info.cep > (*no)->infoUm.cep) 
    {
        *sobe = info;
        maior = criarNo((*no)->infoDois, filhoDir, (*no)->dir);
        (*no)->quantInfo = 1;
    }
    else 
    {
        *sobe = (*no)->infoUm;
        maior = criarNo((*no)->infoDois, (*no)->cen, (*no)->dir);
        (*no)->infoUm = info;
        (*no)->cen = filhoDir;
        (*no)->quantInfo = 1;
    }
    return maior;
}

ArvDoisTres* inserirNo(ArvDoisTres **raiz, ArvDoisTres *pai, Dados info, Dados *sobe) 
{
    ArvDoisTres *maiorNo = NULL;
    if (*raiz == NULL) 
    {
        *raiz = criarNo(info, NULL, NULL);
    } 
    else 
    {
        if ((*raiz)->esq == NULL) 
        {
            if ((*raiz)->quantInfo == 1) 
            {
                adicionarInfo(raiz, info, NULL);
            } 
            else 
            {
                maiorNo = quebrarNo(raiz, info, sobe, NULL);
                if (pai == NULL) 
                {
                    *raiz = criarNo(*sobe, *raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        } 
        else 
        {
            if (info.cep < (*raiz)->infoUm.cep) 
            {
                maiorNo = inserirNo(&(*raiz)->esq, *raiz, info, sobe);
            } 
            else if ((*raiz)->quantInfo == 1 || info.cep < (*raiz)->infoDois.cep) 
            {
                maiorNo = inserirNo(&(*raiz)->cen, *raiz, info, sobe);
            } 
            else 
            {
                maiorNo = inserirNo(&(*raiz)->dir, *raiz, info, sobe);
            }
            if (maiorNo != NULL) 
            {
                if ((*raiz)->quantInfo == 1) 
                {
                    adicionarInfo(raiz, *sobe, maiorNo);
                    maiorNo = NULL;
                } 
                else 
                {
                    maiorNo = quebrarNo(raiz, *sobe, sobe, maiorNo);
                    if (pai == NULL) 
                    {
                        *raiz = criarNo(*sobe, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}

ArvDoisTres* buscaNo(ArvDoisTres *raiz, int cep) 
{
    ArvDoisTres *no = NULL;
    if (raiz != NULL) 
    {
        if(cep == raiz->infoUm.cep || (raiz->quantInfo == 2 && cep == raiz->infoDois.cep))
            no = raiz;
        else 
        {
            if (cep < raiz->infoUm.cep) {
                no = buscaNo(raiz->esq, cep);
            } else if (raiz->quantInfo == 1 || cep < raiz->infoDois.cep) {
                no = buscaNo(raiz->cen, cep);
            } else {
                no = buscaNo(raiz->dir, cep);
            }
        }
    }
    return no;
}

void exibirCeps(ArvDoisTres *raiz) 
{
    if (raiz) 
    {
        exibirCeps(raiz->esq);
        printf("Cep: %d\n", raiz->infoUm.cep);
        exibirCeps(raiz->cen);
        if (raiz->quantInfo == 2) 
        {
            printf("Cep: %d\n", raiz->infoDois.cep);
            exibirCeps(raiz->dir);
        }
    }
}

void exibirCidades(ArvDoisTres *raiz) 
{
    if (raiz) 
    {
        exibirCidades(raiz->esq);
        printf("Cidade: %d\n", raiz->infoUm.cidade.nome);
        exibirCeps(raiz->infoUm.cidade.ceps);
        exibirCeps(raiz->cen);
        if (raiz->quantInfo == 2) 
        {
            printf("Cidade: %d\n", raiz->infoDois.cidade.nome);    
            exibirCeps(raiz->infoDois.cidade.ceps);
            exibirCidades(raiz->dir);
        }
    }
}

void exibirPessoas(ArvDoisTres *raiz) 
{
    if (raiz) 
    {
        exibirPessoas(raiz->esq);
        printf("CPF: %d\n", raiz->infoUm.pessoa.cpf);
        exibirPessoas(raiz->cen);
        if (raiz->quantInfo == 2) 
        {
            printf("CPF: %d\n", raiz->infoDois.pessoa.cpf);
            exibirPessoas(raiz->dir);
        }
    }
}