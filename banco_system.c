#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

int main (void) {

    typedef enum {
    DEPOSITO,
    SAQUE,
    TRANSFERENCIA
    } transacao;

    typedef struct {
        int id;
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
        EDITAR_T,
        PESQUISAR,
        SAIR
    } menu;

    int opcao;
    int id_transacao = 0;
    int id_pesquisa;
    int proximo_id = 0;

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
        printf("5- EDITAR TRANSFERENCIA\n");
        printf("6- PESQUISAR TRANSFERENCIA\n");
        printf("7- sair\n");
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
            printf("ID    TIPO    VALOR    DESTINO\n");
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
                printf("%-5i %-15s %-10.2lf %s\n", one.extrato[i].id, tipo
                    ,one.extrato[i].valor, one.extrato[i].destino);
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
                one.extrato[id_transacao].id = proximo_id;
                id_transacao++;
                proximo_id++;
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
                one.extrato[id_transacao].id = proximo_id;
                id_transacao++;
                proximo_id++;
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
                one.extrato[id_transacao].id = proximo_id;
                id_transacao++;
                proximo_id++;
            }
            else {
                printf("\n");
                printf("<JARVIS>: SALDO INSUFICIENTE\n");
            }
            printf("\n");
            break;
        case PESQUISAR:
            printf("\n");
            printf("<JARVIS>: informe o id da tran-\n");
            printf("          sação\n");
            printf("          ID:");
            if(scanf("%i", &id_pesquisa)!=1) {
                printf("\n");
                printf("<JARVIS>: Opa, digite corretamente\n");
                while (getchar() != '\n');
                break;
            }
            int indice = -1;

            for (int i = 0; i < id_transacao; i++)
            {
                if (one.extrato[i].id == id_pesquisa)
                {
                    indice = i;
                    break;
                }
            }
            if (indice == -1)
            {
                printf("<JARVIS>: Valor nao registrado.\n");
                break;
            }

            else {
                char *tipo;
                switch (one.extrato[indice].tipo)
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
                printf("ID    TIPO    VALOR    DESTINO\n");
                printf("%-5i %-15s %-10.2lf %s\n", one.extrato[indice].id, tipo
                    ,one.extrato[indice].valor, one.extrato[indice].destino);
                 
            }
            printf("\n");
            break;
        case EDITAR_T:
            printf("\n");
            printf("<JARVIS>: informe o id da tran-\n");
            printf("          sação\n");
            printf("          ID:");
            if(scanf("%i", &id_pesquisa)!=1) {
                printf("\n");
                printf("<JARVIS>: Opa, digite corretamente\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');
            id_pesquisa = abs(id_pesquisa);
            
            typedef enum {
                EDITAR=1,
                APAGAR,
                VOLTAR
            } menu_edit;
            int opcao_edit=0;
            printf("\n");
            
            while (opcao_edit != VOLTAR)
            {
                printf("================\n");
                printf("  MENU EDITAR\n");
                printf("================\n");
                printf("\n");
                printf("escolha uma opcao de acordo com seu numero");
                printf("\n");
                printf("1- EDITAR\n");
                printf("2- APAGAR\n");
                printf("3- VOLTAR\n");
                printf("Digite sua opcao:");
                if (scanf("%i", &opcao_edit) != 1) {
                    printf("OPCAO INVALIDA\n");
                    while (getchar() != '\n');
                    printf("\n");
                    continue;
                }
                while (getchar() != '\n');

                int indice = -1;

                for (int i = 0; i < id_transacao; i++)
                {
                    if (one.extrato[i].id == id_pesquisa)
                    {
                        indice = i;
                        break;
                    }
                } 
                if (indice == -1)
                {
                    printf("<JARVIS>: Transacao nao encontrada.\n");
                    break;
                }

                switch (opcao_edit)
                {
                    case EDITAR:
                        if (one.extrato[indice].tipo == SAQUE)
                        {
                            printf("<JARVIS>: Edite este saque infor-\n");
                            printf("          me o valor\n");
                            printf("          VALOR:");
                            double temp;
                            if (scanf("%lf", &temp) != 1)
                            {
                                printf("\n");
                                printf("<JARVIS>: Opa, digite corretamente\n");
                                while (getchar() != '\n');
                                break;
                            }
                            while (getchar() != '\n');
                            temp = fabs(temp);
                            one.saldo += one.extrato[indice].valor;
                            if (temp <= one.saldo)
                            {
                                printf("\n");
                                printf("<JARVIS>: SAQUE MODIFICADO\n");
                                one.saldo -= temp;
                                one.extrato[indice].valor = temp;
                                printf("\n");
                                break;
                            }
                            else {
                                printf("\n");
                                printf("<JARVIS>: SALDO INSUFICIENTE\n");
                                one.saldo -= one.extrato[indice].valor;
                                printf("\n");
                                break;
                            }
                            
                            
                        }
                        else if (one.extrato[indice].tipo == TRANSFERENCIA) {
                            printf("<JARVIS>: Edite essa transferencia\n");
                            printf("          informe o valor\n");
                            printf("          VALOR:");
                            double temp;
                            if (scanf("%lf", &temp) != 1) {
                                printf("\n");
                                printf("<JARVIS>: Opa, digite corretamente\n");
                                while (getchar() != '\n');
                                break;
                            }
                            while (getchar() != '\n');
                            temp = fabs(temp);
                            one.saldo += one.extrato[indice].valor;
                            if (temp <= one.saldo)
                            {
                                printf("\n");
                                printf("<JARVIS>: TRANSFERENCIA MODIFICADA\n");
                                one.saldo -= temp;
                                one.extrato[indice].valor = temp;
                                printf("\n");
                            }
                            else {
                                printf("\n");
                                printf("<JARVIS>: SALDO INSUFICIENTE\n");
                                one.saldo -= one.extrato[indice].valor;
                                printf("\n");
                                break;
                            }
                            printf("<JARVIS>: informe o novo desti-\n");
                            printf("          no (caso seja o mesmo\n");
                            printf("          repita\n");
                            printf("          DESTINO:");
                            fgets(one.extrato[indice].destino, sizeof(one.extrato[indice].destino), stdin);
                            one.extrato[indice].destino[strcspn(one.extrato[indice].destino, "\n")] = '\0';
                            printf("\n");
                            printf("<JARVIS>: TRANSFERENCIA MODIFICADA!\n");
                            break;
                        }
                        else if (one.extrato[indice].tipo == DEPOSITO)
                        {
                            printf("<JARVIS>: Edite esse Depósito infor-\n");
                            printf("          me o valor\n");
                            printf("          VALOR:");
                            double temp;
                            if (scanf("%lf", &temp) != 1) {
                                printf("\n");
                                printf("<JARVIS>: Opa, digite corretamente\n");
                                while (getchar() != '\n');
                                break;
                            }
                            while (getchar() != '\n');
                            temp = fabs(temp);
                            if (one.saldo - one.extrato[indice].valor + temp > DBL_MAX) {
                                printf("<JARVIS>: Opa, ta com pacote grande demais pae\n");
                                printf("          , insira um valor menor\n");
                                break;
                            }

                            if (temp <= 0)
                            {
                                printf("<JARVIS>: opa, insira um valor dife-\n");
                                printf("          rente de 0\n");
                                printf("\n");
                                break;
                            }
                            else {
                                one.saldo -= one.extrato[indice].valor;
                                one.saldo += temp;
                                one.extrato[indice].valor = temp;
                                printf("<JARVIS>: DEPÓSITO MODIFICADO!\n");
                                printf("\n");
                                break;
                            }
                            break;
                            
                        }
                        break;
                    case APAGAR:
                        printf("<JARVIS>: AVISO!!!!\n");
                        printf("          Apagar uma transação não anula\n");
                        printf("          sua modificação, se quiser ze-\n");
                        printf("          ar a transação e receber extor-\n");
                        printf("          no, edite-a, aqui você apaga o\n");
                        printf("          registro\n");
                        printf("\n");
                        printf("<JARVIS>: Digite 1 para continuar, 0 para\n");
                        printf("          cancelar\n");
                        int escolha;
                        if (scanf("%i", &escolha) != 1) {
                            printf("\n");
                                printf("<JARVIS>: digite números\n");
                                while (getchar() != '\n');
                                break;
                        }

                        if (escolha == 1) {
                            printf("<JARVIS>: TRANSAÇÃO APAGADA!\n");
                            printf("\n");
                            id_transacao--;
                            for (int i = indice; i < id_transacao; i++)
                            {
                                one.extrato[i] = one.extrato[i + 1];
                            }
                            break;
                        }
                        else if (escolha == 0)
                        {
                            break;
                        }
                        else {
                            printf("<JARVIS>: Escolha 1 ou 0\n");
                            printf("\n");
                            break;
                        }
                    case VOLTAR:
                        break;
                    default:
                        printf("\n");
                        printf("OPCAO INVALIDA\n");
                        printf("\n");
                        break;
                }
            }
            
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