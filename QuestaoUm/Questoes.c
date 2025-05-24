#include <stdio.h>
#include "prototiposUm.h"
#include <stdlib.h>

//Questões
//questao 2: Qual a população da Capital de um determinado estado? 
void populacaoDaCapital(ArvRubNeg *raiz, int capital, int populacao) //ARRUMAR A RAIZ PARA O UNION
{
    if (raiz)
    {
        if(raiz->info.cidade.nome == capital) 
        {
            if(raiz->info.cidade.populacao > populacao)
            {
                populacao = raiz->info.cidade.populacao;
            }
        }
        populacaoDaCapital(raiz->esq, capital, populacao);
        populacaoDaCapital(raiz->dir, capital, populacao);
    }
}

//questao 3: Qual a cidade mais populosa de um estado sem ser a Capital? 
void cidadeMaisPopulosa(ArvRubNeg *raiz, int capital, ArvRubNeg *cidade) //ARRUMAR A RAIZ PARA O UNION
{
    if (raiz)
    {
        if (raiz->info.cidade.nome != capital)
        {
            if (raiz->info.cidade.populacao > cidade->info.cidade.nome) 
            {
                cidade = raiz;
            }
        }
        cidadeMaisPopulosa(raiz->esq, capital, cidade);
        cidadeMaisPopulosa(raiz->dir, capital, cidade);
    }
} 

//questao 4: Quantas pessoas não moram na cidade natal. 
void quantidadePessoasCepAtual(ArvRubNeg *pessoas, int *quantidade)
{
    if(pessoas)
    {
        if(pessoas->info.pessoa.cepNatal != pessoas->info.pessoa.cepAtual)
        {
            (*quantidade)++;
        }
        quantidadePessoasCepAtual(pessoas->esq, quantidade);
        quantidadePessoasCepAtual(pessoas->dir, quantidade);
    }
}

//questao 5: Qual cidade natal de uma pessoa dado o CEP da cidade? 

//questao 6: Quantas pessoas nascidas em uma determinada cidade não mora na cidade natal? (versao 1)
/*void quantidadePessoasCepNatal(ArvRubNeg *pessoas, int *quantidade, ArvRubNeg *cidade)
{
    int existe;
    if(pessoas)
    {
        existe = verificaCep(cidade, pessoas->info.pessoa.cepNatal);
        if(existe)
        {
            if(pessoas->info.pessoa.cepNatal != pessoas->info.pessoa.cepAtual)
            {
                (*quantidade)++;
            }
        }
        quantidadePessoasCepNatal(pessoas->esq, quantidade, cidade);
        quantidadePessoasCepNatal(pessoas->dir, quantidade, cidade);
    }
}*/

/*void quantidadePessoasCepNatal(ArvRubNeg *pessoas, int *quantidade, int cepCidade) (versao 2)
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
        quantidadePessoasCepNatal(pessoas->esq, quantidade, cepCidade);
        quantidadePessoasCepNatal(pessoas->dir, quantidade, cepCidade);
    }
}*/

//questao 7:Quantas pessoas que moram em uma determinada cidade não nasceram na cidade?
/*void quantidadePessoasCepAtual(ArvRubNeg *pessoas, int *quantidade, int cepCidade) (versao 2)
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
        quantidadePessoasCepAtual(pessoas->esq, quantidade, cepCidade);
        quantidadePessoasCepAtual(pessoas->dir, quantidade, cepCidade);
    }
}*/