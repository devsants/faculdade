#include <stdio.h>

// Inicialização das Arrays e da Matriz de forma global para ser utilizada nas funções recursivas

int navio[3] = {3,3,3};

int tabuleiro[10][10] = {
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

// Função para a exibição do Tabuleiro utilizando Loop Aninhado
void exibirTabuleiro() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            //Verificação para ver se a coordenada está vaga.
            if(tabuleiro[i][j] == 0) {
                if(j < 9) printf("%d \t", tabuleiro[i][j]);
                else printf("%d \n", tabuleiro[i][j]);
            }

        }
    }
}


// Função main, responsável pela lógica da inserção do Navio no tabuleiro;
void main()
{
    // Inserindo os navios no tabuleiro
    for(int i; i < 3; i++) {
        tabuleiro[0][i] = navio[i];
        tabuleiro[i+3][6] = navio[i];
    }

    exibirTabuleiro();
}
