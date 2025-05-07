#include "prototipos.h"
#include <stdlib.h>

int lerCep() 
{
    //dispensável por hora
}
CEP* alocarCep(int numCep) 
{
    CEP *aux = (CEP*) malloc (sizeof(CEP));
    aux->dir = NULL;
    aux->esq = NULL;
    aux->info = numCep;

    return aux;
}

int inserirCep(CEP **raiz, CEP *novoNo)
{
    
}
int removerCep(CEP **raiz, int numCep);
void exibirCeps(CEP *raiz);
void liberarCeps(CEP **raiz);