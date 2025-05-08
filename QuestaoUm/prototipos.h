#pragma once
#define preto 0
#define vermelho 1

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
    int cor;
    struct Pessoa *esq, *dir;
} Pessoa;

typedef struct CEP
{
    int info;
    int cor;
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
    int cor;
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

//Estados
InfoEstado lerInfoEstado();
Estado* alocarEstado(InfoEstado info);
int inserirEstado(Estado **lista, Estado *novoNo);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);

//Cidades

//Ceps
int lerCep();
CEP* alocarCep(int numCep);
CEP* buscaCep(CEP *raiz, int valor);
int corCep(CEP *raiz);
void rotEsqCep(CEP **raiz);
void rotDirCep(CEP **raiz);
void trocaCorCep(CEP **raiz);
void balanceamentoCep(CEP **raiz);
int inserirCep(CEP **raiz, CEP *novoNo);
int insercaoCep(CEP **raiz, CEP *novoNo); 
int removerCep(CEP **raiz, int numCep);
void exibirCeps(CEP *raiz);
void liberarCeps(CEP **raiz);

//Pessoas