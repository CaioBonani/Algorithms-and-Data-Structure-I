
//Bibliotecas utilizadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//Tamanho máximo dos polinômios
#define MAX 99

//Criando struct da lista.
struct lista {

    int info; //Coeficiente.
    int exp; //Expoente.
    struct lista* ant; //Ponteiro para o nó anterior.
    struct lista* prox; //Ponteiro para o próximo nó.
    
};
typedef struct lista Lista;

/*Função para inserir o polinômio na lista, insere de forma ordenada,
colocando em ordem decrescente de expoente-coeficiente.*/
Lista* insere(Lista* l, int info, int exp){

    Lista *aux, *ant, *novo;

    novo = (Lista*)malloc(sizeof(Lista)); //Cria o novo nó.

    //Atribui os dados do polinômio as variáveis do nó.
    novo->info = info; 
    novo->exp = exp;

    if(l == NULL){ //Caso seja o primeiro nó.

        //Prox. e anterior não existem, portando são NULL.
        novo->ant = NULL;
        novo->prox = NULL;

        l = novo; //Lista recebe o nó criado.

    }else{ //Caso não seja o primeiro nó.

        aux = l;

        while(aux->prox != NULL && aux->exp > exp ) //Vai iterando pela lista.
            aux = aux->prox;
        
        if(aux->exp > exp){ //Se o expoente da lista for maior que o exp. atual.

            //Coloca na direita.
            novo->prox = NULL;
            novo->ant = aux;
            aux->prox = novo;

        }else{ //Senão.

            //Coloca na esquerda.
            novo->prox = aux;
            novo->ant = aux->ant;

            if(aux->ant != NULL)
                aux->ant->prox = novo;

            else{

                l = novo;
                novo->ant = NULL;

            }

            aux->ant = novo;

        }
    }

    return l; //Retorna a lista.
}

//Função que recebe os polinômios.
void polinomio(char polinomio1[], char polinomio2[]){

    puts("\nDigite na linha abaixo o primeiro polinômio."); 
    fgets(polinomio1, MAX, stdin); //Pega o polinômio.
    polinomio1[strcspn(polinomio1, "\n")] = 0; //Tira o '\n' do final.
    strcat(polinomio1, "\0"); //Coloca um '\0' no final da string.
    puts("");

    //Análogo.
    puts("Digite na linha abaixo o segundo polinômio.");
    fgets(polinomio2, MAX, stdin);
    polinomio2[strcspn(polinomio2, "\n")] = 0;
    strcat(polinomio2, "\0");

    //Limpa a tela do terminal ou do CMD.
    //system("clear || cls");

}

void valida(char p[]){

    int i, j=0;
    char aux[MAX];

    for(i=0; i<strlen(p); i++){

        if(p[i] == ' ')
            continue;

        aux[j++] = p[i];

    }

    memset(p, 0, strlen(p));

    for(i=0; i<strlen(aux); i++)
        p[i] = aux[i];

}

//Função para liberar o espaço alocado para os nós.
Lista* free_(Lista* l){

    //Se o próximo nó ser NULL, significa que só existe um nó.
    if(l->prox == NULL){

        free(l); //Libera ele.
        return NULL; //Retorna NULL.

    }
    
    //Caso exista mais de um nó.
    while(l != NULL){

        free(l); //Vai liberando os nós.
        l = l->prox; //Até o último nó.

    }

    return NULL;

}

