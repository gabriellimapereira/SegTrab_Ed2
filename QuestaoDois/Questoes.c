#include "prototiposDois.h"
#include <stdlib.h>
#include <string.h>

// questao 01
Estado* estadoMaisPopuloso(Estado *raiz) 
{
    Estado *aux = raiz;
    Estado *estado = raiz;
    if (raiz) 
    {
        while (aux != NULL)
        {
            if (aux->info.populacao > estado->info.populacao)
            {
                estado = aux;
            }
            aux = aux->prox;
        }
    }
    return estado;
}

//questao 02
void populacaoDaCapital(ArvDoisTres *raiz, const char *capital, int *populacao) 
{
    if (raiz)
    {
        int flag = 0;
        if (raiz->quantInfo == 2)
        {
            if (strcmp(raiz->infoDois.cidade.nome, capital) == 0)
            {
                *populacao = raiz->infoDois.cidade.populacao;
                flag = 1;
            }
        }
        if (!flag && strcmp(raiz->infoUm.cidade.nome, capital) == 0)
        {
            *populacao = raiz->infoUm.cidade.populacao;
            flag = 1;
        }
        if (!flag)
        {
            populacaoDaCapital(raiz->esq, capital, populacao);
            populacaoDaCapital(raiz->cen, capital, populacao);
            if (raiz->quantInfo == 2)
                populacaoDaCapital(raiz->dir, capital, populacao);
        }
    }
}

//questao 03
void cidadeMaisPopulosa(ArvDoisTres *raiz, const char *capital, ArvDoisTres **cidade)
{
    if (raiz)
    {
        if (raiz->quantInfo == 2)
        {
            if (strcmp(raiz->infoDois.cidade.nome, capital) != 0)
            {
                if (raiz->infoDois.cidade.populacao > (*cidade)->infoUm.cidade.populacao)
                {
                    (*cidade)->infoUm = raiz->infoDois;
                }
            }
        }
        if (strcmp(raiz->infoUm.cidade.nome, capital) != 0)
        {
            if (raiz->infoUm.cidade.populacao > (*cidade)->infoUm.cidade.populacao)
            {
                (*cidade)->infoUm = raiz->infoUm;
            }
        }
        cidadeMaisPopulosa(raiz->esq, capital, cidade);
        cidadeMaisPopulosa(raiz->cen, capital, cidade);
        if (raiz->quantInfo == 2)
            cidadeMaisPopulosa(raiz->dir, capital, cidade);
    }
}
// Questão 4: Quantas pessoas não moram na cidade natal.
void pessoasForaCepNatal(ArvDoisTres *pessoas, int *quantidade)
{
    if (pessoas)
    {
        if (pessoas->infoUm.pessoa.cepAtual != pessoas->infoUm.pessoa.cepNatal)
        {
            (*quantidade)++;
        }
        if (pessoas->quantInfo == 2)
        {
            if (pessoas->infoDois.pessoa.cepAtual != pessoas->infoDois.pessoa.cepNatal)
            {
                (*quantidade)++;
            }
        }
        pessoasForaCepNatal(pessoas->esq, quantidade);
        pessoasForaCepNatal(pessoas->cen, quantidade);
        if (pessoas->quantInfo == 2)
            pessoasForaCepNatal(pessoas->dir, quantidade);
    }
}

// Questão 5: Qual cidade natal de uma pessoa dado o CEP da cidade? 
int cidadeNatal(ArvDoisTres *cidades, const char *cep, char *nomeCidade)
{
    int existe = 0;
    if (cidades)
    {
        if (cidades->quantInfo == 2)
        {
            existe = verificaCep(cidades->infoDois.cidade.ceps, cep);
            if (existe)
            {
                strcpy(nomeCidade, cidades->infoDois.cidade.nome);
            }
            else
            {
                existe = cidadeNatal(cidades->esq, cep, nomeCidade);
                if (!existe)
                {
                    existe = cidadeNatal(cidades->cen, cep, nomeCidade);
                    if (!existe && cidades->quantInfo == 2)
                    {
                        existe = cidadeNatal(cidades->dir, cep, nomeCidade);
                    }
                }
            }
        }
        if (!existe)
        {
            existe = verificaCep(cidades->infoUm.cidade.ceps, cep);
            if (existe)
            {
                strcpy(nomeCidade, cidades->infoUm.cidade.nome);
            }
            else
            {
                existe = cidadeNatal(cidades->esq, cep, nomeCidade);
                if (!existe)
                {
                    existe = cidadeNatal(cidades->cen, cep, nomeCidade);
                }
            }
        }
    }
    return existe;
}

int estadoNatal(Estado *inicio, const char *cep, char *nomeCidade) 
{
    int existe = 0;
    if (inicio) 
    {
        existe = cidadeNatal(inicio->info.cidades, cep, nomeCidade);
        if (existe == 0)
        {
            existe = estadoNatal(inicio->prox, cep, nomeCidade);
        }
    } 
    return existe;
}

// Questão 6: Quantas pessoas nascidas em uma determinada cidade não moram na cidade natal?
void nascidosQueNaoMoram(ArvDoisTres *pessoas, int *quantidade, const char *cepCidade) 
{
    if (pessoas)
    {
        if (strcmp(pessoas->infoUm.pessoa.cepNatal, cepCidade) == 0 &&
            strcmp(pessoas->infoUm.pessoa.cepAtual, cepCidade) != 0)
        {
            (*quantidade)++;
        }
        if (pessoas->quantInfo == 2)
        {
            if (strcmp(pessoas->infoDois.pessoa.cepNatal, cepCidade) == 0 &&
                strcmp(pessoas->infoDois.pessoa.cepAtual, cepCidade) != 0)
            {
                (*quantidade)++;
            }
        }
        nascidosQueNaoMoram(pessoas->esq, quantidade, cepCidade);
        nascidosQueNaoMoram(pessoas->cen, quantidade, cepCidade);
        if (pessoas->quantInfo == 2) 
            nascidosQueNaoMoram(pessoas->dir, quantidade, cepCidade);
    }
}

// Questão 7: Quantas pessoas que moram em uma determinada cidade não nasceram na cidade?
void moradoresNaoNascidos(ArvDoisTres *pessoas, int *quantidade, const char *cepCidade) 
{
    if (pessoas)
    {
        if (strcmp(pessoas->infoUm.pessoa.cepAtual, cepCidade) == 0 &&
            strcmp(pessoas->infoUm.pessoa.cepNatal, cepCidade) != 0)
        {
            (*quantidade)++;
        }
        if (pessoas->quantInfo == 2)
        {
            if (strcmp(pessoas->infoDois.pessoa.cepAtual, cepCidade) == 0 &&
                strcmp(pessoas->infoDois.pessoa.cepNatal, cepCidade) != 0)
            {
                (*quantidade)++;
            }
        }
        moradoresNaoNascidos(pessoas->esq, quantidade, cepCidade);
        moradoresNaoNascidos(pessoas->cen, quantidade, cepCidade);
        if (pessoas->quantInfo == 2) 
            moradoresNaoNascidos(pessoas->dir, quantidade, cepCidade);
    }
}
