#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prototipos.h"

int insereEstados(Estado **raiz) 
{
    int valores[] = {100, 30, 25, 20, 35, 200, 300, 350, 320, 150, 125, 110, 120, 170, 130, 10};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) 
    {
        InfoEstado dado;
        dado.nome = valores[i];
        dado.cidades = NULL;  // apenas o campo nome do estado é usado
        Estado *novoNo = alocarEstado(dado);
        inserirEstado(raiz, novoNo);
    }
    return 0;
} 

int insereCidades(ArvRubNeg **raiz) 
{
    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) 
    {
        Dados dado;
        dado.cidade.nome = valores[i];  // apenas o campo nome da cidade é usado
        dado.cidade.ceps = NULL;
        ArvRubNeg *novoNo = criarNo(dado);
        insercao(raiz, novoNo);
    }
    return 0;
} 

int insereCeps(ArvRubNeg **raiz) 
{
    int valores[] = {10000, 3000, 2500, 2000, 3500, 20000, 30000, 35000, 32000, 15000, 12500, 11000, 12000, 17000, 13000, 1000};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) 
    {
        Dados dado;
        dado.cep = valores[i]; 
        ArvRubNeg *novoNo = criarNo(dado);
        insercao(raiz, novoNo);
    }
    return 0;
} 

int inserePessoas(ArvRubNeg **raiz) 
{
    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) 
    {
        Dados dado;
        dado.pessoa.cpf = valores[i]; 
        ArvRubNeg *novoNo = criarNo(dado);
        insercao(raiz, novoNo);
    }
    return 0;
}

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

int main() 
{
    Estado *estados = NULL, *NoEstado = NULL;
    ArvRubNeg *pessoas = NULL;
    ArvRubNeg *No = NULL;
    int opcao, dado, inseriu;
    InfoEstado dadosEstado; // informaçoes de estado para preencher
    InfoCidade dadosCidade; // informaçoes de cidade para preencher
    Dados dadosQuaisquer;

    insereEstados(&estados);
    //estados->info.cidades = NULL;
    insereCidades(&(estados->info.cidades));
    //estados->info.cidades->info.cidade.ceps = NULL;
    insereCeps(&(estados->info.cidades->info.cidade.ceps));

    inserePessoas(&pessoas);
    
    do 
    {
        menu();
        printf("Escolha uma opção: ");
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
                dadosCidade = lerInfoCidade();
                dadosQuaisquer.cidade = dadosCidade;
                No = criarNo(dadosQuaisquer);
                inseriu = insercao(&estados->info.cidades, No);
                if(inseriu)
                {
                    printf("Cidade inserida com sucesso!\n");
                }
                else
                {
                    printf("A cidade ja existe! Nao houve insercao.\n");
                }
                break;
            case 3:
                //cadastrarCEP();
                break;
            case 4:
                //cadastrarPessoa();
                break;
            case 5:
                //removerCEP();
                break;
            case 6:
                //removerPessoa();
                break;
            case 7:
                //estadoMaisPopuloso();
                break;
            case 8:
                //populacaoCapital();
                break;
            case 9:
                //cidadeMaisPopulosaExcetoCapital();
                break;
            case 10:
                //pessoasForaCidadeNatal();
                break;
            case 11:
                //cidadeNatalPorCep();
                break;
            case 12:
                //nascidosQueNaoMoram();
                break;
            case 13:
                //moradoresNaoNascidos();
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
    liberarArvore(estados->info.cidades->info.cidade.ceps);
    liberarArvore(estados->info.cidades);
    liberarLista(&estados);
    liberarArvore(pessoas);
    return 0;
}