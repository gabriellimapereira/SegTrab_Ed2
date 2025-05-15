#include <stdio.h>
#include "prototipos.h"
#include <stdlib.h>

InfoEstado lerInfoEstado() 
{
    //dispensável por hora já que estão sendo usados valores inteiros
}

Estado *alocarEstado(InfoEstado info) 
{
    Estado *no = (Estado*) malloc(sizeof(Estado));
    if(no == NULL)
    {
        printf("Erro de alocacao.\n");
        exit(1);
    }
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
        printf("\nEstado: %d\n ", aux->info.nome);
        exibirCidades(aux->info.cidades);
        aux = aux->prox;
    }
}

void liberarLista(Estado **lista) {
    Estado *aux = *lista;
    while (aux != NULL) {
        Estado *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    *lista = NULL;  // opcional, mas limpa o ponteiro original
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

