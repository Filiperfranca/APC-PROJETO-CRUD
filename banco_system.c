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
        int valor;
        char destino[51];

    } historico;

    typedef struct {
        char nome[51];
        double saldo;
        historico extrato;

    } user;
    
    typedef enum {
        CONSULTAR_S = 1,
        DEPOSITAR,
        SACAR,
        TRANSFERIR,
        SAIR
    } menu;

    int opcao;

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
        switch (opcao)
        {
        case CONSULTAR_S:
            
            break;
        default:
            break;
        }

    } while (opcao > 5 || opcao < 1);

    
    return 0;
}