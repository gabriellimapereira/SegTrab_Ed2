#include <stdlib.h>
#include <stdio.h>
#include "prototiposUm.h"

ArvRubNeg* criarNo(Dados dado) 
{
    ArvRubNeg *novoNo = (ArvRubNeg*) malloc(sizeof(ArvRubNeg));
    if (novoNo != NULL) 
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

int verificaCep(ArvRubNeg *ceps, int cep) 
{
    int existe = 0;

    if (ceps) 
    {
        if (ceps->info.cep == cep) 
            existe = 1;
        else 
        {
            if (cep < ceps->info.cep) 
                existe = verificaCep(ceps->esq, cep);
            else 
                existe = verificaCep(ceps->dir, cep);
        }
    }

    return existe;
}

int verificaCepCidade(ArvRubNeg *cidades, int cep)
{
    int existe = 0;
    if (cidades)
    {
        existe = verificaCep(cidades->info.cidade.ceps, cep);
        if (existe == 0)
        {
            existe = verificaCepCidade(cidades->esq, cep);
            if (existe == 0) existe = verificaCepCidade(cidades->dir, cep);
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
        if(existe == 0) verificaCepEstado(inicio->prox, cep);
    } 
    return existe;
}

InfoPessoa lerInfoPessoa(Estado *raiz) 
{
    InfoPessoa info;
    int existe;
    printf("Digite o nome da pessoa: \n"); scanf("%d", &info.nome);
    printf("Digite o cpf: \n"); scanf("%d", &info.cpf);
    printf("Digite a data de nascimento: "); scanf("%d", &info.dataNasc);
    do 
    {
        printf("Digite o cep atual: \n"); scanf("%d", &info.cepAtual);
        existe = verificaCepEstado(raiz, info.cepAtual);
        if(existe == 0)
        {
            printf("Digite um cep válido!\n");
        }
    } while(existe != 0);

    do 
    {
        printf("Digite o cep natal: \n"); scanf("%d", &info.cepNatal);
        existe = verificaCepEstado(raiz, info.cepNatal);
        if(existe == 0)
        {
          printf("Digite um cep válido!\n");  
        }
    } while(existe != 0);
    return info;
}

void imprimirArvore(ArvRubNeg *r, int espaco) 
{
    if (r == NULL) return;
    const int DISTANCIA = 5;
    espaco += DISTANCIA;
    imprimirArvore(r->dir, espaco);
    printf("\n");
    for (int i = DISTANCIA; i < espaco; i++)
    {
        printf(" ");
    }
    printf("%d (%s)\n", r->info.cep, r->cor == 0 ? "P" : "V");
    imprimirArvore(r->esq, espaco);
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

ArvRubNeg* buscaNo(ArvRubNeg *r, int valor) 
{
    ArvRubNeg *no;
    if (r->info.cep == valor) 
        no = r;
    else if(r->info.cep > valor)
        no = buscaNo(r->esq, valor);
    else if(r->info.cep < valor)
        no = buscaNo(r->dir, valor);
    else
       no = NULL; 
    return no;
}

int cor(ArvRubNeg *raiz) 
{
    int cor = preto;
    if(raiz) cor = (*raiz).cor;
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
        rotEsq(raiz);
    if(cor((**raiz).esq) == vermelho && cor((**raiz).esq->esq) == vermelho)
        rotDir(raiz);
    if(cor((**raiz).esq) == vermelho && cor((**raiz).dir) == vermelho)
        trocaCor(raiz); 
}

int insereNo(ArvRubNeg **raiz, ArvRubNeg *novoNo) 
{
    int inseriu = 1;
    if(*raiz == NULL)
    {
        *raiz = novoNo;
    }
    else 
    {
        if((**raiz).info.cep > (*novoNo).info.cep) 
            inseriu = insereNo(&((**raiz).esq), novoNo);
        else if((**raiz).info.cep < (*novoNo).info.cep)
            inseriu = insereNo(&((**raiz).dir), novoNo);
        else 
            inseriu = 0; 
        if(inseriu)
            balanceamento(raiz);
    }
    return inseriu;
}

int  insercao(ArvRubNeg **raiz, ArvRubNeg *novoNo) 
{
    int inseriu = insereNo(raiz, novoNo);
    if(inseriu) (**raiz).cor = preto;
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
        return NULL;
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

ArvRubNeg* removeNo(ArvRubNeg *raiz, int valor) 
{
    if(valor < (*raiz).info.cep) 
    {
        if(cor((*raiz).esq) == preto && cor((*raiz).dir) == preto) raiz = moveTwoEsqRed(raiz);  
        (*raiz).esq = removeNo((*raiz).esq, valor);

    } 
    else 
    {
        if(cor((*raiz).esq) == vermelho) 
        {
            rotDir(&raiz);
        }
        if(valor == (*raiz).info.cep && ((*raiz).dir) == NULL) 
        {
            free(raiz);
            return NULL;
        }
        if (cor((*raiz).dir) == preto && cor((*raiz).dir->esq) == preto) 
        {
            raiz = moveTwoDirRed(raiz);
        }
        if (valor == (*raiz).info.cep) 
        {
            ArvRubNeg *menor = procuraMenor((*raiz).dir);
            (*raiz).info = (*menor).info;
            (*raiz).dir = removeMenor((*raiz).dir);
        } 
        else 
        {
            (*raiz).dir = removeNo((*raiz).dir, valor);
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
        printf("Cep: %d\n", raiz->info.cep);
        exibirCeps(raiz->dir);
    }
}

void exibirCidades(ArvRubNeg *raiz) 
{
    if(raiz) 
    {
        exibirCidades(raiz->esq);
        printf("Cidade: %d\n", raiz->info.cidade.nome);
        exibirCeps(raiz->info.cidade.ceps);
        exibirCidades(raiz->dir);
    }
}

void exibirPessoas(ArvRubNeg *raiz) 
{
    if(raiz) 
    {
        exibirPessoas(raiz->esq);
        printf("CPF: %d\n", raiz->info.pessoa.cpf);
        exibirPessoas(raiz->dir);
    }
}