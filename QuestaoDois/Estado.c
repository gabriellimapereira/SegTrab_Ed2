#include <stdio.h>
#include <string.h>
#include "prototiposDois.h"
#include <stdlib.h>

InfoEstado lerInfoEstado(InfoCidade *capital) 
{
    InfoEstado info;
    printf("Digite o nome do estado: \n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);

    printf("Digite o nome da capital: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", capital->nome);

    printf("Digite a população da capital: ");
    scanf("%d", &capital->populacao);

    capital->ceps = NULL;
    strcpy(info.capital, capital->nome);
    info.populacao = capital->populacao;
    info.quantCidades = 1;
    info.cidades = NULL;
    return info;
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

Estado *buscarEstado(Estado *raiz, const char *nome) 
{
    Estado *aux = raiz;
    while (aux != NULL && strcmp(aux->info.nome, nome) != 0) 
    {
        aux = aux->prox;
    }
    return aux;
}

int inserirEstado(Estado** inicio, Estado *novoNo) 
{
    int inseriu = 1;
    if (*inicio == NULL)
        *inicio = novoNo;
    else 
    {
        Estado* atual = *inicio;
        if (strcmp(novoNo->info.nome, atual->info.nome) == 0) 
            inseriu = 0;
        else if (strcmp(novoNo->info.nome, atual->info.nome) < 0) 
        {
            novoNo->prox = atual;
            atual->ant = novoNo;
            *inicio = novoNo;
        } 
        else 
        {
            while (atual->prox != NULL && strcmp(atual->prox->info.nome, novoNo->info.nome) < 0)
            {
                atual = atual->prox;
            }
            if((atual->prox != NULL && strcmp(atual->prox->info.nome, novoNo->info.nome) == 0) || strcmp(atual->info.nome, novoNo->info.nome) == 0)
                inseriu = 0;
            else 
            {
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
        printf("\nEstado: %s\n", aux->info.nome);
        exibirCidades(aux->info.cidades);
        aux = aux->prox;
    }
}

void liberarLista(Estado **lista) 
{
    Estado *aux = *lista;
    while (aux != NULL) 
    {
        Estado *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    *lista = NULL;  
}