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
int verificaCep(ArvRubNeg *ceps, int cep);
int verificaCepCidade(ArvRubNeg *cidades, int cep);
InfoPessoa lerInfoPessoa(Estado *raiz);

//Estados - DuplaEncadeada
InfoEstado lerInfoEstado();
Estado* alocarEstado(InfoEstado info);
int inserirEstado(Estado **inicio, Estado *novoNo);
Estado *buscarEstado(Estado *raiz, int nome);
void exibirEstados(Estado *lista);
void liberarLista(Estado **lista);
Estado* estadoMaisPopuloso(Estado *raiz);

//Questões
/*
//questao 2: Qual a população da Capital de um determinado estado? 
void populacaoDaCapital(Cidade *raiz, int capital, int populacao) //ARRUMAR A RAIZ PARA O UNION
{
    if (raiz)
    {
        if(raiz->info.nome == capital) 
        {
            if(raiz->info.populacao > populacao)
            {
                populacao = raiz->info.populacao;
            }
        }
        populacaoDaCapital(raiz->esq, capital, populacao);
        populacaoDaCapital(raiz->dir, capital, populacao);
    }
}

//questao 3: Qual a cidade mais populosa de um estado sem ser a Capital? 
void cidadeMaisPopulosa(Cidade *raiz, int capital, Cidade *cidade) //ARRUMAR A RAIZ PARA O UNION
{
    if (raiz)
    {
        if (raiz->info.nome != capital)
        {
            if (raiz->info.populacao > cidade->info.populacao) 
            {
                cidade = raiz;
            }
        }
        cidadeMaisPopulosa(raiz->esq, capital, cidade);
        cidadeMaisPopulosa(raiz->dir, capital, cidade);
    }
} 

//questao 4: Quantas pessoas não moram na cidade natal. 
void quantidadePessoasCepAtual(ArvRubNeg *pessoas, int *quantidade)
{
    if(pessoas)
    {
        if(pessoas->info.pessoa->info.cepNatal != pessoas->info.pessoa->info.cepAtual)
        {
            (*quantidade)++;
        }
        quantidadePessoasCepAtual(pessoas->esq, quantidade);
        quantidadePessoasCepAtual(pessoas->dir, quantidade);
    }
}

questao 5: Qual cidade natal de uma pessoa dado o CEP da cidade? 

questao 6: Quantas pessoas nascidas em uma determinada cidade não mora na cidade natal? 
void quantidadePessoasCepNatal(ArvRubNeg *pessoas, int *quantidade, ArvRubNeg *cidade)
{
    int existe;
    if(pessoas)
    {
        existe = verificaCep(cidade->info.ceps, pessoas->info.pessoa->cepNatal);
        if(existe)
        {
            if(pessoas->info.pessoa->cepNatal != pessoas->info.pessoa->cepAtual)
            {
                (*quantidade)++;
            }
        }
        quantidadePessoasCepNatal(pessoas->esq, quantidade, cidade);
        quantidadePessoasCepNatal(pessoas->dir, quantidade, cidade);
    }
}
*/
