#pragma once

typedef struct InfoPessoa
{
    int cpf;
    int nome;
    int cepNatal;
    int cepAtual;
    int dataNasc;
} InfoPessoa;

typedef struct InfoCidade 
{
    int nome;
    int populacao;
    struct ArvRubNeg *ceps;
} InfoCidade;

typedef union {
    int cep;
    InfoCidade cidade;
    InfoPessoa pessoa;
} Dados;

typedef struct InfoEstado 
{
    int nome;
    int capital;
    int quantCidades;
    int populacao;
    struct ArvRubNeg *cidades;
} InfoEstado;

typedef struct Estado 
{
    InfoEstado info;
    struct Estado *ant, *prox;
} Estado;

typedef struct ArvRubNeg {
    Dados infoUm;
    Dados infoDois;
    int quantInfo;
    struct ArvRubNeg *esq, *cen, *dir;
} ArvRubNeg;

//Dois-Três
ArvRubNeg* criarNo(Dados info, ArvRubNeg *fEsq, ArvRubNeg *fCen);
void imprimirArv(ArvRubNeg *raiz, int nivel);
void liberarArv(ArvRubNeg **raiz);
void adicionarInfo(ArvRubNeg **no, Dados info, ArvRubNeg *subArvInfo);
ArvRubNeg* quebrarNo(ArvRubNeg **no, Dados info, Dados *sobe, ArvRubNeg *filhoDir);
ArvRubNeg* inserirNo(ArvRubNeg **raiz, ArvRubNeg *pai, Dados info, Dados *sobe);

void exibirCeps(ArvRubNeg *raiz);
void exibirCidades(ArvRubNeg *raiz);
void exibirPessoas(ArvRubNeg *raiz);

InfoEstado lerInfoEstado();
InfoCidade lerInfoCidade();
int lerCep();
InfoPessoa lerInfoPessoa();

//Estados - DuplaEncadeada
InfoEstado lerInfoEstado();
Estado* alocarEstado(InfoEstado info);
int inserirEstado(Estado** inicio, Estado *novoNo);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);
Estado* estadoMaisPopuloso(Estado *raiz);