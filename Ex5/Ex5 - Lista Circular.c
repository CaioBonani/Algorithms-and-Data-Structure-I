
//Bibliotecas utilizadas.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

//Tamanho máximo das strings.
#define MAX 51

//Criando a struct da lista.
struct lista{

    char info;
    struct lista* prox;

};
typedef struct lista Lista;


//Função para inserir na lista.
Lista* insere(Lista* ultimo, char c){

    Lista* novo;
    novo = (Lista*)malloc(sizeof(Lista));

    novo->info = c;

    //ultimo == NULL seria a primeira vez que inserimos um dado na lista.
    if(ultimo == NULL){
        
        ultimo = novo;
        novo->prox = novo;

    }else{
        
        novo->prox = ultimo->prox;
        ultimo->prox = novo;

    }

    return ultimo;
}

//Função para remover o buffer causado pelo scanf.
void flush(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

//Função para comparar a string com as substrings.
void compara (Lista* lista, char sub[][MAX], int qtd){

    //Variáveis.
    int i=0, j=0, k=0, reset=0;
    int contador=0, num=0, pontuacao=MAX;
    char stringajuda[MAX];

    Lista* aux;
    Lista* p[MAX]; //Vetor para guardar endereços.
    
    //For principal, qtd é a quantidade de substrings.
    for(i=0; i<qtd; i++){

        //"Reseta" a string.
        for(reset=0; reset<MAX; reset++)
            stringajuda[reset] = '\0';

        aux = lista->prox;
        k=0;
        contador=0;

        //Passará por todas as letras da string.
        do{

            //Se o char do nó da lista for igual a primeira letra da substring.
            if(aux->info == sub[i][0]){

                p[k] = aux;//Salva o endereço do nó.
                k++;
                contador++;

            }

            aux = aux->prox;

        }while(aux != lista->prox);//Enquanto não dar uma "volta" completa na lista.

        //For que fará o loop para todas as ocorrências de letras iguais(contador).
        for(k=0; k<contador; k++){

            j=0;
            aux = p[k];//Aux pega o endereço da ocorrência.

            /*A partir da letra ocorrência, vai olhando pra ver se as próximas
            letras são iguais a da substring.*/
            do{
                
                //Caso seja NULL (primeiro nó) pula ele.
                if(aux->info != '\00'){

                    stringajuda[j] = aux->info;//Vai salvando as letras na string.
                    j++;
                    aux = aux->prox;

                }else
                    aux = aux->prox;
                
            }while(j<strlen(sub[i]));/*Faz esse loop até j ser igual o tamanho da susbtring.*/

            stringajuda[j] = '\0';//Coloca um fim na string.

            if(strcmp(stringajuda, sub[i]) == 0)//Se a string de ajuda for igual a substring.
                num = num +1;//Ela era cíclica.

            if(pontuacao > strlen(stringajuda))/*Se a pontuação anterior for maior que o tamanho da string.*/
                pontuacao = strlen(stringajuda);//Muda a pontuação.
        }
    }

    printf("\nNúmero de strings cíclicas: %d\n", num);

    if(num == 0)
        pontuacao = 0;
    
    printf("Menor pontuação: %d\n\n", pontuacao);
    
}

//Função main.
int main(){

    //Localizando o idioma para pt-br.
    setlocale(LC_ALL, "portuguese_Brazil");

    //Declaração de variáveis.
    Lista* lista;
    int num_substrings, i, tam_substrings;
    char string[MAX], auxiliar[MAX];

    //Inicializando a lista.
    lista = NULL;

    //Guardando a string principal.
    printf("Digite a string principal: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = 0;

    //Perguntando quantas substrings terá. 
    printf("\nDigite quantas substrings você terá: ");
    scanf("%d", &num_substrings);
    flush();

    //Declarando uma matriz para armazenar essas substrings.
    char substrings [num_substrings][MAX];

    printf("\n");

    //For para ir salvando todas substrings.
    for(i=0; i<num_substrings; i++){

        printf("Digite a substring %d: ", i+1);
        scanf("%s", substrings[i]);
        flush();

    }

    /*For para ir inserindo todas letras da string principal
    nos nós da lista*/
    for(i=strlen(string); i>=0; i--)
        lista = insere(lista, string[i]);

    //Chamando a função de comparar.
    compara(lista, substrings, num_substrings);

    //Desalocando a lista.
    free(lista);

    return 0;
}