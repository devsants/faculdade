#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Definições de Estruturas ---

/**
 * @brief Estrutura que representa um cômodo da mansão (nó da Árvore Binária).
 */
typedef struct Sala {
    char nome[50];
    char pista_estatica[100]; // Pista associada a este cômodo (definida na montagem do mapa)
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/**
 * @brief Estrutura que representa uma pista coletada (nó da Árvore BST de Pistas).
 */
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// --- Tabela Hash para Suspeitos ---
#define TAMANHO_HASH 10
#define MAX_PISTAS 50

/**
 * @brief Estrutura para entrada na Tabela Hash (Pista -> Suspeito).
 */
typedef struct HashEntry {
    char pista[100];
    char suspeito[50];
    struct HashEntry *proximo; // Para lidar com colisões (encadeamento)
} HashEntry;

HashEntry *tabelaHash[TAMANHO_HASH]; // A Tabela Hash propriamente dita

// --- Protótipos de Funções ---

// Funções para o Mapa da Mansão (Árvore Binária)
Sala *criarSala(const char *nome, const char *pista);
void explorarSalas(Sala *sala_atual, PistaNode **raiz_pistas);

// Funções para a Árvore de Pistas (BST)
PistaNode *inserirPista(PistaNode *raiz, const char *pista_str);
void exibirPistas(PistaNode *raiz);

// Funções para a Tabela Hash
unsigned int hash(const char *chave);
void inserirNaHash(const char *pista, const char *suspeito);
const char *encontrarSuspeito(const char *pista);
void inicializarHash();
void liberarHash();

// Funções do Jogo/Julgamento
void verificarSuspeitoFinal(PistaNode *raiz_pistas);
int contarPistasParaSuspeito(PistaNode *raiz_pistas, const char *suspeito_acusado);

// --- Implementação das Funções ---

/**
 * @brief Inicializa a Tabela Hash com ponteiros nulos.
 */
void inicializarHash() {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabelaHash[i] = NULL;
    }
}

/**
 * @brief Função hash simples (soma dos valores ASCII dos caracteres).
 * @param chave String (pista) para a qual calcular o índice.
 * @return O índice na tabela hash.
 */
unsigned int hash(const char *chave) {
    unsigned long int valor = 0;
    int i = 0;
    while (valor < ULONG_MAX && i < 6) { // Usa os primeiros 6 caracteres para evitar loops longos
        valor = valor << 8;
        valor += chave[i];
        i++;
    }
    return valor % TAMANHO_HASH;
}

/**
 * @brief Insere a associação Pista -> Suspeito na Tabela Hash.
 * @param pista String que serve como chave (a pista coletada).
 * @param suspeito String que serve como valor (o suspeito relacionado).
 */
void inserirNaHash(const char *pista, const char *suspeito) {
    unsigned int indice = hash(pista);
    HashEntry *novoEntry = (HashEntry *)malloc(sizeof(HashEntry));
    if (novoEntry == NULL) {
        perror("Erro de alocação de memória para HashEntry");
        exit(EXIT_FAILURE);
    }
    
    strncpy(novoEntry->pista, pista, sizeof(novoEntry->pista) - 1);
    novoEntry->pista[sizeof(novoEntry->pista) - 1] = '\0';
    strncpy(novoEntry->suspeito, suspeito, sizeof(novoEntry->suspeito) - 1);
    novoEntry->suspeito[sizeof(novoEntry->suspeito) - 1] = '\0';
    novoEntry->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoEntry;
}

/**
 * @brief Consulta o suspeito correspondente a uma pista na Tabela Hash.
 * @param pista A string da pista para procurar.
 * @return O nome do suspeito associado, ou uma string vazia se não for encontrado.
 */
