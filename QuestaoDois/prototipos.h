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
    struct ArvDoisTres *ceps;
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
    struct ArvDoisTres *cidades;
} InfoEstado;

typedef struct Estado 
{
    InfoEstado info;
    struct Estado *ant, *prox;
} Estado;

typedef struct ArvDoisTres {
    Dados infoUm;
    Dados infoDois;
    int quantInfo;
    struct ArvDoisTres *esq, *cen, *dir;
} ArvDoisTres;

//Dois-Três
ArvDoisTres* criarNo(Dados info, ArvDoisTres *fEsq, ArvDoisTres *fCen);
void imprimirArv(ArvDoisTres *raiz, int nivel);
void liberarArv(ArvDoisTres **raiz);
void adicionarInfo(ArvDoisTres **no, Dados info, ArvDoisTres *subArvInfo);
ArvDoisTres* quebrarNo(ArvDoisTres **no, Dados info, Dados *sobe, ArvDoisTres *filhoDir);
ArvDoisTres* inserirNo(ArvDoisTres **raiz, ArvDoisTres *pai, Dados info, Dados *sobe);

void exibirCeps(ArvDoisTres *raiz);
void exibirCidades(ArvDoisTres *raiz);
void exibirPessoas(ArvDoisTres *raiz);

InfoEstado lerInfoEstado();
InfoCidade lerInfoCidade();
int lerCep();
InfoPessoa lerInfoPessoa();

//Estados - DuplaEncadeada
InfoEstado lerInfoEstado();
Estado* alocarEstado(InfoEstado info);
int inserirEstado(Estado **lista, Estado *novoNo);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);
Estado* estadoMaisPopuloso(Estado *raiz);