//
// Created by gusta on 24/10/2023.
//

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <string.h>

typedef struct {
    char tipo; // 'D' para débito, 'C' para crédito, 'P' para transferência enviada, 'R' para transferência recebida
    float valor;
    char data[11]; // campo para armazenar a data no formato dd/mm/yyyy
    char hora[6]; // campo para armazenar a hora no formato hh:mm
} Transacao;

typedef struct {
    char nome[100];
    char cpf[12];
    int tipo_conta;
    float saldo;
    char senha[20];
    Transacao extrato[100];
    int numTransacoes;
} Cliente;


void salvarClientes(Cliente clientes[], int numClientes);
int carregarClientes(Cliente clientes[]);
void salvarExtrato(Transacao extratoClientes[], int numExtratos);
int carregarExtrato(Transacao extratoClientes[]);
void criarNCliente(Cliente clientes[], int *numClientes);
void apagarCliente(Cliente clientes[], int *numClientes);
void listarClientes(Cliente clientes[], int numClientes);
void debito(Cliente clientes[], int numClientes);
void deposito(Cliente clientes[], int numClientes);
void extrato(Cliente clientes[], int numClientes);
void transferencia(Cliente clientes[], int numClientes);
void verificarSaldo(Cliente clientes[], int clienteEncontrado);

#endif
