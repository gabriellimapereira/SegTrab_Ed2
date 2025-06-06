#include "prototiposDois.h"
#include <stdlib.h>

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
void populacaoDaCapital(ArvDoisTres *raiz, int capital, int *populacao) 
{
    if(raiz)
    {
        int flag = 0;
        if (raiz->quantInfo == 2)
        {
            if (raiz->infoDois.cidade.nome == capital) 
            {
                    *populacao = raiz->infoDois.cidade.populacao;
                    flag = 1;
            }
        }
        if(!flag && raiz->infoUm.cidade.nome == capital) 
        {
                *populacao = raiz->infoUm.cidade.populacao;
                flag = 1;
        }
        if (!flag) 
        {
            populacaoDaCapital(raiz->esq, capital, populacao);
            populacaoDaCapital(raiz->cen, capital, populacao);
            if (raiz->quantInfo == 2) populacaoDaCapital(raiz->dir, capital, populacao);
        }
    }
}

//questao 3: Qual a cidade mais populosa de um estado sem ser a Capital?
void cidadeMaisPopulosa(ArvDoisTres *raiz, int capital, ArvDoisTres**cidade)
{
    if(raiz)
    {
        if(raiz->quantInfo == 2)
        {
            if(raiz->infoDois.cidade.nome != capital)
            {
                if(raiz->infoDois.cidade.populacao > (*cidade)->infoUm.cidade.populacao)
                {
                    (*cidade)->infoUm = raiz->infoDois;
                }
            }
        }
        if(raiz->infoUm.cidade.nome != capital)
        {
            if(raiz->infoUm.cidade.populacao > (*cidade)->infoUm.cidade.populacao)
            {
                (*cidade)->infoUm = raiz->infoUm;
            }
        }
        cidadeMaisPopulosa(raiz->esq, capital, cidade);
        cidadeMaisPopulosa(raiz->cen, capital, cidade);
        if(raiz->quantInfo == 2) cidadeMaisPopulosa(raiz->dir, capital, cidade);          
    }
}
//questao 4: Quantas pessoas não moram na cidade natal.
void pessoasForaCepNatal(ArvDoisTres *pessoas, int *quantidade)
{
    if(pessoas)
    {
        if(pessoas->infoUm.pessoa.cepAtual != pessoas->infoUm.pessoa.cepNatal)
        {
            (*quantidade)++;
        }
        if(pessoas->quantInfo == 2)
        {
            if(pessoas->infoDois.pessoa.cepAtual != pessoas->infoDois.pessoa.cepNatal)
            {
                (*quantidade)++;
            }
        }
        pessoasForaCepNatal(pessoas->esq, quantidade);
        pessoasForaCepNatal(pessoas->cen, quantidade);
        if(pessoas->quantInfo == 2) pessoasForaCepNatal(pessoas->dir, quantidade);
    }
}

//questao 5: Qual cidade natal de uma pessoa dado o CEP da cidade? 
int cidadeNatal(ArvDoisTres *cidades, int cep, int nomeCidade)
{
    int existe = 0;
    if (cidades)
    {
        if(cidades->quantInfo == 2)
        {
            existe = verificaCep(cidades->infoDois.cidade.ceps, cep);
            if(existe)
            {
                nomeCidade = cidades->infoDois.cidade.nome;
            }
            else
            {
                existe = verificaCepCidade(cidades->esq, cep);
                if (!existe)
                {
                    existe = verificaCepCidade(cidades->cen, cep);
                    if(!existe)
                    {
                        existe = verificaCepCidade(cidades->dir, cep);
                    }
                }
            }
        }
        if(!existe)
        {
            existe = verificaCep(cidades->infoUm.cidade.ceps, cep);
            if (existe) 
            {
                nomeCidade = cidades->infoUm.cidade.nome;
            }
            else
            {
                existe = verificaCepCidade(cidades->esq, cep);
                if (!existe)
                {
                    existe = verificaCepCidade(cidades->cen, cep);
                }
            }
        }
    }
    return existe;
}

//questao 6: Quantas pessoas nascidas em uma determinada cidade não mora na cidade natal?
void nascidosQueNaoMoram(ArvDoisTres *pessoas, int *quantidade, int cepCidade) 
{
    if (pessoas)
    {
        if(pessoas->infoUm.pessoa.cepNatal == cepCidade)
        {
            if(pessoas->infoUm.pessoa.cepAtual != cepCidade)
            {
                (*quantidade)++;
            }
        }
        if(pessoas->quantInfo == 2)
        {
            if(pessoas->infoDois.pessoa.cepNatal == cepCidade)
            {
                if(pessoas->infoDois.pessoa.cepAtual != cepCidade)
                {
                    (*quantidade)++;
                }
            }
        }
        nascidosQueNaoMoram(pessoas->esq, quantidade, cepCidade);
        nascidosQueNaoMoram(pessoas->cen, quantidade, cepCidade);
        if(pessoas->quantInfo == 2) nascidosQueNaoMoram(pessoas->dir, quantidade, cepCidade);
    }
}

//questao 7:Quantas pessoas que moram em uma determinada cidade não nasceram na cidade?
void moradoresNaoNascidos(ArvDoisTres *pessoas, int *quantidade, int cepCidade) 
{
    if (pessoas)
    {
        if(pessoas->infoUm.pessoa.cepAtual == cepCidade)
        {
            if(pessoas->infoUm.pessoa.cepNatal != cepCidade)
            {
                (*quantidade)++;
            }
        }
        if(pessoas->quantInfo == 2)
        {
            if(pessoas->infoDois.pessoa.cepAtual == cepCidade)
            {
                if(pessoas->infoDois.pessoa.cepNatal != cepCidade)
                {
                    (*quantidade)++;
                }
            }
        }
        moradoresNaoNascidos(pessoas->esq, quantidade, cepCidade);
        moradoresNaoNascidos(pessoas->cen, quantidade, cepCidade);
        if(pessoas->quantInfo == 2) moradoresNaoNascidos(pessoas->dir, quantidade, cepCidade);
    }
}