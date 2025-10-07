#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

// Enum para definir critérios de ordenação
typedef enum {
    NENHUM = 0,
    NOME,
    TIPO,
    PRIORIDADE
} Criterio;

// Estrutura do item
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Função de ordenação (Insertion Sort)
int ordenarItens(Item mochila[], int total, Criterio criterio) {
    int comparacoes = 0;

    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            int comp = 0;
            if (criterio == NOME)
                comp = strcmp(mochila[j].nome, chave.nome);
            else if (criterio == TIPO)
                comp = strcmp(mochila[j].tipo, chave.tipo);
            else if (criterio == PRIORIDADE)
                comp = mochila[j].prioridade - chave.prioridade;

            comparacoes++;

            if (comp > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }
        mochila[j + 1] = chave;
    }

    return comparacoes;
}

// Função de busca binária (por nome)
int buscaBinaria(Item mochila[], int total, char nomeBusca[]) {
    int esquerda = 0, direita = total - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int comp = strcmp(mochila[meio].nome, nomeBusca);

        if (comp == 0)
            return meio;
        else if (comp < 0)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    bool estaOrdenada = false;
    Criterio criterioAtual = NENHUM;

    do {
        printf("\n===== CODIGO DA ILHA - NIVEL MESTRE =====\n");
        printf("1. Adicionar item\n");
        printf("2. Listar itens\n");
        printf("3. Ordenar mochila\n");
        printf("4. Buscar item (busca binaria por nome)\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (total >= MAX_ITENS) {
                    printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
                } else {
                    printf("\n--- Adicionar Item ---\n");
                    printf("Nome do item: ");
                    fgets(mochila[total].nome, TAM_NOME, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                    printf("Tipo do item: ");
                    fgets(mochila[total].tipo, TAM_TIPO, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    getchar();

                    printf("Prioridade (1 a 5): ");
                    scanf("%d", &mochila[total].prioridade);
                    getchar();

                    if (mochila[total].prioridade < 1 || mochila[total].prioridade > 5)
                        mochila[total].prioridade = 1; // valor padrão

                    total++;
                    estaOrdenada = false; // perdeu a ordenação
                    printf("Item adicionado com sucesso!\n");
                }
                break;

            case 2:
                if (total == 0) {
                    printf("\nA mochila esta vazia.\n");
                } else {
                    printf("\n--- Itens na Mochila ---\n");
                    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
                    printf("----------------------------------------------------------\n");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d %-10d\n",
                               mochila[i].nome, mochila[i].tipo,
                               mochila[i].quantidade, mochila[i].prioridade);
                    }
                }
                break;

            case 3: {
                if (total == 0) {
                    printf("\nNao ha itens para ordenar.\n");
                    break;
                }

                printf("\n--- Escolha o criterio de ordenacao ---\n");
                printf("1. Nome\n");
                printf("2. Tipo\n");
                printf("3. Prioridade\n");
                printf("Escolha: ");
                int opc;
                scanf("%d", &opc);
                getchar();

                Criterio criterioEscolhido;
                switch (opc) {
                    case 1: criterioEscolhido = NOME; break;
                    case 2: criterioEscolhido = TIPO; break;
                    case 3: criterioEscolhido = PRIORIDADE; break;
                    default:
                        printf("Opcao invalida!\n");
                        continue;
                }

                int comparacoes = ordenarItens(mochila, total, criterioEscolhido);
                estaOrdenada = (criterioEscolhido == NOME); // só é válida p/ busca binária
                criterioAtual = criterioEscolhido;

                printf("\nMochila ordenada com sucesso por ");
                if (criterioEscolhido == NOME) printf("nome!\n");
                else if (criterioEscolhido == TIPO) printf("tipo!\n");
                else printf("prioridade!\n");

                printf("Comparacoes realizadas: %d\n", comparacoes);
                break;
            }

            case 4: {
                if (total == 0) {
                    printf("\nNao ha itens na mochila para buscar.\n");
                    break;
                }
                if (!estaOrdenada) {
                    printf("\nA mochila precisa estar ordenada por nome para usar busca binaria.\n");
                    break;
                }

                char nomeBusca[TAM_NOME];
                printf("\nDigite o nome do item para buscar: ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                int pos = buscaBinaria(mochila, total, nomeBusca);

                if (pos >= 0) {
                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\n", mochila[pos].nome);
                    printf("Tipo: %s\n", mochila[pos].tipo);
                    printf("Quantidade: %d\n", mochila[pos].quantidade);
                    printf("Prioridade: %d\n", mochila[pos].prioridade);
                } else {
                    printf("\nItem '%s' nao encontrado.\n", nomeBusca);
                }
                break;
            }

            case 5:
                printf("\nSaindo do Jogo, ate a proxima!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}
