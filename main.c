#include <stdio.h>
#include <string.h>

// Estrutura para transações
typedef struct Transacao {
    char tipo;
    float valor;
} Transacao;

// Estrutura para informações do cliente
typedef struct {
    char nome[100];
    char cpf[12];
    int tipo_conta; // 1 para comum, 2 para plus
    float saldo;
    char senha[20];
    Transacao extrato[100]; // Histórico de transações
    int numTransacoes; // Número de transações no extrato
} Cliente;

// Função para salvar os dados dos clientes em um arquivo binário
void salvarClientes(Cliente clientes[], int numClientes) {
    FILE *arquivo = fopen("dados_bancarios.bin", "wb");
    if (arquivo) {
        fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para gravação.\n");
    }
}

// Função para carregar os dados dos clientes de um arquivo binário
int carregarClientes(Cliente clientes[]) {
    FILE *arquivo = fopen("dados_bancarios.bin", "rb");
    int numClientes = 0;

    if (arquivo) {
        fread(clientes, sizeof(Cliente), 1000, arquivo);
        fseek(arquivo, 0, SEEK_END);
        numClientes = ftell(arquivo) / sizeof(Cliente);
        fclose(arquivo);
    }

    return numClientes;
}

// Função para salvar extrato em um arquivo binário
void salvarExtrato(Transacao extratoClientes[], int numExtratos) {
    FILE *arquivo = fopen("extratos_bancarios.bin", "wb");
    if (arquivo) {
        fwrite(extratoClientes, sizeof(Transacao), numExtratos, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de extratos para gravação.\n");
    }
}

// Função para carregar extrato de um arquivo binário separado
int carregarExtrato(Transacao extratoClientes[]) {
    FILE *arquivo = fopen("extratos_bancarios.bin", "rb");
    int numExtratos = 0;

    if (arquivo) {
        fread(extratoClientes, sizeof(Transacao), 1000, arquivo);
        fseek(arquivo, 0, SEEK_END);
        numExtratos = ftell(arquivo) / sizeof(Transacao);
        fclose(arquivo);
    }

    return numExtratos;
}

// Função para criar um cliente
void criarNCliente(Cliente clientes[], int *numClientes) {
    if (*numClientes < 1000) {
        Cliente novoCliente;
        printf("Nome: ");
        scanf("%s", novoCliente.nome);
        printf("CPF: ");
        scanf("%s", novoCliente.cpf);
        printf("Tipo de conta (1 para comum, 2 para plus): ");
        scanf("%d", &novoCliente.tipo_conta);
        printf("Valor inicial da conta: ");
        scanf("%f", &novoCliente.saldo);
        printf("Senha do usuário: ");
        scanf("%s", novoCliente.senha);

        clientes[*numClientes] = novoCliente;
        (*numClientes++);

        FILE *arquivo = fopen("dados_bancarios.bin", "wb");
        if (arquivo) {
            fwrite(clientes, sizeof(Cliente), *numClientes, arquivo);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo para gravação.\n");
        }

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

    int clienteEncontrado = -1;

    for (int i = 0; i < *numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfParaApagar) == 0) {
            clienteEncontrado = i;
            break;
        }
    }

    if (clienteEncontrado != -1) {
        for (int i = clienteEncontrado; i < *numClientes - 1; i++) {
            clientes[i] = clientes[i + 1];
        }

        (*numClientes)--;

        FILE *arquivo = fopen("dados_bancarios.bin", "wb");
        if (arquivo) {
            fwrite(clientes, sizeof(Cliente), *numClientes, arquivo);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo para gravação.\n");
        }

        printf("Cliente apagado com sucesso.\n");
    } else {
        printf("Cliente com o CPF %s não encontrado.\n", cpfParaApagar);
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

    int clienteEncontrado = -1;

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfCliente) == 0 && strcmp(clientes[i].senha, senhaCliente) == 0) {
            clienteEncontrado = i;
            break;
        }
    }

    if (clienteEncontrado != -1) {
        if (clientes[clienteEncontrado].tipo_conta == 1) {
            if (clientes[clienteEncontrado].saldo - valorDebito >= -1000) {
                valorDebito = valorDebito + valorDebito * 0.05;
                clientes[clienteEncontrado].saldo -= valorDebito;
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].tipo = 'D';
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].valor = valorDebito;
                clientes[clienteEncontrado].numTransacoes++;
                printf("Débito de %.2lf realizado com sucesso.\n", valorDebito);
            } else {
                printf("Limite de saldo negativo excedido para este tipo de conta.\n");
            }
        } else if (clientes[clienteEncontrado].tipo_conta == 2) {
            if (clientes[clienteEncontrado].saldo - valorDebito >= -5000) {
                valorDebito = valorDebito + valorDebito * 0.03;
                clientes[clienteEncontrado].saldo -= valorDebito;
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].tipo = 'D';
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].valor = valorDebito;
                clientes[clienteEncontrado].numTransacoes++;
                printf("Débito de %.2lf realizado com sucesso.\n", valorDebito);
            } else {
                printf("Limite de saldo negativo excedido para este tipo de conta.\n");
            }
        }
        // Atualize o arquivo binário após realizar o débito
        FILE *arquivo = fopen("dados_bancarios.bin", "wb");
        if (arquivo) {
            fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo para gravação.\n");
        }
    } else {
        printf("CPF ou senha incorretos. Não é possível realizar o débito.\n");
    }
}

