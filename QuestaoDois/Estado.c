#include <stdio.h>
#include "prototiposDois.h"
#include <stdlib.h>

InfoEstado lerInfoEstado() 
{
    
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

int inserirEstado(Estado** inicio, Estado *novoNo) {
    int inseriu = 1;

    if (*inicio == NULL)
        *inicio = novoNo;
    else {
        Estado* atual = *inicio;

        if (novoNo->info.nome == atual->info.nome) 
            inseriu = 0;
        else if (novoNo->info.nome < atual->info.nome) {
            novoNo->prox = atual;
            atual->ant = novoNo;
            *inicio = novoNo;
        } else {

            while (atual->prox != NULL && atual->prox->info.nome < novoNo->info.nome) atual = atual->prox;

            if ((atual->prox != NULL && atual->prox->info.nome == novoNo->info.nome) || atual->info.nome == novoNo->info.nome)
                inseriu = 0;
            else {
                novoNo->prox = atual->prox;
                novoNo->ant = atual;
                if (atual->prox != NULL) atual->prox->ant = novoNo;
                atual->prox = novoNo;
            }
        }
    }

    return inseriu;
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

