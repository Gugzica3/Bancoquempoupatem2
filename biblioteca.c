//
// Created by gusta on 24/10/2023.
//

#include "biblioteca.h"

#include "biblioteca.h"

// Função para salvar os dados dos clientes em um arquivo binário
void salvarClientes(Cliente clientes[], int numClientes) {
    FILE *arquivo = fopen("dados_bancarios.bin", "wb"); // Abre um arquivo binário para escrita
    if (arquivo) { // Verifica se o arquivo foi aberto com sucesso
        fwrite(clientes, sizeof(Cliente), numClientes, arquivo); // Escreve os dados dos clientes no arquivo
        fclose(arquivo); // Fecha o arquivo
    } else {
        printf("Erro ao abrir o arquivo para gravação.\n"); // Imprime uma mensagem de erro caso o arquivo não possa ser aberto
    }
}

// Função para carregar os dados dos clientes de um arquivo binário
int carregarClientes(Cliente clientes[]) {
    FILE *arquivo = fopen("dados_bancarios.bin", "rb"); // Abre um arquivo binário para leitura
    int numClientes = 0; // Inicializa o número de clientes como 0

    if (arquivo) { // Verifica se o arquivo foi aberto com sucesso
        fread(clientes, sizeof(Cliente), 1000, arquivo); // Lê os dados dos clientes do arquivo
        fseek(arquivo, 0, SEEK_END); // Move o cursor para o fim do arquivo
        numClientes = ftell(arquivo) / sizeof(Cliente); // Calcula o número de clientes com base no tamanho do arquivo e o tamanho de cada registro de cliente
        fclose(arquivo); // Fecha o arquivo
    }

    return numClientes; // Retorna o número de clientes lidos
}

// Função para salvar extrato em um arquivo binário
void salvarExtrato(Transacao extratoClientes[], int numExtratos) {
    FILE *arquivo = fopen("extratos_bancarios.bin", "wb"); // Abre um arquivo binário para escrita
    if (arquivo) { // Verifica se o arquivo foi aberto com sucesso
        fwrite(extratoClientes, sizeof(Transacao), numExtratos, arquivo); // Escreve os dados de transação no arquivo
        fclose(arquivo); // Fecha o arquivo
    } else {
        printf("Erro ao abrir o arquivo de extratos para gravação.\n"); // Imprime uma mensagem de erro caso o arquivo não possa ser aberto
    }
}

// Função para carregar extrato de um arquivo binário separado
int carregarExtrato(Transacao extratoClientes[]) {
    FILE *arquivo = fopen("extratos_bancarios.bin", "rb"); // Abre um arquivo binário para leitura
    int numExtratos = 0; // Inicializa o número de transações como 0

    if (arquivo) { // Verifica se o arquivo foi aberto com sucesso
        fread(extratoClientes, sizeof(Transacao), 1000, arquivo); // Lê os dados de transação do arquivo
        fseek(arquivo, 0, SEEK_END); // Move o cursor para o fim do arquivo
        numExtratos = ftell(arquivo) / sizeof(Transacao); // Calcula o número de transações com base no tamanho do arquivo e o tamanho de cada registro de transação
        fclose(arquivo); // Fecha o arquivo
    }

    return numExtratos; // Retorna o número de transações lidas
}

// Função para criar um cliente
void criarNCliente(Cliente clientes[], int *numClientes) {
    if (*numClientes < 1000) { // Verifica se o número de clientes é menor que 1000
        Cliente novoCliente; // Cria uma nova instância de Cliente
        printf("Nome: "); // Solicita o nome do cliente
        scanf("%s", novoCliente.nome); // Lê o nome do cliente
        printf("CPF: "); // Solicita o CPF do cliente
        scanf("%s", novoCliente.cpf); // Lê o CPF do cliente
        printf("Tipo de conta (1 para comum, 2 para plus): "); // Solicita o tipo de conta
        scanf("%d", &novoCliente.tipo_conta); // Lê o tipo de conta
        printf("Valor inicial da conta: "); // Solicita o valor inicial da conta
        scanf("%f", &novoCliente.saldo); // Lê o valor inicial da conta
        printf("Senha do usuário: "); // Solicita a senha do usuário
        scanf("%s", novoCliente.senha); // Lê a senha do usuário

        clientes[(*numClientes)] = novoCliente; // Adiciona o novo cliente ao array de clientes
        (*numClientes)++; // Incrementa o número de clientes

        FILE *arquivo = fopen("dados_bancarios.bin", "wb"); // Abre um arquivo binário para escrita
        if (arquivo) { // Verifica se o arquivo foi aberto com sucesso
            fwrite(clientes, sizeof(Cliente), *numClientes, arquivo); // Escreve os dados dos clientes no arquivo
            fclose(arquivo); // Fecha o arquivo
        } else {
            printf("Erro ao abrir o arquivo para gravação.\n"); // Imprime uma mensagem de erro caso o arquivo não possa ser aberto
        }

        printf("Novo cliente criado com sucesso.\n"); // Informa que o novo cliente foi criado com sucesso
    } else {
        printf("Limite de clientes atingido. Não é possível adicionar mais clientes.\n"); // Informa que o limite de clientes foi atingido
    }
}

