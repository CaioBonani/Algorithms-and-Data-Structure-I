
//Bibliotecas utilizadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
//====================================================================================================================//

//Definindo o m�ximo de caracteres para as strings. Para n�meros maiores que 100 d�gitos, aumentar aqui!
#define MAX 100
//====================================================================================================================//


//Criando as 3 structs(listas).
struct lista {

    int info; //Onde o conte�do ser� armazenado.

    struct lista *prox; //Apontando para o ponteiro do pr�ximo n� da lista.

};
struct lista2 {

    int info2;

    struct lista2 *prox2;

};
struct lista3 {

    int info3;

    struct lista3 *prox3;

};

typedef struct lista Lista;
typedef struct lista2 Lista2;   //Usando typedef para a chamada das structs serem mais f�ceis.
typedef struct lista3 Lista3;
//====================================================================================================================//


//Fun��es para inicializar as listas.
Lista* inicializa(){

    return NULL; //Retornando NULL para o primeiro n�.

}
Lista2* inicializa_2(){

    return NULL;

}
Lista3* inicializa_3(){

    return NULL;

}
//====================================================================================================================//


//Fun��es para inserir os dados nas 3 listas.
Lista* insere(Lista* l, int i){

    Lista* novo = (Lista*) malloc(sizeof(Lista)); //Sempre que entrar na fun��o cria um novo n�.

    novo->info = i;

    novo->prox = l;

    return novo; // Retorna o n�.
}
Lista2* insere_2(Lista2* l2, int i){

    Lista2* novo2 = (Lista2*) malloc(sizeof(Lista2));

    novo2->info2 = i;

    novo2->prox2 = l2;

    return novo2;
}
Lista3* insere_3(Lista3* l3, int i){

    Lista3* novo3 = (Lista3*) malloc(sizeof(Lista3));

    novo3->info3 = i;

    novo3->prox3 = l3;

    return novo3;

}
//====================================================================================================================//


//Fun��es de free(desalocar mem�ria) das 3 listas.
void libera(Lista* l){

    Lista* p = l;
    Lista* t;

    while(p != NULL){

        t = p->prox;

        free(p); //Faz um loop pra ir dando free em cada n�, at� que ele chegue no primeiro n�(NULL).

        p = t;

    }

}
void libera_2(Lista2* l2){

    Lista2* p = l2;
    Lista2* t;

    while(p != NULL){

        t = p->prox2;

        free(p);

        p = t;

    }

}
void libera_3(Lista3* l3){

    Lista3* p = l3;
    Lista3* t;

    while(p != NULL){

        t = p->prox3;

        free(p);

        p = t;

    }

}
//====================================================================================================================//


//Fun��o para as mostrar as listas.
void imprime(Lista* l){

    Lista* aux;

    printf("\n(** LISTA INVERTIDA **)\nN�mero 1:  ");

    for(aux = l; aux != NULL; aux = aux->prox) //Loop at� chegar no primeiro n�, printa cada elemento da lista.
        printf("| %d", aux->info);
    printf(" |");
}
void imprime_2(Lista2* l2){

    Lista2* aux2;

    printf("\n\n(** LISTA INVERTIDA **)\nN�mero 2:  ");

    for(aux2 = l2 ; aux2 != NULL; aux2= aux2->prox2)
        printf("| %d", aux2->info2);
    printf(" |");
}
void imprime_3(Lista3* l3){

    Lista3* aux3;

    char resultado[MAX];
    int i;

    printf("\n\nResultado:\n\n(FORMA DE LISTA):  ");

    for(aux3 = l3, i=0; aux3 != NULL; aux3 = aux3->prox3, i++){
        printf("| %d", aux3->info3);
        resultado[i] = aux3->info3 + '0'; //Aqui vai salvando os digitos na string.
    }
    printf(" |");

    resultado[i] = '\0'; //"Termina" a string para n�o ter lixo de mem�ria

    printf("\n\n(FORMATADO): %s\n\n", resultado); //Printa o resultado formatdo, al�m da forma em lista.

}
//====================================================================================================================//


//Fun��o para transformar um caractere num�rico em inteiro.
int numero_int(char numero){
    int num_int;

    num_int = numero - '0';

    return num_int;
}
//====================================================================================================================//


