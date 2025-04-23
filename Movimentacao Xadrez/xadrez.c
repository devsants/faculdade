#include <stdio.h>

// Função Recursiva para a moviemntação do Bispo com sentido fixo.
void movimentacaoBispo(int casas) {
    printf("\nMovimentação Bispo\n");
    
    // Declação de variáveis da movimentação nos eixos.
    int movH, movV;

    //Loop informando a movimentação Vertical
    for( movV = 1; movV < casas; movV++) {

        //Loop informando a movimentação horizontal
        for( movH = 1; movH < casas; movH++) {
            printf("Esquerda\n");
            break;
        }

        printf("Cima\n");
    }
}

void movimentacaoTorre(int casas) {

    //Loop informando a movimentação horizontal

    printf("\nMovimentação Torre\n");
    for(int i = 0; i < casas; i++) {
        printf("Direita\n");
    }
}

// Função Recursiva para a moviemntação da Rainha com sentido fixo.
void movimentacaoRainha(int casas) {
    printf("\nMovimentação Rainha\n");

    //Loop informando a movimentação horizontal

    for(int i = 0; i < casas; i++) {
        printf("Esquerda\n");
    }
}

// Para a moviemntação do Cavalo com sentido fixo.

void movimentacaoCavalo() {
    printf("\nMovimentação Cavalo\n");

    //Declação das variáveis
    int movH, movV;

    //Loop informando a movimentação Horizontal

    for( movH = 0; movH < 1; movH++) {
        //Loop informando a movimentação Vertical

        for( movV = 0; movV < 2; movV++) {
            printf("Cima\n");
            //Condicional para verificar a movimentação horizontal
            if(movH == 1) break;           
        }
        printf("Direita\n");

    }
}

void main() {

    //Chamando todas as funções

    movimentacaoTorre(5);
    movimentacaoBispo(3);
    movimentacaoRainha(7);
    movimentacaoCavalo();
    

}