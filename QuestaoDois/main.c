#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "prototiposDois.h"

void menu() {
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

int main() {
    Estado *estados = NULL, *NoEstado = NULL;
    ArvDoisTres *pessoas = NULL;
    ArvDoisTres *No = NULL;
    ArvDoisTres *noCidade = NULL;
    char nome[50], dado[50], cep[50];
    int opcao, dadoInt, inseriu, existe;
    InfoEstado dadosEstado; // informaçoes de estado para preencher
    InfoCidade dadosCidade; // informaçoes de cidade para preencher
    InfoPessoa dadosPessoa; // informaçoes de pessoa para preencher
    Dados dadosQuaisquer, sobe;
    
    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dadosEstado = lerInfoEstado(&dadosCidade);
                NoEstado = alocarEstado(dadosEstado);
                inseriu = inserirEstado(&estados, NoEstado);
                if (inseriu) 
                {
                    printf("Estado inserido com sucesso!\n");
                    dadosQuaisquer.cidade = dadosCidade;
                    inserirNo(&(NoEstado->info.cidades), NULL, dadosQuaisquer, &sobe);
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
                    inserirNo(&(NoEstado->info.cidades), NULL, dadosQuaisquer, &sobe);
                    NoEstado->info.populacao += dadosCidade.populacao;
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
                        lerCep(dado);
                        strcpy(dadosQuaisquer.cep, dado);
                        if (strcmp(noCidade->infoUm.cidade.nome, nome) == 0)
                            inserirNo(&(noCidade->infoUm.cidade.ceps), NULL, dadosQuaisquer, &sobe);
                        else 
                            inserirNo(&(noCidade->infoDois.cidade.ceps), NULL, dadosQuaisquer, &sobe);
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
                inserirNo(&pessoas, NULL, dadosQuaisquer, &sobe);
                break;
            case 5:
                //removerCEP();
                break;
            case 6:
                //removerPessoa();
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
                //populacaoDaCapital();
                printf("Digite o nome do estado: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    ArvDoisTres *capital = buscaNo(NoEstado->info.cidades, NoEstado->info.capital);
                    printf("Populacao da capital %s: %d\n", capital->infoUm.cidade.nome, capital->infoUm.cidade.populacao);
                    /*
                    dado = 0;
                    populacaoDaCapital(NoEstado->info.cidades, NoEstado->info.capital, &dado);
                    if(dado)
                    {
                        printf("Populacao da capital %d: %d\n", NoEstado->info.capital, dado);
                    } */
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
                    cidadeMaisPopulosa(NoEstado->info.cidades, NoEstado->info.capital, &noCidade);
                    if(noCidade)
                    {
                        printf("Cidade mais populosa: %s\n", noCidade->infoUm.cidade.nome);
                    }
                    else
                    {
                        printf("A cidade mais populosa eh a capital!\n");
                    }
                }
                break;
            case 10:
                //pessoasForaCidadeNatal();
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
                printf("Digite o cep: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", cep);
                existe = verificaCepEstado(estados, cep);
                if(existe)
                {
                    dadoInt = 0;
                    nascidosQueNaoMoram(pessoas, &dadoInt, cep);
                    if(dado)
                    {
                        printf("%d pessoas nao moram na cidade natal %s.\n", dadoInt, cep);
                    }
                    else
                    {
                        printf("Todos moram na cidade natal!\n");
                    }
                }
                else
                {
                    printf("Cep invalido!\n");
                }
                break;
            case 13:
                //moradoresNaoNascidos();
                printf("Digite o cep: "); 
                setbuf(stdin, NULL);
                scanf("%[^\n]", cep);
                existe = verificaCepEstado(estados, cep);
                if(existe)
                {
                    dadoInt = 0;
                    moradoresNaoNascidos(pessoas, &dadoInt, cep);
                    if(dado)
                    {
                        printf("%s pessoas nao nasceram na cidade %s.\n", dado, cep);
                    }
                    else
                    {
                        printf("Todos nasceram na cidade!\n");
                    }
                }
                else
                {
                    printf("Cep invalido!\n");
                }
                break;
            case 14:
                exibirEstados(estados);
                printf("\n");
                exibirPessoas(pessoas);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    liberarArv(&(estados->info.cidades->infoUm.cidade.ceps));
    liberarArv(&(estados->info.cidades));
    liberarLista(&estados);
    liberarArv(&(pessoas));
    return 0;
}