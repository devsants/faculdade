#include <stdio.h>
#include <string.h>

void main()  {
    char estado1, estado2;
    char codigo1[5], codigo2[5];
    char nome1[50],nome2[50];
    int populacao1, populacao2;
    float area1, area2;
    float pib1, pib2;
    int numpt1, numpt2;



    //Coleta de dados
    printf("Digite o Estado da Carta 1: \n");
    scanf(" %c", &estado1);

    //Evitar buffer overflow    
    while (getchar()!='\n');
    
    printf("Digite o Código da Carta 1: \n");
    scanf(" %s", codigo1);

    //Evitar buffer overflow
    while (getchar()!='\n');
    

    printf("Digite o Nome da Carta 1: \n");
    fgets(nome1, 50, stdin);
    nome1[strcspn(nome1, "\n")] = 0;

    printf("Digite a População da Carta 1: \n");
    scanf("%d", &populacao1);

    printf("Digite a Área da Carta 1: \n");
    scanf("%f", &area1);

    printf("Digite o PIB da Carta 1: \n");
    scanf("%f", &pib1);

    printf("Digite o Número de Pontos Turísticos da Carta 1:\n");
    scanf("%i", &numpt1);

    //Exibição dados da Primeira Carta

    printf("Carta 1:\n");

    printf("Estado da Carta 1: %c \n", estado1);
    
    printf("Código da Carta 1: %s \n", codigo1);

    printf("Nome da Carta 1: %s \n", nome1);

    printf("População da Carta 1: %i milhões \n", populacao1);
    
    printf("Área da Carta 1: %0.2f km²\n", area1);
    
    printf("PIB da Carta 1: R$ %0.2f milhões\n",pib1);
    
    printf("Número de Pontos Turísticos da Carta 1: %d \n", numpt1);




    //Coleta de dados da segunda carta
    printf("Digite o Estado da Carta 2: \n");
    scanf(" %c", &estado2);

    //Evitar buffer overflow    
    while (getchar()!='\n');
    
    printf("Digite o Código da Carta 2: \n");
    scanf(" %s", codigo2);

    //Evitar buffer overflow
    while (getchar()!='\n');
    

    printf("Digite o Nome da Carta 2: \n");
    fgets(nome2, 50, stdin);
    nome2[strcspn(nome2, "\n")] = 0;

    printf("Digite a População da Carta 2: \n");
    scanf("%d", &populacao2);

    printf("Digite a Área da Carta 2: \n");
    scanf("%f", &area2);

    printf("Digite o PIB da Carta 2: \n");
    scanf("%f", &pib2);

    printf("Digite o Número de Pontos Turísticos da Carta 2:\n");
    scanf("%i", &numpt2);

    //Exibição dados da Primeira Carta

    printf("Carta 2:\n");

    printf("Estado da Carta 2: %c \n", estado2);
    
    printf("Código da Carta 2: %s \n", codigo2);

    printf("Nome da Carta 2: %s \n", nome2);

    printf("População da Carta 2: %i milhões \n", populacao2);
    
    printf("Área da Carta 2: %0.2f km²\n", area2);
    
    printf("PIB da Carta 2: R$ %0.2f milhões\n",pib2);
    
    printf("Número de Pontos Turísticos da Carta 2: %d \n ", numpt2);
    
    
}


