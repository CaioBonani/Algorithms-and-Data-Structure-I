
//Bibliotecas usadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Definindo a struct com os dados dos carros.
typedef struct Carro{
    char Marca[15];
    char Modelo[25];
    int Ano_de_fabricacao;
    char Placa_do_carro[6];
    int Quilometragem;
    int Numeros_de_portas;
    char Ar_condicionado[1];
}Carro;

//Ponteiro de Vetor para salvar os dados da struct.
Carro* carros[10];


//Fun��o para criar um novo cadastro.
void novo_cadastro(){

    /*Criando o ponteiro de arquivo, e abrindo-o com a op��o "a" para ele escrever somente no fim do arquivo.*/
    FILE *arquivo;

    arquivo = fopen("carros.txt", "a");

    if (arquivo == NULL){
        printf("N�o foi poss�vel criar o arquivo");
        return;
    }

    /*Alocando a mem�ria.*/
    Carro* carro = (Carro*)malloc(sizeof(Carro));

    system("clear||cls");

    printf("----------------------------------------------------------");
    printf("\nCadastrar Ve�culo!");


    printf("\n\nQual a marca do carro: \n");

    /*Lendo a string digitada, e salvando em carro.Marca.*/
    fgets(carro->Marca, sizeof(carro->Marca), stdin);
    /*Realizando a varredura da string, caso ache uma palavra composta, com espa�o(' '), troca por h�fen('-')
    procedimento realizado para salvar a string no arquivo.*/
    for (int i = 0; i <= strlen(carro->Marca); ++i) {
        if(carro->Marca[i]==' '){
            carro->Marca[i]='-';
        }
    }
    /*Salvando a string no arquivo.*/
    fprintf(arquivo, "%s", carro->Marca);

    printf("Qual o modelo do carro: \n");
    /*Lendo a string digitada, e salvando em carro.Modelo.*/
    fgets(carro->Modelo, sizeof(carro->Modelo), stdin);
    /*Realizando a varredura da string, caso ache uma palavra composta, com espa�o(' '), troca por h�fen('-')
    procedimento realizado para salvar a string no arquivo.*/
    for (int i = 0; i <= strlen(carro->Modelo); ++i) {
        if(carro->Modelo[i]==' '){
            carro->Modelo[i]='-';
        }
    }
    /*Salvando a string no arquivo.*/
    fprintf(arquivo, "%s", carro->Modelo);

    printf("Qual o ano de fabrica��o do carro: \n");
    /*Lendo a string digitada, e salvando em carro.Ano_de_fabricacao.*/
    scanf("%d", &carro->Ano_de_fabricacao);
    getchar();
    /*Salvando a string no arquivo.*/
    fprintf(arquivo, "%d\n", carro->Ano_de_fabricacao);

    printf("Qual a placa do carro(5 digitos): \n");
    /*Lendo a string digitada, e salvando em carro.Placa_do_carro.*/
    scanf("%s", carro->Placa_do_carro);
    getchar();
    /*Salvando a string no arquivo.*/
    fprintf(arquivo, "%s\n", carro->Placa_do_carro);

    printf("Qual a quilometragem do carro: \n");
    /*Lendo a string digitada, e salvando em carro.Quilometragem.*/
    scanf("%d", &carro->Quilometragem);
    /*Salvando a string no arquivo.*/
    fprintf(arquivo, "%d\n", carro->Quilometragem);

    printf("Qual o n�mero de portas do carro: \n");
    /*Lendo a string digitada, e salvando em carro.Numeros_de_portas.*/
    scanf("%d", &carro->Numeros_de_portas);
    /*Salvando a string no arquivo.*/
    fprintf(arquivo, "%d\n", carro->Numeros_de_portas);

    printf("O carro tem Ar Condicionado(s/n): \n");
    /*Lendo a string digitada, e salvando em carro.Ar_condicionado.*/
    scanf("%s", carro->Ar_condicionado);
    getchar();
    /*Salvando a string no arquivo.*/
    fprintf(arquivo, "%s\n", carro->Ar_condicionado);

    system("clear||cls");
    printf("\nCarro cadastrado com sucesso!\n");

    /*Fechando o arquivo.*/
    fclose(arquivo);

    /*Desalocando a mem�ria.*/
    free(carro);

}

