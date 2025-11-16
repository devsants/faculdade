

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 100
#define MAX_COMPONENTES 20

// ============================
//       ESTRUTURAS EXISTENTES
// ============================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ============================
//   VARIÁVEIS PARA CONTAGEM
// ============================

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ============================
//     FUNÇÕES UTILITÁRIAS
// ============================

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void cadastrarItem(Item *item) {
    printf("\nNome do Item: ");
    fgets(item->nome, sizeof(item->nome), stdin);
    item->nome[strcspn(item->nome, "\n")] = '\0';

    printf("Tipo do Item: ");
    fgets(item->tipo, sizeof(item->tipo), stdin);
    item->tipo[strcspn(item->tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &item->quantidade);
    clearBuffer();
}

// ============================
//     CÓDIGO ORIGINAL VETOR / LISTA
// ============================

// Inserção no vetor
void inserirItemVetor(Item *vetor, int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    cadastrarItem(&vetor[*qtd]);
    (*qtd)++;

    printf("Item inserido no vetor!\n");
}

// Remoção no vetor
void removerItemVetor(Item *vetor, int *qtd, const char *nome) {
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*qtd)--;
            printf("Item removido do vetor!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

// Listar vetor
void listarItensVetor(Item *vetor, int qtd) {
    if (qtd == 0) {
        printf("Nenhum item no vetor.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("\nItem %d\nNome: %s\nTipo: %s\nQuantidade: %d\n",
               i+1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item *vetor, int qtd, const char *nome) {
    comparacoesSequencial = 0;

    for (int i = 0; i < qtd; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordenação do vetor (Bubble Sort por nome) - utilizado no menu original
void ordenarVetor(Item *vetor, int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item tmp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = tmp;
            }
        }
    }
    printf("Vetor ordenado!\n");
}

// Busca binária
int buscarBinariaVetor(Item *vetor, int qtd, const char *nome) {
    int inicio = 0, fim = qtd - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(nome, vetor[meio].nome);

        if (cmp == 0)
            return meio;

        if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ============================
//   OPERAÇÕES LISTA ENCADEADA
// ============================

// Inserção
void inserirItemLista(No **lista) {
    No *novo = (No*) malloc(sizeof(No));
    cadastrarItem(&novo->dados);
    novo->proximo = *lista;
    *lista = novo;

    printf("Item inserido na lista!\n");
}

// Remoção
void removerItemLista(No **lista, const char *nome) {
    No *atual = *lista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                *lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado na lista!\n");
}

// Listar
void listarItensLista(No *lista) {
    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (lista != NULL) {
        printf("\nNome: %s\nTipo: %s\nQuantidade: %d\n",
               lista->dados.nome,
               lista->dados.tipo,
               lista->dados.quantidade);
        lista = lista->proximo;
    }
}

// Busca sequencial na lista
No* buscarSequencialLista(No *lista, const char *nome) {
    comparacoesSequencial = 0;

    while (lista != NULL) {
        comparacoesSequencial++;
        if (strcmp(lista->dados.nome, nome) == 0)
            return lista;
        lista = lista->proximo;
    }
    return NULL;
}

// ============================
//   NOVO MÓDULO: COMPONENTES
// ============================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;

// Função para cadastrar um componente (até MAX_COMPONENTES)
void cadastrarComponente(Componente comp[], int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido (%d).\n", MAX_COMPONENTES);
        return;
    }

    printf("\nCadastro do componente %d:\n", *n + 1);
    printf("Nome (ex: chip central): ");
    fgets(comp[*n].nome, sizeof(comp[*n].nome), stdin);
    comp[*n].nome[strcspn(comp[*n].nome, "\n")] = '\0';

    printf("Tipo (ex: controle / suporte / propulsao): ");
    fgets(comp[*n].tipo, sizeof(comp[*n].tipo), stdin);
    comp[*n].tipo[strcspn(comp[*n].tipo, "\n")] = '\0';

    do {
        printf("Prioridade (1 a 10): ");
        if (scanf("%d", &comp[*n].prioridade) != 1) {
            clearBuffer();
            comp[*n].prioridade = -1;
        } else {
            clearBuffer();
        }
    } while (comp[*n].prioridade < 1 || comp[*n].prioridade > 10);

    (*n)++;
    printf("Componente cadastrado!\n");
}

// Mostrar componentes formatados
void mostrarComponentes(Componente comp[], int n) {
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    printf("\n=== COMPONENTES (%d) ===\n", n);
    printf("%-3s | %-25s | %-15s | %s\n", "N", "NOME", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d | %-25s | %-15s | %d\n", i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
}

// ============================
//   ALGORITMOS DE ORDENAÇÃO
//   Cada função recebe um ponteiro para contador de comparações
// ============================

// Bubble Sort por nome (string)
void bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i -1; j++) {
            (*comparacoes)++;
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break; // otimização simples
    }
}

// Insertion Sort por tipo (string)
void insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = arr[i];
        int j = i - 1;
        // comparar tipos
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(arr[j].tipo, key.tipo) > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// Selection Sort por prioridade (int) - menor prioridade primeiro (1..10)
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (arr[j].prioridade < arr[minIdx].prioridade) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Componente tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }
}

