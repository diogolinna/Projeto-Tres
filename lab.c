#include "lab.h"

// Função para encontrar o comprimento de uma string personalizada
size_t meu_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Função para remover a quebra de linha de uma string lida com fgets
void removerQuebraLinha(char *str) {
    size_t length = customStrLen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

// Criando a opção de cadastrar as tarefas
void cadastrarTarefa(FILE *arquivo) {
    struct Tarefa novaTarefa;

    printf("Digite a prioridade da nova tarefa (entre 0 e 10): ");
    scanf("%d", &novaTarefa.prioridade);
    getchar(); // Consumir o caractere de nova linha deixado pelo scanf

    printf("Digite a descricao da nova tarefa (ate 300 caracteres): ");
    fgets(novaTarefa.descricao, sizeof(novaTarefa.descricao), stdin);
    removeNewLine(novaTarefa.descricao);

    printf("Digite a categoria da nova tarefa (ate 100 caracteres): ");
    fgets(novaTarefa.categoria, sizeof(novaTarefa.categoria), stdin);
    removeNewLine(novaTarefa.categoria);

    // Voltar para o final do arquivo antes de escrever uma nova tarefa
    fseek(arquivo, 0, SEEK_END);

    // Escrever a nova tarefa no arquivo
    fwrite(&novaTarefa, sizeof(struct Tarefa), 1, arquivo);

    // Garantir que os dados sejam gravados imediatamente
    fflush(arquivo);

    printf("Nova tarefa cadastrada com sucesso!\n");
}

// Criando a opção de listar as tarefas
void listarTarefas(FILE *arquivo) {
    struct Tarefa tarefa;

    // Abrir o arquivo no modo de leitura
    arquivo = fopen("tarefas.dat", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de tarefas");
        return;
    }

    // Voltar para o início do arquivo
    rewind(arquivo);

    printf("Lista de Tarefas:\n");

    while (fread(&tarefa, sizeof(struct Tarefa), 1, arquivo) == 1) {
        printf("Prioridade: %d\n", tarefa.prioridade);
        printf("Descricao: %s\n", tarefa.descricao);
        printf("Categoria: %s\n", tarefa.categoria);
        printf("\n");
    }

    // Fechar o arquivo após listar as tarefas
    fclose(arquivo);
}

// Criando a opção de deletar as tarefas
void deletarTarefa(FILE *arquivo) {
    int prioridade;

    printf("Digite a prioridade da tarefa que deseja deletar: ");
    scanf("%d", &prioridade);

    struct Tarefa tarefa;
    int tarefaEncontrada = 0; // Flag para indicar se a tarefa foi encontrada

    // Fechar o arquivo antes de reabri-lo para garantir que as alterações sejam reconhecidas
    fclose(arquivo);

    // Reabrir o arquivo no modo de leitura e escrita
    arquivo = fopen("tarefas.dat", "rb+");
    if (arquivo == NULL) {
        perror("Erro ao reabrir arquivo original");
        return;
    }

    // Criar um arquivo temporário para armazenar as tarefas que não serão excluídas
    FILE *temporario = fopen("temporario.dat", "wb");
    if (temporario == NULL) {
        perror("Erro ao criar arquivo temporario");
        fclose(arquivo);
        return;
    }

    // Ler as tarefas do arquivo original e copiar para o arquivo temporário, exceto a tarefa a ser deletada
    while (fread(&tarefa, sizeof(struct Tarefa), 1, arquivo) == 1) {
        if (tarefa.prioridade != prioridade) {
            fwrite(&tarefa, sizeof(struct Tarefa), 1, temporario);
        } else {
            tarefaEncontrada = 1; // Tarefa encontrada
            printf("Tarefa com prioridade %d encontrada e excluida.\n", prioridade);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    // Se a tarefa não foi encontrada, permitir que o usuário insira uma nova prioridade
    while (!tarefaEncontrada) {
        printf("Tarefa com prioridade %d nao encontrada.\n", prioridade);

        printf("Digite outra prioridade (ou digite 0 para cancelar): ");
        scanf("%d", &prioridade);

        if (prioridade == 0) {
            remove("temporario.dat"); // Remover o arquivo temporário, pois não é necessário
            return;
        }

        // Reabrir o arquivo original para a próxima iteração
        arquivo = fopen("tarefas.dat", "ab+");
        if (arquivo == NULL) {
            perror("Erro ao reabrir arquivo original");
            remove("temporario.dat"); // Remover o arquivo temporário, pois não é necessário
            return;
        }

        // Reinicializar a flag e reexecutar o loop de busca
        tarefaEncontrada = 0;
        rewind(arquivo);
        temporario = fopen("temporario.dat", "wb");
        if (temporario == NULL) {
            perror("Erro ao criar arquivo temporario");
            return;
        }
        // Ler as tarefas do arquivo original e copiar para o arquivo temporário
        while (fread(&tarefa, sizeof(struct Tarefa), 1, arquivo) == 1) {
            if (tarefa.prioridade != prioridade) {
                fwrite(&tarefa, sizeof(struct Tarefa), 1, temporario);
            } else {
                tarefaEncontrada = 1; // Tarefa encontrada
                printf("Tarefa com prioridade %d encontrada e excluida.\n", prioridade);
            }
        }

        fclose(arquivo);
        fclose(temporario);
    }

    // Substituir o arquivo original pelo arquivo temporário
    remove("tarefas.dat");
    rename("temporario.dat", "tarefas.dat");

    printf("Tarefa deletada com sucesso!\n");
}
