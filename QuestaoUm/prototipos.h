#pragma once

typedef struct InfoPessoa
{
    int cpf;
    char nome[50];
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
    char nome[50];
    int populacao[50];
    CEP *ceps;
} InfoCidade;

typedef struct Cidade
{
    InfoCidade info;
    struct Cidade *esq, *dir;
} Cidade;

typedef struct InfoEstado 
{
    char nome[50];
    char capital[50];
    int quantCidades;
    int populacao;
    Cidade *cidades;
} InfoEstado;

typedef struct Estado 
{
    InfoEstado info;
    struct Estado *ant, *prox;
} Estado;

int inserirEstado(Estado **lista, Estado *novoNo);
