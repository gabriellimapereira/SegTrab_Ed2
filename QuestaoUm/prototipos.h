#pragma once

typedef struct InfoPessoa
{
    int cpf;
    int nome;
    int cepNatal;
    int cepAtual;
    int dataNasc;
} InfoPessoa;

typedef struct Pessoa {
    InfoPessoa info;
    struct Pessoa *esq, *dir;
} Pessoa;

typedef struct CEP
{
    int info;
    struct CEP *esq, *dir;
} CEP;

typedef struct InfoCidade 
{
    int nome;
    int populacao;
    CEP *ceps;
} InfoCidade;

typedef struct Cidade
{
    InfoCidade info;
    struct Cidade *esq, *dir;
} Cidade;

typedef struct InfoEstado 
{
    int nome;
    int capital;
    int quantCidades;
    int populacao;
    Cidade *cidades;
} InfoEstado;

typedef struct Estado 
{
    InfoEstado info;
    struct Estado *ant, *prox;
} Estado;

InfoEstado lerInfoEstado();
Estado* alocarEstado(InfoEstado info);
int inserirEstado(Estado **lista, Estado *novoNo);
void exibeListaEstado(Estado *lista);
void liberarLista(Estado **lista);
