#include <stdio.h>
#include <string.h>

int main (void) {

    typedef enum {
    DEPOSITO,
    SAQUE,
    TRANSFERENCIA
    } transacao;

    typedef struct {
        transacao tipo;
        double valor;
        char destino[51];

    } historico;

    typedef struct {
        char nome[51];
        double saldo;
        historico extrato[999];

    } user;


    user one;
    one.saldo = 0;
    
    printf("=================\n");
    printf("   BEM VINDO\n");
    printf("=================\n");
    printf("<JARVIS>: olá me chamo Jarvis, serei seu auxílio,\n");
    printf("          vamos começar criando seu usuário, di-\n");
    printf("          te seu nome:\n");
    printf("          USERNAME:");
    fgets(one.nome, sizeof(one.nome), stdin);
    one.nome[strcspn(one.nome, "\n")] = '\0';
    printf("\n");
    printf("<JARVIS>: Perfeito senhor(a) %s; estou contente em\n", one.nome);
    printf("          te ter por aqui, seja bem vindo!\n");
    printf("\n");

    typedef enum {
        CONSULTAR_S = 1,
        DEPOSITAR,
        SACAR,
        TRANSFERIR,
        SAIR
    } menu;

    int opcao;
    int id_transacao = 0;

    do
    {
        printf("==========\n");
        printf("  BANCO\n");
        printf("==========\n");
        printf("\n");
        printf("escolha uma opcao de acordo com seu numero");
        printf("\n");
        printf("1- CONSULTAR SALDO\n");
        printf("2- DEPOSITAR VALOR\n");
        printf("3- SACAR VALOR\n");
        printf("4- TRANSFERIR VALOR\n");
        printf("5- sair\n");
        printf("Digite sua opcao:");
        scanf("%i", &opcao);
        while (getchar() != '\n');
        switch (opcao)
        {
        case CONSULTAR_S:
            printf("\n");
            printf("<JARVIS>: Seu saldo atual: %.2lf\n", one.saldo);
            printf("\n");
            break;
        case TRANSFERIR:
            printf("\n");
            printf("<JARVIS>: informe o nome da pessoa a se\n");
            printf("          transferir\n");
            printf("          DESTINO:");
            fgets(one.extrato[id_transacao].destino, sizeof(one.extrato[id_transacao].destino), stdin);
            one.extrato[id_transacao].destino[strcspn(one.extrato[id_transacao].destino, "\n")] = '\0';
            printf("\n");
            printf("<JARVIS>: informe o valor a ser trans-\n");
            printf("          ferido\n");
            printf("          VALOR:");
            scanf("%lf", &one.extrato[id_transacao].valor);
            if (one.extrato[id_transacao].valor <= one.saldo) {
                printf("\n");
                printf("<JARVIS>: TRANSFERENCIA REALIZADA\n");
                one.saldo -= one.extrato[id_transacao].valor;
            }
            else {
                printf("\n");
                printf("<JARVIS>: VALOR INSUFICIENTE\n");
                one.extrato[id_transacao].valor = 0;
            }
            one.extrato->tipo = TRANSFERENCIA;
            id_transacao ++;
            printf("\n");
            break;
        default:
            printf("\n");
            printf("OPCAO INVALIDA\n");
            printf("\n");
            break;
        }

    } while (opcao != SAIR);

    
    return 0;
}