//Fun��o para calcular o resultado final.
Lista3* soma(Lista* l, Lista2* l2){

    int valor, n=0;
    char c[3];

    Lista3* l3;

    Lista2* aux2;
    Lista* aux;

    l3 = inicializa_3(); //Inicializando a terceira lista(resultado).

    for(aux = l, aux2 = l2; aux != NULL && aux2 != NULL; aux = aux->prox, aux2= aux2->prox2){ //At� que as duas sejam NULL, repetir o FOR.

        valor = aux->info + aux2->info2 + n; //Soma os dados das duas listas + "n"(no primeiro loop n=0).

        if(valor >= 10){ //Caso a soma tenha dado mais de 10.

            sprintf(c, "%d", valor); //Passo a soma para uma string.

            valor = c[1] - '0'; //Pego o segundo digito dela e atribuo � vari�vel valor.

            n = c[0] - '0'; //"n" recebe o primeiro digito da string.

        }else if(valor < 10){

            n = 0; //Se o valor n�o for 10 ou maior, "n" continua como 0.

        }

        l3 = insere_3(l3, valor); //Insere o valor da soma na terceira lista.

    }

    if(n == 0){

    }else if(n != 0){ //Caso o "n" n�o seja 0.

        l3 = insere_3(l3, n); //Inserir "n" na lista, tamb�m.

    }

    return l3;
}
//====================================================================================================================//


//Fun��o main.
int main(){

    //Localizando o idioma para pt-br.
    setlocale(LC_ALL, "portuguese_Brazil");
    //====================================================================================================================//

    //Declara��o de vari�veis.
    Lista* l1;
    Lista2* l2;
    Lista3* l3;

    char char1[MAX], char2[MAX];

    int i, j, x;
    int tam, tam2;
    int num[MAX];
    //====================================================================================================================//

    //Inicializando as 2 listas de entrada, a terceira lista ser� inicializada na fun��o soma().
    l1 = inicializa();
    l2 = inicializa_2();
    //====================================================================================================================//

    //"Pegando os dois n�meros que ser�o somados.
    printf("Digite o primeiro n�mero: ");
    fgets(char1, MAX, stdin);
    char1[strcspn(char1, "\n")] = 0; //Tirando o '\n' que o fgets deixa no final da string.

    printf("Digite o segundo n�mero: ");
    fgets(char2, MAX, stdin);
    char2[strcspn(char2, "\n")] = 0;

    tam = strlen(char1); //Salvando o tamanhdo da string1.
    tam2 = strlen(char2); //Salvando o tamanhdo da string2.
    //====================================================================================================================//

    //Vendo se foram digitados somente n�meros inteiros positivos.
    for(i=0; i<tam; i++){

        if(isdigit(char1[i]) == 0){
            puts("\nDigite somente n�meros inteiros postivos.");
            exit(1);
        }

    }
    for(i=0; i<tam2; i++){

        if(isdigit(char2[i]) == 0){
            puts("\nDigite somente n�meros inteiros positivos.");
            exit(1);
        }
    }
    //====================================================================================================================//

    /*
        Comparando os tamanhos das strings, e caso uma seja menor que a outra colocar 0 � esquerda, para deixar as duas
        strings com o mesmo tamanho, ou seja, duas listas de mesmo tamanho!
    */
    if(tam<tam2){

        for(j=0; j<tam2-tam; j++) //Completa o vetor num�rico com 0 � esquerda.
            num[j] = 0;

        for(j=tam2-tam, i=0; i< tam2; j++, i++) //Coloca os n�meros ap�s o zero.
            num[j] = char1[i] -'0';

        for(j=0; j<tam2; j++)
            char1[j] = num[j] +'0'; //Passa o digitos para a string, caractere por caractere.

        char1[j] = '\0'; //"Finaliza" a string para n�o ocorrer problemas inesperados com lixo de mem�ria.

        tam = tam2; //Os dois tamanhos agora s�o iguais.

    }
    if(tam2<tam){

        for(j=0; j<tam-tam2; j++)
            num[j] = 0;

        for(j=tam-tam2, i=0; i< tam; j++, i++)
            num[j] = char2[i] -'0';

        for(j=0; j<tam; j++)
            char2[j] = num[j] +'0';

        char2[j] = '\0';

        tam2 = tam;

    }
    //====================================================================================================================//


    /*
        Transformando os caracteres em inteiro(fun��o numero_int) e passando como argumento(fun��es insere e insere_2) para ser
        inserido nas listas.
    */
    for(i=0; i < tam; i++){

        x = numero_int(char1[i]); //Retorno da fun��o � um digito inteiro.
        l1= insere(l1, x); //Passa esse inteiro para ser inserido da lista.

    }
    for(i=0; i < tam2; i++){

        x = numero_int(char2[i]);
        l2= insere_2(l2, x);

    }
    //====================================================================================================================//

    //"Pegando" o retorno da fun��o soma, a terceira lista(resultado) e atribuindo ao ponteiro l3.
    l3 = soma(l1, l2);
    //====================================================================================================================//


    //Chamando a fun��o de imprimir o resultado, e passando o ponteiro l3(guarda a terceira lista) como par�metro.
    imprime(l1);
    imprime_2(l2);
    imprime_3(l3);
    //====================================================================================================================//


    //Liberando as 3 listas.
    libera(l1);
    libera_2(l2);
    libera_3(l3);
    //====================================================================================================================//

    return 0;
}