//Função que formata a string e insere na lista..
Lista* transf_pol(char polinomio[], Lista* l){          //32x^4-33-2x^2+8x

    char aux[strlen(polinomio)];
    char aux_exp[strlen(polinomio)];
    int i, j, k=0;
    int condicional = 0;


    for(i=0; i < strlen(polinomio); i++){ //Itera a string(polinômio) inteiro.

        memset(aux, 0, sizeof(aux)); //Coloca '\0' na string inteira.
        memset(aux_exp, 0, sizeof(aux_exp)); //Coloca '\0' na string inteira.
        
        //Vai colocando o coeficiente na string aux até achar um X.
        for(j=i; !(polinomio[j] == 'x' || polinomio[j] == 'X'); j++){     

            if(polinomio[j+1] == '-' || polinomio[j+1] == '+' || polinomio[j+1] == '\0'){

                condicional = 1;
                break;  

            }                                                     
            
            aux[k++] = polinomio[j];

        }

        if(condicional == 1){

            k=0;
            
            memset(aux, 0, sizeof(aux));

            if(polinomio[i] == '-' || polinomio[i] == '+'){

                aux[k++] = polinomio[i];

                for(j=i+1; !(polinomio[j] == '-' || polinomio[j] == '+' || polinomio[j] == '\0'); j++)
                    aux[k++] = polinomio[j];

            }else{

                for(j=i; !(polinomio[j] == '-' || polinomio[j] == '+' || polinomio[j] == '\0'); j++)
                    aux[k++] = polinomio[j];

            }

        }

        if(polinomio[j+1] == '^' && condicional == 0){
            
            j=j+2; //Pula o 'X' e o '^'.
            k=0; //Reseta o K.

            //Vai colocando o expoente na string aux_exp até achar um operador, ou acabar a string.
            for(j=j; !(polinomio[j] == '-' || polinomio[j] == '+' || polinomio[j] == '\0'); j++){

                aux_exp[k++] = polinomio[j];

            }

            i=j-1; //i recebe j-1(ou seja, começa a partir do operador).
            k=0; //Reseta o K novamente.

            if(atoi(aux) != 0) //Não insere na lista monômios com coeficiente igual a 0.
                l = insere(l, atoi(aux), atoi(aux_exp)); //Insere o coeficiente e o expoente na lista.
        
        }else if(condicional == 0){

            k=0;
            i=j+1;

            if(atoi(aux) != 0) //Não insere na lista monômios com coeficiente igual a 0.
                l = insere(l, atoi(aux), 1); //Insere o coeficiente e o expoente na lista.

        }else{

            i=j-1;

            if(atoi(aux) != 0) //Não insere na lista monômios com coeficiente igual a 0.
                l = insere(l, atoi(aux), 0); //Insere o coeficiente e o expoente na lista.            

        }

        k=0;
        condicional = 0;

    }

    return l; //Retorna a lista.
}

//Função Menu. Função simples para mostrar o menu de opções.
void menu(){
    
    puts("1 - Inserir novos polinômios.");
    puts("2 - Somar Polinômios.");
    puts("3 - Substrair Polinômios.");
    puts("4 - Derivar Polinômios.");
    puts("5 - Sair.\n");
    printf("Escolha a opção desejada: ");

}

//Funções para imprimir as listas.
void imprime(Lista* l1){

    Lista* aux;

    for(aux=l1; aux!=NULL; aux=aux->prox){ //Passa por todos os nós da lista.
        
        if(aux->info > 0){ //Caso o coeficiente seja positivo.

            if(aux->exp == 0) //Expoente 0.
                printf("+%d", aux->info); //Formatação de polinômio.

            if(aux->exp == 1) //Expoente 1.
                printf("+%dx", aux->info, aux->exp); //Formatação de polinômio.

            if(aux->exp > 1) //Expoente maior que 1.
                printf("+%dx^%d", aux->info, aux->exp); //Formatação de polinômio.

        }else if(aux->info < 0){ //Caso o coeficiente seja negativo.

            if(aux->exp == 0) //Expoente 0.
                printf("%d", aux->info); //Formatação de polinômio.

            if(aux->exp == 1) //Expoente 1.
                printf("%dx", aux->info, aux->exp); //Formatação de polinômio.

            if(aux->exp > 1) //Expoente maior que 1.
                printf("%dx^%d", aux->info, aux->exp); //Formatação de polinômio.

        }

    }

    puts(""); //Pula linha.

}

