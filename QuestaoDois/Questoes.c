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
    if (raiz)
    {
        int flag = 0;
        if (raiz->quantInfo == 2) 
            if (raiz->infoDois.cidade.nome == capital) {
                    *populacao = raiz->infoDois.cidade.populacao;
                    flag = 1;
            }

        if (!flag && raiz->infoUm.cidade.nome == capital) {
                *populacao = raiz->infoUm.cidade.populacao;
                flag = 1;
        }
        
        if (!flag) {
            populacaoDaCapital(raiz->esq, capital, populacao);
            populacaoDaCapital(raiz->cen, capital, populacao);
            if (raiz->quantInfo == 2) populacaoDaCapital(raiz->dir, capital, populacao);
        }
    }
}