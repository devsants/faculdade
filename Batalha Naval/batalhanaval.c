#include <stdio.h>


// Inicialização das Arrays e da Matriz de forma global para ser utilizada nas funções recursivas

int navio[3] = {3,3,3};

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
    {0,0,0,0,0,0,0,0,0,0}
};

// Função para a exibição do Tabuleiro utilizando Loop Aninhado
void exibirTabuleiro() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(j < 9) printf("%d \t", tabuleiro[i][j]);
            else printf("%d \n", tabuleiro[i][j]);

        }
    }
}

// Função que insere o navio linear já verificando se está dentro do tabuleiro e se a casa está vazia;

void inserirNavio(int linha, int coluna, int valor) {
    if(linha >= 0 && coluna >= 0 && linha <= TAMANHO && coluna <= TAMANHO) {
        if(tabuleiro[linha][coluna] == 0) {
            tabuleiro[linha][coluna] = valor;
        }
    }    
}

// Função main, responsável pela lógica da inserção do Navio no tabuleiro;
void main()
{


    for(int i; i < 3; i++) {
        //Inserindo Navios, horizontal e vertical
        inserirNavio(i, 0, navio[i]);
        inserirNavio(8, i, navio[i]);


        //Inserindo navios na diagonal
        inserirNavio(4+i, 1+i, navio[i]);
        inserirNavio(6+i, 7+i, navio[i]);
        
    }


    //exibirTabuleiro;
    exibirTabuleiro();
}
