#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definição das Estruturas ---

// Definição da estrutura de uma Peça
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;   // Identificador único da peça
} Peca;

// Constantes para os tamanhos máximos
#define TAMANHO_MAXIMO_FILA 5
#define TAMANHO_MAXIMO_PILHA 3

// Estrutura para a Fila Circular de Peças Futuras
typedef struct {
    Peca pecas[TAMANHO_MAXIMO_FILA];
    int frente; // Índice do primeiro elemento (próxima peça a ser jogada/reservada)
    int tras;   // Índice do último elemento + 1 (próximo local de inserção)
    int contador; // Número atual de elementos na fila
    int proximo_id_disponivel; // Contador global para gerar IDs únicos
} FilaPecas;

// Estrutura para a Pilha de Reserva
typedef struct {
    Peca pecas[TAMANHO_MAXIMO_PILHA];
    int topo; // Índice do topo da pilha
} PilhaReserva;


// --- Protótipos das Funções ---

// Funções de Inicialização e Geração
void inicializarFila(FilaPecas *fila);
void inicializarPilha(PilhaReserva *pilha);
Peca gerarPeca(FilaPecas *fila);

// Funções da Fila
int filaCheia(FilaPecas *fila);
int filaVazia(FilaPecas *fila);
int enqueue(FilaPecas *fila, Peca novaPeca); 
Peca dequeue(FilaPecas *fila);

// Funções da Pilha
int pilhaCheia(PilhaReserva *pilha);
int pilhaVazia(PilhaReserva *pilha);
int push(PilhaReserva *pilha, Peca peca);
Peca pop(PilhaReserva *pilha);

// Funções de Ação do Jogo
void jogarPeca(FilaPecas *fila);
void reservarPeca(FilaPecas *fila, PilhaReserva *pilha);
void usarPecaReservada(PilhaReserva *pilha);
// NOVAS FUNÇÕES:
void trocarPecaAtual(FilaPecas *fila, PilhaReserva *pilha);
void trocaMultipla(FilaPecas *fila, PilhaReserva *pilha);

// Funções de Exibição
void exibirFila(FilaPecas *fila);
void exibirPilha(PilhaReserva *pilha);
void exibirEstadoAtual(FilaPecas *fila, PilhaReserva *pilha);
void exibirMenu(FilaPecas *fila, PilhaReserva *pilha);


// --- Implementação das Funções de Inicialização e Geração ---

/**
 * @brief Inicializa a fila de peças, preenchendo-a com o número fixo inicial.
 * @param fila Ponteiro para a estrutura FilaPecas.
 */
void inicializarFila(FilaPecas *fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->contador = 0;
    fila->proximo_id_disponivel = 0;

    // Inicializa a fila com o número fixo de elementos (5)
    for (int i = 0; i < TAMANHO_MAXIMO_FILA; i++) {
        Peca nova = gerarPeca(fila);
        // Enqueue inicial (sem checagem de "cheia")
        fila->pecas[fila->tras] = nova;
        fila->tras = (fila->tras + 1) % TAMANHO_MAXIMO_FILA;
        fila->contador++;
    }

    printf("✅ Fila inicializada com sucesso (%d peças).\n", TAMANHO_MAXIMO_FILA);
}

/**
 * @brief Inicializa a pilha de reserva.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void inicializarPilha(PilhaReserva *pilha) {
    // Inicializa o topo para -1, indicando que a pilha está vazia
    pilha->topo = -1;
    printf("✅ Pilha de reserva inicializada com sucesso (%d de capacidade).\n", TAMANHO_MAXIMO_PILHA);
}

/**
 * @brief Gera uma nova peça com um tipo aleatório e um ID único.
 * @param fila Ponteiro para a estrutura FilaPecas (usado para o ID).
 * @return A nova peça gerada.
 */
Peca gerarPeca(FilaPecas *fila) {
    Peca novaPeca;
    
    // Lista dos tipos de peças
    char tipos[] = {'I', 'O', 'T', 'L'};
    int numTipos = sizeof(tipos) / sizeof(tipos[0]);
    
    // Gera um índice aleatório para selecionar o tipo da peça
    int indiceAleatorio = rand() % numTipos;
    
    // Atribui o tipo e o ID único
    novaPeca.nome = tipos[indiceAleatorio];
    // Atribui e incrementa o ID global
    novaPeca.id = fila->proximo_id_disponivel++; 
    
    return novaPeca;
}


// --- Implementação das Funções da Fila ---

int filaCheia(FilaPecas *fila) {
    return fila->contador == TAMANHO_MAXIMO_FILA;
}

int filaVazia(FilaPecas *fila) {
    return fila->contador == 0;
}

