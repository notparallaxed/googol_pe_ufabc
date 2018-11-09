/****************************************
*     Projeto Googol - PE - 2018        *
*           Gabrielle Arruda            *
*             Luigi Perillo             *
*           Vinicius Teixeira           *
*****************************************/
#include <stdio.h>

#define MAX_SIZE 1003

void imprimeNumerao(char numerao[MAX_SIZE], int tam);
int sanitizeNumerao(char numerao[MAX_SIZE]);

/* return tamNumeraoResultado */
int soma(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2, char *numeraoResultado);

int main() {
    char numerao1[MAX_SIZE], numerao2[MAX_SIZE], operador = ' ', *numeraoResultado; 
    int tam1 = 0, tam2 = 0, tam3 = 0;
    
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
            
            imprimeNumerao(numeraoResultado, tam3);
            
        } else {
            /* define operador como zero para encerrar aplicacao */
            operador = '0';
        }
    }
    
    return 0;
}

void imprimeNumerao(char numerao[MAX_SIZE], int tam) {
    int i;
    for(i = 0; i < tam; i++) {
        printf("%c", numerao[i]);
    }
}

int sanitizeNumerao(char numerao[MAX_SIZE]) {
    char numerao_copy[MAX_SIZE];
    int i = 0, size = -1;
    
    /* encontra o tamanho do numerao */
    while(size == -1 && i < MAX_SIZE) {
        if(numerao[i] == '\0'){
           size = i;
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

int soma(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2, char *numeraoResultado) {
    /*falta implementar essa bagaça aqui*/
}
