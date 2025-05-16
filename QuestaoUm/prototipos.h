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
    Dados info;
    int cor;
    struct ArvDoisTres *esq, *dir;
} ArvDoisTres;

//Rubro-Negra
ArvDoisTres* criarNo(Dados dado);
void imprimirArvore(ArvDoisTres *raiz, int espaco);
void liberarArvore(ArvDoisTres *raiz);
ArvDoisTres* buscaNo(ArvDoisTres *raiz, int valor) ;
int cor(ArvDoisTres *raiz);
void rotEsq(ArvDoisTres **raiz);
void rotDir(ArvDoisTres **raiz);
void trocaCor(ArvDoisTres **raiz);
void balanceamento(ArvDoisTres **raiz);
int insereNo(ArvDoisTres **raiz, ArvDoisTres *novoNo);
int  insercao(ArvDoisTres **raiz, ArvDoisTres *novoNo);
ArvDoisTres* moveTwoEsqRed(ArvDoisTres *raiz);
ArvDoisTres* moveTwoDirRed(ArvDoisTres *raiz);
ArvDoisTres *removeMenor(ArvDoisTres *raiz);
ArvDoisTres* procuraMenor(ArvDoisTres *raiz);
ArvDoisTres* removeNo(ArvDoisTres *raiz, int valor);
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

//Questões
/*
void populacaoDaCapital(Cidade *raiz, int capital, int populacao) 
{
    if (raiz)
    {
        if (raiz->info.nome == capital) if (raiz->info.populacao > populacao) populacao = raiz->info.populacao;
        populacaoDaCapital(raiz->esq, capital, populacao);
        populacaoDaCapital(raiz->dir, capital, populacao);
    }
}

void cidadeMaisPopulosa(Cidade *raiz, int capital, Cidade *cidade) 
{
    if (raiz)
    {
        if (raiz->info.nome != capital) if (raiz->info.populacao > cidade->info.populacao) cidade = raiz;
        populacaoDaCapital(raiz->esq, capital, cidade);
        populacaoDaCapital(raiz->dir, capital, cidade);
    }
} */
