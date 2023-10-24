#include <stdio.h>
#include "biblioteca.h"

// armazenar informações do cliente
typedef struct {
    char nome[100];
    char cpf[12];
    int tipo_conta; // 1 para comum, 2 para plus
    double saldo;
    char senha[20];
} Cliente;

// Função para criar um novo cliente
void criarNCliente(Cliente clientes[], int *numClientes) {
    if (*numClientes < 1000) { // Verificar se há espaço para mais clientes
        Cliente novoCliente;
        printf("Nome: ");
        scanf("%s", novoCliente.nome); // Supondo que o nome não contém espaços
        printf("CPF: ");
        scanf("%s", novoCliente.cpf);
        printf("Tipo de conta (1 para comum, 2 para plus): ");
        scanf("%d", &novoCliente.tipo_conta);
        printf("Valor inicial da conta: ");
        scanf("%lf", &novoCliente.saldo);
        printf("Senha do usuário: ");
        scanf("%s", novoCliente.senha);

        // Adicione o novo cliente ao array de clientes
        clientes[*numClientes] = novoCliente;
        (*numClientes)++;

        printf("Novo cliente criado com sucesso.\n");
    } else {
        printf("Limite de clientes atingido. Não é possível adicionar mais clientes.\n");
    }
}

// Função para apagar um cliente pelo CPF
void apagarCliente(Cliente clientes[], int *numClientes) {
    char cpfParaApagar[12];
    printf("Digite o CPF do cliente que deseja apagar: ");
    scanf("%s", cpfParaApagar);

    int clienteEncontrado = -1; // Inicializamos com -1 para indicar que o cliente não foi encontrado

    for (int i = 0; i < *numClientes; i++) {
        if (CompararString(clientes[i].cpf, cpfParaApagar) == 0) {
            clienteEncontrado = i; // Encontrou o cliente pelo CPF
            break;
        }
    }

    if (clienteEncontrado != -1) {
        // Movemos todos os clientes após o cliente excluído uma posição para trás
        for (int i = clienteEncontrado; i < *numClientes - 1; i++) {
            clientes[i] = clientes[i + 1];
        }

        (*numClientes)--; // Decrementamos o número de clientes
        printf("Cliente apagado com sucesso.\n");
    } else {
        printf("Cliente com o CPF %s não encontrado.\n", cpfParaApagar);
    }

    // Atualize o arquivo binário após apagar um cliente
    FILE *arquivo = fopen("dados_bancarios.dat", "wb");
    if (arquivo) {
        fwrite(clientes, sizeof(Cliente), *numClientes, arquivo);
        fclose(arquivo);
    }
}

// Função para listar todos os clientes
void listarClientes(Cliente clientes[], int numClientes) {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
    } else {
        printf("Lista de clientes:\n");
        for (int i = 0; i < numClientes; i++) {
            printf("Cliente %d:\n", i + 1);
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            if (clientes[i].tipo_conta == 1) {
                printf("Tipo de conta: Comum\n");
            } else if (clientes[i].tipo_conta == 2) {
                printf("Tipo de conta: Plus\n");
            }
            printf("Saldo: %.2lf\n", clientes[i].saldo);
            printf("\n");
        }
    }

}

// Função para realizar um débito na conta do cliente
void debito(Cliente clientes[], int numClientes) {
    char cpfCliente[12];
    char senhaCliente[20];
    double valorDebito;

    printf("Digite o CPF: ");
    scanf("%s", cpfCliente);
    printf("Digite a senha: ");
    scanf("%s", senhaCliente);
    printf("Digite o valor a ser debitado: ");
    scanf("%lf", &valorDebito);

    int clienteEncontrado = -1; // Inicializamos com -1 para indicar que o cliente não foi encontrado

    for (int i = 0; i < numClientes; i++) {
        if (CompararString(clientes[i].cpf, cpfCliente) && CompararString(clientes[i].senha, senhaCliente)) {
            clienteEncontrado = i; // Encontrou o cliente pelo CPF e senha
            break;
        }
    }

    if (clienteEncontrado != -1) {
        if (clientes[clienteEncontrado].saldo >= valorDebito) {
            // Efetua o débito na conta do cliente
            clientes[clienteEncontrado].saldo -= valorDebito;
            printf("Débito de %.2lf realizado com sucesso.\n", valorDebito);
        } else {
            printf("Saldo insuficiente para realizar o débito.\n");
        }
    } else {
        printf("CPF ou senha incorretos. Não é possível realizar o débito.\n");
    }
}


// Função para realizar um depósito na conta do cliente
void deposito(Cliente clientes[], int numClientes) {
    FILE *arquivo = fopen("dados_bancarios.dat", "wb");
    if (arquivo) {
        fread(clientes, sizeof(Cliente), 1000, arquivo);
        fclose(arquivo);
    }
}

// Função para gerar um extrato
void extrato(Cliente clientes[], int numClientes) {
    FILE *arquivo = fopen("dados_bancarios.dat", "wb");
    if (arquivo) {
        fread(clientes, sizeof(Cliente), 1000, arquivo);
        fclose(arquivo);
    }
}

// Função para realizar uma transferência entre contas
void transferencia(Cliente clientes[], int numClientes) {
    FILE *arquivo = fopen("dados_bancarios.dat", "wb");
    if (arquivo) {
        fread(clientes, sizeof(Cliente), 1000, arquivo);
        fclose(arquivo);
    }
}

int main() {
    Cliente clientes[1000]; // Array para armazenar os clientes
    int numClientes = 0;

    FILE *arquivo = fopen("dados_bancarios.dat", "rb");
    if (arquivo) {
        fread(clientes, sizeof(Cliente), 1000, arquivo);
        fclose(arquivo);
        }
    int opcao;
    do {
        printf("Menu de Opções:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Débito\n");
        printf("5. Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência Entre Contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
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
    arquivo = fopen("dados_bancarios.dat", "wb");
    if (arquivo) {
        fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
        fclose(arquivo);
    }
    return 0;
    }