// ============================
//   FUNÇÃO GENERICA PARA MEDIR TEMPO
//   Recebe um ponteiro para função de ordenação com assinatura:
//     void algoritmo(Componente[], int, long*)
//   Retorna tempo em segundos (double) e escreve comparações em *comparacoes
// ============================
double medirTempo(void (*algoritmo)(Componente[], int, long*), Componente arr[], int n, long *comparacoes) {
    clock_t start = clock();
    algoritmo(arr, n, comparacoes);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// ============================
//   BUSCA BINÁRIA POR NOME
//   Retorna índice ou -1; conta comparações
// ============================
int buscaBinariaPorNome(Componente arr[], int n, const char *chave, long *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, arr[meio].nome);
        if (cmp == 0) return meio;
        if (cmp > 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ============================
//        MENU DO MÓDULO
// ============================
void menuTorre() {
    Componente comp[MAX_COMPONENTES];
    int n = 0;
    int opc;
    int ordenadoPorNome = 0; // flag que indica se o vetor está ordenado por nome

    do {
        printf("\n=== MONTAGEM: TORRE DE RESGATE ===\n");
        printf("1 - Cadastrar componente (max %d)\n", MAX_COMPONENTES);
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar (escolha algoritmo)\n");
        printf("4 - Buscar componente-chave por nome (busca binária - exige ordenação por nome)\n");
        printf("5 - Montagem final (exibe e confirma chave)\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { clearBuffer(); opc = -1; }
        clearBuffer();

        if (opc == 1) {
            cadastrarComponente(comp, &n);
            ordenadoPorNome = 0; // alteração no vetor -> perdeu ordenação
        }
        else if (opc == 2) {
            mostrarComponentes(comp, n);
        }
        else if (opc == 3) {
            if (n == 0) {
                printf("Nenhum componente para ordenar.\n");
                continue;
            }

            printf("\nEscolha algoritmo de ordenação:\n");
            printf("1 - Bubble Sort (por NOME)\n");
            printf("2 - Insertion Sort (por TIPO)\n");
            printf("3 - Selection Sort (por PRIORIDADE)\n");
            printf("0 - Cancelar\n");
            int alg = -1;
            if (scanf("%d", &alg) != 1) { clearBuffer(); alg = -1; }
            clearBuffer();

            long comparacoes = 0;
            double tempo = 0.0;
            // fazemos uma cópia para não perder original se desejar medir em paralelo
            // (aqui aplicamos direto no vetor para refletir no estado)
            if (alg == 1) {
                // ordenar por nome (Bubble)
                tempo = medirTempo(bubbleSortNome, comp, n, &comparacoes);
                printf("Bubble Sort (nome) concluído. Comparações: %ld, Tempo: %.6f s\n", comparacoes, tempo);
                ordenadoPorNome = 1;
            } else if (alg == 2) {
                tempo = medirTempo(insertionSortTipo, comp, n, &comparacoes);
                printf("Insertion Sort (tipo) concluído. Comparações: %ld, Tempo: %.6f s\n", comparacoes, tempo);
                ordenadoPorNome = 0;
            } else if (alg == 3) {
                tempo = medirTempo(selectionSortPrioridade, comp, n, &comparacoes);
                printf("Selection Sort (prioridade) concluído. Comparações: %ld, Tempo: %.6f s\n", comparacoes, tempo);
                ordenadoPorNome = 0;
            } else {
                printf("Operação cancelada.\n");
            }
        }
        else if (opc == 4) {
            if (n == 0) {
                printf("Nenhum componente cadastrado.\n");
                continue;
            }
            if (!ordenadoPorNome) {
                printf("A busca binária exige que os componentes estejam ordenados por NOME.\n");
                printf("Deseja ordenar por nome agora com Bubble Sort? (s/n): ");
                char ans = getchar();
                clearBuffer();
                if (ans == 's' || ans == 'S') {
                    long c = 0;
                    double t = medirTempo(bubbleSortNome, comp, n, &c);
                    printf("Vetor ordenado por nome. Comparações: %ld, Tempo: %.6f s\n", c, t);
                    ordenadoPorNome = 1;
                } else {
                    printf("Busca binária cancelada. Ordene por nome primeiro.\n");
                    continue;
                }
            }

            char chave[30];
            printf("Digite o nome do componente-chave para buscar (ex: chip central): ");
            fgets(chave, sizeof(chave), stdin);
            chave[strcspn(chave, "\n")] = '\0';

            long comps = 0;
            clock_t start = clock();
            int idx = buscaBinariaPorNome(comp, n, chave, &comps);
            clock_t end = clock();
            double tempoBusca = ((double)(end - start)) / CLOCKS_PER_SEC;

            if (idx != -1) {
                printf("Componente-CHAVE encontrado no índice %d.\n", idx);
                printf("Comparações na busca binária: %ld. Tempo: %.6f s\n", comps, tempoBusca);
                printf("Dados: Nome: %s | Tipo: %s | Prioridade: %d\n", comp[idx].nome, comp[idx].tipo, comp[idx].prioridade);
            } else {
                printf("Componente não encontrado. Comparações: %ld. Tempo: %.6f s\n", comps, tempoBusca);
            }
        }
        else if (opc == 5) {
            // Montagem final: exibir componentes e confirmar presença do componente-chave
            mostrarComponentes(comp, n);
            if (n == 0) continue;
            printf("\nDeseja confirmar presença de um componente-chave? (s/n): ");
            char r = getchar(); clearBuffer();
            if (r == 's' || r == 'S') {
                char chave[30];
                printf("Digite o nome do componente-chave a confirmar: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';

                // Podemos usar busca sequencial (rápida para até 20 elementos) para confirmação
                int encontrado = 0;
                long comps = 0;
                for (int i = 0; i < n; i++) {
                    comps++;
                    if (strcmp(comp[i].nome, chave) == 0) {
                        encontrado = 1;
                        printf("Componente presente! Índice: %d | Comparações (seq): %ld\n", i, comps);
                        break;
                    }
                }
                if (!encontrado) printf("Componente-chave NÃO presente. Comparações (seq): %ld\n", comps);
            }
            printf("Montagem final exibida.\n");
        }
        else if (opc != 0) {
            printf("Opção inválida.\n");
        }

    } while (opc != 0);
}

// ============================
//            MENUS EXISTENTES
// ============================

void menuVetor(Item *vetor, int *qtd) {
    int op;
    char nomeBusca[30];

    do {
        printf("\n=== MENU VETOR ===\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("4 - Ordenar\n");
        printf("5 - Buscar Sequencial\n");
        printf("6 - Buscar Binária\n");
        printf("0 - Voltar\n");

        if (scanf("%d", &op) != 1) { clearBuffer(); op = -1; }
        clearBuffer();

        switch(op) {
            case 1:
                inserirItemVetor(vetor, qtd);
                break;

            case 2:
                printf("Nome do item a remover: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                removerItemVetor(vetor, qtd, nomeBusca);
                break;

            case 3:
                listarItensVetor(vetor, *qtd);
                break;

            case 4:
                ordenarVetor(vetor, *qtd);
                break;

            case 5:
                printf("Nome do item para busca sequencial: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                if (buscarSequencialVetor(vetor, *qtd, nomeBusca) != -1)
                    printf("Encontrado! Comparações: %d\n", comparacoesSequencial);
                else
                    printf("Não encontrado! Comparações: %d\n", comparacoesSequencial);
                break;

            case 6:
                printf("Nome do item para busca binária: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                if (buscarBinariaVetor(vetor, *qtd, nomeBusca) != -1)
                    printf("Encontrado! Comparações: %d\n", comparacoesBinaria);
                else
                    printf("Não encontrado! Comparações: %d\n", comparacoesBinaria);
                break;

            default:
                if (op != 0) printf("Opção inválida.\n");
        }

    } while (op != 0);
}

void menuLista(No **lista) {
    int op;
    char nomeBusca[30];

    do {
        printf("\n=== MENU LISTA ===\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("4 - Buscar Sequencial\n");
        printf("0 - Voltar\n");

        if (scanf("%d", &op) != 1) { clearBuffer(); op = -1; }
        clearBuffer();

        switch(op) {
            case 1:
                inserirItemLista(lista);
                break;

            case 2:
                printf("Nome do item a remover: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                removerItemLista(lista, nomeBusca);
                break;

            case 3:
                listarItensLista(*lista);
                break;

            case 4:
                printf("Nome do item para busca sequencial: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                if (buscarSequencialLista(*lista, nomeBusca) != NULL)
                    printf("Encontrado! Comparações: %d\n", comparacoesSequencial);
                else
                    printf("Não encontrado! Comparações: %d\n", comparacoesSequencial);
                break;

            default:
                if (op != 0) printf("Opção inválida.\n");
        }

    } while (op != 0);
}

// ============================
//           MAIN
// ============================
int main() {
    Item vetor[MAX_ITENS];
    int qtdVetor = 0;

    No *lista = NULL;

    int escolha;

    do {
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("1 - Mochila com Vetor\n");
        printf("2 - Mochila com Lista Encadeada\n");
        printf("3 - Montagem: Torre de Resgate (ordenacao/busca)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &escolha) != 1) { clearBuffer(); escolha = -1; }
        clearBuffer();

        if (escolha == 1)
            menuVetor(vetor, &qtdVetor);
        else if (escolha == 2)
            menuLista(&lista);
        else if (escolha == 3)
            menuTorre();
        else if (escolha != 0)
            printf("Opção inválida.\n");

    } while (escolha != 0);

    printf("Encerrando...\n");
    return 0;
}