//Fun��o para alterar os dados.
void alt_dados(){

    int i=0, j, num, linha=1, saida_cad=0, placa_encontrada=1, placa_existe, cont1=0, cont2=0, opcao_alt_cadast=0;
    char aux[15], placa[6], caracter;

    /*Criando o ponteiro de arquivo, e abrindo-o com a op��o "r" (somente leitura).*/
    FILE *arquivo;

    arquivo = fopen("carros.txt", "r");

    if (arquivo == NULL){
        system("clear||cls");
        printf("N�o foi poss�vel achar o arquivo");
        return;
    }

    /*Fun��o para saber se h� algum carro no arquivo.*/
    rewind(arquivo);
    caracter = getc(arquivo);
    if (caracter == '�'){
        system("clear||cls");
        printf("Nenhum carro cadastrado no Banco de Dados!");
        return;
    }


    /*Escanenado linha por linhas e atribuindo os dados aos respectivos espa�os da struct.*/
    while(fscanf(arquivo, "%[^\n]%*c", aux) != EOF){

        /*Alocando espa�o para cada vetor de carro.*/
        carros[i] = (Carro*)malloc(sizeof(Carro));

        strcpy(carros[i]->Marca, aux);
        fscanf(arquivo, "%[^\n]%*c", carros[i]->Modelo);
        fscanf(arquivo, "%d%*c", &carros[i]->Ano_de_fabricacao);
        fscanf(arquivo, "%[^\n]%*c", carros[i]->Placa_do_carro);
        fscanf(arquivo, "%d%*c", &carros[i]->Quilometragem);
        fscanf(arquivo, "%d%*c", &carros[i]->Numeros_de_portas);
        fscanf(arquivo, "%s%*c", carros[i]->Ar_condicionado);
        i++;
    }

    /*Voltando o indicador de posi��o para o in�cio do arquivo.*/
    rewind(arquivo);
    /*char "caracter" recebendo o primeiro caracter do arquivo.*/
    caracter = getc(arquivo);
    /*Fun��o WHILE para para contar linhas do arquivo.*/
    while(caracter!=EOF){
        if(caracter=='\n'){
            linha++;
        }
        caracter = getc(arquivo);
    }

    /*A vari�vel "linha" agora guarda a quantidade de carros armazenados, em vez da quantidade de linhas.*/
    linha = linha - 1;
    linha = linha/7;

    system("clear||cls");

    printf("----------------------------------------------------------");
    printf("\nAlterar Dados!");


    printf("\n\nDigite a placa do carro que voc� deseja alterar os dados: ");
    /*Atribuindo a placa do carro que deseja alterar os dados ao char "placa".*/
    scanf("%s", placa);
    j=i;
    /*Fun��o FOR para comparar a vari�vel "placa" com as placas existentes no arquivo.*/
    for(i=0; i<j; i++){
        if(strcmp(carros[i]->Placa_do_carro, placa)==0){
            num = i; //Salva a posi��o do vetor em que a placa est�, ou seja, de qual carro a placa �.
            placa_existe=1;
        }else{
            placa_encontrada=0;
        }
    }

    if(placa_existe==1){
        placa_encontrada=1;
    }

    if(placa_encontrada==0){
        system("clear||cls");
        printf("Placa n�o encontrada.\n");
        return;
    }


    system("clear||cls");

    /*Realizando a varredura da string, caso ache uma palavra composta, com h�fen('-'), troca por espa�o(' ')
    procedimento realizado para exibir a informa��o na tela.*/
    for (int i = 0; i < strlen(carros[num]->Marca); ++i) {
        if(carros[num]->Marca[i]=='-'){
            carros[num]->Marca[i]=' ';
        }
    }

    /*Realizando a varredura da string, caso ache uma palavra composta, com h�fen('-'), troca por espa�o(' ')
    procedimento realizado para exibir a informa��o na tela.*/
    for (int i = 0; i < strlen(carros[num]->Modelo); ++i) {
        if(carros[num]->Modelo[i]=='-'){
            carros[num]->Modelo[i]=' ';
        }
    }

    /*Menu interno da op��o dois.*/
    do{
        /*2 Fun��es para trocar o h�fen por espa�o, para mostrar na tela.*/
        for (int i = 0; i < strlen(carros[num]->Marca); ++i) {
            if(carros[num]->Marca[i]=='-'){
                carros[num]->Marca[i]=' ';
            }
        }

        for (int i = 0; i < strlen(carros[num]->Modelo); ++i) {
            if(carros[num]->Modelo[i]=='-'){
                carros[num]->Modelo[i]=' ';
            }
        }

        /*IF para formatar a tela, por problemas com a quebra de linha '\n' que a fun��o fgets deixa ao final
        da string lida.*/
        if(cont1==0 && cont2==0){
            printf("\nMarca: %s", carros[num]->Marca);
            printf("\nModelo: %s", carros[num]->Modelo);
            printf("\nAno de Fabrica��o: %d", carros[num]->Ano_de_fabricacao);
        }else if(cont1==1 && cont2==0){
            printf("\nMarca: %s", carros[num]->Marca);
            printf("Modelo: %s", carros[num]->Modelo);
            printf("\nAno de Fabrica��o: %d", carros[num]->Ano_de_fabricacao);
        }else if(cont2==1 && cont1==0){
            printf("\nMarca: %s", carros[num]->Marca);
            printf("\nModelo: %s", carros[num]->Modelo);
            printf("Ano de Fabrica��o: %d", carros[num]->Ano_de_fabricacao);
        }else if(cont1==1 && cont2 ==1){
            printf("\nMarca: %s", carros[num]->Marca);
            printf("Modelo: %s", carros[num]->Modelo);
            printf("Ano de Fabrica��o: %d", carros[num]->Ano_de_fabricacao);
        }
        printf("\nPlaca: %s", placa);
        printf("\nQuilometragem: %d", carros[num]->Quilometragem);
        printf("\nN�mero de portas: %d", carros[num]->Numeros_de_portas);
        printf("\nAr condicionado: %s", carros[num]->Ar_condicionado);

        printf("\n\n1) Alterar Marca");
        printf("\n2) Alterar Modelo");
        printf("\n3) Alterar Ano de Fabrica��o");
        printf("\n4) Alterar Quilometragem");
        printf("\n5) Alterar N�mero de portas");
        printf("\n6) Alterar Ar Condicionado");
        printf("\n7) Fim da altera��o");

        printf("\n\nO que voc� deseja alterar: ");
        scanf("%d", &opcao_alt_cadast);
        fflush(stdin); /*Limpa buffer ocasionado pelo scanf, buffer esse que pode ocasionar erros nos
                        pr�ximos scanf*/

        /*SWITCH/CASE que direciona para a op��o selecionada.*/
        switch(opcao_alt_cadast){
            case 1:
                printf("\nQual a marca do Carro: ");
                /*Lendo a string digitada, e salvando em carro.Marca.*/
                fgets(carros[num]->Marca, sizeof(carros[num]->Marca), stdin);
                /*Realizando a varredura da string, caso ache uma palavra composta, com espa�o(' '), troca por h�fen('-')
                procedimento realizado para salvar a string no arquivo.*/
                for (int i = 0; i < strlen(carros[num]->Marca); ++i) {
                    if(carros[num]->Marca[i]==' '){
                        carros[num]->Marca[i]='-';
                    }
                }
                system("clear||cls");
                printf("Dados alterados com sucesso!\n");
                cont1=1; //Contador utilizado nos IFs a cima.
            break;

            case 2:
                printf("\nQual o modelo do Carro:");
                /*Lendo a string digitada, e salvando em carro.Modelo.*/
                fgets(carros[num]->Modelo, sizeof(carros[num]->Modelo), stdin);
                /*Realizando a varredura da string, caso ache uma palavra composta, com espa�o(' '), troca por h�fen('-')
                procedimento realizado para salvar a string no arquivo.*/
                for (int i = 0; i < strlen(carros[num]->Modelo); ++i) {
                    if(carros[num]->Modelo[i]==' '){
                        carros[num]->Modelo[i]='-';
                    }
                }
                system("clear||cls");
                printf("Dados alterados com sucesso!\n");
                cont2=1; //Contador utilizado nos IFs a cima.
            break;

            case 3:
                printf("\nQual o ano de fabrica��o do Carro: ");
                /*Lendo a string digitada, e salvando em carro.Ano_de_fabricacao.*/
                scanf("%d", &carros[num]->Ano_de_fabricacao);
                system("clear||cls");
                printf("Dados alterados com sucesso!\n");
            break;

            case 4:
                printf("\nQual a quilometragem do Carro: ");
                /*Lendo a string digitada, e salvando em carro.Quilometragem.*/
                scanf("%d", &carros[num]->Quilometragem);
                system("clear||cls");
                printf("Dados alterados com sucesso!\n");
            break;

            case 5:
                printf("\nQual o n�mero de portas do Carro: ");
                /*Lendo a string digitada, e salvando em carro.Numeros_de_portas.*/
                scanf("%d", &carros[num]->Numeros_de_portas);
                system("clear||cls");
                printf("Dados alterados com sucesso!\n");
            break;

            case 6:
                printf("\nO carro tem Ar Condicionado: ");
                /*Lendo a string digitada, e salvando em carro.Ar_condicionado.*/
                scanf("%s", carros[num]->Ar_condicionado);
                system("clear||cls");
                printf("Dados alterados com sucesso!\n");
            break;

            case 7:
                system("clear||cls");
                printf("Dados alterados com sucesso!\n");
                saida_cad = 1;
            break;

            default:
                system("clear||cls");
                printf("Op��o inv�lida, tente novamente.\n");
        }

    }while(saida_cad!=1);

    /*Fechando o arquivo de somente leitura.*/
    fclose(arquivo);

    /*Abrindo um arquivo novo, em branco, para salvar os dados alterados e, tamb�m, os n�o alterados.*/
    arquivo = fopen("carros.txt", "w");
    if (arquivo == NULL){
        printf("N�o foi poss�vel achar o arquivo");
        return;
    }

    /*Trocando espa�os por h�fens para poder salvar as strings no arquivo.*/
    for (int i = 0; i < strlen(carros[num]->Marca); ++i) {
        if(carros[num]->Marca[i]==' '){
            carros[num]->Marca[i]='-';
        }
    }
    /*Trocando espa�os por h�fens para poder salvar as strings no arquivo.*/
    for (int i = 0; i < strlen(carros[num]->Modelo); ++i) {
        if(carros[num]->Modelo[i]==' '){
            carros[num]->Modelo[i]='-';
        }
    }

    /*FOR para ir salvando os dados linha por linha.*/
    for(i=0; i<linha; i++){
        /*IFs para poder salvar de forma correta(linha por linha), sem estes IFs pode ocorrer uma grava��o
        incorreta, por conta do '\n' que a fun��o fgets coloca ao final da string.*/
        if(i==num){
            if(cont1==1 && cont2==0){
                fprintf(arquivo, "%s", carros[i]->Marca);
                fprintf(arquivo, "%s\n", carros[i]->Modelo);
                fprintf(arquivo, "%d\n", carros[i]->Ano_de_fabricacao);
                fprintf(arquivo, "%s\n", carros[i]->Placa_do_carro);
                fprintf(arquivo, "%d\n", carros[i]->Quilometragem);
                fprintf(arquivo, "%d\n", carros[i]->Numeros_de_portas);
                fprintf(arquivo, "%s\n", carros[i]->Ar_condicionado);
            }else if(cont2==1 && cont1==0){
                fprintf(arquivo, "%s\n", carros[i]->Marca);
                fprintf(arquivo, "%s", carros[i]->Modelo);
                fprintf(arquivo, "%d\n", carros[i]->Ano_de_fabricacao);
                fprintf(arquivo, "%s\n", carros[i]->Placa_do_carro);
                fprintf(arquivo, "%d\n", carros[i]->Quilometragem);
                fprintf(arquivo, "%d\n", carros[i]->Numeros_de_portas);
                fprintf(arquivo, "%s\n", carros[i]->Ar_condicionado);
            }else if(cont1==0 && cont2==0){
                fprintf(arquivo, "%s\n", carros[i]->Marca);
                fprintf(arquivo, "%s\n", carros[i]->Modelo);
                fprintf(arquivo, "%d\n", carros[i]->Ano_de_fabricacao);
                fprintf(arquivo, "%s\n", carros[i]->Placa_do_carro);
                fprintf(arquivo, "%d\n", carros[i]->Quilometragem);
                fprintf(arquivo, "%d\n", carros[i]->Numeros_de_portas);
                fprintf(arquivo, "%s\n", carros[i]->Ar_condicionado);
            }else{
                fprintf(arquivo, "%s", carros[i]->Marca);
                fprintf(arquivo, "%s", carros[i]->Modelo);
                fprintf(arquivo, "%d\n", carros[i]->Ano_de_fabricacao);
                fprintf(arquivo, "%s\n", carros[i]->Placa_do_carro);
                fprintf(arquivo, "%d\n", carros[i]->Quilometragem);
                fprintf(arquivo, "%d\n", carros[i]->Numeros_de_portas);
                fprintf(arquivo, "%s\n", carros[i]->Ar_condicionado);
            }
        }else{
            fprintf(arquivo, "%s\n", carros[i]->Marca);
            fprintf(arquivo, "%s\n", carros[i]->Modelo);
            fprintf(arquivo, "%d\n", carros[i]->Ano_de_fabricacao);
            fprintf(arquivo, "%s\n", carros[i]->Placa_do_carro);
            fprintf(arquivo, "%d\n", carros[i]->Quilometragem);
            fprintf(arquivo, "%d\n", carros[i]->Numeros_de_portas);
            fprintf(arquivo, "%s\n", carros[i]->Ar_condicionado);
        }
    }

    /*Fecha o arquivo de escrita.*/
    fclose(arquivo);

    /*Desaloca o espa�o alocado pelo malloc.*/
    for(i=0;i<linha;i++){
        free(carros[i]);
    }
}

