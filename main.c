#include <stdio.h>
#include "biblioteca.h"

int main() {
    Cliente clientes[1000]; // Array para armazenar os clientes
    Transacao extratoClientes[1000]; // Array para armazenar os extratos
    int numClientes = carregarClientes(clientes); // Carregar os clientes do arquivo
    int numExtratos = carregarExtrato(extratoClientes); // Carregar os extratos do arquivo

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
            case 4:
                debito(clientes, numClientes);
                break;
            case 5:
                deposito(clientes, numClientes);
                break;
            case 6:
                extrato(clientes, numClientes);
                break;
            case 7:
                transferencia(clientes, numClientes);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");

        }

    } while (opcao != 0);

    salvarClientes(clientes, numClientes); // Salvar os clientes no arquivo
    salvarExtrato(extratoClientes, numExtratos); // Salvar os extratos no arquivo

    return 0;
}