// Função para apagar um cliente pelo CPF
void apagarCliente(Cliente clientes[], int *numClientes) {
    char cpfParaApagar[12]; // Declara uma variável para armazenar o CPF a ser apagado
    printf("Digite o CPF do cliente que deseja apagar: "); // Solicita o CPF do cliente a ser apagado
    scanf("%s", cpfParaApagar); // Lê o CPF do cliente a ser apagado

    int clienteEncontrado = -1; // Inicializa o índice do cliente como -1

    for (int i = 0; i < *numClientes; i++) { // Percorre todos os clientes
        if (strcmp(clientes[i].cpf, cpfParaApagar) == 0) { // Verifica se o CPF do cliente atual é igual ao CPF fornecido
            clienteEncontrado = i; // Atualiza o índice do cliente encontrado
            break; // Sai do loop
        }
    }

    if (clienteEncontrado != -1) { // Verifica se o cliente foi encontrado
        for (int i = clienteEncontrado; i < *numClientes - 1; i++) { // Move os clientes uma posição para trás a partir do cliente encontrado
            clientes[i] = clientes[i + 1];
        }

        (*numClientes)--; // Decrementa o número de clientes

        FILE *arquivo = fopen("dados_bancarios.bin", "wb"); // Abre um arquivo binário para escrita
        if (arquivo) { // Verifica se o arquivo foi aberto com sucesso
            fwrite(clientes, sizeof(Cliente), *numClientes, arquivo); // Escreve os dados dos clientes no arquivo
            fclose(arquivo); // Fecha o arquivo
        } else {
            printf("Erro ao abrir o arquivo para gravação.\n"); // Imprime uma mensagem de erro caso o arquivo não possa ser aberto
        }

        printf("Cliente apagado com sucesso.\n"); // Informa que o cliente foi apagado com sucesso
    } else {
        printf("Cliente com o CPF %s não encontrado.\n", cpfParaApagar); // Informa que o cliente com o CPF fornecido não foi encontrado
    }
}

// Função para listar todos os clientes
void listarClientes(Cliente clientes[], int numClientes) {
    if (numClientes == 0) { // Verifica se não há clientes cadastrados
        printf("Nenhum cliente cadastrado.\n"); // Informa que não há clientes cadastrados
    } else {
        printf("Lista de clientes:\n"); // Informa que uma lista de clientes será exibida
        for (int i = 0; i < numClientes; i++) { // Percorre todos os clientes
            printf("Cliente %d:\n", i + 1); // Informa o número do cliente
            printf("Nome: %s\n", clientes[i].nome); // Exibe o nome do cliente
            printf("CPF: %s\n", clientes[i].cpf); // Exibe o CPF do cliente
            if (clientes[i].tipo_conta == 1) { // Verifica se o tipo de conta é 1 (comum)
                printf("Tipo de conta: Comum\n"); // Informa que o tipo de conta é comum
            } else if (clientes[i].tipo_conta == 2) { // Verifica se o tipo de conta é 2 (plus)
                printf("Tipo de conta: Plus\n"); // Informa que o tipo de conta é plus
            }
            printf("Saldo: %.2lf\n", clientes[i].saldo); // Exibe o saldo do cliente
            printf("\n");
        }
    }
}

