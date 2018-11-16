/****************************************
*     Projeto Googol - PE - 2018        *
*           Gabrielle Arruda            *
*             Luigi Perillo             *
*           Vinicius Teixeira           *
*****************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1003

int sanitizeNumerao(char numerao[MAX_SIZE]);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 *  Todas as funcoes abaixo somente funcionam se o numerao estiver sanitizado, ou seja, *
 *  tenha passado pela funcao "sanitizeNumerao".                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void imprimeNumerao(char numerao[MAX_SIZE], int tam);
int soma(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2, char **numeraoResultado);

int main() {
    char numerao1[MAX_SIZE], numerao2[MAX_SIZE], operador = ' ', **numeraoResultado = NULL;
    int tam1 = 0, tam2 = 0, tam3 = 0;
    
    numeraoResultado = malloc(sizeof(char));

    while(operador != '0'){
        /* primeira leitura (numero ou fim) */
        scanf("%s", numerao1);
        /* verifica se numero ou fim para continuar*/
        if(numerao1[0] != 'F' && numerao1[1] != 'I' && numerao1[2] != 'M') {
            scanf("%s", numerao2);
            scanf(" %c", &operador);
        
            tam1 = sanitizeNumerao(numerao1);
            tam2 = sanitizeNumerao(numerao2);        
    
            switch(operador){
                case '+': tam3 = soma(numerao1, tam1, numerao2, tam2, numeraoResultado);
                          break;
                default: printf("Operador invalido!");
            }
            
            imprimeNumerao(*numeraoResultado, tam3);
            
        } else {
            /* define operador como zero para encerrar aplicacao */
            operador = '0';
        }
    }
    
    free(numeraoResultado[0]);
    free(numeraoResultado);

    return 0;
}

/* Sanitiza os numeros em ordem no menos significativo para o mais significativo
   >>preserva o sinal de negativo na frente do numerao<< 
   Recebe:
    char numerao: vetor de char corresponde ao numerao
   Retorna: 
    int size: tamanho do numerao sanitizado */
int sanitizeNumerao(char numerao[MAX_SIZE]) {
    char numerao_copy[MAX_SIZE];
    int i = 0, size = -1;
    
    /* encontra o tamanho do numerao */
    while(size == -1 && i < MAX_SIZE) {
        if(numerao[i] == '\0'){
           size = i;
           break;   
        }
        i++;
    }
    
    /* cria um espelho */
    for(i = 0; i < size; i++) {
        numerao_copy[i] = numerao[i];
    }
    
    /* reordena do menos significativo para o mais significativo */
    if(numerao[0] == '-') {
        /* mantem o menos para simbolizar o numero negativo */
        for(i = 1; i < size; i++){
            numerao[i] = numerao_copy[size - i];
        }
    } else {
        for(i = 0; i < size; i++){
            numerao[i] = numerao_copy[(size - 1) - i];
        }
    }
        
    return size;  
}

/* Imprime numerao sanitizado 
   Recebe:
    char numerao: vetor de char corresponde ao numerao a ser impresso
    int tam: inteiro correspondente ao tamanho do numerao
   Retorna: 
    nada    */
void imprimeNumerao(char numerao[MAX_SIZE], int tam) {
    int i;
    /* caso o numero negativo, imprime o sinal antes do numero */
    if(numerao[0] == '-'){
        printf("%c", numerao[0]);
        for(i = 0; i < tam; i++) {
            printf("%c", numerao[tam - i]);
        }
    }else {
        for(i = 0; i < tam; i++) {
            printf("%c", numerao[(tam - i) - 1]);
        }
    }

    printf("\n");
}

/*
   Recebe: 
    char numerao1: vetor de char correspondente ao primeiro numero
    int n1: tamanho do vetor numerao1
    char numerao2: vetor de char corresponde ao segundo numero
    int n2: tamanho do vetor numerao2
    char **numeraoResultado: ponteiro de ponteiro de char que contera o resultado da soma
   Retorna:
    int tam: tamanho do numeraoResultado  */
int soma(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2, char **numeraoResultado) {
    int i, tam = 0, calculated = 0, rest = 0;    

    /* define o tamanho preliminar do array */
    tam = tam1 > tam2 ? tam1 : tam2;
    
    /* aloca memoria para o array */
    *numeraoResultado = malloc(tam * sizeof(char));
    
    /* verifica se alocacao de memoria foi efetuada */
    if(*numeraoResultado) {
        /* percorre ambos os vetores somando e iterando o resto */
        for(i = 0; i < tam; i++) {
            calculated = rest;
            if (i < tam1) {
                calculated += (numerao1[i] - '0');    
            }
            if (i < tam2) {
                calculated += (numerao2[i] - '0');
            }
            if(calculated > 9) {
                calculated -= 10;
                rest = 1;
            } else {
                rest = 0;
            }
            
            *numeraoResultado[i] = '0' + calculated;   
        }
        
        /* realoca aumentanto o tamanho do vetor para incluir o resto que sobrou */
        if(rest > 0) {
            tam++;
            *numeraoResultado = (char *) realloc(*numeraoResultado, tam * sizeof(char));
            if(*numeraoResultado) {
                *numeraoResultado[tam - 1] = '1';
            }else {
                return -1;
            }
        }
    } else {
        return -1;
    }
   
    return tam;
}