/**
 * @brief Insere uma peça no final da fila (enqueue).
 * @param fila Ponteiro para a estrutura FilaPecas.
 * @param novaPeca A peça a ser inserida.
 * @return 1 se a inserção foi bem-sucedida, 0 se a fila estiver cheia.
 */
int enqueue(FilaPecas *fila, Peca novaPeca) {
    if (filaCheia(fila)) {
        return 0; 
    }
    
    // Insere a nova peça na posição 'tras'
    fila->pecas[fila->tras] = novaPeca;
    
    // Atualiza a posição 'tras' (avança para o próximo espaço, de forma circular)
    fila->tras = (fila->tras + 1) % TAMANHO_MAXIMO_FILA;
    
    // Incrementa o contador de elementos
    fila->contador++;
    
    return 1; // Inserção bem-sucedida
}

/**
 * @brief Remove a peça da frente da fila (dequeue).
 * @param fila Ponteiro para a estrutura FilaPecas.
 * @return A peça removida. Retorna uma peça com nome '\0' se a fila estiver vazia.
 */
Peca dequeue(FilaPecas *fila) {
    Peca pecaRemovida = {'\0', -1}; // Peça de erro/vazia
    
    if (filaVazia(fila)) {
        return pecaRemovida;
    }

    // Pega a peça na posição 'frente'
    pecaRemovida = fila->pecas[fila->frente];
    
    // Atualiza a posição 'frente' (avança para o próximo elemento, de forma circular)
    fila->frente = (fila->frente + 1) % TAMANHO_MAXIMO_FILA;
    
    // Decrementa o contador de elementos
    fila->contador--;

    return pecaRemovida;
}


// --- Implementação das Funções da Pilha ---

int pilhaCheia(PilhaReserva *pilha) {
    // A pilha está cheia se o topo for o último índice válido
    return pilha->topo == TAMANHO_MAXIMO_PILHA - 1;
}

int pilhaVazia(PilhaReserva *pilha) {
    // A pilha está vazia se o topo for -1
    return pilha->topo == -1;
}

/**
 * @brief Insere uma peça no topo da pilha (push).
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 * @param peca A peça a ser inserida.
 * @return 1 se a inserção foi bem-sucedida, 0 se a pilha estiver cheia.
 */
int push(PilhaReserva *pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        printf("🛑 ERRO: A reserva está cheia! Capacidade máxima: %d.\n", TAMANHO_MAXIMO_PILHA);
        return 0; // Inserção falhou
    }
    
    // Incrementa o topo e insere a peça
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
    
    printf("⬆️ RESERVA FEITA: Peça [%c %d] adicionada à reserva.\n", peca.nome, peca.id);
    return 1; // Inserção bem-sucedida
}

/**
 * @brief Remove e retorna a peça do topo da pilha (pop).
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 * @return A peça removida. Retorna uma peça com nome '\0' se a pilha estiver vazia.
 */
Peca pop(PilhaReserva *pilha) {
    Peca pecaRemovida = {'\0', -1}; // Peça de erro/vazia
    
    if (pilhaVazia(pilha)) {
        printf("🛑 ERRO: Não há peças para usar. A reserva está vazia!\n");
        return pecaRemovida; // Remoção falhou
    }

    // Pega a peça do topo
    pecaRemovida = pilha->pecas[pilha->topo];
    
    // Decrementa o topo
    pilha->topo--;

    printf("⬇️ PEÇA USADA: Peça [%c %d] removida da reserva.\n", pecaRemovida.nome, pecaRemovida.id);
    return pecaRemovida; // Remoção bem-sucedida
}


// --- Implementação das Funções de Ação do Jogo ---

/**
 * @brief Simula a ação de jogar uma peça: remove da fila e adiciona uma nova.
 * @param fila Ponteiro para a estrutura FilaPecas.
 */
void jogarPeca(FilaPecas *fila) {
    Peca pecaJogada = dequeue(fila);
    
    if (pecaJogada.id != -1) { 
        printf("▶️ PEÇA JOGADA: Peça [%c %d] removida da frente da fila.\n", pecaJogada.nome, pecaJogada.id);
        
        // *Requisito:* Adiciona uma nova peça ao final da fila.
        Peca nova = gerarPeca(fila);
        enqueue(fila, nova);
        printf("➕ NOVA PEÇA: Peça [%c %d] gerada e adicionada ao final da fila.\n", nova.nome, nova.id);
    } else {
        printf("🛑 ERRO: A fila está vazia, não há peças para jogar!\n");
    }
}

