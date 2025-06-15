#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototiposDois.h"

ArvDoisTres* criarNo(Dados info, ArvDoisTres *fEsq, ArvDoisTres *fCen) 
{
    ArvDoisTres *no = malloc(sizeof(ArvDoisTres));
    if(no) 
    {
        no->infoUm = info;
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
    printf("Digite o nome da cidade: "); 
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);
    printf("Digite a populacao da cidade: "); scanf("%d", &info.populacao);
    info.ceps = NULL;
    return info;
}

void lerCep(char *cep) 
{
    printf("Digite o CEP: \n"); 
    setbuf(stdin, NULL);
    scanf("%[^\n]", cep);
}

int verificaCep(ArvDoisTres *raiz, const char *cep) 
{
    int existe = 0;
    if (raiz != NULL) 
    {
        if (strcmp(cep, raiz->infoUm.cep) == 0 || 
            (raiz->quantInfo == 2 && strcmp(cep, raiz->infoDois.cep) == 0)) 
        {
            existe = 1;
        } 
        else 
        {
            if (strcmp(cep, raiz->infoUm.cep) < 0) 
            {
                existe = verificaCep(raiz->esq, cep);
            } 
            else if (raiz->quantInfo == 1 || strcmp(cep, raiz->infoDois.cep) < 0) 
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
int verificaCepCidade(ArvDoisTres *cidades, const char *cep) 
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

int verificaCepEstado(Estado *inicio, const char *cep) 
{
    int existe = 0;
    if (inicio) 
    {
        existe = verificaCepCidade(inicio->info.cidades, cep);
        if (existe == 0)
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
    printf("Digite o nome da pessoa:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);
    printf("Digite o CPF:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.cpf);
    printf("Digite a data de nascimento:\n"); scanf("%d", &info.dataNasc);
    do {
        printf("Digite o CEP atual:\n"); 
        setbuf(stdin, NULL);
        scanf("%[^\n]", info.cepAtual);
        valido = (verificaCepEstado(raiz, info.cepAtual));
        if(!valido) 
        {
            printf("Digite um CEP válido!\n");
        }
    } while (!valido);
    do {
        printf("Digite o CEP natal:\n"); 
        setbuf(stdin, NULL);
        scanf("%[^\n]", info.cepNatal);
        valido = (verificaCepEstado(raiz, info.cepNatal));
        if(!valido)
        {
            printf("Digite um CEP válido!\n");
        }
    } while (!valido);
    return info;
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
    if (strcmp(info.cep, (*no)->infoUm.cep) > 0) 
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
    if (strcmp(info.cep, (*no)->infoDois.cep) > 0) 
    {
        *sobe = (*no)->infoDois;
        maior = criarNo(info, (*no)->dir, filhoDir);
        (*no)->quantInfo = 1;
    } 
    else if (strcmp(info.cep, (*no)->infoUm.cep) > 0) 
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

int infoNaoEstaNoNo(ArvDoisTres *no, Dados info) {
    int retorno = 1;

    if (strcmp(no->infoUm.cep, info.cep) == 0) {
        retorno = 0;
    } else if (no->quantInfo == 2 && strcmp(no->infoDois.cep, info.cep) == 0)
        retorno = 0;

    return 1;
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
            if (infoNaoEstaNoNo(*raiz, info)) {
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
        } 
        else 
        {
            if (infoNaoEstaNoNo(*raiz, info)) {
                if (strcmp(info.cep, (*raiz)->infoUm.cep) < 0) 
                {
                    maiorNo = inserirNo(&(*raiz)->esq, *raiz, info, sobe);
                } 
                else if ((*raiz)->quantInfo == 1 || strcmp(info.cep, (*raiz)->infoDois.cep) < 0) 
                {
                    maiorNo = inserirNo(&(*raiz)->cen, *raiz, info, sobe);
                } 
                else 
                {
                    maiorNo = inserirNo(&(*raiz)->dir, *raiz, info, sobe);
                }
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

ArvDoisTres* buscaNo(ArvDoisTres *raiz, const char *valor) 
{
    ArvDoisTres *no = NULL;
    if (raiz != NULL) 
    {
        if (strcmp(valor, raiz->infoUm.cep) == 0 || (raiz->quantInfo == 2 && strcmp(valor, raiz->infoDois.cep) == 0))
            no = raiz;
        else 
        {
            if (strcmp(valor, raiz->infoUm.cep) < 0) {
                no = buscaNo(raiz->esq, valor);
            } else if (raiz->quantInfo == 1 || strcmp(valor, raiz->infoDois.cep) < 0) {
                no = buscaNo(raiz->cen, valor);
            } else {
                no = buscaNo(raiz->dir, valor);
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
        printf("   Cep: %s\n", raiz->infoUm.cep);
        exibirCeps(raiz->cen);
        if (raiz->quantInfo == 2) 
        {
            printf("   Cep: %s\n", raiz->infoDois.cep);
            exibirCeps(raiz->dir);
        }
    }
}

void exibirCidades(ArvDoisTres *raiz) 
{
    if (raiz) 
    {
        exibirCidades(raiz->esq);
        printf("  Cidade: %s População: %d\n", raiz->infoUm.cidade.nome, raiz->infoUm.cidade.populacao);
        exibirCeps(raiz->infoUm.cidade.ceps);
        exibirCeps(raiz->cen);
        if (raiz->quantInfo == 2) 
        {
            printf("  Cidade: %s População: %d\n", raiz->infoDois.cidade.nome, raiz->infoDois.cidade.populacao);    
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
        printf("\nNome: %s CPF: %s ", raiz->infoUm.pessoa.nome, raiz->infoUm.pessoa.cpf);
        printf("Cidade natal: %s Cidade atual: %s", raiz->infoUm.pessoa.cepNatal, raiz->infoUm.pessoa.cepAtual);
        exibirPessoas(raiz->cen);
        if (raiz->quantInfo == 2) 
        {
            printf("\nNome: %s CPF: %s ", raiz->infoDois.pessoa.nome, raiz->infoDois.pessoa.cpf);
            printf("Cidade natal: %s Cidade atual: %s", raiz->infoDois.pessoa.cepNatal, raiz->infoDois.pessoa.cepAtual);
            exibirPessoas(raiz->dir);
        }
    }
}