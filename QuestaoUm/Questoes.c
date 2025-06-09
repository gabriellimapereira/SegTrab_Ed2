#include <stdio.h>
#include "prototiposUm.h"
#include <stdlib.h>
#include <string.h>

Estado* estadoMaisPopuloso(Estado *raiz) 
{
    Estado *aux = raiz;
    Estado *estado = raiz;
    if(raiz)
    {
        while(aux != NULL)
        { 
            if(aux->info.populacao > estado->info.populacao) 
            {
                estado = aux;
            }
            aux = aux->prox;
        }
    }
    return estado;
}

void populacaoDaCapital(ArvRubNeg *raiz, const char *capital, int *populacao) 
{
    if (raiz)
    {
        if(strcmp(raiz->info.cidade.nome, capital) == 0) 
        {
            *populacao = raiz->info.cidade.populacao;
        }
        populacaoDaCapital(raiz->esq, capital, populacao);
        populacaoDaCapital(raiz->dir, capital, populacao);
    }
}

void cidadeMaisPopulosa(ArvRubNeg *raiz, const char *capital, ArvRubNeg **cidade) 
{
    if (raiz)
    {
        if(strcmp(raiz->info.cidade.nome, capital) != 0)
        {
            if(raiz->info.cidade.populacao > (*cidade)->info.cidade.populacao)
            {
                *cidade = raiz;
            }
        }
        cidadeMaisPopulosa(raiz->esq, capital, cidade);
        cidadeMaisPopulosa(raiz->dir, capital, cidade);
    }
} 

void pessoasForaCepNatal(ArvRubNeg *pessoas, int *quantidade)
{
    if(pessoas)
    {
        if(strcmp(pessoas->info.pessoa.cepNatal, pessoas->info.pessoa.cepAtual) != 0)
        {
            (*quantidade)++;
        }
        pessoasForaCepNatal(pessoas->esq, quantidade);
        pessoasForaCepNatal(pessoas->dir, quantidade);
    }
}

int estadoNatal(Estado *inicio, const char *cep, char *nomeCidade) 
{
    int existe = 0;
    if(inicio) 
    {
        existe = cidadeNatal(inicio->info.cidades, cep, nomeCidade);
        if(existe == 0)
        {
           existe = estadoNatal(inicio->prox, cep, nomeCidade);
        }
    } 
    return existe;
}

int cidadeNatal(ArvRubNeg *cidades, const char *cep, char *nomeCidade)
{
    int existe = 0;
    if (cidades)
    {
        existe = verificaCep(cidades->info.cidade.ceps, cep);
        if(existe) 
        {
            strcpy(nomeCidade, cidades->info.cidade.nome);
        }
        else
        {
            existe = cidadeNatal(cidades->esq, cep, nomeCidade);
            if (existe == 0)
            {
                existe = cidadeNatal(cidades->dir, cep, nomeCidade);
            }
        }
    }
    return existe;
}

void nascidosQueNaoMoram(ArvRubNeg *pessoas, int *quantidade, const char *cepCidade) 
{
    if (pessoas)
    {
        if (strcmp(pessoas->info.pessoa.cepNatal, cepCidade) == 0)
        {
            if (strcmp(pessoas->info.pessoa.cepAtual, cepCidade) != 0)
            {
                (*quantidade)++;
            }
        }
        nascidosQueNaoMoram(pessoas->esq, quantidade, cepCidade);
        nascidosQueNaoMoram(pessoas->dir, quantidade, cepCidade);
    }
}

void moradoresNaoNascidos(ArvRubNeg *pessoas, int *quantidade, const char *cepCidade) 
{
    if (pessoas)
    {
        if (strcmp(pessoas->info.pessoa.cepAtual, cepCidade) == 0)
        {
            if (strcmp(pessoas->info.pessoa.cepNatal, cepCidade) != 0)
            {
                (*quantidade)++;
            }
        }
        moradoresNaoNascidos(pessoas->esq, quantidade, cepCidade);
        moradoresNaoNascidos(pessoas->dir, quantidade, cepCidade);
    }
}