/**
 * @brief Simula a ação de reservar uma peça: move da fila para a pilha e adiciona uma nova na fila.
 * @param fila Ponteiro para a estrutura FilaPecas.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void reservarPeca(FilaPecas *fila, PilhaReserva *pilha) {
    Peca pecaReservada = {'\0', -1};
    
    if (filaVazia(fila)) {
        printf("🛑 ERRO: Não há peças na fila para reservar!\n");
        return;
    }
    
    // 1. Remove a peça da frente da fila (dequeue)
    pecaReservada = dequeue(fila);
    
    // 2. Tenta inserir a peça removida no topo da pilha (push)
    if (push(pilha, pecaReservada) == 1) { // Se o push foi bem-sucedido:
        // *Requisito:* Adiciona uma nova peça ao final da fila.
        Peca nova = gerarPeca(fila);
        enqueue(fila, nova);
        printf("➕ NOVA PEÇA: Peça [%c %d] gerada e adicionada ao final da fila (após reserva).\n", nova.nome, nova.id);
    } else {
        // Se a pilha estava cheia e o push falhou, a peça "reservada" é perdida (simplificação)
        printf("⚠️ A peça [%c %d] removida da fila foi perdida, pois a reserva estava cheia.\n", pecaReservada.nome, pecaReservada.id);
    }
}

/**
 * @brief Simula a ação de usar uma peça reservada: remove do topo da pilha.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void usarPecaReservada(PilhaReserva *pilha) {
    // A remoção e as mensagens de sucesso/erro estão dentro do `pop`.
    pop(pilha);
    // Requisito: A remoção de peças da pilha não gera nova peça na fila.
}

/**
 * @brief Troca a peça da frente da fila com a peça do topo da pilha.
 * @param fila Ponteiro para a estrutura FilaPecas.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void trocarPecaAtual(FilaPecas *fila, PilhaReserva *pilha) {
    if (filaVazia(fila) || pilhaVazia(pilha)) {
        printf("🛑 ERRO: A fila e/ou a pilha devem ter pelo menos uma peça para realizar a troca de peça atual.\n");
        return;
    }

    // Acessa a peça da frente da fila e do topo da pilha diretamente (sem dequeue/pop)
    Peca *pecaFila = &fila->pecas[fila->frente];
    Peca *pecaPilha = &pilha->pecas[pilha->topo];
    
    printf("🔄 TROCA SIMPLES: Trocando peça da fila [%c %d] com peça da pilha [%c %d].\n", 
           pecaFila->nome, pecaFila->id, pecaPilha->nome, pecaPilha->id);

    // Variável temporária para a troca
    Peca temp = *pecaFila;
    *pecaFila = *pecaPilha;
    *pecaPilha = temp;
    
    printf("✅ Troca de peça atual realizada com sucesso.\n");
}

/**
 * @brief Alterna as 3 primeiras peças da fila com as 3 peças da pilha.
 * @param fila Ponteiro para a estrutura FilaPecas.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void trocaMultipla(FilaPecas *fila, PilhaReserva *pilha) {
    int P_TROCA = 3;

    // A fila deve ter P_TROCA peças e a pilha deve estar cheia
    if (fila->contador < P_TROCA || pilha->topo + 1 < P_TROCA) {
        printf("🛑 ERRO: Ambas as estruturas devem ter %d peças para a troca múltipla (Fila: %d/%d, Pilha: %d/%d).\n", 
               P_TROCA, fila->contador, TAMANHO_MAXIMO_FILA, pilha->topo + 1, TAMANHO_MAXIMO_PILHA);
        return;
    }
    
    printf("🔄 TROCA MÚLTIPLA: Trocando os %d primeiros da fila com os %d da pilha.\n", P_TROCA, P_TROCA);
    
    // Troca os elementos um por um
    for (int i = 0; i < P_TROCA; i++) {
        // Posição da peça na fila (a partir da frente, de forma circular)
        int idxFila = (fila->frente + i) % TAMANHO_MAXIMO_FILA; 
        // Posição da peça na pilha (do topo para a base)
        int idxPilha = pilha->topo - i; 

        // Troca
        Peca temp = fila->pecas[idxFila];
        fila->pecas[idxFila] = pilha->pecas[idxPilha];
        pilha->pecas[idxPilha] = temp;
    }
    
    printf("✅ Troca múltipla realizada com sucesso.\n");
}


// --- Implementação das Funções de Exibição e Menu ---

/**
 * @brief Exibe o estado atual da fila de forma clara.
 * @param fila Ponteiro para a estrutura FilaPecas.
 */
