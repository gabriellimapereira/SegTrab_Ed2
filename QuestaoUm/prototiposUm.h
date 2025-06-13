#pragma once
#define preto 0
#define vermelho 1

typedef struct InfoPessoa
{
    char cpf[50];
    char nome[50];
    char cepNatal[50];
    char cepAtual[50];
    int dataNasc;
} InfoPessoa;

typedef struct InfoCidade 
{
    char nome[50];
    int populacao;
    struct ArvRubNeg *ceps;
} InfoCidade;

typedef union 
{
    char cep[50];
    InfoCidade cidade;
    InfoPessoa pessoa;
} Dados;

typedef struct InfoEstado 
{
    char nome[50];
    char capital[50];
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
void liberarArvore(ArvRubNeg *raiz);
ArvRubNeg* buscaNo(ArvRubNeg *raiz, const char *valor);
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
ArvRubNeg* removeNo(ArvRubNeg *raiz, const char *valor);
int remocao(ArvRubNeg **raiz, const char *valor);
void exibirCeps(ArvRubNeg *raiz);
void exibirCidades(ArvRubNeg *raiz);
void exibirPessoas(ArvRubNeg *raiz);
InfoCidade lerInfoCidade();
void lerCep(char *cep);
int verificaCep(ArvRubNeg *ceps, const char *cep);
int verificaCepCidade(ArvRubNeg *cidades, const char *cep);
int verificaCepEstado(Estado *inicio, const char *cep);
int verificaPessoa(ArvRubNeg *raiz, const char *nome);
InfoPessoa lerInfoPessoa(Estado *raiz);

//Estados - DuplaEncadeada
InfoEstado lerInfoEstado(InfoCidade *capital);
Estado* alocarEstado(InfoEstado info);
int inserirEstado(Estado **inicio, Estado *novoNo);
Estado *buscarEstado(Estado *raiz, const char *nome);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);
Estado* estadoMaisPopuloso(Estado *raiz);

//questoes
Estado* estadoMaisPopuloso(Estado *raiz);//1
void populacaoDaCapital(ArvRubNeg *raiz, const char *capital, int *populacao); //2
void cidadeMaisPopulosa(ArvRubNeg *raiz, const char *capital, ArvRubNeg **cidade);//3
void pessoasForaCepNatal(ArvRubNeg *pessoas, int *quantidade);//4
int estadoNatal(Estado *inicio, const char *cep, char *nomeCidade);
int cidadeNatal(ArvRubNeg *cidades, const char *cep, char *nomeCidade); //5
void nascidosQueNaoMoram(ArvRubNeg *pessoas, int *quantidade, const char *cepCidade);//6
void moradoresNaoNascidos(ArvRubNeg *pessoas, int *quantidade, const char *cepCidade);//7