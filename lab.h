#ifndef LAB_H
#define LAB_H

#include <stdio.h>

// Definindo a estrutura Tarefa para representar informações sobre tarefas
struct Tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
};

// Função para encontrar o comprimento de uma string personalizada
size_t meu_strlen(const char *str);

// Função para remover a quebra de linha de uma string lida com fgets
void removerQuebraLinha(char *str);

// Criando a opção de cadastrar as tarefas
void cadastrarTarefa(FILE *arquivo);

// Criando a opção de listar as tarefas
void listarTarefas(FILE *arquivo);

// Criando a opção de deletar as tarefas
void deletarTarefa(FILE *arquivo);

#endif // LAB_H
