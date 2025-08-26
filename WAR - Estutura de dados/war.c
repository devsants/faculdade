#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

// Estrutura para armazenar informações dos territórios
struct Territorio {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
};

// Protótipos das funções
void clearBuffer();
void cadastrarTerritorio(struct Territorio *territorio, int index);
void listarTerritorios(struct Territorio *territorios, int quantidade);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void liberarMemoria(struct Territorio *mapa);
void exibirMenu();
int validarAtaque(struct Territorio *atacante, struct Territorio *defensor);

// Função para fazer a limpeza do buffer de entrada
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar um território
void cadastrarTerritorio(struct Territorio *territorio, int index) {
    printf("\nCadastro de Território %d:\n", index + 1);
    
    printf("Nome do Território: ");
    fgets(territorio->nome, MAX_NOME, stdin);
    territorio->nome[strcspn(territorio->nome, "\n")] = '\0';

    printf("Cor do Território: ");
    fgets(territorio->cor, MAX_COR, stdin);
    territorio->cor[strcspn(territorio->cor, "\n")] = '\0';

    printf("Número de Tropas: ");
    scanf("%d", &territorio->tropas);
    clearBuffer();

    printf("Território cadastrado com sucesso!\n");
}

// Função para listar todos os territórios
void listarTerritorios(struct Territorio *territorios, int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum território cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE TERRITÓRIOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }
}

// Função para validar se um ataque é possível
int validarAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Não é possível atacar um território da mesma cor!\n");
        return 0;
    }
    
    if (atacante->tropas <= 1) {
        printf("Erro: O território atacante precisa de pelo menos 2 tropas para atacar!\n");
        return 0;
    }
    
    return 1;
}

// Função para simular um ataque entre territórios
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    printf("\n=== SIMULAÇÃO DE ATAQUE ===\n");
    printf("%s (%s) ataca %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    
    // Validar se o ataque é possível
    if (!validarAtaque(atacante, defensor)) {
        return;
    }
    
    // Simular dados de batalha (1-6 para cada lado)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("O atacante venceu a batalha!\n");
        
        // Transferir metade das tropas do defensor para o atacante
        int tropasConquistadas = defensor->tropas / 2;
        atacante->tropas += tropasConquistadas;
        defensor->tropas -= tropasConquistadas;
        
        // Mudar a cor do território conquistado
        strcpy(defensor->cor, atacante->cor);
        
        printf("O território %s foi conquistado pela cor %s!\n", defensor->nome, atacante->cor);
        printf("%d tropas foram transferidas para o atacante.\n", tropasConquistadas);
        
    } else {
        // Defensor vence
        printf("O defensor venceu a batalha!\n");
        
        // Atacante perde uma tropa
        atacante->tropas--;
        printf("O atacante perdeu 1 tropa.\n");
    }
    
    printf("\nSituação após a batalha:\n");
    printf("Atacante %s: %d tropas\n", atacante->nome, atacante->tropas);
    printf("Defensor %s: %d tropas (%s)\n", defensor->nome, defensor->tropas, defensor->cor);
}

// Função para liberar memória alocada
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
    printf("Memória liberada com sucesso!\n");
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n====================\n");
    printf("     JOGO WAR\n");
    printf("====================\n");
    printf("1 - Cadastrar Território\n");
    printf("2 - Listar Territórios\n");
    printf("3 - Realizar Ataque\n");
    printf("0 - Sair\n");
    printf("====================\n");
    printf("Escolha uma opção: ");
}

int main() {
    int totalTerritorios;
    struct Territorio *territorios;
    int territoriosCadastrados = 0;
    int option;
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Solicitar o número total de territórios
    printf("=== SISTEMA DE GERENCIAMENTO DE TERRITÓRIOS ===\n");
    printf("Digite o número total de territórios: ");
    scanf("%d", &totalTerritorios);
    clearBuffer();
    
    // Alocar memória dinamicamente para os territórios
    territorios = (struct Territorio *)malloc(totalTerritorios * sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("Erro: Não foi possível alocar memória!\n");
        return 1;
    }
    
    do {
        exibirMenu();
        scanf("%d", &option);
        clearBuffer();
        
        switch(option) {
            case 1:
                if (territoriosCadastrados >= totalTerritorios) {
                    printf("Limite máximo de territórios atingido (%d territórios).\n", totalTerritorios);
                    break;
                }
                
                cadastrarTerritorio(&territorios[territoriosCadastrados], territoriosCadastrados);
                territoriosCadastrados++;
                break;
                
            case 2:
                listarTerritorios(territorios, territoriosCadastrados);
                break;
                
            case 3:
                if (territoriosCadastrados < 2) {
                    printf("É necessário cadastrar pelo menos 2 territórios para realizar um ataque.\n");
                    break;
                }
                
                int indexAtacante, indexDefensor;
                
                listarTerritorios(territorios, territoriosCadastrados);
                
                printf("\nSelecione o território ATACANTE (1 a %d): ", territoriosCadastrados);
                scanf("%d", &indexAtacante);
                clearBuffer();
                
                printf("Selecione o território DEFENSOR (1 a %d): ", territoriosCadastrados);
                scanf("%d", &indexDefensor);
                clearBuffer();
                
                // Ajustar índices para base 0
                indexAtacante--;
                indexDefensor--;
                
                if (indexAtacante < 0 || indexAtacante >= territoriosCadastrados ||
                    indexDefensor < 0 || indexDefensor >= territoriosCadastrados) {
                    printf("Índices inválidos!\n");
                    break;
                }
                
                if (indexAtacante == indexDefensor) {
                    printf("Não é possível atacar o próprio território!\n");
                    break;
                }
                
                // Realizar o ataque
                atacar(&territorios[indexAtacante], &territorios[indexDefensor]);
                break;
                
            case 0:
                printf("Saindo do programa...\n");
                break;
                
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        
    } while (option != 0);
    
    // Liberar memória alocada
    liberarMemoria(territorios);
    
    return 0;
}