// Função para realizar um depósito na conta do cliente
void deposito(Cliente clientes[], int numClientes) {
    char cpfCliente[12];
    double valorDeposito;

    printf("Digite o CPF: ");
    scanf("%s", cpfCliente);
    printf("Digite o valor a ser depositado: ");
    scanf("%lf", &valorDeposito);

    int clienteEncontrado = -1;

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfCliente) == 0) {
            clienteEncontrado = i;
            break;
        }
    }

    if (clienteEncontrado != -1) {
        clientes[clienteEncontrado].saldo += valorDeposito;

        clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].tipo = 'C';
        clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].valor = valorDeposito;
        clientes[clienteEncontrado].numTransacoes++;

        FILE *arquivo = fopen("dados_bancarios.bin", "wb");
        if (arquivo) {
            fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo para gravação.\n");
        }

        printf("Depósito de %.2lf realizado com sucesso.\n", valorDeposito);
    } else {
        printf("Cliente com o CPF %s não encontrado.\n", cpfCliente);
    }
}

// Função para gerar um extrato
void extrato(Cliente clientes[], int numClientes) {
    char cpfCliente[12];
    char senhaCliente[20];

    printf("Digite o CPF: ");
    scanf("%s", cpfCliente);
    printf("Digite a senha: ");
    scanf("%s", senhaCliente);

    int clienteEncontrado = -1;

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfCliente) == 0 && strcmp(clientes[i].senha, senhaCliente) == 0) {
            clienteEncontrado = i;
            break;
        }
    }

    if (clienteEncontrado != -1) {
        printf("Extrato para o cliente: %s\n", clientes[clienteEncontrado].nome);
        printf("CPF: %s\n", clientes[clienteEncontrado].cpf);
        printf("Historico de transacoes:\n");

        for (int i = 0; i < clientes[clienteEncontrado].numTransacoes; i++) {
            if (clientes[clienteEncontrado].extrato[i].tipo == 'D') {
                printf("(-) Debito: %.2lf\n ", clientes[clienteEncontrado].extrato[i].valor);
            } else if (clientes[clienteEncontrado].extrato[i].tipo == 'C') {
                printf("(+) Deposito: %.2lf\n ", clientes[clienteEncontrado].extrato[i].valor);
            } else if (clientes[clienteEncontrado].extrato[i].tipo == 'P') {
                printf("(-) Transferencia: %.2lf\n ", clientes[clienteEncontrado].extrato[i].valor);
            } else if (clientes[clienteEncontrado].extrato[i].tipo == 'R') {
                printf("(+) Transferencia: %.2lf\n ", clientes[clienteEncontrado].extrato[i].valor);
            }
        }
        printf("Saldo atual: %.2lf\n", clientes[clienteEncontrado].saldo);
    } else {
        printf("CPF ou senha incorretos. Não é possível gerar o extrato.\n");
    }
}

// Função para realizar uma transferência entre contas
void transferencia(Cliente clientes[], int numClientes) {
    char cpfOrigem[12];
    char senhaOrigem[20];
    char cpfDestino[12];
    float valorTransferencia;

    printf("Digite o CPF da conta de origem: ");
    scanf("%s", cpfOrigem);
    printf("Digite a senha da conta de origem: ");
    scanf("%s", senhaOrigem);
    printf("Digite o CPF da conta de destino: ");
    scanf("%s", cpfDestino);
    printf("Digite o valor a ser transferido: ");
    scanf("%f", &valorTransferencia);

    int clienteOrigem = -1;
    int clienteDestino = -1;

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfOrigem) == 0 && strcmp(clientes[i].senha, senhaOrigem) == 0) {
            clienteOrigem = i;
        }
        if (strcmp(clientes[i].cpf, cpfDestino) == 0) {
            clienteDestino = i;
        }
    }

    if (clienteOrigem != -1 && clienteDestino != -1) {
        if (clientes[clienteOrigem].tipo_conta == 1) {
            if (clientes[clienteOrigem].saldo - valorTransferencia >= -1000) {
                clientes[clienteOrigem].saldo -= valorTransferencia;
                clientes[clienteDestino].saldo += valorTransferencia;
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].tipo = 'P';
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].valor = valorTransferencia;
                clientes[clienteOrigem].numTransacoes++;
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].tipo = 'R';
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].valor = valorTransferencia;
                clientes[clienteDestino].numTransacoes++;
                printf("Transferência de %.2f realizada com sucesso.\n", valorTransferencia);
            } else {
                printf("Limite de saldo negativo excedido para a conta de origem.\n");
            }
        } else if (clientes[clienteOrigem].tipo_conta == 2) {
            if (clientes[clienteOrigem].saldo - valorTransferencia >= -5000) {
                clientes[clienteOrigem].saldo -= valorTransferencia;
                clientes[clienteDestino].saldo += valorTransferencia;
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].tipo = 'P';
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].valor = valorTransferencia;
                clientes[clienteOrigem].numTransacoes++;
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].tipo = 'R';
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].valor = valorTransferencia;
                clientes[clienteDestino].numTransacoes++;
                printf("Transferência de %.2f realizada com sucesso.\n", valorTransferencia);
            } else {
                printf("Limite de saldo negativo excedido para a conta de origem.\n");
            }
        }

        FILE *arquivo = fopen("dados_bancarios.bin", "wb");
        if (arquivo) {
            fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo para gravação.\n");
        }
    } else {
        printf("Conta de origem, conta de destino ou senha incorretos. Não é possível realizar a transferência.\n");
    }
}

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
