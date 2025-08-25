#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TERRITORIOS 5

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



struct Territorios {
    char nome[30];
    char cor[10];
    int tropas;
} ;

struct Territorios territorio[MAX_TERRITORIOS];
int territoriosCadastrados = 0;
int option;


void getTerritorios() {
    printf("\nLista de Territórios:\n");
    for (int i = 0; i < territoriosCadastrados; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorio[i].nome);
        printf("Cor: %s\n", territorio[i].cor);
        printf("Tropas: %d\n", territorio[i].tropas);
        printf("--------------------\n");
    }
}

void createTerritorio() {
    if(territoriosCadastrados >= MAX_TERRITORIOS) {
        printf("Limite de territórios cadastrados atingido.\n");
        printf("Listando Territórios:.\n");
        getTerritorios();
        return;
    }

    printf("\nCadastro de Território %d:\n", territoriosCadastrados + 1);
    printf("Nome do Território: ");
    fgets(territorio[territoriosCadastrados].nome, sizeof(territorio[territoriosCadastrados].nome), stdin);
    territorio[territoriosCadastrados].nome[strcspn(territorio[territoriosCadastrados].nome, "\n")] = 0; // Remove newline

    printf("Cor do Território: ");
    fgets(territorio[territoriosCadastrados].cor, sizeof(territorio[territoriosCadastrados].cor), stdin);
    territorio[territoriosCadastrados].cor[strcspn(territorio[territoriosCadastrados].cor, "\n")] = 0; // Remove newline

    printf("Número de Tropas: ");
    scanf("%d", &territorio[territoriosCadastrados].tropas);
    clearBuffer();

    territoriosCadastrados++;
    printf("Território cadastrado com sucesso!\n");
    createTerritorio();
}

int main () {

    printf("====================\n");
    printf("\n  JOGO WAR  \n");
    printf("====================\n");
    printf("1 - Cadastrar Território\n");
    printf("2 - Listar Territórios\n");
    printf("====================\n");
    printf("Escolha uma opção: ");
    
    scanf("%d", &option);
    clearBuffer();

    do {
        switch(option) {
            case 1:
                createTerritorio();
                break;

            case 2: {}
                if (territoriosCadastrados == 0) {
                    printf("Nenhum território cadastrado.\n");
                } else {
                    getTerritorios();
                }
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        

    } while (territoriosCadastrados <= MAX_TERRITORIOS);
    return 0;
}