// Função para realizar um débito na conta do cliente
void debito(Cliente clientes[], int numClientes) {
    char cpfCliente[12];
    char senhaCliente[20];
    double valorDebito;

    // Solicita ao usuário que digite o CPF, a senha e o valor a ser debitado
    printf("Digite o CPF: ");
    scanf("%s", cpfCliente);
    printf("Digite a senha: ");
    scanf("%s", senhaCliente);
    printf("Digite o valor a ser debitado: ");
    scanf("%lf", &valorDebito);

    // Inicializa a variável clienteEncontrado com -1 para verificar se o cliente existe
    int clienteEncontrado = -1;

    // Procura o cliente pelo CPF e senha no array de clientes
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfCliente) == 0 && strcmp(clientes[i].senha, senhaCliente) == 0) {
            clienteEncontrado = i;
            break;
        }
    }

    // Verifica se o cliente foi encontrado
    if (clienteEncontrado != -1) {
        // Verifica o tipo de conta e se o saldo é suficiente para o débito
        if (clientes[clienteEncontrado].tipo_conta == 1) {
            if (clientes[clienteEncontrado].saldo - valorDebito >= -1000) {
                // Calcula as taxas e atualiza o saldo e o extrato do cliente
                valorDebito = valorDebito + valorDebito * 0.05;
                clientes[clienteEncontrado].saldo -= valorDebito;
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].tipo = 'D';
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].valor = valorDebito;
                clientes[clienteEncontrado].numTransacoes++;
                printf("Débito de %.2lf realizado com sucesso.\n", valorDebito);
            } else {
                // Mensagem de erro se o saldo não for suficiente
                printf("Limite de saldo negativo excedido para este tipo de conta.\n");
            }
        } else if (clientes[clienteEncontrado].tipo_conta == 2) {
            if (clientes[clienteEncontrado].saldo - valorDebito >= -5000) {
                // Calcula as taxas e atualiza o saldo e o extrato do cliente
                valorDebito = valorDebito + valorDebito * 0.03;
                clientes[clienteEncontrado].saldo -= valorDebito;
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].tipo = 'D';
                clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].valor = valorDebito;
                clientes[clienteEncontrado].numTransacoes++;
                printf("Débito de %.2lf realizado com sucesso.\n", valorDebito);
            } else {
                // Mensagem de erro se o saldo não for suficiente
                printf("Limite de saldo negativo excedido para este tipo de conta.\n");
            }
        }
        // Atualize o arquivo binário após realizar o débito
        FILE *arquivo = fopen("dados_bancarios.bin", "wb");
        if (arquivo) {
            fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
            fclose(arquivo);
        } else {
            // Mensagem de erro se não for possível abrir o arquivo
            printf("Erro ao abrir o arquivo para gravação.\n");
        }
    } else {
        // Mensagem de erro se o cliente não for encontrado
        printf("CPF ou senha incorretos. Não é possível realizar o débito.\n");
    }
}

// Função para realizar um depósito na conta do cliente
void deposito(Cliente clientes[], int numClientes) {
    char cpfCliente[12];
    double valorDeposito;

    // Solicita ao usuário que digite o CPF e o valor a ser depositado
    printf("Digite o CPF: ");
    scanf("%s", cpfCliente);
    printf("Digite o valor a ser depositado: ");
    scanf("%lf", &valorDeposito);

    // Inicializa a variável clienteEncontrado com -1 para verificar se o cliente existe
    int clienteEncontrado = -1;

    // Procura o cliente pelo CPF no array de clientes
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfCliente) == 0) {
            clienteEncontrado = i;
            break;
        }
    }

    // Verifica se o cliente foi encontrado
    if (clienteEncontrado != -1) {
        // Atualiza o saldo e o extrato do cliente
        clientes[clienteEncontrado].saldo += valorDeposito;
        clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].tipo = 'C';
        clientes[clienteEncontrado].extrato[clientes[clienteEncontrado].numTransacoes].valor = valorDeposito;
        clientes[clienteEncontrado].numTransacoes++;

        // Atualize o arquivo binário após realizar o depósito
        FILE *arquivo = fopen("dados_bancarios.bin", "wb");
        if (arquivo) {
            fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
            fclose(arquivo);
        } else {
            // Mensagem de erro se não for possível abrir o arquivo
            printf("Erro ao abrir o arquivo para gravação.\n");
        }

        printf("Depósito de %.2lf realizado com sucesso.\n", valorDeposito);
    } else {
        // Mensagem de erro se o cliente não for encontrado
        printf("Cliente com o CPF %s não encontrado.\n", cpfCliente);
    }
}

// Função para gerar um extrato
void extrato(Cliente clientes[], int numClientes) {
    char cpfCliente[12];
    char senhaCliente[20];

    // Solicita ao usuário que digite o CPF e a senha
    printf("Digite o CPF: ");
    scanf("%s", cpfCliente);
    printf("Digite a senha: ");
    scanf("%s", senhaCliente);

    // Inicializa a variável clienteEncontrado com -1 para verificar se o cliente existe
    int clienteEncontrado = -1;

    // Procura o cliente pelo CPF e senha no array de clientes
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfCliente) == 0 && strcmp(clientes[i].senha, senhaCliente) == 0) {
            clienteEncontrado = i;
            break;
        }
    }

    // Verifica se o cliente foi encontrado
    if (clienteEncontrado != -1) {
        // Imprime o extrato do cliente
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
        // Mensagem de erro se o cliente não for encontrado
        printf("CPF ou senha incorretos. Não é possível gerar o extrato.\n");
    }
}

