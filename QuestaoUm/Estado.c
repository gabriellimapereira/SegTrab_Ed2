#include "prototipos.h"
#include <stdlib.h>

InfoEstado lerInfoEstado() 
{
    //dispensável por hora já que estão sendo usados valores inteiros
}

Estado *alocarEstado(InfoEstado info) 
{
    Estado *no = (Estado*) malloc(sizeof(Estado));

    no->ant = NULL;
    no->prox = NULL;
    no->info = info;

    return no;
}

int inserirEstado(Estado **lista, Estado *novoNo) 
{
    int inseriu = 1;

    if (*lista == NULL) 
        *lista = novoNo;
    else if ((*lista)->info.nome == novoNo->info.nome)
        inseriu = 0; 
    else if ((*lista)->prox == NULL) 
    {
        (*lista)->prox = novoNo;
        novoNo->ant = *lista;
    } 
    else 
        inseriu = inserirEstado(&(*lista)->prox, novoNo);

    return 1;
}

void exibirEstados(Estado *lista) 
{
    Estado *aux = lista;

    while (aux != NULL)
    {
        printf("Estado: %d\n", aux->info.nome);
        aux = aux->prox;
    }
}

void liberarLista(Estado **lista)
{
    Estado *aux;
    while(aux != NULL)
    {   
        aux = lista;
        *lista = (*lista)->prox;
        free(aux);
    }
}

Estado* estadoMaisPopuloso(Estado *raiz) 
{
    Estado *aux = raiz;
    Estado *estado = raiz;

    if (raiz)
    {
        while (aux != NULL)
        { 
            if (aux->info.populacao > estado->info.populacao) estado = aux;
            aux = aux->prox;
        }
    }

    return estado;
}

void populacaoDaCapital(Cidade *raiz, int capital, int populacao) 
{
    if (raiz)
    {
        if (raiz->info.nome == capital) if (raiz->info.populacao > populacao) populacao = raiz->info.populacao;
        populacaoDaCapital(raiz->esq, capital, populacao);
        populacaoDaCapital(raiz->dir, capital, populacao);
    }
}

void cidadeMaisPopulosa(Cidade *raiz, int capital, Cidade *cidade) 
{
    if (raiz)
    {
        if (raiz->info.nome != capital) if (raiz->info.populacao > cidade->info.populacao) cidade = raiz;
        populacaoDaCapital(raiz->esq, capital, cidade);
        populacaoDaCapital(raiz->dir, capital, cidade);
    }
}