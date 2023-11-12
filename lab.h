#ifndef LAB_H
#define LAB_H

#include <stdio.h>

// Definindo a estrutura Tarefa para representar informações sobre tarefas
struct Tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
    char estado[20]; // Adicionando o campo de estado da tarefa
};

// Função para calcular o comprimento de uma string
size_t meu_strlen(const char *str);

// Função para remover quebras de linha de uma string
void removerQuebraLinha(char *str);

// Função para cadastrar uma tarefa em um arquivo
void cadastrarTarefa(FILE *arquivo);

// Função para listar tarefas armazenadas em um arquivo
void listarTarefas(FILE *arquivo);

// Função para deletar uma tarefa de um arquivo
void deletarTarefa(FILE *arquivo);

// Função para modificar o estado de uma tarefa
void modificarEstado(FILE *arquivo);

#endif // LAB_H