//Fun��o para exibir os dados.
void mostrar_dados(){

    int i=0, j, linha=1, num, placa_existe, placa_encontrada;

    char aux[15], placa[6], caracter;

    /*Criando o ponteiro de arquivo e abrindo-o no modo somente leitura("r").*/
    FILE *arquivo;
    arquivo = fopen("carros.txt", "r");

    if (arquivo == NULL){
        system("clear||cls");
        printf("N�o foi poss�vel achar o arquivo");

        return;
    }

    /*Fun��o para saber se h� algum carro no arquivo.*/
    rewind(arquivo);
    caracter = getc(arquivo);
    if (caracter == '�'){
        system("clear||cls");
        printf("Nenhum carro cadastrado no Banco de Dados!");
        return;
    }

    /*Lendo linha por linha do arquivo e atribuindo os dados aos respectivos espa�os da struct.*/
    while(fscanf(arquivo, "%[^\n]%*c", aux) != EOF){

        /*Alocando espa�o para cada vetor de carro.*/
        carros[i] = (Carro*)malloc(sizeof(Carro));

        strcpy(carros[i]->Marca, aux);
        fscanf(arquivo, "%[^\n]%*c", carros[i]->Modelo);
        fscanf(arquivo, "%d%*c", &carros[i]->Ano_de_fabricacao);
        fscanf(arquivo, "%[^\n]%*c", carros[i]->Placa_do_carro);
        fscanf(arquivo, "%d%*c", &carros[i]->Quilometragem);
        fscanf(arquivo, "%d%*c", &carros[i]->Numeros_de_portas);
        fscanf(arquivo, "%s%*c", carros[i]->Ar_condicionado);
        i++;
    }
    /*Voltando o indicador de posi��o para o in�cio do arquivo.*/
    rewind(arquivo);
    /*char "caracter" recebendo o primeiro caracter do arquivo.*/
    caracter = getc(arquivo);
    /*Fun��o WHILE para para contar linhas do arquivo.*/
    while(caracter!=EOF){
        if(caracter=='\n'){
            linha++;
        }
        caracter = getc(arquivo);
    }

    /*A vari�vel "linha" agora guarda a quantidade de carros armazenados, em vez da quantidade de linhas.*/
    linha = linha - 1;
    linha = linha/7;

    system("clear||cls");

    printf("----------------------------------------------------------");
    printf("\nExibir dados!");


    printf("\n\nDigite a placa do carro que voc� deseja visualizar os dados: ");
    /*Atribuindo a placa que desejamos procurar na vari�vel "placa".*/
    scanf("%s", placa);

    j=i;

    /*Comparando a placa digitada com as placas salvas dos carros no banco de dados.*/
    for(i=0; i<j; i++){
        if(strcmp(carros[i]->Placa_do_carro, placa)==0){
            num = i; //Salva a posi��o do vetor em que a placa est�, ou seja, de qual carro a placa �.
            placa_existe=1;
        }else{
            placa_encontrada=0;
        }
    }

    if(placa_existe==1){
        placa_encontrada=1;
    }

    if(placa_encontrada==0){
        system("clear||cls");
        printf("Placa n�o encontrada\n");
        return;
    }

    system("clear||cls");

    /*Mudando h�fen(formato salvo no arquivo) por espa�o(formata��o da string para exibir na tela).*/
    for (int i = 0; i < strlen(carros[num]->Marca); ++i) {
        if(carros[num]->Marca[i]=='-'){
            carros[num]->Marca[i]=' ';
        }
    }
    /*Mudando h�fen(formato salvo no arquivo) por espa�o(formata��o da string para exibir na tela).*/
    for (int i = 0; i < strlen(carros[num]->Modelo); ++i) {
        if(carros[num]->Modelo[i]=='-'){
            carros[num]->Modelo[i]=' ';
        }
    }

    /*Exibindo dados na tela.*/
    printf("\nDados do carro placa: %s\n\n", placa);
    printf("Marca: %s\n", carros[num]->Marca);
    printf("Modelo: %s\n", carros[num]->Modelo);
    printf("Ano de Fabrica��o: %d\n", carros[num]->Ano_de_fabricacao);
    printf("Placa: %s\n", carros[num]->Placa_do_carro);
    printf("Quilometragem: %d\n", carros[num]->Quilometragem);
    printf("N�mero de Portas: %d\n", carros[num]->Numeros_de_portas);
    printf("Ar Condicionado: %s\n", carros[num]->Ar_condicionado);

    printf("\nDigite enter para continuar...\n");
    system("pause");
    system("clear||cls");

    /*Fecha o arquivo.*/
    fclose(arquivo);

    /*Desaloca o espa�o alocado pelo malloc.*/
    for(i=0;i<linha;i++){
        free(carros[i]);
    }

}

