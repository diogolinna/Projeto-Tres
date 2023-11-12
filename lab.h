#ifndef LAB_H
#define LAB_H
// criação da nossa struct com as informações basicas para nosso projeto
struct Tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
};
// cadastrando aqui nossas funções para utilizar no lab.c
void cadastrarTarefa(FILE *arquivo);
void listarTarefas(FILE *arquivo);
void deletarTarefa(FILE *arquivo);

#endif // LAB_H