const char *encontrarSuspeito(const char *pista) {
    unsigned int indice = hash(pista);
    HashEntry *atual = tabelaHash[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return ""; // Suspeito não encontrado para esta pista
}

/**
 * @brief Cria, de forma dinâmica, uma sala com nome e pista estática.
 * @param nome O nome da sala.
 * @param pista A pista associada à sala (pode ser vazia "").
 * @return Um ponteiro para a nova Sala.
 */
Sala *criarSala(const char *nome, const char *pista) {
    Sala *novaSala = (Sala *)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        perror("Erro de alocação de memória para Sala");
        exit(EXIT_FAILURE);
    }
    strncpy(novaSala->nome, nome, sizeof(novaSala->nome) - 1);
    novaSala->nome[sizeof(novaSala->nome) - 1] = '\0';
    strncpy(novaSala->pista_estatica, pista, sizeof(novaSala->pista_estatica) - 1);
    novaSala->pista_estatica[sizeof(novaSala->pista_estatica) - 1] = '\0';
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/**
 * @brief Insere uma nova pista na árvore BST de pistas.
 * @param raiz A raiz da árvore BST.
 * @param pista_str A string da pista a ser inserida.
 * @return A nova raiz da árvore (ou a raiz existente se não houver inserção).
 */
PistaNode *inserirPista(PistaNode *raiz, const char *pista_str) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode *)malloc(sizeof(PistaNode));
        if (novo == NULL) {
            perror("Erro de alocação de memória para PistaNode");
            exit(EXIT_FAILURE);
        }
        strncpy(novo->pista, pista_str, sizeof(novo->pista) - 1);
        novo->pista[sizeof(novo->pista) - 1] = '\0';
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    int comparacao = strcmp(pista_str, raiz->pista);
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista_str);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, pista_str);
    }
    // Se a comparação for 0, a pista já existe, não insere.
    return raiz;
}

