#pragma once

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
    struct ArvDoisTres *ceps;
} InfoCidade;

typedef union {
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
void liberarArv(ArvDoisTres **raiz);
void adicionarInfo(ArvDoisTres **no, Dados info, ArvDoisTres *subArvInfo);
ArvDoisTres* quebrarNo(ArvDoisTres **no, Dados info, Dados *sobe, ArvDoisTres *filhoDir);
int infoNaoEstaNoNo(ArvDoisTres *no, Dados info);
ArvDoisTres* inserirNo(ArvDoisTres **raiz, ArvDoisTres *pai, Dados info, Dados *sobe);
ArvDoisTres* buscaNo(ArvDoisTres *raiz, const char *valor);

void exibirCeps(ArvDoisTres *raiz);
void exibirCidades(ArvDoisTres *raiz);
void exibirPessoas(ArvDoisTres *raiz);

InfoCidade lerInfoCidade();
void lerCep(char *cep);
int verificaCep(ArvDoisTres *ceps, const char *cep);
int verificaCepCidade(ArvDoisTres *cidades, const char *cep);
int verificaCepEstado(Estado *inicio, const char *cep);
InfoPessoa lerInfoPessoa(Estado *raiz);

//Estados - DuplaEncadeada
InfoEstado lerInfoEstado(InfoCidade *capital);
Estado* alocarEstado(InfoEstado info);
Estado *buscarEstado(Estado *raiz, const char *nome);
int inserirEstado(Estado** inicio, Estado *novoNo);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);

//Questoes
Estado* estadoMaisPopuloso(Estado *raiz);//1
void populacaoDaCapital(ArvDoisTres *raiz, const char *capital, int *populacao);//2
void cidadeMaisPopulosa(ArvDoisTres *raiz, const char *capital, ArvDoisTres**cidade); //3
void pessoasForaCepNatal(ArvDoisTres *pessoas, int *quantidade);//4
int cidadeNatal(ArvDoisTres *cidades, const char *cep, char *nomeCidade);//5
int estadoNatal(Estado *inicio, const char *cep, char *nomeCidade); // 5
void nascidosQueNaoMoram(ArvDoisTres *pessoas, int *quantidade, ArvDoisTres *cepCidade, const char *nomeDaCidade);//6
void moradoresNaoNascidos(ArvDoisTres *pessoas, int *quantidade, ArvDoisTres *cepCidade, const char *nomeDaCidade);//7