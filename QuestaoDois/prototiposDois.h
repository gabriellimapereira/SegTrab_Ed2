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
ArvDoisTres* buscaNo(ArvDoisTres *raiz, int valor);

void exibirCeps(ArvDoisTres *raiz);
void exibirCidades(ArvDoisTres *raiz);
void exibirPessoas(ArvDoisTres *raiz);

InfoCidade lerInfoCidade();
int lerCep();
int verificaCep(ArvDoisTres *ceps, int cep);
int verificaCepCidade(ArvDoisTres *cidades, int cep);
int verificaCepEstado(Estado *inicio, int cep);
InfoPessoa lerInfoPessoa(Estado *raiz);

//Estados - DuplaEncadeada
InfoEstado lerInfoEstado(InfoCidade *capital);
Estado* alocarEstado(InfoEstado info);
Estado *buscarEstado(Estado *raiz, int nome);
int inserirEstado(Estado** inicio, Estado *novoNo);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);


//Questoes
Estado* estadoMaisPopuloso(Estado *raiz);//1
void populacaoDaCapital(ArvDoisTres *raiz, int capital, int *populacao);//2
void cidadeMaisPopulosa(ArvDoisTres *raiz, int capital, ArvDoisTres**cidade); //3
void pessoasForaCepNatal(ArvDoisTres *pessoas, int *quantidade);//4
int cidadeNatal(ArvDoisTres *cidades, int cep, int nomeCidade)//5
void nascidosQueNaoMoram(ArvDoisTres *pessoas, int *quantidade, int cepCidade);//6
void moradoresNaoNascidos(ArvDoisTres *pessoas, int *quantidade, int cepCidade);//7