//Função para somar.
void soma(Lista* l1, Lista* l2){

    int soma;

    Lista* lista_soma = NULL;
    Lista* l1_aux;
    Lista* l2_aux;

    l1_aux = l1;
    l2_aux = l2;

    while(!(l1_aux == NULL && l2_aux == NULL)){ //Enquanto as duas lista não estiverem no último nó.

        if(l1_aux != NULL && l2_aux != NULL){ //Se as duas forem diferentes de NULL.

            if (l1_aux->exp == l2_aux->exp){ //Expoentes iguais somam os coeficientes.
                soma = l1_aux->info + l2_aux->info;
                lista_soma = insere(lista_soma, soma, l1_aux->exp); //Insere a soma com o msm coef. .

                l1_aux = l1_aux->prox; //Prox. nó.
                l2_aux = l2_aux->prox; //Prox. nó.

            }else if (l1_aux->exp < l2_aux->exp){ //Expoente da segunda lista é maior.

                lista_soma = insere(lista_soma, l2_aux->info, l2_aux->exp); //Insere direto o coef. e expoente da l2.
                l2_aux = l2_aux->prox; //Prox. nó.

            }else if (l1_aux->exp > l2_aux->exp){ //Expoente da primeira lista é maior.

                lista_soma = insere(lista_soma, l1_aux->info, l1_aux->exp); //Insere direto o coef. e expoente da l1.
                l1_aux = l1_aux->prox; //Prox. nó.
            }

        }else{

            if (l1_aux == NULL){ //Último nó da l1.

                lista_soma = insere(lista_soma, l2_aux->info, l2_aux->exp); //Insere direto o coef. e expoente da l2.
                l2_aux = l2_aux->prox; //Prox. nó.

            }else if (l2_aux == NULL){ //Último nó da l2.

                lista_soma = insere(lista_soma, l1_aux->info, l1_aux->exp); //Insere direto o coef. e expoente da l1.
                l1_aux = l1_aux->prox; //Prox. nó.
            }
        }

    } 
    
    imprime(lista_soma); //Imprime o polinômio resultante.
    free_(lista_soma); //Libera a lista de soma.

    puts("Aperte enter para continuar...");
    getchar();
}

//Função para subtração. a função de subtração é análoga à de soma. Porém, as poucas diferenças estão comentadas.
void subtracao(Lista* l1, Lista* l2){

    int sub;

    Lista* lista_sub = NULL;
    Lista* l1_aux;
    Lista* l2_aux;

    l1_aux = l1;
    l2_aux = l2;

    while(!(l1_aux == NULL && l2_aux == NULL)){

        if(l1_aux != NULL && l2_aux != NULL){

            if (l1_aux->exp == l2_aux->exp){
                sub = l1_aux->info - l2_aux->info; //Em vez de somar os coeficientes, subtrair.
                lista_sub = insere(lista_sub, sub, l1_aux->exp);

                l1_aux = l1_aux->prox;
                l2_aux = l2_aux->prox;

            }else if (l1_aux->exp < l2_aux->exp){

                lista_sub = insere(lista_sub, (-1*l2_aux->info), l2_aux->exp); /*Aqui seria algo como: 0-2. Então o coef.
                                                                                é multiplicado por -1, para ficar neg.*/
                l2_aux = l2_aux->prox;

            }else if (l1_aux->exp > l2_aux->exp){


                lista_sub = insere(lista_sub, l1_aux->info, l1_aux->exp);
                l1_aux = l1_aux->prox;
            }

        }else{

            if (l1_aux == NULL){

            lista_sub = insere(lista_sub, (-1*l2_aux->info), l2_aux->exp); //Multiplica por -1 aqui também.
            l2_aux = l2_aux->prox;

            }else if (l2_aux == NULL){

            lista_sub = insere(lista_sub, l1_aux->info, l1_aux->exp);
            l1_aux = l1_aux->prox;
            }
        }

    } 

    imprime(lista_sub); //Imprime o polinômio resultante.
    free_(lista_sub); //Libera a lista.

    puts("Aperte enter para continuar...");
    getchar();
}

//Função para derivar.
void deriva(Lista* l){

    int coeficiente;
    int expoente;

    Lista* lista_derivada = NULL;
    Lista* l_aux;

    l_aux = l;

    while(l_aux != NULL){

        coeficiente = l_aux->info * l_aux->exp; //Regra do tombo.
        expoente = l_aux->exp -1 ; //Regra do tombo.

        lista_derivada = insere(lista_derivada, coeficiente, expoente); //Insere os novos coeficientes e expoentes.

        l_aux = l_aux->prox; //Prox. nó.       

    }   

    imprime(lista_derivada); //Mostra o polinômio derivado.
    free_(lista_derivada); //Libera a lista.

    puts("Aperte enter para continuar...");
    getchar();

}

//Função para limpar o buffer do scanf.
void limpa_buffer(){ 

  while ( getchar() != '\n' );

}

