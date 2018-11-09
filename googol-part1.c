/****************************************
*     Projeto Googol - PE - 2018        *
*           Gabrielle Arruda            *
*             Luigi Perillo             *
*           Vinicius Teixeira           *
*****************************************/
#include <stdio.h>

#define MAX_SIZE 1003

int tamNumerao(char numerao[MAX_SIZE]);

/* return tamNumeraoResultado */
int soma(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2, char *numeraoResultado);

int main() {
    char numerao1[MAX_SIZE], numerao2[MAX_SIZE], operador = ' ', *numeraoResultado; 
    int tam1 = 0, tam2 = 0, tam3 = 0
    
    while(operador != '0'){
        /* primeira leitura (numero ou fim) */
        scanf("%s", numerao1);
        /* verifica se numero ou fim para continuar*/
        if(numerao1[0] != 'F' && numerao1[1] != 'I' && numerao1[2] != 'M') {
            scanf("%s", numerao2);
            scanf(" %c", &operador);
        
            tam1 = tamNumerao(numerao1);
            tam2 = tamNumerao(numerao2);
            
            switch(operador){
                case '+': tam3 = soma(numerao1, tam1, numerao2, tam2, numeraoResultado);
                          break;
                default: printf("Operador invalido!");
            }
            
            printf("%s", numeraoResultado);
            
        } else {
            /* define operador como zero para encerrar aplicacao */
            operador = '0';
        }
    }
    
    return 0;
}

int tamNumerao(char numerao[MAX_SIZE]){
    int i = 0;

    while(i < MAX_SIZE) {
        if(numerao[i] == '\0'){
           return i;
        }
        i++;
    }
    return 0;  
}
