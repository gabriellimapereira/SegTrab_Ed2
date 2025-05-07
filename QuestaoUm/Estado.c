#include "prototipos.h"
#include <stdlib.h>

InfoEstado lerInfoEstado() {
    //
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
    else if (strcmp((*lista)->info.nome, novoNo->info.nome) == 0) 
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
        return inserirEstado(&(*lista)->prox, novoNo);
    }

    return 1;
}

