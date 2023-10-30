//
// Created by gusta on 24/10/2023.
//

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 1000
#define MAX_TRANSACOES 100

typedef struct {
    char nome[100];
    char cpf[12];
    int tipo_conta; // 1 para comum, 2 para plus
    double saldo;
    char senha[20];
    struct {
        char tipo; // 'D' para débito, 'C' para crédito, 'P' para transferência enviada, 'R' para transferência recebida
        double valor;
    } extrato[MAX_TRANSACOES];
    int numTransacoes;
} Cliente;

void salvarClientes(Cliente clientes[], int numClientes);
int carregarClientes(Cliente clientes[]);
void salvarExtratoTXT(Cliente clientes[], int numClientes);
void criarNCliente(Cliente clientes[], int *numClientes);
void apagarCliente(Cliente clientes[], int *numClientes);
void listarClientes(Cliente clientes[], int numClientes);
void debito(Cliente clientes[], int numClientes, char *cpfCliente, char *senhaCliente, double valorDebito);
void deposito(Cliente clientes[], int numClientes);
void extrato(Cliente clientes[], int numClientes);
void transferencia(Cliente clientes[], int numClientes);
void verificarSaldo(Cliente clientes[], int clienteEncontrado);

#endif
