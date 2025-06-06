#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prototiposDois.h"

int insereEstados(Estado **raiz) {

    int valores[] = {100, 30, 25, 20, 35, 200, 300, 350, 320, 150, 125, 110, 120, 170, 130, 10};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        InfoEstado dado;
        dado.nome = valores[i];
        dado.cidades = NULL;  // apenas o campo nome do estado é usado
        Estado *novoNo = alocarEstado(dado);
        inserirEstado(raiz, novoNo);
    }

    return 0;
} 

int insereCidades(ArvDoisTres **raiz) {

    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        Dados sobe;
        Dados dado;
        dado.cidade.nome = valores[i];  // apenas o campo nome da cidade é usado
        dado.cidade.ceps = NULL;
        inserirNo(raiz, NULL, dado, &sobe);
    }

    return 0;
} 

int insereCeps(ArvDoisTres **raiz) {

    int valores[] = {10000, 3000, 2500, 2000, 3500, 20000, 30000, 35000, 32000, 15000, 12500, 11000, 12000, 17000, 13000, 1000};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        Dados sobe;
        Dados dado;
        dado.cep = valores[i]; 
        inserirNo(raiz, NULL, dado, &sobe);
    }

    return 0;
} 

int inserePessoas(ArvDoisTres **raiz) {
    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        Dados sobe;
        Dados dado;
        dado.pessoa.cpf = valores[i]; 
        inserirNo(raiz, NULL, dado, &sobe);
    }

    return 0;
}

void menu() {
    printf("\n=========== MENU ===========\n");
    printf("1 - Cadastrar Estado\n");
    printf("2 - Cadastrar Cidade\n");
    printf("3 - Cadastrar CEP\n");
    printf("4 - Cadastrar Pessoa\n");
    printf("5 - Remover CEP\n");
    printf("6 - Remover Pessoa\n");
    printf("7 - Estado mais populoso\n");
    printf("8 - População da capital de um estado\n");
    printf("9 - Cidade mais populosa de um estado (exceto a capital)\n");
    printf("10 - Quantas pessoas não moram na cidade natal\n");
    printf("11 - Cidade natal de uma pessoa pelo CEP de natalidade\n");
    printf("12 - Quantas pessoas nascidas em uma cidade não moram nela\n");
    printf("13 - Quantas pessoas que moram em uma cidade não nasceram nela\n");
    printf("14 - Visualizar todas as árvores\n");
    printf("0 - Sair\n");
    printf("============================\n");
}

