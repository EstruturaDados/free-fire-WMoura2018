#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

// Estrutura que representa um item da mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== CODIGO DA ILHA - NIVEL NOVATO =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                if (total >= MAX_ITENS) {
                    printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
                } else {
                    printf("\n--- Adicionar Item ---\n");
                    printf("Nome do item: ");
                    fgets(mochila[total].nome, TAM_NOME, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0'; // remove \n

                    printf("Tipo do item: ");
                    fgets(mochila[total].tipo, TAM_TIPO, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    getchar(); // limpa buffer

                    total++;
                    printf("Item adicionado com sucesso!\n");
                }
                break;

            case 2:
                if (total == 0) {
                    printf("\nNenhum item para remover.\n");
                } else {
                    char nomeRemover[TAM_NOME];
                    printf("\n--- Remover Item ---\n");
                    printf("Digite o nome do item a remover: ");
                    fgets(nomeRemover, TAM_NOME, stdin);
                    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                    int encontrado = 0;
                    for (int i = 0; i < total; i++) {
                        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                            // Move os itens seguintes uma posição para trás
                            for (int j = i; j < total - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            total--;
                            encontrado = 1;
                            printf("Item '%s' removido com sucesso!\n", nomeRemover);
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("Item nao encontrado.\n");
                    }
                }
                break;

            case 3:
                if (total == 0) {
                    printf("\nA mochila esta vazia.\n");
                } else {
                    printf("\n--- Itens na Mochila ---\n");
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                    printf("-----------------------------------------------\n");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    }
                }
                break;

            case 4:
                printf("\nSaindo do sistema... Boa sorte na ilha! 🏝️\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}
