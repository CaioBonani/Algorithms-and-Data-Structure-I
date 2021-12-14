
//Bibliotecas usadas.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <math.h>

//Definindo o tamanho máximo da pilha e dos char vetores.
#define max 99
#define MAX_PILHA 100

//Definindo a estrutura da pilha.
typedef struct {

    char vetor[MAX_PILHA]; //Pilha principal.

    int resultado[MAX_PILHA]; //Pilha secundária.

    int topo; //Topo da pilha principal.

    int topo_p_resul; //Topo da pilha secundária.

} Pilha;

//Função para criar a pilha.
Pilha* criar(){

    Pilha* pilha;
    pilha = (Pilha *)malloc(sizeof(Pilha)); //Aloca espaço para uma struct pilha.

    pilha->topo = -1; //Inicializando o topo com -1.

    pilha->topo_p_resul = -1; //Inicializando o topo com -1.

    return pilha; //Retorna a pilha criada.
}

//Função para desalacoar a memória da pilha.
Pilha* desalocar(Pilha* pilha){

    free(pilha);

    return(NULL);

}

//Função push(empilhar) da pilha principal.
int push(Pilha* pilha, char caractere){

    if(pilha->topo >= MAX_PILHA-1){

        return -1; //Caso a pilha esteja cheia, sai da função.
    }

    (pilha->topo)++; //Incrementa o topo(de -1 vai para 0).
    pilha->vetor[pilha->topo] = caractere; //Posição 0 da pilha recebe um caractere.

    return 0;
}

////Função push(empilhar) da pilha secundária.
int push_int(Pilha* pilha, int valor){

    if(pilha->topo_p_resul >= MAX_PILHA-1){

        return -1; //Caso a pilha esteja cheia, sai da função.
    }

    (pilha->topo_p_resul)++; //Incrementa o topo(de -1 vai para 0).
    pilha->resultado[pilha->topo_p_resul] = valor; //Posição 0 da pilha recebe um número inteiro.

    return 0;
}

//Função pop(desempilhar) da pilha principal.
char pop(Pilha* pilha){

    char caractere;

    if(pilha->topo < 0){

        return EXIT_FAILURE; //Caso a pilha esteja vazia, returna erro.
    }

    caractere = pilha->vetor[pilha->topo]; //Variável caractere recebe o char do topo da pilha.
    (pilha->topo)--; //Decrementa a pilha.

    return(caractere); //Função retorna o char.
}

//Função pop(desempilhar) da pilha secundária.
int pop_int(Pilha* pilha){

    int valor;

    if(pilha->topo_p_resul < 0){

        return EXIT_FAILURE; //Caso a pilha esteja vazia, returna erro.

    }

    valor = pilha->resultado[pilha->topo_p_resul]; //Variável valor recebe o valor do topo da pilha.
    (pilha->topo_p_resul)--; //Decrementa a pilha.

    return (valor); //Função retorna o valor.
}

//Função para saber se o caractere é um operador.
int operador(char operador){

    switch(operador){ //Se o caractere passado como argumento, for um operador, a função retorna 1./

        case '^':

            return 1;

        break;

        case '/':

            return 1;

        break;

        case '*':

            return 1;

        break;

        case '+':

            return 1;

        break;

        case '-':

            return 1;

        break;

        default:

            return 0; //Caso não seja um operador, retorna 0;
    }

}

//Função para saber a prioridade dos operadores.
int prioridade(char operador){

    switch(operador){ 

        case '^':

            return (3); //Caso o operador seja expoente a função retorna 3.

        break;

        case '*':

            return(2);

        break;
                        /*
                            Caso o operador seja '*' ou '/' retorna 2.
                        */
        case '/':

            return(2);

        break;
                        
        case '+':
        
            return(1);

        break;
                        /*
                            Caso o operador seja '+' ou '-' retorna 1;
                        */
        case '-':

            return(1);

        break;

    
        default:

            return(0); //Caso não seja um operador retorna 0;
    }

}

//Função para transformar a expressão em posfixa.
int infix_posfix(Pilha pilha, char infixa[], char posfixa[]){

    int i=0, j=0;
    char c, aux;

    push(&pilha, '~'); //Coloca um caractere auxiliar na pilha.
    strcat(infixa, "~"); //Coloca um caractere auxiliar no fim da string.

    for(i=0; infixa[i] != '\0'; i++){ //Itera a string.

        c = infixa[i]; //Variável "c" recebe o caractere de "infixa" na posição indicada
        
        if(isdigit(c)){ 

            posfixa[j++] = c; //Se for digito a string posfixa recebe esse número.

        }else if(c == ' '){

            continue; //Caso seja um espaço ele ignora, e pula para o próximo caracter.
            
        }else if(operador(c)==1){ //Se for um operador...

            aux = pop(&pilha); //"aux" pega o último char da pilha.

            while(operador(aux) == 1 && prioridade(aux) >= prioridade(c)){ //Enquanto o "aux" for um digito e a prioridade de "aux" for >= a prioriade de "c"

                posfixa[j++] = aux; //Posfixa recebe "aux".

                aux = pop(&pilha); //"aux" pega o último char da pilha.

            }

            push(&pilha, aux); //Empilha o "aux".

            push(&pilha, c); //Empilha o "c".

        }else if(c == '~'){ //Se for um til, ou seja, final da string...

            aux = pop(&pilha); //"aux" pega o último char da pilha.

            while(aux != '~'){ //Enquanto o "aux" for diferente de til.

                posfixa[j++] = aux; //posfixa recebe o char q "aux" guarda.

                aux = pop(&pilha); //"aux" pega o último char da pilha.

            }
            
        }else{ //Qualquer outra situação...

            return EXIT_FAILURE; //Ocorreu um erro e o programa fecha, retornando erro.

        }

    }

    posfixa[j] = '\0'; //Add final de string na infixa.

    return 0;
}