int main() {
    Estado *estados = NULL, *NoEstado = NULL;
    ArvDoisTres *pessoas = NULL;
    ArvDoisTres *No = NULL;
    ArvDoisTres *noCidade = NULL;
    int opcao, dado, inseriu, nome, existe, cep;
    InfoEstado dadosEstado; // informaçoes de estado para preencher
    InfoCidade dadosCidade; // informaçoes de cidade para preencher
    InfoPessoa dadosPessoa; // informaçoes de pessoa para preencher
    Dados dadosQuaisquer, sobe;
    insereEstados(&estados);
    //estados->info.cidades = NULL;
    insereCidades(&(estados->info.cidades));
    //estados->info.cidades->info.cidade.ceps = NULL;
    insereCeps(&(estados->info.cidades->infoUm.cidade.ceps));

    inserePessoas(&pessoas);
    
    do {
        menu();
        printf("Escolha uma opção: ");
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
                printf("Digite o nome do estado: "); scanf("%d", &nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    dadosCidade = lerInfoCidade();
                    dadosQuaisquer.cidade = dadosCidade;
                    inserirNo(&(NoEstado->info.cidades), NULL, dadosQuaisquer, &sobe);

                    /*if(inseriu)
                    {
                        printf("Cidade inserida com sucesso!\n");
                    }
                    else
                    {
                        printf("A cidade ja existe! Nao houve insercao.\n");
                        free(No);
                    }*/
                }
                else
                {
                    printf("Estado nao encontrado!\n");
                }
                break;
            case 3:
                //cadastrarCEP();
                printf("Digite o nome do estado: "); scanf("%d", &nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    printf("Digite o nome da cidade: "); scanf("%d", &nome);
                    noCidade = buscaNo(NoEstado->info.cidades, nome);
                    if(noCidade)
                    {
                        dado = lerCep();
                        dadosQuaisquer.cep = dado;
                        if (noCidade->infoUm.cidade.nome == nome)
                            inserirNo(&(noCidade->infoUm.cidade.ceps), NULL, dadosQuaisquer, &sobe);
                        else 
                            inserirNo(&(noCidade->infoDois.cidade.ceps), NULL, dadosQuaisquer, &sobe);

                        /*if(inseriu)
                        {
                            printf("Cep inserido com sucesso!\n");
                        }
                        else
                        {
                            printf("O cep ja existe! Nao houve insercao.\n");
                            free(No);
                        }*/
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
                break;
            case 6:
                //removerPessoa();
                break;
            case 7:
                //estadoMaisPopuloso();
                NoEstado = estadoMaisPopuloso(estados);
                if(NoEstado)
                {
                    printf("Estado mais populoso: %d\n", NoEstado->info.nome);
                }
                else
                {
                    printf("Sem estados cadastrados!\n");
                }
                break;
            case 8:
                //populacaoDaCapital();
                printf("Digite o nome do estado: "); scanf("%d", &nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    dado = 0;
                    populacaoDaCapital(NoEstado->info.cidades, NoEstado->info.capital, &dado);
                    if(dado)
                    {
                        printf("Populacao da capital %d: %d\n", NoEstado->info.capital, dado);
                    }
                }
                else
                {
                    printf("Estado nao cadastrado!\n");
                }
                break;
            case 9:
                //cidadeMaisPopulosaExcetoCapital();
                printf("Digite o nome do estado: "); scanf("%d", &nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    noCidade = NoEstado->info.cidades;
                    cidadeMaisPopulosa(NoEstado->info.cidades, NoEstado->info.capital, &noCidade);
                    if(noCidade)
                    {
                        printf("Cidade mais populosa: %d\n", noCidade->infoUm.cidade.nome);
                    }
                    else
                    {
                        printf("A cidade mais populosa eh a capital!\n");
                    }
                }
                break;
            case 10:
                //pessoasForaCidadeNatal();
                dado = 0;
                pessoasForaCepNatal(pessoas, &dado);
                if(dado)
                {
                    printf("%d pessoas moram fora da cidade natal!\n", dado);
                }
                else
                {
                    printf("Todos moram na cidade natal\n");
                }
                break;
            case 11:
                //cidadeNatal();
                printf("Digite o nome do estado: "); scanf("%d", nome);
                NoEstado = buscarEstado(estados, nome);
                if(NoEstado)
                {
                    printf("Digi")
                }
                break;
            case 12:
                //nascidosQueNaoMoram();
                printf("Digite o cep: "); scanf("%d", &cep);
                existe = verificaCepEstado(estados, cep);
                if(existe)
                {
                    dado = 0;
                    nascidosQueNaoMoram(pessoas, &dado, cep);
                    if(dado)
                    {
                        printf("%d pessoas nao moram na cidade natal %d.\n", dado, cep);
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
                printf("Digite o cep: "); scanf("%d", &cep);
                existe = verificaCepEstado(estados, cep);
                if(existe)
                {
                    dado = 0;
                    moradoresNaoNascidos(pessoas, &dado, cep);
                    if(dado)
                    {
                        printf("%d pessoas nao nasceram na cidade %d.\n", dado, cep);
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
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberarArv(&(estados->info.cidades->infoUm.cidade.ceps));
    liberarArv(&(estados->info.cidades));
    liberarLista(&estados);
    
    liberarArv(&(pessoas));

    return 0;
}