#include <stdio.h>

void main() {

    /*
        Movimentação Cavalo;
        (2 casas à Baixo e 1 à Esquerda)
    */

    int casasH = 1, casasV = 2;

    while(casasV <= 2) {
        for(casasH = 1; casasH < 3; casasH++) {
            printf("Baixo\n");
        }
        printf("Esquerda\n");
        casasV++;
    }
    

}