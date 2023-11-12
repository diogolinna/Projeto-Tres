#include <stdio.h>
#include "lab.h"

// Função para encontrar o comprimento de uma string personalizada
size_t meu_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Função para remover a quebra de linha de uma string lida com fgets
void removerQuebraLinha(char *str) {
    size_t len = meu_strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
//Criando a opção de cadastrar as tarefas
void cadastrarTarefa(FILE *arquivo) {
    struct Tarefa tarefa;

    printf("Digite a prioridade da tarefa (entre 0 e 10): ");
    scanf("%d", &tarefa.prioridade);
    getchar(); // Consumir o caractere de nova linha deixado pelo scanf

    printf("Digite a descricao da tarefa (ate 300 caracteres): ");
    fgets(tarefa.descricao, sizeof(tarefa.descricao), stdin);
    removerQuebraLinha(tarefa.descricao);

    printf("Digite a categoria da tarefa (ate 100 caracteres): ");
    fgets(tarefa.categoria, sizeof(tarefa.categoria), stdin);
    removerQuebraLinha(tarefa.categoria);

    // Escrever a tarefa no arquivo
    fwrite(&tarefa, sizeof(struct Tarefa), 1, arquivo);

    printf("Tarefa cadastrada com sucesso!\n");
}
//Criando a opção de listar as tarefas
void listarTarefas(FILE *arquivo) {
    struct Tarefa tarefa;

    // Voltar para o início do arquivo
    rewind(arquivo);

    printf("Lista de Tarefas:\n");

    while (fread(&tarefa, sizeof(struct Tarefa), 1, arquivo) == 1) {
        printf("Prioridade: %d\n", tarefa.prioridade);
        printf("Descricao: %s\n", tarefa.descricao);
        printf("Categoria: %s\n", tarefa.categoria);
        printf("\n");
    }
}
//Criando a opção de deletar as tarefas
void deletarTarefa(FILE *arquivo) {
    int prioridade;

    printf("Digite a prioridade da tarefa que deseja deletar: ");
    scanf("%d", &prioridade);

    // Criar um arquivo temporário para armazenar as tarefas que não serão excluídas
    FILE *temporario = fopen("temporario.dat", "wb");
    if (temporario == NULL) {
        perror("Erro ao criar arquivo temporario");
        return;
    }

    struct Tarefa tarefa;

    // Ler as tarefas do arquivo original e copiar para o arquivo temporário, exceto a tarefa a ser deletada
    while (fread(&tarefa, sizeof(struct Tarefa), 1, arquivo) == 1) {
        if (tarefa.prioridade != prioridade) {
            fwrite(&tarefa, sizeof(struct Tarefa), 1, temporario);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    // Substituir o arquivo original pelo arquivo temporário
    remove("tarefas.dat");
    rename("temporario.dat", "tarefas.dat");

    printf("Tarefa deletada com sucesso!\n");
}
