#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "prototiposUm.h"

ArvRubNeg* criarNo(Dados dado) 
{
    ArvRubNeg *novoNo = (ArvRubNeg*) malloc(sizeof(ArvRubNeg));
    if(novoNo != NULL) 
    {
        novoNo->info = dado;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->cor = vermelho;
    }
    return novoNo;
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

int verificaCep(ArvRubNeg *ceps, const char *cep) 
{
    int existe = 0;
    if (ceps) 
    {
        int cmp = strcmp(cep, ceps->info.cep);
        if(cmp == 0)
        {
            existe = 1;
        }
        else if(cmp < 0)
        {
            existe = verificaCep(ceps->esq, cep);
        }
        else
        {
            existe = verificaCep(ceps->dir, cep);
        }
    }
    return existe;
}

int verificaCepCidade(ArvRubNeg *cidades, const char *cep)
{
    int existe = 0;
    if (cidades)
    {
        existe = verificaCep(cidades->info.cidade.ceps, cep);
        if(existe == 0)
        {
            existe = verificaCepCidade(cidades->esq, cep);
            if (existe == 0)
            {
                existe = verificaCepCidade(cidades->dir, cep);
            }
        }
    }
    return existe;
}

int verificaCepEstado(Estado *inicio, const char *cep) 
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
    int existe;
    printf("Digite o nome da pessoa: \n"); 
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);
    printf("Digite o cpf: \n"); 
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.cpf);
    printf("Digite a data de nascimento: "); scanf("%d", &info.dataNasc);
    do 
    {
        printf("Digite o cep atual: \n"); 
        setbuf(stdin, NULL);
        scanf("%[^\n]", info.cepAtual);
        existe = verificaCepEstado(raiz, info.cepAtual);
        if(existe == 0)
        {
            printf("Digite um cep válido!\n");
        }
    } while(existe == 0);
    do 
    {
        printf("Digite o cep natal: \n");
        setbuf(stdin, NULL);
        scanf("%[^\n]", info.cepNatal);
        existe = verificaCepEstado(raiz, info.cepNatal);
        if(existe == 0)
        {
          printf("Digite um cep válido!\n");  
        }
    } while(existe == 0);
    return info;
}

int verificaPessoa(ArvRubNeg *raiz, const char *nome)
{
    int existe = 0;
    if (raiz)
    {
        if (strcmp(raiz->info.pessoa.nome, nome) == 0)
        {
            existe = 1;
        }
        else
        {
            existe = verificaPessoa(raiz->esq, nome);
            if (!existe)
            {
                existe = verificaPessoa(raiz->dir, nome);
            }
        }
    }
    return existe;
}

void liberarArvore(ArvRubNeg *r) 
{
    if(r) 
    {
        liberarArvore(r->esq);
        liberarArvore(r->dir);
        free(r);
    }
}
ArvRubNeg* buscaNo(ArvRubNeg *r, const char *valor) 
{
    ArvRubNeg *no = NULL;
    if (r)
    {
        int cmp = strcmp(r->info.cep, valor);
        if (cmp == 0)
        {
            no = r;
        }
        else if (cmp > 0)
        {
            no = buscaNo(r->esq, valor);
        }
        else // cmp < 0
        {
            no = buscaNo(r->dir, valor);
        }
    }
    return no;
}

int cor(ArvRubNeg *raiz) 
{
    int cor = preto;
    if(raiz)
    {
        cor = (*raiz).cor;  
    } 
    return cor;
}

void rotEsq(ArvRubNeg **raiz) 
{
    ArvRubNeg *aux = (**raiz).dir;
    (**raiz).dir = (*aux).esq;
    (*aux).esq = *raiz;
    (*aux).cor = (**raiz).cor;
    (**raiz).cor = vermelho;
    (*raiz) = aux;
}

void rotDir(ArvRubNeg **raiz) 
{
    ArvRubNeg *aux = (**raiz).esq;
    (**raiz).esq = (*aux).dir;
    (*aux).dir = *raiz;
    (*aux).cor = (**raiz).cor;
    (**raiz).cor = vermelho;
    (*raiz) = aux;
}

void trocaCor(ArvRubNeg **raiz) 
{
    (**raiz).cor = !((**raiz).cor);
    (**raiz).esq->cor = !((**raiz).esq->cor);
    (**raiz).dir->cor = !((**raiz).dir->cor);
}