//Fun��o para apagar o registro.
void excluir_reg(){
    /*Vari�veis.*/
    int i=0, num, j, linha=1, placa_encontrada=1, placa_existe;

    char aux[15], placa[6], caracter;

    /*Criando o ponteiro de arquivo e abrindo-o no modo somente leitura("r").*/
    FILE *arquivo;
    arquivo = fopen("carros.txt", "r");

    if (arquivo == NULL){
        system("clear||cls");
        printf("N�o foi poss�vel achar o arquivo");
        return;
    }

    /*Fun��o para saber se h� algum carro no arquivo.*/
    rewind(arquivo);
    caracter = getc(arquivo);
    if (caracter == '�'){
        system("clear||cls");
        printf("Nenhum carro cadastrado no Banco de Dados!");
        return;
    }

    /*Lendo linha por linha do arquivo e atribuindo os dados aos respectivos espa�os da struct*/
    while(fscanf(arquivo, "%[^\n]%*c", aux) != EOF){

        /*Alocando espa�o para cada vetor de carro.*/
        carros[i] = (Carro*)malloc(sizeof(Carro));

        strcpy(carros[i]->Marca, aux);
        fscanf(arquivo, "%[^\n]%*c", carros[i]->Modelo);
        fscanf(arquivo, "%d%*c", &carros[i]->Ano_de_fabricacao);
        fscanf(arquivo, "%[^\n]%*c", carros[i]->Placa_do_carro);
        fscanf(arquivo, "%d%*c", &carros[i]->Quilometragem);
        fscanf(arquivo, "%d%*c", &carros[i]->Numeros_de_portas);
        fscanf(arquivo, "%s%*c", carros[i]->Ar_condicionado);
        i++;
    }

    /*Alocando mem�ria para i+1, e atribuindo o valor "0" para a placa desse �ndice.*/
    carros[i] = (Carro*)malloc(sizeof(Carro));
    strcpy(carros[i]->Placa_do_carro, "0");

    /*"Mini fun��o" para calcular a quantidade de linhas e depois calcular a quantidade de carros cadastrados.*/
    rewind(arquivo);
    caracter = getc(arquivo);

    while(caracter!=EOF){
        if(caracter=='\n'){
            linha++;
        }
        caracter = getc(arquivo);
    }

    linha = linha - 1;
    linha = linha/7;

    system("clear||cls");

    printf("----------------------------------------------------------");
    printf("\nExcluir Dados!");

    j=i;

    /*Menu interno da op��o 4.*/
    do{
        printf("\n\nDigite a placa do carro que voc� deseja excluir os dados: ");
        /*Atribuindo a placa, do carro que desejamos excluir, na vari�vel "placa".*/
        scanf("%s", placa);

        for(i=0; i<j; i++){
            if(strcmp(carros[i]->Placa_do_carro, placa)==0){
                num = i;
                placa_existe=1;
            }else{
                placa_encontrada=0;
            }
        }

        if(placa_existe==1){
            placa_encontrada=1;
        }

        if(placa_encontrada==0){
            system("clear||cls");
            printf("Placa n�o encontrada.\n");
            return;
        }

    }while(placa_existe!=1);

    system("clear||cls");

    /*Trocando h�fen por espa�o(para exibir na tela).*/
    for (int i = 0; i < strlen(carros[num]->Marca); ++i) {
        if(carros[num]->Marca[i]=='-'){
            carros[num]->Marca[i]=' ';
        }
    }
    /*Trocando h�fen por espa�o(para exibir na tela).*/
    for (int i = 0; i < strlen(carros[num]->Modelo); ++i) {
        if(carros[num]->Modelo[i]=='-'){
            carros[num]->Modelo[i]=' ';
        }
    }

    /*Mostrando os dados do carro que ser� removido.*/
    printf("Apagando os dados do seguinte carro:\n");
    printf("\nMarca: %s", carros[num]->Marca);
    printf("\nModelo: %s", carros[num]->Modelo);
    printf("\nAno de Fabrica��o: %d", carros[num]->Ano_de_fabricacao);
    printf("\nPlaca: %s", placa);
    printf("\nQuilometragem: %d", carros[num]->Quilometragem);
    printf("\nN�mero de portas: %d", carros[num]->Numeros_de_portas);
    printf("\nAr Condicionado: %s", carros[num]->Ar_condicionado);

    /*Trocando espa�o por h�fen()para salvar no arquivo).*/
    for (int i = 0; i < strlen(carros[num]->Marca); ++i) {
        if(carros[num]->Marca[i]==' '){
            carros[num]->Marca[i]='-';
        }
    }
    /*Trocando espa�o por h�fen()para salvar no arquivo).*/
    for (int i = 0; i < strlen(carros[num]->Modelo); ++i) {
        if(carros[num]->Modelo[i]==' '){
            carros[num]->Modelo[i]='-';
        }
    }

    /*Para excluir os dados de um carros em espec�fico, a fun��o passa todos os dados deste carro
    que tem a posi��o "num", para o os vetores que armazenam as informa��es do carro seguinte "num+1".
    Ou seja, � como se estivesse passando os dados pra frente.*/
    for(i=num; i<linha; i++){
        if(strcmp(carros[i]->Placa_do_carro, "0")==0){
            break;
        }
        strcpy(carros[i]->Marca, carros[i+1]->Marca);
        strcpy(carros[i]->Modelo, carros[i+1]->Modelo);
        carros[i]->Ano_de_fabricacao = carros[i+1]->Ano_de_fabricacao;
        strcpy(carros[i]->Placa_do_carro, carros[i+1]->Placa_do_carro);
        carros[i]->Quilometragem = carros[i+1]->Quilometragem;
        carros[i]->Numeros_de_portas = carros[i+1]->Numeros_de_portas;
        strcpy(carros[i]->Ar_condicionado, carros[i+1]->Ar_condicionado);
    }


    /*Fecha o arquivo de somente leitura.*/
    fclose(arquivo);

    /*Abre um novo em branco, usando "w".*/
    arquivo = fopen("carros.txt", "w");

    if (arquivo == NULL){
        printf("N�o foi poss�vel achar o arquivo");
        return;
    }

    /*Realiza o salvamento de todas informa��es no novo arquivo.*/
    for(i=0; i<linha-1; i++){
        fprintf(arquivo, "%s\n", carros[i]->Marca);
        fprintf(arquivo, "%s\n", carros[i]->Modelo);
        fprintf(arquivo, "%d\n", carros[i]->Ano_de_fabricacao);
        fprintf(arquivo, "%s\n", carros[i]->Placa_do_carro);
        fprintf(arquivo, "%d\n", carros[i]->Quilometragem);
        fprintf(arquivo, "%d\n", carros[i]->Numeros_de_portas);
        fprintf(arquivo, "%s\n", carros[i]->Ar_condicionado);
    }

    printf("\n\nDados apagados com sucesso!\n\nPressione enter para continuar\n\n.");
    system("pause");
    system("clear||cls");

    /*Fechando o arquivo novo, atualizado.*/
    fclose(arquivo);

    /*Desaloca o espa�o alocado pelo malloc.*/

    for(i=0;i<linha;i++){
        free(carros[i]);
    }

}

