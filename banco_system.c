#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

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
    while (1)
    {
        fgets(one.nome, sizeof(one.nome), stdin);
        one.nome[strcspn(one.nome, "\n")] = '\0';
        if (strlen(one.nome) == 0)
        {
            printf("<JARVIS>: Opa, parece que nada foi digi-");
            printf("          tado, tente novamente\n");
            printf("\n");
        }
        else {
            break;
        }
    }
    
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
        printf("1- CONSULTAR SALDO/EXTRATO\n");
        printf("2- DEPOSITAR VALOR\n");
        printf("3- SACAR VALOR\n");
        printf("4- TRANSFERIR VALOR\n");
        printf("5- sair\n");
        printf("Digite sua opcao:");
        if (scanf("%i", &opcao) != 1) {
            printf("OPCAO INVALIDA\n");
            while (getchar() != '\n');
            printf("\n");
            continue;
        }
        while (getchar() != '\n');
        switch (opcao)
        {
        case CONSULTAR_S:
            printf("\n");
            printf("<JARVIS>: Seu saldo atual: %.2lf\n", one.saldo);
            printf("\n");
            if (id_transacao == 0) {
                printf("<JARVIS>: Nenhuma transacao registrada.\n\n");
                break;
            }
            printf("<JARVIS>: Seu extrato:\n");
            printf("TIPO    VALOR    DESTINO\n");
            for (int i = 0; i < id_transacao; i++) {
                char *tipo;

            switch (one.extrato[i].tipo)
            {
                case DEPOSITO:
                    tipo = "DEPOSITO";
                    break;

                case SAQUE:
                    tipo = "SAQUE";
                    break;

                case TRANSFERENCIA:
                    tipo = "TRANSFERENCIA";
                    break;
                default:
                    tipo = "DESCONHECIDO";
                    break;
            }
                printf("%-15s %-10.2lf %s\n", tipo, one.extrato[i].valor, one.extrato[i].destino);
            }
            printf("\n");
            break;
        case TRANSFERIR:
            if (id_transacao >= 999) {
            printf("LIMITE DE TRANSACOES ATINGIDO\n");
            break;
            }
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
            if(scanf("%lf", &one.extrato[id_transacao].valor) != 1){
                printf("\n");
                printf("<JARVIS>: Opa, digite corretamente\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');
            one.extrato[id_transacao].valor = fabs(one.extrato[id_transacao].valor);
            if (one.extrato[id_transacao].valor == 0)
            {
                printf("\n");
                printf("<JARVIS>: TRANSFIRA UM VALOR MAIOR QUE 0\n");
            }
            else if (one.extrato[id_transacao].valor <= one.saldo) {
                printf("\n");
                printf("<JARVIS>: TRANSFERENCIA REALIZADA\n");
                one.saldo -= one.extrato[id_transacao].valor;
                one.extrato[id_transacao].tipo = TRANSFERENCIA;
                id_transacao++;
            }
            else {
                printf("\n");
                printf("<JARVIS>: SALDO INSUFICIENTE\n");
            }
            printf("\n");
            break;
        case DEPOSITAR:
            if (id_transacao >= 999) {
            printf("LIMITE DE TRANSACOES ATINGIDO\n");
            break;
            }
            printf("\n");
            printf("<JARVIS>: Informe o valor a se de-\n");
            printf("          positar\n");
            printf("          VALOR:");
            if(scanf("%lf", &one.extrato[id_transacao].valor) != 1){
                printf("\n");
                printf("<JARVIS>: Opa, digite corretamente\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');
            one.extrato[id_transacao].valor = fabs(one.extrato[id_transacao].valor);
            if (one.extrato[id_transacao].valor != 0)
            {
                if (one.saldo + one.extrato[id_transacao].valor > DBL_MAX) {
                    printf("<JARVIS>: Opa, ta com pacote grande demais pae\n");
                    printf("          , insira um valor menor\n");
                    one.extrato[id_transacao].valor = 0;
                    break;
                }
                one.saldo += one.extrato[id_transacao].valor;
                printf("\n");
                printf("<JARVIS>: DEPOSITO REALIZADO\n");
                one.extrato[id_transacao].tipo = DEPOSITO;
                strcpy(one.extrato[id_transacao].destino, one.nome);
                printf("\n");
                id_transacao ++;
            }
            else {
                printf("\n");
                printf("<JARVIS>: DEPOSITE UM VALOR MAIOR QUE 0\n");
            }
            printf("\n");
            break;
            
        case SACAR:
            if (id_transacao >= 999) {
            printf("LIMITE DE TRANSACOES ATINGIDO\n");
            break;
            }
            printf("\n");
            printf("<JARVIS>: Informe o valor a ser sa-\n");
            printf("          cado\n");
            printf("          VALOR:");
            if(scanf("%lf", &one.extrato[id_transacao].valor) != 1){
                printf("\n");
                printf("<JARVIS>: Opa, digite corretamente\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');
            one.extrato[id_transacao].valor = fabs(one.extrato[id_transacao].valor);
            if (one.extrato[id_transacao].valor == 0)
            {
                printf("\n");
                printf("<JARVIS>: SAQUE UM VALOR MAIOR QUE 0\n");
            }
            
            else if (one.extrato[id_transacao].valor <= one.saldo)
            {
                printf("\n");
                printf("<JARVIS>: SAQUE REALIZADO\n");
                one.extrato[id_transacao].tipo = SAQUE;
                strcpy(one.extrato[id_transacao].destino, one.nome);
                one.saldo -= one.extrato[id_transacao].valor;
                id_transacao++;
            }
            else {
                printf("\n");
                printf("<JARVIS>: SALDO INSUFICIENTE\n");
            }
            printf("\n");
            break;
        
        case SAIR:
            printf("\n");
            printf("<JARVIS>: ENCERRANDO SISTEMA\n");
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