//Main
int main(){

    //Localizando o idioma para pt-br.
    setlocale(LC_ALL, "portuguese_Brazil");
    
    char polinomio1[MAX], polinomio2[MAX];
    int opcao, opcao_derivada;

    //'\0' para todas posições das strings.
    memset(polinomio1, 0, sizeof(polinomio1));
    memset(polinomio2, 0, sizeof(polinomio2));

    Lista* l1;
    Lista* l2;

    l1 = NULL;
    l2 = NULL;

    //Instruções.
    puts("\n-------------------------------------------------------------");
    puts("Os polinômios devem ser digitado no formato: coefX^exp.\n\nNão digite nenhum espaço.\n\nRepresentar, também, os expoentes 1 e 0, assim: coefx^1 e coefx^0, e não assim: coefx e coef, respectivamente.");
    puts("-------------------------------------------------------------\n");
    puts("Digite enter para continuar.");
    getchar();

    //Limpa o terminal ou o cmd.
    system("clear || cls");

    //Loop até escolher a opção desejada ser escolhida.
    do{
        puts("\n------------MENU-------------");

        //Mostra os polinômios digitados, já em ordem decrescente de expoentes.
        printf("Polinômio 1: "); 
        imprime(l1);
        printf("Polinômio 2: ");
        imprime(l2);

        puts("");
        menu();

        scanf("%d", &opcao);
        limpa_buffer();

        //Limpa o terminal ou o cmd.
        system("clear || cls");

        //Switch para direcionar para as funções corretas, partindo da opção selecionada.
        switch (opcao){

            case 1:

                if(l1 == NULL && l2 == NULL){ //Caso as listas sejam NULL, ou seja, primeira vez rodando o programa.

                    polinomio(polinomio1, polinomio2); //Recebe os polinômios.

                    valida(polinomio1);
                    valida(polinomio2);

                    //Transoforma eles e insere nas respectivas listas.
                    l1 = transf_pol(polinomio1, l1); 
                    l2 = transf_pol(polinomio2, l2);

                } else{ //Caso não seja a primeira vez.

                    //Desaloca as listas.
                    l1 = free_(l1);
                    l2 = free_(l2);

                    //E depois faz os processos de criar uma nova lista.
                    polinomio(polinomio1, polinomio2);

                    valida(polinomio1);
                    valida(polinomio2);
                    
                    l1 = transf_pol(polinomio1, l1);
                    l2 = transf_pol(polinomio2, l2);

                }
                break;

            case 2:

                if(l1 == NULL && l2 == NULL){ //Caso as listas sejam NULL, ou seja, primeira vez rodando o programa.

                    puts("ERRO! Não foram inseridos polinômios.");
                    break;

                }else{ //Senão.

                    printf("\nSoma entre os dois polinômios: "); //Chama a função de soma.
                    soma(l1, l2);

                }
                break;
            
            case 3:

                if(l1 == NULL && l2 == NULL){ //Caso as listas sejam NULL, ou seja, primeira vez rodando o programa.

                    puts("ERRO! Não foram inseridos polinômios.");
                    break;

                }else{ //Senão.
                    
                    printf("\nSubtração entre os dois polinômios: "); //Chama a função de subtração.
                    subtracao(l1, l2);
                    
                }
                break;

            case 4:

                if(l1 == NULL && l2 == NULL){ //Caso as listas sejam NULL, ou seja, primeira vez rodando o programa.

                    puts("ERRO! Não foram inseridos polinômios.");
                    break;

                }else{ //Senão.

                    puts("Qual polinômio você quer derivar: ");
                    scanf("%d", &opcao_derivada);
                    limpa_buffer();

                    if(opcao_derivada == 1){

                        //Chama a função de derivar.
                        printf("\nDerivada do primeiro polinômio: ");
                        deriva(l1); 

                    }else if(opcao_derivada == 2){
                        
                        //Chama a função de derivar.
                        printf("Derivada do segundo polinômio: ");
                        deriva(l2);
                    
                    }else{

                        puts("Polinômio inexistente, selecione o polinômio 1 ou 2.");

                    }
                    
                    
                }
                break;

            case 5: //Caso esolhar sair do programa.

                //Libera as listas principais.  
                //Obs.: As listas de soma, subtração e derivada são liberadas em suas respectivas funções.
                l1 = free_(l1);
                l2 = free_(l2);

                puts("Saindo do programa...");  
                break;

            default: //Caso seja escolhida uma uma opção que não exista no menu.
                
                puts("Opção inválida!");
                break;

            }

    }while (opcao != 5); //Acaba com o loop caso a opção 5(sair) seja escolhida.

    return 0;
}