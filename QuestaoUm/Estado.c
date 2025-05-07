#include "prototipos.h"
#include <stdlib.h>

InfoEstado lerInfoEstado() {
    //dispensável por hora já que estão sendo usados valores inteiros
}

Estado *alocarEstado(InfoEstado info) {
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
    {
        *lista = novoNo;
    } 
    else if ((*lista)->info.nome == novoNo->info.nome)
    {
        inseriu = 0; 
    }
    else if ((*lista)->prox == NULL) 
    {
        (*lista)->prox = novoNo;
        novoNo->ant = *lista;
    } 
    else 
    {
        inseriu = inserirEstado(&(*lista)->prox, novoNo);
    }

    return 1;
}

void exibeListaEstado(Estado *lista) {
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