// Função para realizar uma transferência entre contas
void transferencia(Cliente clientes[], int numClientes) {
    char cpfOrigem[12];
    char senhaOrigem[40];
    char cpfDestino[12];
    float valorTransferencia;

    // Solicita ao usuário que digite os dados da transferência
    printf("Digite o CPF da conta de origem: ");
    scanf("%s", cpfOrigem);
    printf("Digite a senha da conta de origem: ");
    scanf("%s", senhaOrigem);
    printf("Digite o CPF da conta de destino: ");
    scanf("%s", cpfDestino);
    printf("Digite o valor a ser transferido: ");
    scanf("%f", &valorTransferencia);

    // Inicializa as variáveis clienteOrigem e clienteDestino com -1 para verificar se os clientes existem
    int clienteOrigem = -1;
    int clienteDestino = -1;

    // Procura os clientes de origem e destino pelo CPF no array de clientes
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfOrigem) == 0 && strcmp(clientes[i].senha, senhaOrigem) == 0) {
            clienteOrigem = i;
        }
        if (strcmp(clientes[i].cpf, cpfDestino) == 0) {
            clienteDestino = i;
        }
    }

    // Verifica se os clientes de origem e destino foram encontrados
    if (clienteOrigem != -1 && clienteDestino != -1) {
        // Verifica o tipo de conta e se o saldo é suficiente para a transferência
        if (clientes[clienteOrigem].tipo_conta == 1) {
            if (clientes[clienteOrigem].saldo - valorTransferencia >= -1000) {
                // Atualiza os saldos e os extratos dos clientes de origem e destino
                clientes[clienteOrigem].saldo -= valorTransferencia;
                clientes[clienteDestino].saldo += valorTransferencia;
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].tipo = 'P';
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].valor = valorTransferencia;
                clientes[clienteOrigem].numTransacoes++;
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].tipo = 'R';
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].valor = valorTransferencia;
                clientes[clienteDestino].numTransacoes++;
                printf("Transferência de %.2f realizada com sucesso.\n", valorTransferencia);

                // Atualize o arquivo binário após a transferência
                FILE *arquivo = fopen("dados_bancarios.bin", "wb");
                if (arquivo) {
                    fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
                    fclose(arquivo);
                } else {
                    // Mensagem de erro se não for possível abrir o arquivo
                    printf("Erro ao abrir o arquivo para gravação.\n");
                }
            } else {
                // Mensagem de erro se o saldo não for suficiente
                printf("Limite de saldo negativo excedido para a conta de origem.\n");
            }
        } else if (clientes[clienteOrigem].tipo_conta == 2) {
            if (clientes[clienteOrigem].saldo - valorTransferencia >= -5000) {
                // Atualiza os saldos e os extratos dos clientes de origem e destino
                clientes[clienteOrigem].saldo -= valorTransferencia;
                clientes[clienteDestino].saldo += valorTransferencia;
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].tipo = 'P'; //Tipo "P" para reconhecer como "pago" no historico de transaçoes, dando a dizer que "perdeu" esse dinheiro.
                clientes[clienteOrigem].extrato[clientes[clienteOrigem].numTransacoes].valor = valorTransferencia;
                clientes[clienteOrigem].numTransacoes++;
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].tipo = 'R'; //Tipo "R" para reconhecer como "recebido" no historico de transaçoes, dando a dizer que "recebeu" esse dinheiro.
                clientes[clienteDestino].extrato[clientes[clienteDestino].numTransacoes].valor = valorTransferencia;
                clientes[clienteDestino].numTransacoes++;
                printf("Transferência de %.2f realizada com sucesso.\n", valorTransferencia);

                // Atualize o arquivo binário após a transferência
                FILE *arquivo = fopen("dados_bancarios.bin", "wb");
                if (arquivo) {
                    fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
                    fclose(arquivo);
                } else {
                    // Mensagem de erro se não for possível abrir o arquivo
                    printf("Erro ao abrir o arquivo para gravação.\n");
                }
            } else {
                // Mensagem de erro se o saldo não for suficiente
                printf("Limite de saldo negativo excedido para a conta de origem.\n");
            }
        }
    } else {
        // Mensagem de erro se os clientes de origem e destino não forem encontrados
        printf("Conta de origem, conta de destino ou senha incorretos. Não é possível realizar a transferência.\n");
    }
}
