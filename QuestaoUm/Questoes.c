#include <stdio.h>
#include "prototiposUm.h"
#include <stdlib.h>
#include <string.h>

//Questão 01
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

//Questão 02
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

// Questão 03
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

// Questão 04
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

// parte da questão 05
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

// Questão 05
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

// Questão 06
void nascidosQueNaoMoram(ArvRubNeg *pessoas, int *quantidade, ArvRubNeg *cidade) 
{
    if (pessoas)
    {
        if (verificaCep(cidade->info.cidade.ceps, pessoas->info.pessoa.cepNatal))
        {
            if (verificaCep(cidade->info.cidade.ceps, pessoas->info.pessoa.cepAtual) == 0)
            {
                (*quantidade)++;
            }
        }
        nascidosQueNaoMoram(pessoas->esq, quantidade, cidade);
        nascidosQueNaoMoram(pessoas->dir, quantidade, cidade);
    }
}

// Questão 07
void moradoresNaoNascidos(ArvRubNeg *pessoas, int *quantidade, ArvRubNeg *cidade) {
    if (pessoas)
    {
        if (verificaCep(cidade->info.cidade.ceps, pessoas->info.pessoa.cepAtual))
        {
            if (verificaCep(cidade->info.cidade.ceps, pessoas->info.pessoa.cepNatal) == 0)
            {
                (*quantidade)++;
            }
        }
        nascidosQueNaoMoram(pessoas->esq, quantidade, cidade);
        nascidosQueNaoMoram(pessoas->dir, quantidade, cidade);
    }
}