//Fun��o main.
int main(void){

    /*Fun��o para localizar o idioma PT-BR, aceitando "�" e acentos.*/
    setlocale(LC_ALL, "Portuguese_Brazil");

    int saida=0, opcao;

    /*Menu principal.*/
    do{
        printf("\n\n----------------------------------------------------------");
        printf("\n1) Inserir novo cadastro de ve�culo");
        printf("\n2) Alterar cadastro");
        printf("\n3) Mostrar os dados de um ve�culo");
        printf("\n4) Apagar registro");
        printf("\n5) Sair");

        printf("\n\nO que deseja fazer: ");
        scanf("%d", &opcao);
        fflush(stdin); /*Limpa buffer ocasionado pelo scanf, buffer esse que pode ocasionar erros nos
                        pr�ximos scanf*/

        /*SWITCH/CASE que direciona para a op��o selecionada.*/
        switch(opcao){
            case 1:
                /*Caso a op��o 1 seja a selecionada, � chamada da fun��o para cadastrar um novo carro.*/
                novo_cadastro(); //"carros" � o par�metro que a fun��o recebe.
            break;

            case 2:
                /*Caso a op��o 2 seja a selecionada, � chamada da fun��o para alterar os dados.*/
                alt_dados();//"carros" � o par�metro que a fun��o recebe.
            break;

            case 3:
                /*Caso a op��o 3 seja a selecionada, � chamada da fun��o para exibir os dados.*/
                mostrar_dados();//"carros" � o par�metro que a fun��o recebe.
            break;

            case 4:
                /*Caso a op��o 4 seja a selecionada, � chamada da fun��o para excluir os dados.*/
                excluir_reg();
            break;

            case 5:
                system("clear||cls");
                printf("Programa finalizado com sucesso!\n\n");
                saida = 1;
            break;

            default:
                system("clear||cls");
                printf("Erro!\n");
        }
    } while (saida != 1);

    return 0;
}
