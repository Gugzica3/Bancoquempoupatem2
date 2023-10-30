#include <stdio.h>
#include "biblioteca.h"

int main() {
    Cliente clientes[MAX_CLIENTES];
    int numClientes = carregarClientes(clientes);

    int opcao;
    do {
        printf("Menu de Opcoes:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Debito\n");
        printf("5. Deposito\n");
        printf("6. Extrato\n");
        printf("7. Transferencia Entre Contas\n");
        printf("8. Acessar saldo atual\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarNCliente(clientes, &numClientes);
                break;
            case 2:
                apagarCliente(clientes, &numClientes);
                break;
            case 3:
                listarClientes(clientes, numClientes);
                break;
            case 4: {
                char cpfCliente[12];
                char senhaCliente[20];
                double valorDebito;
                printf("Digite o CPF: ");
                scanf("%s", cpfCliente);
                printf("Digite a senha: ");
                scanf("%s", senhaCliente);
                printf("Digite o valor a ser debitado: ");
                scanf("%lf", &valorDebito);
                printf("");
                debito(clientes, numClientes, cpfCliente, senhaCliente, valorDebito);
                break;
            }
            case 5:
                deposito(clientes, numClientes);
                break;
            case 6:
                extrato(clientes, numClientes);
                break;
            case 7:
                transferencia(clientes, numClientes);
                break;
            case 8:
                verificarSaldo(clientes, numClientes);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");

        }

    } while (opcao != 0);

    salvarClientes(clientes, numClientes);
    salvarExtratoTXT(clientes, numClientes);

    return 0;
}