void exibirFila(FilaPecas *fila) {
    if (filaVazia(fila)) {
        printf("Fila de peças (Frente -> Trás): VAZIA (0/%d)\n", TAMANHO_MAXIMO_FILA);
        return;
    }

    printf("Fila de peças (Frente -> Trás): ");
    
    int i = fila->frente;
    int count = 0;
    
    // Percorre a fila a partir do índice 'frente' até 'contador' elementos
    while (count < fila->contador) {
        // Adiciona um separador visual para a primeira peça (FRENTE)
        if (count == 0) printf("[FRENTE] ");
        
        printf("[%c %d]", fila->pecas[i].nome, fila->pecas[i].id);
        
        if (count < fila->contador - 1) {
            printf(" -> ");
        }
        
        // Avança o índice de forma circular
        i = (i + 1) % TAMANHO_MAXIMO_FILA;
        count++;
    }
    printf(" (Total: %d/%d)\n", fila->contador, TAMANHO_MAXIMO_FILA);
}

/**
 * @brief Exibe o estado atual da pilha de forma clara.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void exibirPilha(PilhaReserva *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha de reserva (Topo -> Base): VAZIA (0/%d)\n", TAMANHO_MAXIMO_PILHA);
        return;
    }

    printf("Pilha de reserva (Topo -> Base): ");
    
    // Percorre a pilha do topo para a base
    for (int i = pilha->topo; i >= 0; i--) {
        // Adiciona um separador visual para a peça do topo
        if (i == pilha->topo) printf("[TOPO] ");
        
        printf("[%c %d]", pilha->pecas[i].nome, pilha->pecas[i].id);
        
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf(" (Total: %d/%d)\n", pilha->topo + 1, TAMANHO_MAXIMO_PILHA);
}

/**
 * @brief Exibe o estado atual (fila e pilha).
 * @param fila Ponteiro para a estrutura FilaPecas.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void exibirEstadoAtual(FilaPecas *fila, PilhaReserva *pilha) {
    printf("\n=======================================================\n");
    printf("🚀 Estado Atual do Gerenciador de Peças\n");
    printf("=======================================================\n");
    exibirFila(fila);
    exibirPilha(pilha);
    printf("=======================================================\n");
}

/**
 * @brief Exibe o menu de opções e processa a escolha do usuário.
 * @param fila Ponteiro para a estrutura FilaPecas.
 * @param pilha Ponteiro para a estrutura PilhaReserva.
 */
void exibirMenu(FilaPecas *fila, PilhaReserva *pilha) {
    int opcao;
    
    do {
        // Exibe o estado antes de cada ação
        exibirEstadoAtual(fila, pilha);

        // Exibe as opções de menu (ATUALIZADO)
        printf("\n--- Opções de Ação ---\n");
        printf("Código | Ação\n");
        printf("-----------------------------------------------------------\n");
        printf(" 1     | Jogar peça (Remove da fila e gera nova)\n");
        printf(" 2     | Reservar peça (Fila -> Pilha e gera nova na fila)\n");
        printf(" 3     | Usar peça reservada (Remove da pilha)\n");
        printf(" 4     | Trocar peça atual (Frente da fila <-> Topo da pilha)\n");
        printf(" 5     | Troca Múltipla (3 primeiras da fila <-> 3 da pilha)\n");
        printf(" 0     | Sair\n");
        printf("-----------------------------------------------------------\n");
        printf("Opção: ");
        
        // Lê a opção do usuário
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de falha na leitura
            while (getchar() != '\n');
            opcao = -1; 
        } else {
            // Consome o caractere de nova linha pendente
            while (getchar() != '\n');
        }

        // Processa a opção escolhida
        switch (opcao) {
            case 1:
                jogarPeca(fila); 
                break;
            case 2:
                reservarPeca(fila, pilha); 
                break;
            case 3:
                usarPecaReservada(pilha); 
                break;
            case 4:
                trocarPecaAtual(fila, pilha);
                break;
            case 5:
                trocaMultipla(fila, pilha);
                break;
            case 0:
                printf("\n👋 Saindo do Gerenciador de Peças. Programa encerrado!\n");
                break;
            default:
                printf("\n⚠️ Opção inválida. Por favor, escolha 1, 2, 3, 4, 5 ou 0.\n");
                break;
        }

    } while (opcao != 0);
}

/**
 * @brief Função principal do programa.
 */
int main() {
    // Inicializa a semente para a função rand() para gerar tipos de peças aleatórios
    srand((unsigned int)time(NULL));
    
    FilaPecas filaDePecasFuturas;
    PilhaReserva pilhaDeReserva;
    
    printf("--- INICIALIZAÇÃO DO JOGO ---\n");
    // Inicializa as estruturas
    inicializarFila(&filaDePecasFuturas);
    inicializarPilha(&pilhaDeReserva);
    printf("-----------------------------\n");
    
    // Inicia o loop do jogo
    exibirMenu(&filaDePecasFuturas, &pilhaDeReserva);

    return 0;
}