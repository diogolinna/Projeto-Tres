#include <stdio.h>
#include "lab.h"

int main() {
    FILE *arquivo;

    // Abre o arquivo no modo de leitura e gravação
    arquivo = fopen("tarefas.dat", "ab+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de tarefas");
        return 1;
    }

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Deletar Tarefa\n");
        printf("4. Modificar Estado da Tarefa\n");
        printf("5. Sair\n");
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
                modificarEstado(arquivo);
                break;
            case 5:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    fclose(arquivo);

    return 0;
}