void balanceamento(ArvRubNeg **raiz) 
{
    if(cor((**raiz).esq) == preto && cor((**raiz).dir) == vermelho)
    {
        rotEsq(raiz);
    }
    if(cor((**raiz).esq) == vermelho && cor((**raiz).esq->esq) == vermelho)
    {
        rotDir(raiz);
    }
    if(cor((**raiz).esq) == vermelho && cor((**raiz).dir) == vermelho)
    {
        trocaCor(raiz);  
    }
}
int insereNo(ArvRubNeg **raiz, ArvRubNeg *novoNo) 
{
    int inseriu = 1;
    if (*raiz == NULL)
    {
        *raiz = novoNo;
    }
    else 
    {
        int cmp = strcmp((**raiz).info.cep, (*novoNo).info.cep);
        if (cmp > 0) 
        {
            inseriu = insereNo(&((**raiz).esq), novoNo);
        }
        else if (cmp < 0)
        {
            inseriu = insereNo(&((**raiz).dir), novoNo);
        }
        else
        {
            inseriu = 0;
        }
        if (inseriu)
        {
            balanceamento(raiz);
        }
    }
    return inseriu;
}

int  insercao(ArvRubNeg **raiz, ArvRubNeg *novoNo) 
{
    int inseriu = insereNo(raiz, novoNo);
    if(inseriu)
    {
        (**raiz).cor = preto;
    }
    return inseriu;
}

ArvRubNeg* moveTwoEsqRed(ArvRubNeg *raiz) 
{
    trocaCor(&raiz);
    if(cor((*raiz).dir->esq) == vermelho) 
    {
        rotDir(&((*raiz).dir));
        rotEsq(&raiz);
        trocaCor(&raiz);
    }
    return raiz;
}

ArvRubNeg* moveTwoDirRed(ArvRubNeg *raiz) 
{
    trocaCor(&raiz);
    if(cor((*raiz).esq->esq) == vermelho) 
    {
        rotDir(&raiz);
        trocaCor(&raiz);
    }
    return raiz;
}

ArvRubNeg *removeMenor(ArvRubNeg *raiz) 
{
    if((*raiz).esq == NULL) 
    {
        free (raiz);
        raiz = NULL;
    }
    if(cor((*raiz).esq) == preto && cor((*raiz).esq->esq) == preto)
    {
        raiz =  moveTwoEsqRed((*raiz).esq);
    }
    (*raiz).esq = removeMenor((*raiz).esq);
    
    balanceamento(&raiz);
    return raiz;
}

ArvRubNeg* procuraMenor(ArvRubNeg *raiz) 
{
    ArvRubNeg *aux = raiz;
    while (aux->esq != NULL) aux = aux->esq; 
    return aux;
}
ArvRubNeg* removeNo(ArvRubNeg *raiz, const char *valor) 
{
    if (strcmp(valor, raiz->info.cep) < 0) 
    {
        if (cor(raiz->esq) == preto && cor(raiz->esq->esq) == preto) 
            raiz = moveTwoEsqRed(raiz);
        raiz->esq = removeNo(raiz->esq, valor);
    } 
    else 
    {
        if (cor(raiz->esq) == vermelho) 
            rotDir(&raiz);
        if (strcmp(valor, raiz->info.cep) == 0 && raiz->dir == NULL) 
        {
            free(raiz);
            raiz = NULL;
        } else {
            if (cor(raiz->dir) == preto && cor(raiz->dir->esq) == preto) 
                raiz = moveTwoDirRed(raiz);
            if (strcmp(valor, raiz->info.cep) == 0) 
            {
                ArvRubNeg *menor = procuraMenor(raiz->dir);
                raiz->info = menor->info;
                raiz->dir = removeMenor(raiz->dir);
            } 
            else 
            {
                raiz->dir = removeNo(raiz->dir, valor);
            }
        }
    }

    balanceamento(&raiz);
    return raiz;
}

void exibirCeps(ArvRubNeg *raiz) 
{
    if(raiz) 
    {
        exibirCeps(raiz->esq);
        printf("   Cep: %s\n", raiz->info.cep);
        exibirCeps(raiz->dir);
    }
}

void exibirCidades(ArvRubNeg *raiz) 
{
    if(raiz) 
    {
        exibirCidades(raiz->esq);
        printf("  Cidade: %s\n", raiz->info.cidade.nome);
        if (raiz->info.cidade.ceps) 
        {
            printf("  Árvore de ceps dessa cidade: \n");
            exibirCeps(raiz->info.cidade.ceps);
        }
        exibirCidades(raiz->dir);
    }
}

void exibirPessoas(ArvRubNeg *raiz) 
{
    if(raiz) 
    {
        exibirPessoas(raiz->esq);
        printf("\nCPF: %s ", raiz->info.pessoa.cpf);
        printf("cidade natal: %s cidade atual: %s", raiz->info.pessoa.cepNatal, raiz->info.pessoa.cepAtual);
        exibirPessoas(raiz->dir);
    }
}