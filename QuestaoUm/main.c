#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prototipos.h"

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
    printf("0 - Sair\n");
    printf("============================\n");
}

int main() {
    int opcao;
    
    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                //cadastrarEstado();
                break;
            case 2:
                //cadastrarCidade();
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
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

/*
int teste() {

    ArvRubNeg *raiz = NULL;

    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        Dados dado;
        dado.cidade.nome = valores[i];  // Apenas o campo nome da cidade é usado
        ArvRubNeg *novoNo = criarNo(dado);
        insercao(&raiz, novoNo);
    }

    printf("\nárvore antes da remoção:\n");
    imprimirArvore(raiz, 0);

    printf("\n");

    // Exemplo de remoção (descomente se quiser testar):
    // raiz = removeNo(raiz, 2000);
    // printf("\nárvore depois da remoção:\n");
    // imprimirArvore(raiz, 0);

    liberarArvore(raiz);
    return 0;
} */