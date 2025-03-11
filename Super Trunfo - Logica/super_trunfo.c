#include <stdio.h>
#include <string.h>

void main()  {
    //Declação de variáveis da aplicação

    char estado1, estado2;
    char codigo1[5], codigo2[5];
    char nome1[50],nome2[50];
    long int populacao1, populacao2;
    float area1, area2;
    float pib1, pib2;
    int numpt1, numpt2;
    float densidade1, densidade2;
    float pibpcap1, pibpcap2;
    float superpoder1, superpoder2;

    //Declação de variáveis do menu
    int opcao;


    // ------ Carta 2 ------


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


    //Processamento de dados
    densidade1 = (float) populacao1 / area1;
    pibpcap1 = (float) pib1 / populacao1;

    superpoder1 = (float) populacao1 + area1 + pib1 + numpt1 + (densidade1 * -1);


    //Exibição dados da Primeira Carta
    // printf("Carta 1:\n");

    // printf("Estado: %c \n", estado1);
    
    // printf("Código: %s \n", codigo1);

    // printf("Nome da Cidade: %s \n", nome1);

    // printf("População: %i habitantes\n", populacao1);
    
    // printf("Área: %0.2f km²\n", area1);
    
    // printf("PIB: R$ %0.2f bilhões\n",pib1);
    
    // printf("Número de Pontos Turísticos: %d \n", numpt1);

    // printf("Densidade demográfica: %0.2f hab/km²\n", densidade1);

    // printf("PIB per capita: R$%0.2f \n", pibpcap1);


    // ------ Carta 2 ------

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

    
    // Processamento de dados
    
    densidade2 = (float) populacao2 / area2;
    pibpcap2 = (float) pib2 / populacao2;
    superpoder2 = (float) populacao2 + area2 + pib2 + numpt2 + (densidade2 * -1);



    //Exibição dados da Segunda Carta

    // printf("Carta 2:\n");

    // printf("Estado: %c \n", estado2);
    
    // printf("Código: %s \n", codigo2);

    // printf("Nome da Cidade: %s \n", nome2);

    // printf("População: %i habitantes\n", populacao2);
    
    // printf("Área: %0.2f km²\n", area2);
    
    // printf("PIB: R$ %0.2f bilhões\n",pib2);
    
    // printf("Número de Pontos Turísticos da Carta 2: %d \n", numpt2);
    
    // printf("Densidade demográfica: %0.2f hab/km²\n", densidade2);

    // printf("PIB per capita: R$ %0.2f \n\n", pibpcap2);




    // Menu do usuário para decidir a comparação ou exibição
    printf("===== Menu =====\n");
    printf("1. Nome do estado (Exibição)\n");
    printf("2. População\n");
    printf("3. Área\n");
    printf("4. PIB\n");
    printf("5. Número de Pontos Turísticos\n");
    printf("6. Densidade demográfica\n");
    printf("Digite a opção: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
        case 1:
            printf("Nome dos países: Carta 1: %s | Carta 2: %s\n", nome1, nome2);
            break;
        
        case 2:
            if(populacao1 == populacao2) {
                printf("A população dos dois países é a mesma!");
            }
            if(populacao1 > populacao2) {
                printf("A maior população é da Carta 1 (%s) com: %i habitantes\n", nome1, populacao1);
            } else {
                printf("A maior população é da Carta 2 (%s) com: %i habitantes\n", nome2, populacao2);

            }
            break;

        case 3:
            if(area1 == area2) {
                printf("A Área dos dois países é a mesma!");
            } else if(area1 > area2) {
                printf("A maior área é da Carta 1 (%s) com: %0.2f km²\n", nome1, area1);
            } else {
                printf("A maior área é da Carta 2 (%s) com: %0.2f km²\n", nome2, area2);

            }
            break;

        case 4:
            if(pib1 == pib2) {
                printf("O PIB dos dois países é a mesma!");
            }
            else if(pib1 > pib2) {
                printf("O maior PIB é da Carta 1 (%s) com: R$%0.2f bilhões\n", nome1, pib1);
            } else {
                printf("O maior PIB é da Carta 2 (%s) com: R$%0.2f bilhões\n", nome2, pib2);

            }
            break;

        case 5:
            if(numpt1 == numpt2) {
                printf("O Número de Pontos Turísticos dos dois países é a mesma!");
            } else if(numpt1 > numpt2) {
                printf("O maior Número de Pontos Turísticos é da Carta 1 (%s) com: %i\n", nome1, numpt1);
            } else {
                printf("O maior Número de Pontos Turísticos é da Carta 2 (%s) com: %i\n", nome2, numpt2);

            }
            break;

        case 6:
            if(densidade1 == densidade2) {
                printf("A densidade demográfica dos dois países é a mesma!");
            }
            if(densidade1 < densidade2) {
                printf("A menor Densidade demográfica é da Carta 1 (%s) com: %0.2f hab/km²\n", nome1, densidade1);
            } else {
                printf("A menor Densidade demográfica é da Carta 2 (%s) com: %0.2f hab/km²\n", nome2, densidade2);

            }
            break;
        default:
            printf("Digite uma opção válida.");
            break;
    }
    
}


