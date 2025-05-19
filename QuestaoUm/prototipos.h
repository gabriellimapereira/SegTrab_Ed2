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
    struct ArvRubNeg *ceps;
} InfoCidade;

typedef union 
{
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

typedef struct ArvRubNeg 
{
    Dados info;
    int cor;
    struct ArvRubNeg *esq, *dir;
} ArvRubNeg;

//Rubro-Negra
ArvRubNeg* criarNo(Dados dado);
void imprimirArvore(ArvRubNeg *raiz, int espaco);
void liberarArvore(ArvRubNeg *raiz);
ArvRubNeg* buscaNo(ArvRubNeg *raiz, int valor) ;
int cor(ArvRubNeg *raiz);
void rotEsq(ArvRubNeg **raiz);
void rotDir(ArvRubNeg **raiz);
void trocaCor(ArvRubNeg **raiz);
void balanceamento(ArvRubNeg **raiz);
int insereNo(ArvRubNeg **raiz, ArvRubNeg *novoNo);
int  insercao(ArvRubNeg **raiz, ArvRubNeg *novoNo);
ArvRubNeg* moveTwoEsqRed(ArvRubNeg *raiz);
ArvRubNeg* moveTwoDirRed(ArvRubNeg *raiz);
ArvRubNeg *removeMenor(ArvRubNeg *raiz);
ArvRubNeg* procuraMenor(ArvRubNeg *raiz);
ArvRubNeg* removeNo(ArvRubNeg *raiz, int valor);
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
