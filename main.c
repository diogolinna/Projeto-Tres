#include <stdio.h>
#include "lab.h"
int main() {
    // irformando nossas variaveis e a opção de erro do arquivo.
    FILE *arquivo;
    arquivo = fopen("tarefas.dat", "ab+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de tarefas");
        return 1;
    }

    int opcao;
// criação da parte do Menu mais estética
    do {
        printf("Menu:\n");
        printf("1. Cadastrar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Deletar Tarefa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
//Logica do Menu
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
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 4);

    fclose(arquivo);

    return 0;
}