//Função para calcular a expressão na forma posfixa.
void calc(Pilha pilha, char posfixa[]){

    int resultado = 0;

    int i=0;

    int num, num1, num2;

    char c;

    c = posfixa[i]; //Variável recebe os caracteres da string posfixa.

    while(c != '\0'){ //Itera a string até o final dela.

        if(operador(c) == 0){ //Se não for um operador.

            num = c - '0'; //Transforma o char em int.

            push_int(&pilha, num); //Empilha esse número.

        }else{ //Caso seja um operador.
            
            switch(c){ /*Os seguintes "cases" são cópias um do outro, 
                        mudando somente a operação feita no "resultado".*/

                case '+':

                    num2 = pop_int(&pilha); //Num2 recebe o int que está no topo da pilha(desempilha).

                    num1 = pop_int(&pilha); //Num1 recebe o int que está no topo da pilha(desempilha).

                    resultado = num1 + num2; //Resultado é a operação entre num1 e num2.

                    push_int(&pilha, resultado); //Empilha o resultado na pilha.


                break;

                case '-':
                    
                    num2 = pop_int(&pilha);

                    num1 = pop_int(&pilha);

                    resultado = num1 - num2;

                    push_int(&pilha, resultado);

                break;

                case '*':

                    num2 = pop_int(&pilha);

                    num1 = pop_int(&pilha);

                    resultado = num1 * num2;

                    push_int(&pilha, resultado);

                break;

                case '/':

                    num2 = pop_int(&pilha);

                    num1 = pop_int(&pilha);

                    resultado = num1 / num2;

                    push_int(&pilha, resultado);

                break;

                case '^':

                    num2 = pop_int(&pilha);

                    num1 = pop_int(&pilha);

                    resultado = pow(num1, num2); //No caso de exponenciação, usa a função pow() da <math.h>.

                    push_int(&pilha, resultado);

                break;

            }

        }

        i++; //Incrementa i;

        c = posfixa[i]; //C recebe o char da posição incrementada.
    }

    resultado = pop_int(&pilha); //Desempilha o resultado.

    printf("\nResultado da expressão: %d\n\n", resultado); //Printa o resultado.

    return;
}

//Função main
int main(){

    setlocale(LC_ALL, " "); //Localiza o idioma para o mesmo idioma que o Sistema Operacional está.

    char infixa[max], posfixa[max];

    int i, j, correto = 0;

    Pilha* pilha; 
    pilha = criar(); //"pilha" recebe "pilha"(retorno da função criar();).

    puts("\nDigite a expressão na forma infixa: ");
    fgets(infixa, max, stdin); //Pega a expressão na forma infixa.
    infixa[strcspn(infixa, "\n")] = 0; //Tira o /n que a função FGETS deixa ao final da string.

    for(i=0; infixa[i] != '\0'; i++){ //Itera a string infixa.

        if((infixa[i]>= 48 && infixa[i] <= 57) || (operador(infixa[i]) == 1) || infixa[i] == ' '){

            continue; //Caso seja um número de 0 à 9 ou um operador, pula para o próximo caractere da string.

        }else{

            correto = 1; //Caso não seja, correto recebe 1.

        }
    }


    for(i=0; infixa[i] != '\0'; i++){  //Itera a string infixa.

        if(((infixa[i]>= 48 && infixa[i] <= 57) && (infixa[i+1]>= 48 && infixa[i+1] <= 57)) || ((infixa[i]>= 48 && infixa[i] <= 57) && (infixa[i+1] == ' ') &&(infixa[i+2]>= 48 && infixa[i+2] <= 57))){

            correto = 1; //Caso existam dois dois números seguidos, correto recebe 1.

        }

        if((operador(infixa[i]) == 1 && operador(infixa[i+1]) == 1) || (operador(infixa[i]) == 1 && (infixa[i+1] == ' ') && (operador(infixa[i+2])) == 1)){

            correto = 1; //Caso existam dois operadores seguidos, correto recebe 1.

        }

        if(infixa[i] == ' ' && infixa[i+1] == ' '){

            correto =1;


        }

        j = i; //"j" recebe o valor de "i" referente ao último caractere da string.

    }
    

    if(infixa[j]=='+' || infixa[j]=='/' || infixa[j]=='*' || infixa[j]=='-' || infixa[j]=='^'){

        correto = 1; //Caso a string termine com um operador, correto recebe 1.
        
    }


    if(correto == 1){

        puts("\nExpressão digitada incorretamente.");

        return -1; //Caso correto seja 1, a expressão foi digitada incorretamente, encerra o programa com erro.

    }


    infix_posfix(*pilha, infixa, posfixa); //Chamada da função que transforma a expressão infixa em posfixa.

    puts("\nExpressão na forma posfixa: ");
    puts(posfixa); //Imprime a expressão na forma posfixa.

    calc(*pilha, posfixa); //Chamada da função que calcula a expressão na forma posfixa.

    desalocar(pilha); //Desaloca a memória.

    return 0;

}