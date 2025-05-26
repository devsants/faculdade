#include <stdio.h>

// Inicialização das Arrays e da Matriz de forma global para ser utilizada nas funções recursivas
int navio[3] = {3, 3, 3};
#define TAMANHO 10

int tabuleiro[TAMANHO][TAMANHO] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

// Matrizes de habilidades
int cone[5][5] = {
    {0,0,1,0,0},
    {0,1,1,1,0},
    {1,1,1,1,1},
    {1,1,1,1,1},
    {1,1,1,1,1},
};

int cruz[5][5] = {
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,1,1,1,1},
    {0,0,1,0,0},
    {0,0,1,0,0}
};

int octa[5][5] = {
    {0,0,1,0,0},
    {0,1,1,1,0},
    {1,1,1,1,1},
    {0,1,1,1,0},
    {0,0,1,0,0}
};

// Função para a exibição do Tabuleiro utilizando Loop Aninhado
void exibirTabuleiro() {
    printf("   ");
    for(int j = 0; j < TAMANHO; j++) {
        printf("%2d ", j);  // Exibe índices das colunas
    }
    printf("\n");
    
    for(int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);  // Exibe índice da linha
        for(int j = 0; j < TAMANHO; j++) {
            switch(tabuleiro[i][j]) {
                case 0: printf(" 0 "); break;  // Água
                case 3: printf(" 3 "); break;  // Navio
                case 5: printf(" 5 "); break;  // Área de habilidade
                default: printf(" ? "); break;
            }
        }
        printf("\n");
    }
}

// Função que insere o navio linear já verificando se está dentro do tabuleiro e se a casa está vazia
void inserirNavio(int linha, int coluna, int valor) {
    if(linha >= 0 && coluna >= 0 && linha < TAMANHO && coluna < TAMANHO) {
        if(tabuleiro[linha][coluna] == 0) {
            tabuleiro[linha][coluna] = valor;
        }
    }    
}

// Função genérica para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int habilidade[][5], int tamanho, int linha_origem, int coluna_origem) {
    int offset = tamanho / 2;
    
    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            int linha_tab = linha_origem - offset + i;
            int coluna_tab = coluna_origem - offset + j;
            
            // Verificar se está dentro dos limites do tabuleiro
            if(linha_tab >= 0 && linha_tab < TAMANHO && 
               coluna_tab >= 0 && coluna_tab < TAMANHO) {
                
                // Se a posição na matriz de habilidade for 1, marcar no tabuleiro
                if(habilidade[i][j] == 1) {
                    tabuleiro[linha_tab][coluna_tab] = 5;
                }
            }
        }
    }
}

// Funções específicas para cada habilidade
void inserirCone(int linha, int coluna) {
    aplicarHabilidade((int (*)[5])cone, 7, linha, coluna);
}

void inserirCruz(int linha, int coluna) {
    aplicarHabilidade(cruz, 5, linha, coluna);
}

void inserirOctaedro(int linha, int coluna) {
    aplicarHabilidade(octa, 5, linha, coluna);
}

int main() {
    // Inserindo Navios, horizontal e vertical
    for(int i = 0; i < 3; i++) {
        inserirNavio(i, 0, navio[i]);
        inserirNavio(8, i, navio[i]);
    }

    // Inserindo navios na diagonal
    for(int i = 0; i < 3; i++) {
        inserirNavio(4+i, 1+i, navio[i]);
        inserirNavio(6+i, 7+i, navio[i]);
    }

    // Aplicando habilidades especiais
    inserirCone(3, 3);
    inserirCruz(5, 5);
    inserirOctaedro(7, 2);

    // Exibindo o tabuleiro
    exibirTabuleiro();
    return 0;
}