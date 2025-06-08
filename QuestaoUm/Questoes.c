#include <stdio.h>
#include "prototiposUm.h"
#include <stdlib.h>

//Questões
//questao 1: Qual o estado mais populoso?
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

//questao 2: Qual a população da Capital de um determinado estado? 
void populacaoDaCapital(ArvRubNeg *raiz, int capital, int *populacao) 
{
    if (raiz)
    {
        if(raiz->info.cidade.nome == capital) 
        {
                *populacao = raiz->info.cidade.populacao;
        }
        populacaoDaCapital(raiz->esq, capital, populacao);
        populacaoDaCapital(raiz->dir, capital, populacao);
    }
}

//questao 3: Qual a cidade mais populosa de um estado sem ser a Capital? 
void cidadeMaisPopulosa(ArvRubNeg *raiz, int capital, ArvRubNeg **cidade) 
{
    if (raiz)
    {
        if(raiz->info.cidade.nome != capital)
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

//questao 4: Quantas pessoas não moram na cidade natal. 
void pessoasForaCepNatal(ArvRubNeg *pessoas, int *quantidade)
{
    if(pessoas)
    {
        if(pessoas->info.pessoa.cepNatal != pessoas->info.pessoa.cepAtual)
        {
            (*quantidade)++;
        }
        pessoasForaCepNatal(pessoas->esq, quantidade);
        pessoasForaCepNatal(pessoas->dir, quantidade);
    }
}

int estadoNatal(Estado *inicio, int cep, int *nomeCidade) 
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

//questao 5: Qual cidade natal de uma pessoa dado o CEP da cidade? 
int cidadeNatal(ArvRubNeg *cidades, int cep, int *nomeCidade)
{
    int existe = 0;
    if (cidades)
    {
        existe = verificaCep(cidades->info.cidade.ceps, cep);
        if(existe) 
        {
            *nomeCidade = cidades->info.cidade.nome;
        }
        else
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

//questao 6: Quantas pessoas nascidas em uma determinada cidade não mora na cidade natal?
void nascidosQueNaoMoram(ArvRubNeg *pessoas, int *quantidade, int cepCidade) 
{
    if (pessoas)
    {
        if (pessoas->info.pessoa.cepNatal == cepCidade)
        {
            if (pessoas->info.pessoa.cepAtual != cepCidade)
            {
                (*quantidade)++;
            }
        }
        nascidosQueNaoMoram(pessoas->esq, quantidade, cepCidade);
        nascidosQueNaoMoram(pessoas->dir, quantidade, cepCidade);
    }
}

//questao 7:Quantas pessoas que moram em uma determinada cidade não nasceram na cidade?
void moradoresNaoNascidos(ArvRubNeg *pessoas, int *quantidade, int cepCidade) 
{
    if (pessoas)
    {
        if (pessoas->info.pessoa.cepAtual == cepCidade)
        {
            if (pessoas->info.pessoa.cepNatal != cepCidade)
            {
                (*quantidade)++;
            }
        }
        moradoresNaoNascidos(pessoas->esq, quantidade, cepCidade);
        moradoresNaoNascidos(pessoas->dir, quantidade, cepCidade);
    }
}