/**
 * @brief Imprime as pistas coletadas em ordem alfabética (travessia In-Ordem da BST).
 * @param raiz A raiz da árvore BST de pistas.
 */
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("  - %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

/**
 * @brief Navega pela árvore do mapa e ativa o sistema de pistas.
 * @param sala_atual A sala em que o jogador se encontra.
 * @param raiz_pistas Ponteiro para o ponteiro da raiz da BST de pistas.
 */
void explorarSalas(Sala *sala_atual, PistaNode **raiz_pistas) {
    char escolha;
    
    while (sala_atual != NULL) {
        printf("\nVocê está em: **%s**\n", sala_atual->nome);

        // --- Coleta de Pista ---
        if (strlen(sala_atual->pista_estatica) > 0) {
            printf("🔍 **Pista encontrada!** -> \"%s\"\n", sala_atual->pista_estatica);
            *raiz_pistas = inserirPista(*raiz_pistas, sala_atual->pista_estatica);
            printf("_(Pista adicionada ao seu Caderno de Pistas.)_\n");
            // Remove a pista estática após a coleta para evitar duplicação em caso de retorno (embora o mapa não permita)
            // Em uma implementação mais complexa, usar-se-ia um flag de "coletado".
            sala_atual->pista_estatica[0] = '\0'; 
        } else {
            printf("Nenhuma pista nova neste cômodo.\n");
        }

        // --- Verificação de Caminhos ---
        int tem_esquerda = sala_atual->esquerda != NULL;
        int tem_direita = sala_atual->direita != NULL;

        if (!tem_esquerda && !tem_direita) {
            printf("\n⛔️ **Fim do caminho!** Não há mais portas neste cômodo. A exploração termina aqui.\n");
            break; // Sai do loop (fim da exploração)
        }

        // --- Opções de Navegação ---
        printf("\nEscolha seu caminho:\n");
        if (tem_esquerda) {
            printf("  [e] Ir para a esquerda (%s)\n", sala_atual->esquerda->nome);
        }
        if (tem_direita) {
            printf("  [d] Ir para a direita (%s)\n", sala_atual->direita->nome);
        }
        printf("  [s] Sair e ir para o julgamento\n");
        printf("Sua escolha: ");
        
        if (scanf(" %c", &escolha) != 1) {
            while (getchar() != '\n'); // Limpa o buffer em caso de erro
            escolha = ' '; // Força nova tentativa ou saída
        }
        
        escolha = tolower(escolha);
        
        printf("----------------------------------------\n");

        if (escolha == 's') {
            printf("Saindo da exploração para o julgamento...\n");
            break;
        } else if (escolha == 'e' && tem_esquerda) {
            sala_atual = sala_atual->esquerda;
        } else if (escolha == 'd' && tem_direita) {
            sala_atual = sala_atual->direita;
        } else {
            printf("🚫 Escolha inválida ou caminho bloqueado. Tente novamente.\n");
        }
    }
}

/**
 * @brief Conduz à fase de julgamento final: lista pistas, solicita acusação e verifica evidências.
 * @param raiz_pistas A raiz da BST de pistas coletadas.
 */
void verificarSuspeitoFinal(PistaNode *raiz_pistas) {
    char suspeito_acusado[50];
    
    printf("\n--- FASE DE JULGAMENTO FINAL ---\n");
    
    if (raiz_pistas == NULL) {
        printf("Nenhuma pista foi coletada. O caso não pode ser resolvido.\n");
        return;
    }

    printf("Seu Caderno de Pistas Coletadas (em ordem alfabética):\n");
    exibirPistas(raiz_pistas);
    printf("----------------------------------------\n");

    printf("Com base nas suas pistas, quem você acusa?\n");
    printf("Acusar (Nome do Suspeito): ");
    scanf(" %49[^\n]", suspeito_acusado); // Lê até 49 caracteres, incluindo espaços, até a quebra de linha

    int pistas_count = contarPistasParaSuspeito(raiz_pistas, suspeito_acusado);

    printf("\n--- VEREDITO ---\n");
    printf("Suspeito Acusado: **%s**\n", suspeito_acusado);
    printf("Pistas que apontam para %s: %d\n", suspeito_acusado, pistas_count);

    if (pistas_count >= 2) {
        printf("✅ **Sucesso!** Você coletou %d pistas incriminadoras. As evidências são suficientes para sustentar a acusação e prender %s. O caso está resolvido!\n", pistas_count, suspeito_acusado);
    } else {
        printf("❌ **Fracasso!** Você só possui %d pistas que ligam o suspeito ao crime. São necessárias pelo menos duas pistas. O caso permanece aberto e o culpado fugiu.\n", pistas_count);
    }
}

/**
 * @brief Conta quantas das pistas coletadas (na BST) apontam para o suspeito acusado (via Hash).
 * @param raiz_pistas A raiz da BST de pistas coletadas.
 * @param suspeito_acusado O nome do suspeito sob acusação.
 * @return O número de pistas coletadas que apontam para esse suspeito.
 */
int contarPistasParaSuspeito(PistaNode *raiz_pistas, const char *suspeito_acusado) {
    if (raiz_pistas == NULL) {
        return 0;
    }

    int count = 0;
    
    // Processa o nó atual
    const char *suspeito_ligado = encontrarSuspeito(raiz_pistas->pista);
    if (strcmp(suspeito_ligado, suspeito_acusado) == 0) {
        count = 1;
    }

    // Processa sub-árvores recursivamente
    count += contarPistasParaSuspeito(raiz_pistas->esquerda, suspeito_acusado);
    count += contarPistasParaSuspeito(raiz_pistas->direita, suspeito_acusado);

    return count;
}

/**
 * @brief Libera a memória alocada para a BST de pistas.
 * @param raiz A raiz da BST.
 */
void liberarPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Libera a memória alocada para o Mapa (Árvore Binária).
 * @param raiz A raiz da Árvore Binária.
 */
void liberarMapa(Sala *raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Libera a memória alocada para a Tabela Hash.
 */
void liberarHash() {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashEntry *atual = tabelaHash[i];
        while (atual != NULL) {
            HashEntry *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        tabelaHash[i] = NULL;
    }
}

// --- Função Principal ---

/**
 * @brief Monta o mapa inicial da mansão (árvore) e inicia a exploração.
 */
int main() {
    // 1. Inicializa a Tabela Hash
    inicializarHash();

    // 2. Monta o Mapa da Mansão (Árvore Binária)
    // Pistas Fictícias:
    // Pista 1: "Um recibo de floricultura debaixo do tapete." -> Suspeito: "O Jardineiro"
    // Pista 2: "Um anel de formatura na Cozinha." -> Suspeito: "O Mordomo"
    // Pista 3: "Apenas uma xícara de café estava suja na Sala de Jantar." -> Suspeito: "A Governanta"
    // Pista 4: "Uma mecha de cabelo grisalho no piano." -> Suspeito: "O Pianista"
    // Pista 5: "Uma nota manuscrita com o nome 'Sr. Black' no Escritório." -> Suspeito: "O Hóspede"
    // Pista 6: "Pegadas de lama frescas na Sala de Estar." -> Suspeito: "O Jardineiro" (Pista repetida para testes de suficiência)
    
    Sala *hall = criarSala("Hall de Entrada", "Um casaco molhado pendurado na bengaleira.");
    
    hall->esquerda = criarSala("Sala de Estar", "Pegadas de lama frescas na Sala de Estar.");
    hall->direita = criarSala("Cozinha", "Um anel de formatura na Cozinha.");
    
    hall->esquerda->esquerda = criarSala("Biblioteca", "Uma página rasgada de um livro raro.");
    hall->esquerda->direita = criarSala("Sala de Jantar", "Apenas uma xícara de café estava suja na Sala de Jantar.");
    
    hall->direita->esquerda = criarSala("Escritório", "Uma nota manuscrita com o nome 'Sr. Black' no Escritório.");
    hall->direita->direita = criarSala("Jardim de Inverno", ""); // Sala Folha (sem pista)
    
    hall->esquerda->esquerda->direita = criarSala("Sala de Música", "Uma mecha de cabelo grisalho no piano.");
    // Outros cômodos folhas (sem filhos):
    hall->esquerda->direita->esquerda = criarSala("Quarto de Hóspedes", "Um lenço bordado com a letra 'M'.");
    
    // 3. Preenche a Tabela Hash Pista -> Suspeito
    inserirNaHash("Um casaco molhado pendurado na bengaleira.", "O Hóspede");
    inserirNaHash("Pegadas de lama frescas na Sala de Estar.", "O Jardineiro");
    inserirNaHash("Um anel de formatura na Cozinha.", "O Mordomo");
    inserirNaHash("Uma página rasgada de um livro raro.", "A Governanta");
    inserirNaHash("Apenas uma xícara de café estava suja na Sala de Jantar.", "A Governanta");
    inserirNaHash("Uma nota manuscrita com o nome 'Sr. Black' no Escritório.", "O Hóspede");
    inserirNaHash("Uma mecha de cabelo grisalho no piano.", "O Pianista");
    inserirNaHash("Um lenço bordado com a letra 'M'.", "O Mordomo");
    
    // 4. Inicia a Exploração
    PistaNode *raiz_pistas = NULL; // Raiz da BST de Pistas
    
    printf("--- DETECTIVE QUEST: EXPLORAÇÃO DA MANSÃO ---\n");
    printf("Bem-vindo(a) ao Hall de Entrada. Você deve explorar a mansão em busca do culpado.\n");
    printf("----------------------------------------\n");
    
    explorarSalas(hall, &raiz_pistas);

    // 5. Julgamento Final
    verificarSuspeitoFinal(raiz_pistas);

    // 6. Liberação de Memória
    liberarMapa(hall);
    liberarPistas(raiz_pistas);
    liberarHash();

    return 0;
}