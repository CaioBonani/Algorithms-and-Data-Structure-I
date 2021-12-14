
//Bibliotecas usadas.
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Definindo a Struct com os dados de cada produto.
typedef struct Dados{
    char Nome[15];
    int Quantidade;
    int Mes;
    char Comprador[10];
}Dados;

//Fun��o Main.
int main(){

    //Fun��o para localizar o idioma em PT-BR, aceitando acentos e '�'.
    setlocale(LC_ALL, "Portuguese_Brazil");

    int n, i, z, lido, j, mes, mes_parada, soma, opcao;

    char cliente[10], nome_produto[15];

    //Vari�vel 'n' recebe a quantidade de produtos que ser�o cadastrados.
    printf("Quantos produtos voc� quer cadastrar: ");
    scanf("%d", &n);
    fflush(stdin);//Limpa buffer do scanf.

    //Declara��o, e aloca��o de mem�ria.
    Dados *produto, *pont;//Declara��o de vari�veis do tipo struct Dados.
    produto  = (Dados *)malloc(n*sizeof(Dados));//Aloc�o din�mica de mem�ria para produto(ser� um vetor do tipo Dados).
    pont = &produto[0];/*Ponteiro pont apontando para o primeiro endere�o do vetor produto, esse ponteiro ser� utilizado para realizar
                        a aritm�tica de ponteiros.*/

    printf("\n");


    //Fun��o FOR para "pegar" os valores de cada produto.
    for(pont = &produto[0]; pont<&produto[n]; pont++){
        printf("\nProduto: ");
        fgets(pont->Nome, sizeof(pont->Nome), stdin);
        pont->Nome[strcspn(pont->Nome, "\n")] = 0;//Fun��o para tirar o '\n' que o fgets deixa ao final da string.

        printf("\nQuantidade: ");
        scanf("%d", &pont->Quantidade);
        fflush(stdin);

        //Fun��o DO/WHILE para pegar o m�s, e n�o aceita meses que n�o sejam 1 at� 12.
        do{
            printf("\nM�s: ");
            scanf("%d", &pont->Mes);
            fflush(stdin);

            if(pont->Mes>=1 && pont->Mes<=12){
                mes_parada = 1;
            }else{
                printf("M�s inv�lido, insira um m�s v�lido.\n");
                mes_parada =0;
            }
        }while(mes_parada!= 1);
        mes_parada =0;


        printf("\nComprador: ");
        fgets(pont->Comprador, sizeof(pont->Comprador), stdin);
        pont->Comprador[strcspn(pont->Comprador, "\n")] = 0;
        system("clear || cls");
    }

    system("clear||cls");

    //Fun��o DO/WHILE para mostrar o menu, funciona at� a op��o 5(sa�da do programa) ser selecionada.
    do{
        printf("\n\n-------------------------------------------");
        printf("\n1) Total de vendas num dado m�s(todos produtos).");
        printf("\n2) Total de vendas de um determinado produto num dado m�s para um determinado cliente");
        printf("\n3) Total de vendas de cada produto.");
        printf("\n4) Total vendido para cada cliente.");
        printf("\n5) Fim.");

        printf("\n\nO que deseja fazer: ");//"Pega" a op��o desejada.
        scanf("%d", &opcao);
        fflush(stdin);

        //Fun��o SWITCH/CASE para direcionar para a op��o desejada.
        switch(opcao){
            case 1:
                system("clear||cls");
                soma = 0;

                //Fun��o SCANF para pegar o m�s que deseja ver a quantidade de vendas.
                printf("Qual m�s gostaria de ver: ");
                fflush(stdin);
                scanf("%d", &mes);
                fflush(stdin);

                //Fun��o IF/ELSE para saber se o m�s digitao � v�lido.
                if(mes>=1 && mes<=12){

                }else{
                    system("clear||cls");
                    printf("M�s inv�lido.\n");
                    system("pause");
                    system("clear||cls");
                    break;
                }

                //Fun��o FOR, utilizando aritm�tica de ponteiros, para ir passando por todos produtos cadastrados.
                for(pont = &produto[0]; pont<&produto[n]; pont++){
                    //Caso o m�s cadastrado seja igual o m�s digitado na busca e realizado a soma do total de vendas no m�s.
                    if(pont->Mes==mes){
                        soma = soma + pont->Quantidade;
                    }
                }

                //Fun��o IF/ELSE para printar a quantidade vendida no m�s, ou a n�o venda de produtos no m�s digitado.
                if(soma==0){
                    system("clear||cls");
                    printf("N�o foram encontradas vendas nesse m�s.\n\n");
                }else{
                    system("clear||cls");
                    printf("No m�s %d a quantidade total de produtos vendidos foi: %d.\n\n", mes, soma);
                }
                system("pause");
                system("clear||cls");
            break;

            case 2://arrumar essa funcao
                system("clear||cls");
                soma = 0;

                //Pega o m�s desejado.
                printf("Qual m�s gostaria de ver: ");
                scanf("%d", &mes);
                fflush(stdin);

                //Pega o cliente desejado.
                printf("Qual cliente gostaria de ver: ");
                fgets(cliente, 10, stdin);
                cliente[strcspn(cliente, "\n")] = 0;

                //Pega o produto desejado.
                printf("Qual produto gostaria de ver: ");
                fgets(nome_produto, 10, stdin);
                nome_produto[strcspn(nome_produto, "\n")] = 0;


                //Fun��o FOR, utilizando aritm�tica de ponteiro para passar por todos produtos cadastrados.
                for(pont=&produto[0];pont<&produto[n];pont++){
                    //Condicional para os dados digitados sejam iguais aos dados cadastrados.
                    if(pont->Mes==mes && strcmp(nome_produto, pont->Nome)==0 && strcmp(cliente, pont->Comprador)==0){
                        soma = soma + pont->Quantidade;//Caso sim soma o total.
                    }
                }

                //IF/ELSE para mostrar a quantidade vendida, ou a n�o venda, para os determinados dados.
                if(soma==0){
                    system("clear||cls");
                    printf("N�o foram encontradas vendas para as inform��es dadas.\n\n");
                }else{
                    system("clear||cls");
                    printf("Foram vendidas %d unidade(s) de %s, para o cliente %s no m�s %d.\n\n", soma, nome_produto, cliente, mes);
                }

                system("pause");
                system("clear||cls");
            break;

            case 3:
		soma=0;
                system("clear||cls");

                //Fun��o FOR(principal) que passa por todos cadastros e utiliza aritm�tica de ponteiros.
                for(pont=&produto[0], i=0; pont<&produto[n]; pont++, i++){
                    lido=0;

                    //Fun��o FOR(auxiliar) que pula um produto repetido, e n�o printar novamente. Utiliza aritm�tica(pont->) e vetor(produto[].).
                    for(z=0; z<i; z++){

                        if(strcmp(pont->Nome, produto[z].Nome)==0){
                            lido=1;
                            break;
                        }
                    }
                    if(lido==1){
                        continue;
                    }
                    

                    /*Fun��o FOR(auxiliar) com IF que compara o nome de todos produtos cadastrados com o nome do produto que o ponteiro(pont)
                    aponta atualmente, ou seja, em qual posi��o ele est�(indicado pelo FOR principal).*/
                    for(j=0; j<n; j++){
                        if(strcmp(produto[j].Nome, pont->Nome)==0){
                            printf("\nNo m�s %d, a quantidade vendida de %s foi: %d.", produto[j].Mes, produto[j].Nome, produto[j].Quantidade);
                            soma= soma + produto[j].Quantidade;
                        }
                    }
                //Printa o total de vendas para o produto em que o ponteiro(pont) est� apontando.
                printf("\nO total de vendas de %s foi: %d.\n", pont->Nome, soma);
                }
            printf("\n");
            system("pause");
            system("clear||cls");
            break;

            case 4:
		soma=0;
            	system("clear||cls");

            	//Fun��o FOR(principal) que passa por todos cadastros e utiliza aritm�tica de ponteiros.
            	for(pont=&produto[0], i=0; pont<&produto[n]; pont++, i++){
                lido=0;

                	//Fun��o FOR(auxiliar) que pula um comprador repetido, e n�o printar novamente. Utiliza aritm�tica(pont->) e vetor(produto[].).
                	for(z=0; z<i; z++){

                    		if(strcmp(pont->Comprador, produto[z].Comprador)==0){
                        		lido=1;
                        		break;
                   		 }
                	}
                	if(lido==1){
                    		continue;
                	}
                

                /*Fun��o FOR(auxiliar) com IF que compara o nome de todos clientes cadastrados com o nome do cliente que o ponteiro(pont)
                aponta atualmente, ou seja, em qual posi��o ele est�(indicado pelo FOR principal).*/
                for(j=0; j<n; j++){
                    if(strcmp(produto[j].Comprador, pont->Comprador)==0){
                        soma= soma + produto[j].Quantidade;
                    }
                }
                //Printa o total de vendas para o cliente em que o ponteiro(pont) est� apontando.
                printf("\nO cliente %s comprou, ao total: %d produtos.", pont->Comprador, soma);

                printf("\n");
            }
            printf("\n");
            system("pause");
            system("clear||cls");
            break;

            case 5:
                system("clear||cls");
                printf("Programa finalizado com sucesso!\n\n");
            break;

            default:
                system("clear||cls");
                printf("Erro!\n");

        }
    }while(opcao!=5);

    /*Desalocando a mem�ria alocada para o ponteiro/vetor "produtos", mem�ria que foi alocada dinamicamente usando o malloc.*/
    free(produto);

    return 0;
}
