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
ArvRubNeg* buscaNo(ArvRubNeg *raiz, int valor);
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
InfoCidade lerInfoCidade();
int lerCep();
int verificaCep(ArvRubNeg *ceps, int cep);
int verificaCepCidade(ArvRubNeg *cidades, int cep);
int verificaCepEstado(Estado *inicio, int cep);
int verificaPessoa(ArvRubNeg *raiz, int nome);
InfoPessoa lerInfoPessoa(Estado *raiz);

//Estados - DuplaEncadeada
InfoEstado lerInfoEstado();
Estado* alocarEstado(InfoEstado info);
int inserirEstado(Estado **inicio, Estado *novoNo);
Estado *buscarEstado(Estado *raiz, int nome);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);
Estado* estadoMaisPopuloso(Estado *raiz);

//questoes
Estado* estadoMaisPopuloso(Estado *raiz);//1
void populacaoDaCapital(ArvRubNeg *raiz, int capital, int *populacao); //2
void cidadeMaisPopulosa(ArvRubNeg *raiz, int capital, ArvRubNeg **cidade);//3
void pessoasForaCepNatal(ArvRubNeg *pessoas, int *quantidade);//4
int estadoNatal(Estado *inicio, int cep, int *nomeCidade);
int cidadeNatal(ArvRubNeg *cidades, int cep, int *nomeCidade); //5
void nascidosQueNaoMoram(ArvRubNeg *pessoas, int *quantidade, int cepCidade);//6
void moradoresNaoNascidos(ArvRubNeg *pessoas, int *quantidade, int cepCidade);//7