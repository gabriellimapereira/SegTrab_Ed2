#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "prototiposUm.h"

void menu() 
{
    printf("\n=========== MENU ===========\n");
    printf("1 - Cadastrar Estado\n");
    printf("2 - Cadastrar Cidade\n");
    printf("3 - Cadastrar CEP\n");
    printf("4 - Cadastrar Pessoa\n");
    printf("5 - Remover CEP\n");
    printf("6 - Remover Pessoa\n");
    printf("7 - Estado mais populoso\n");
    printf("8 - Populacao da capital de um estado\n");
    printf("9 - Cidade mais populosa de um estado (exceto a capital)\n");
    printf("10 - Quantas pessoas nao moram na cidade natal\n");
    printf("11 - Cidade natal de uma pessoa pelo CEP de natalidade\n");
    printf("12 - Quantas pessoas nascidas em uma cidade nao moram nela\n");
    printf("13 - Quantas pessoas que moram em uma cidade nao nasceram nela\n");
    printf("14 - Visualizar todas as arvores\n");
    printf("0 - Sair\n");
    printf("============================\n");
}

int main() 
{
    Estado *estados = NULL, *NoEstado = NULL;
    ArvRubNeg *pessoas = NULL;
    ArvRubNeg *No = NULL;
    ArvRubNeg *noCidade = NULL;
    char dado[50], nome[50], cep[50];
    int opcao, dadoInt, inseriu, existe;
    InfoEstado dadosEstado; // informaçoes de estado para preencher
    InfoCidade dadosCidade; // informaçoes de cidade para preencher
    InfoPessoa dadosPessoa; // informaçoes de pessoa para preencher
    Dados dadosQuaisquer;
    
    do 
    {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) 
        {
            case 1:
                dadosEstado = lerInfoEstado(&dadosCidade);
                NoEstado = alocarEstado(dadosEstado);
                inseriu = inserirEstado(&estados, NoEstado);
                if (inseriu) 
                {
                    printf("Estado inserido com sucesso!\n");
                    dadosQuaisquer.cidade = dadosCidade;
                    inseriu = insereNo(&(NoEstado->info.cidades), criarNo(dadosQuaisquer));
                } 
                else 
                {
                    printf("O estado ja existe! Nao houve insercao.\n");
                }
                break;
            case 2:
                //cadastrarCidade();
                printf("Digite o nome do estado: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    dadosCidade = lerInfoCidade();
                    dadosQuaisquer.cidade = dadosCidade;
                    No = criarNo(dadosQuaisquer);
                    inseriu = insercao(&NoEstado->info.cidades, No);
                    if(inseriu)
                    {
                        printf("Cidade inserida com sucesso!\n");
                        NoEstado->info.populacao += dadosCidade.populacao;
                        NoEstado->info.quantCidades++;
                    }
                    else
                    {
                        printf("A cidade ja existe! Nao houve insercao.\n");
                        free(No);
                    }
                }
                else
                {
                    printf("Estado nao encontrado!\n");
                }
                break;
            case 3:
                //cadastrarCEP();
                printf("Digite o nome do estado: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    printf("Digite o nome da cidade: "); 
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    noCidade = buscaNo(NoEstado->info.cidades, nome);
                    if(noCidade)
                    {
                        lerCep(cep);
                        strcpy(dadosQuaisquer.cep, cep);
                        No = criarNo(dadosQuaisquer);
                        inseriu = insercao(&noCidade->info.cidade.ceps, No);
                        if(inseriu)
                        {
                            printf("Cep inserido com sucesso!\n");
                        }
                        else
                        {
                            printf("O cep ja existe! Nao houve insercao.\n");
                            free(No);
                        }
                    }
                    else
                    {
                        printf("Cidade nao encontrada!\n");
                    }
                }
                else
                {
                    printf("Estado nao encontrado!\n");
                }
                break;
            case 4:
                //cadastrarPessoa();
                dadosPessoa = lerInfoPessoa(estados);
                dadosQuaisquer.pessoa = dadosPessoa;
                No = criarNo(dadosQuaisquer);
                inseriu = insercao(&pessoas, No);
                if(inseriu)
                {
                    printf("Pessoa inserida com sucesso!\n");
                }
                else
                {
                    printf("A pessoa ja existe! Nao houve insercao.\n");
                    free(No);
                }
                break;
            case 5:
                //removerCEP();
                printf("Digite o nome do estado: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    printf("Digite o nome da cidade: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    noCidade = buscaNo(estados->info.cidades, nome);
                    if(noCidade)
                    {
                        printf("Digite o CEP a ser removido: \n"); 
                        setbuf(stdin, NULL);
                        scanf("%[^\n]", cep);
                        dadoInt = remocao(&noCidade->info.cidade.ceps, cep);
                        if(dadoInt)
                        {
                            printf("CEP removido!\n");
                        }
                        else
                        {
                            printf("Falha na remocao!\n");
                        }
                    }
                    else
                        printf("Cidade nao encontrada!\n");
                }
                else
                    printf("Estado nao encontrado!\n");
                break;
            case 6:
                //removerPessoa();
                printf("Digite o CPF da pessoa para remover: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                dadoInt = remocao(&pessoas, nome);
                if(dadoInt)
                {
                    printf("Pessoa removida com sucesso!\n");
                }
                else
                {
                    printf("Falha na remocao!\n");
                }
                break;
            case 7:
                //estadoMaisPopuloso();
                NoEstado = estadoMaisPopuloso(estados);
                if(NoEstado)
                {
                    printf("Estado mais populoso: %s\n", NoEstado->info.nome);
                }
                else
                {
                    printf("Sem estados cadastrados!\n");
                }
                break;
            case 8:
                //populacaoCapital();
                printf("Digite o nome do estado: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    dadoInt = 0;
                    populacaoDaCapital(NoEstado->info.cidades, NoEstado->info.capital, &dadoInt);
                    if(dadoInt)
                    {
                        printf("Populacao da capital %s: %d\n", NoEstado->info.capital, dadoInt);
                    }
                }
                else
                {
                    printf("Estado nao cadastrado!\n");
                }
                break;
            case 9:
                //cidadeMaisPopulosaExcetoCapital();
                printf("Digite o nome do estado: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    noCidade = NoEstado->info.cidades;
                    if(NoEstado->info.cidades->esq == NULL && NoEstado->info.cidades->dir == NULL)
                    {
                        printf("A cidade mais populosa eh a capital!\n");
                    }
                    else
                    {
                        cidadeMaisPopulosa(NoEstado->info.cidades, NoEstado->info.capital, &noCidade);
                        printf("Cidade mais populosa: %s\n", noCidade->info.cidade.nome);
                    }
                } 
                else 
                {
                    printf("Estado nao encontrado!\n");
                }
                break;
            case 10:
                //pessoasForaCepNatal();
                dadoInt = 0;
                pessoasForaCepNatal(pessoas, &dadoInt);
                if(dado)
                {
                    printf("%d pessoas moram fora da cidade natal!\n", dadoInt);
                }
                else
                {
                    printf("Todos moram na cidade natal\n");
                }
                break;
            case 11:
                //cidadeNatal();
                char nomeCidade[50];
                printf("Digite o cep:\n"); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", cep);
                existe = estadoNatal(estados, cep, nomeCidade);
                if(existe) 
                {
                    printf("Cidade natal: %s\n", nomeCidade);
                } 
                else
                {
                    printf("Cep nao encontrado!\n");
                }
                break;
            case 12:
                //nascidosQueNaoMoram();
                printf("Digite o nome do estado: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if (NoEstado) {
                    printf("Digite o nome da cidade: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    noCidade = buscaNo(NoEstado->info.cidades, nome);
                    if (noCidade) {
                        dadoInt = 0;
                        nascidosQueNaoMoram(pessoas, &dadoInt, noCidade);
                        if(dadoInt)
                        {
                            printf("%d pessoas nao moram na cidade %s.\n", dadoInt, noCidade->info.cidade.nome);
                        }
                        else
                        {
                            printf("Todos moram na cidade natal!\n");
                        }
                    } 
                    else 
                    {
                        printf("Cidade nao encontrada!\n");
                    }
                }
                break;
            case 13:
                //moradoresNaoNascidos();
                printf("Digite o nome do estado: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if (NoEstado) {
                    printf("Digite o nome da cidade: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    noCidade = buscaNo(NoEstado->info.cidades, nome);
                    if (noCidade) {
                        dadoInt = 0;
                        moradoresNaoNascidos(pessoas, &dadoInt, noCidade);
                        if(dadoInt)
                        {
                            printf("%d pessoas nao nasceram em %s e moram nela.\n", dadoInt, noCidade->info.cidade.nome);
                        }
                        else
                        {
                            printf("Todos nasceram na cidade!\n");
                        }                    
                    }
                    else 
                    {
                        printf("Cidade nao encontrada!\n");
                    }
                }
                else {
                    printf("Estado nao encontrado!\n");
                }
                break;
            case 14:
                printf("\nEstados:");
                exibirEstados(estados);
                printf("\nPessoas: ");
                exibirPessoas(pessoas);
                printf("\n");
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    liberarArvore(estados->info.cidades->info.cidade.ceps);
    liberarArvore(estados->info.cidades);
    liberarLista(&estados);
    liberarArvore(pessoas);
    return 0;
}