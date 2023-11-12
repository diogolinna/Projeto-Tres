#include <stdio.h>
#include "lab.h"

int main() {
    FILE *arquivo;
    arquivo = fopen("tarefas.dat", "ab+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de tarefas");
        return 1;
    }

    int opcao;

    do {
        printf("Menu:\n");
        printf("1. Cadastrar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Deletar Tarefa\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTarefa(arquivo);
                break;
            case 2:
                listarTarefas(arquivo);
                break;
            case 3:
                deletarTarefa(arquivo);
                break;
            case 4:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    fclose(arquivo);

    return 0;
}
