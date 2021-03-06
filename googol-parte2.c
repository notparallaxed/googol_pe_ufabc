
/****************************************
*     Projeto Googol - PE - 2018        *
*  Gabrielle Arruda  -  11201721761     *
*     Luigi Perillo - 11201722471       *
*   Vinicius Teixeira - 11201720408     *
*****************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2003

int sanitizeNumerao(char numerao[MAX_SIZE]);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*  Todas as funcoes abaixo somente funcionam se o numerao estiver sanitizado, ou seja, *
*  tenha passado pela funcao "sanitizeNumerao".                                        *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void imprimeNumerao(char numerao[MAX_SIZE], int tam);
int soma(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2);
int subtracao(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2);
int multiplicacao(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2);
int resto(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2);
int divide(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2);
int cleanZeros(char numerao[MAX_SIZE], int tam);
int addZero(char numerao[MAX_SIZE], int tam);

int main() {
   char numerao1[MAX_SIZE], numerao2[MAX_SIZE], operador = ' ';
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
                case '+': tam3 = soma(numerao1, tam1, numerao2, tam2);
                         break;
                case '-': tam3 = subtracao(numerao1, tam1, numerao2, tam2);
                         break;
                case '*': tam3 = multiplicacao(numerao1, tam1, numerao2, tam2);
                         break;
                case '/': tam3 = divide(numerao1, tam1, numerao2, tam2);
                         break;
                case '%': tam3 = resto(numerao1, tam1, numerao2, tam2);
                         break;
                default: printf("Operador invalido!");
           }
          
           imprimeNumerao(numerao1, tam3);
          
       } else {
           /* define operador como zero para encerrar aplicacao */
           operador = '0';
       }
   }

   return 0;
}

/* Sanitiza os numeros em ordem no menos significativo para o mais significativo
  >>preserva o sinal de negativo na frente do numerao e adiciona 
    um ' ' em numerao positivo na posição 0<<
  Recebe:
   char numerao: vetor de char corresponde ao numerao
  Retorna:
   int size: tamanho do numerao sanitizado */
int sanitizeNumerao(char numerao[MAX_SIZE]) {
    char numerao_copy[MAX_SIZE];
    int i = 0, size = -1;
    
    /* encontra o tamanho do numerao */
    while(numerao[i] != '\0' && i < MAX_SIZE) {
       i++;
    }
    size = i;
  
    /* cria um espelho */
    for(i = 0; i < size; i++) {
        numerao_copy[i] = numerao[i];
    }
    
    /* define a posicao 0 como referencia do sinal do numero */
    if(numerao[0] != '-') {
        /* sera ' ' caso o numero for positivo, assim como aumentara o array */
        numerao[0] = ' ';
        size++;
        /* reordena do menos significativo para o mais significativo */
        for(i = 1; i < size; i++) {
            numerao[i] = numerao_copy[(size - i) - 1];
        }    
    } else {
        /* somente reordena do menos significativo para o mais significativo */
        for(i = 1; i < size; i++){
            numerao[i] = numerao_copy[(size - i)];
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
    /* caso o numero negativo, imprime o sinal antes do numero, 
       exceto se o numerao for 0 */
    if(numerao[0] == '-' && !(numerao[1] == '0' && tam == 2) ) {
        printf("%c", numerao[0]);
    }
    /* imprime o numero do mais significativo para o menor */
    for(i = 1; i < tam; i++) {
          printf("%c", numerao[tam - i]);
    }

    printf("\n");
}

/* Remove zeros a esquerda
   Recebe:
    char numerao: vetor de char correspondente ao numerao
    int tam: inteiro correspondente ao tamanho do numerao
   Retorna:
    int tam: inteiro correspondente ao tamanho do novo numerao */
int cleanZeros(char numerao[MAX_SIZE], int tam) {
    int i = tam;
    while(i != 2 && numerao[i - 1] == '0') {
        i--;
    }
    
    return i;    
}

/* Acresenta um zero no numero
   Recebe:
    char numerao:  ponteiro de vetor de char correspondente ao numerao
    int tam: inteiro correspondente ao tamanho do numerao
   Retorna:
    int tam: inteiro correspondente ao tamanho do novo numerao */
int addZero(char numerao[MAX_SIZE], int tam) {
    int i;
    char cache;
    /* Acresentar uma unidade no tamanho e inserir o zero na posição final */
    tam++;
    numerao[(tam - 1)] = '0';
    /* Percorrer o  numerão colocando o zero na posição inicial */
    for (i = tam - 1; i > 1; i--) {
        cache = numerao[(i - 1)];
        numerao[(i - 1)] = numerao[i];
        numerao[i] = cache;
    }
    return tam;
}

/*
  Recebe:
   char numerao1: vetor de char correspondente ao primeiro numero
   int n1: tamanho do vetor numerao1
   char numerao2: vetor de char corresponde ao segundo numero
   int n2: tamanho do vetor numerao2
  Retorna:
   int tam: novo tamanho do numerao1  */
int soma(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2) {
    int i, tam = 0, calculated = 0, rest = 0;

    /* define o tamanho preliminar do array */
    tam = tam1 > tam2 ? tam1 : tam2;

    /* caso 1: os numeros são ambos positivos ou ambos negativos */
    if ((numerao1[0] != '-' && numerao2[0] != '-') || (numerao1[0] == '-' && numerao2[0] == '-')) {
         /* percorre ambos os vetores somando e iterando o resto */
        for (i = 1; i < tam; i++) {
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
            numerao1[i] = '0' + calculated;
        }
          
        /* verifica o resto para incluir na proxima casa */
        if(rest > 0) {
            tam++;
            numerao1[tam - 1] = '1';
        }
    }
    /* caso 2: o primeiro numero positivo e o segundo negativo */
    else if (numerao1[0] != '-' && numerao2[0] == '-') {
        /* Remove o sinal negativo do segundo numero */
        numerao2[0] = ' ';
        /* Enviar para a função subtracao */
        tam = subtracao(numerao1, tam1, numerao2, tam2);
    }
    /* caso 3: o primeiro numero negativo e o segundo positivo */
    else{
        /* Remover o sinal negativo do primeiro numero */
        numerao1[0] = ' ';
        /* Envia para a funcao subtracao subtraindo o numerao2 do numerao1 */
        tam = subtracao(numerao2, tam2, numerao1, tam1);
        /* Copia o resultado para o numerao1 */
        for(i = 0; i < tam; i++) {
            numerao1[i] = numerao2[i];
        }
    }
    
    /* remove os zeros a esquerda, caso houver */ 
    tam = cleanZeros(numerao1, tam);
    
    return tam;
}

/*
  Recebe:
   char numerao1: vetor de char correspondente ao primeiro numero
   int n1: tamanho do vetor numerao1
   char numerao2: vetor de char corresponde ao segundo numero
   int n2: tamanho do vetor numerao2
  Retorna:
   int tam: novo tamanho do numerao1  */
int subtracao(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2) {
    int i, j, tam = 0, maior = 1, calculated = 0;

    /* define o tamanho preliminar do array e indicar qual é o maior numero (em módulo) */
    if (tam1 > tam2) {
        tam = tam1;
        maior = 1;
    } else if (tam2 > tam1) {
        tam = tam2;
        maior = 2;
    } else {
        tam = tam1;
        /* Definir o maior entre os dois numeros comparando seus algarismos */
        i = tam - 1;
        while (i != 0) {
           if (numerao1[i] > numerao2[i]) {
               maior = 1;
               break;
           } else if (numerao2[i] > numerao1[i]) {
               maior = 2;
               break;
           } else {
               i--;
           }
       }
    }

    /* caso 1: ambos os numeroes sao positivos */
    if (numerao1[0] != '-' && numerao2[0] != '-') {
        /* se o maior numero em modulo for o numerao1 */
        if (maior == 1) {
            /* percorre ambos os vetores subtraindo seus algarismos */
            for (i = 1; i < tam; i++) {
                calculated = (numerao1[i] - '0');
                if (i < tam2) {
                    calculated -= (numerao2[i] - '0');
                }
                /* caso o numero precise pegar uma unidade emprestada do casa vizinha */
                if (calculated < 0) {
                    j = i + 1;
                    while (j < tam) {
                        /* verificar se o algarismo é diferente de zero */
                        if (numerao1[j] != '0') {
                            numerao1[j] -= 1;
                            break;
                        /* se algarismo igual a zero procurar na casa seguinte*/
                        } else {
                            numerao1[j] = '9'; /* Adicionar 10 e subtrair 1 emprestado */
                            j++;
                        } 
                    }
                    numerao1[i] += 10;
                    calculated = (numerao1[i] - '0');
                    calculated -= (numerao2[i] - '0');
                }
                numerao1[i] = '0' + calculated;
            }
         } /* se o maior numero em modulo for o numerao2 */
        else {
            /* realizar subtracao invertida */
            subtracao(numerao2, tam2, numerao1, tam1);
            /* copiar para o array numerao1 */
            for(i = 1; i < tam; i++) {
                numerao1[i] = numerao2[i];
            }
            /* inverter o sinal */
            numerao1[0] = '-';
        }
    /* caso 2: se o segundo número é negativo, ele se transforma em positivo e é enviado para soma */
    } else if (numerao1[0] != '-' && numerao2[0] == '-') {
        /* Remover o sinal negativo do segundo numero */
        numerao2[0] = ' ';
        /* Enviar para a função soma */
        tam = soma(numerao1, tam1, numerao2, tam2);
    }
    /* caso 3: primeiro número é negativo, segundo positivo */
    else if (numerao1[0] == '-' && numerao2[0] != '-') {
       numerao1[0] = ' ';
       tam = soma(numerao1, tam1, numerao2, tam2);
       numerao1[0] = '-';
    }

    /* caso 4: Ambos negativos, segundo se transforma em positivo, recorre o caso 1, segundo numero maior */
    else{
        numerao2[0] = ' ';
        numerao1[0] = ' ';
        tam = subtracao(numerao2, tam2, numerao1, tam1);
        /* salvar resultado no array numerao1 */
        for(i = 0; i < tam; i++) {
            numerao1[i] = numerao2[i];
        }
    }
    
    tam = cleanZeros(numerao1, tam);

    return tam;
}

/*
  Recebe:
   char numerao1: vetor de char correspondente ao primeiro numero
   int n1: tamanho do vetor numerao1
   char numerao2: vetor de char corresponde ao segundo numero
   int n2: tamanho do vetor numerao2
  Retorna:
   int tam: novo tamanho do numerao1  */
int multiplicacao(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2){
    int i, tamcopy, vezes;
    char sinal, *numeraocopy;
    /* Verificar os sinais */
    if((numerao1[0] == '-' && numerao2[0] == '-') || (numerao1[0] != '-' && numerao2[0] != '-')) {
        sinal = '+';
    } else {
        sinal = '-';
    }
    /* Remover os sinais para evitar conflitos no calculo */
    numerao1[0] = ' ';
    numerao2[0] = ' ';
    /* Copiar o Numerão 2 para o ponteiro */
    numeraocopy = malloc(tam2 * sizeof(char));
    tamcopy = tam2;
    for (i = 1; i < tam2; i++) {
        numeraocopy[i] = numerao2[i];
    }
    /* Copiar o numerao 1 para o numerao 2 */
    tam2 = tam1;
    for (i = 1; i < tam1; i++) {
        numerao2[i] = numerao1[i];
    }
    /* Zerar o Numerão 1 */
    numerao1[1] = '0';
    tam1 = 2;
    /* Operação de multiplicação: somar o numerao 1 por numerao 2 vezes */
    for (i = 1; i < tamcopy; i++) {
        vezes = numeraocopy[i] - '0';
        /* Somar o numero de vezes necessario do algarismo */
        while (vezes > 0) {
            tam1 = soma(numerao1, tam1, numerao2, tam2);
            vezes--;
        }
        /* Multiplicar a copia do numerao 1 por 10 (Adicionar um zero) */
        tam2 = addZero(numerao2, tam2);
    }
    /* Liberar copia do numerao */
    free(numeraocopy);
    /* Colocar o sinal no numerao final */
    if (sinal == '+') {
        numerao1[0] = ' ';
    } else {
        numerao1[0] = '-';
    }
    return tam1;
}

/*
  Recebe:
   char numerao1: vetor de char correspondente ao primeiro numero
   int n1: tamanho do vetor numerao1
   char numerao2: vetor de char corresponde ao segundo numero
   int n2: tamanho do vetor numerao2
  Retorna:
   int tam: novo tamanho do numerao1  */
int divide(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2){
    int i, j, tamdin, tamres, tamcpy, pos, calculated;
    char sinal, *numerodin, *resultado, *numerocpy;
    /* Verificar os sinais */
    if((numerao1[0] == '-' && numerao2[0] == '-') || (numerao1[0] != '-' && numerao2[0] != '-')) {
        sinal = '+';
    } else {
        sinal = '-';
    }
    /* Remover os sinais para evitar conflitos no calculo */
    numerao1[0] = ' ';
    numerao2[0] = ' ';
    /* Alocação de espaço dos ponteiros de vetores */
    numerodin = malloc(MAX_SIZE * sizeof(char));
    resultado = malloc(MAX_SIZE * sizeof(char));
    numerocpy = malloc(tam2 * sizeof(char));
    /* Fazer uma copia do numerao 2 para um ponteiro de um vetor */
    tamcpy = tam2;
    for (i = 0; i < tam2; i++) {
        numerocpy[i] = numerao2[i];
    }
    /* Caso o numerão 2 tenha menos ou o mesmo numero de algarismos do que o numerão 1*/
    if(tam2 <= tam1) {
        tamdin = tam2;
        tamres = 1;
        /* Criação do numero dinamico - os tam2 primeiros algarismos do numero */
        numerodin[0] = ' ';
        /* Definir posição da proxima casa que desce */
        pos = tam1 - tamdin;
        j = 1;
        /* Laço para inserir os elementos no numero dinamico */
        for (i = (pos + 1); i < tam1; i++) {
            numerodin[j] = numerao1[i];
            j++;
        }
        /* Realizar as operações enquanto a posição é valida */
        do {
            /* Vezes em que foi realizado a subtração */
            calculated = 0;
            /* Subtrair até o numero ficar negativo */
            while(numerodin[0] != '-') {
                tamdin = subtracao(numerodin, tamdin, numerocpy, tamcpy);
                calculated++;
            }
            /* Copiar o nuemro 2 para o vetor de copia novamente para a proxima operação */
            tamcpy = tam2;
            for (i = 0; i < tam2; i++) {
                numerocpy[i] = numerao2[i];
            }
            /* Somar uma unidade para obter o resto */
            tamdin = soma(numerodin, tamdin, numerao2, tam2);
            calculated--;
            /* Copiar o nuemro 2 para o vetor de copia novamente para a proxima operação */
            tam2 = tamcpy;
            for (i = 0; i < tamcpy; i++) {
                numerao2[i] = numerocpy[i];
            }
            /* Colocar o resultado no vetor */
            tamres++;
            resultado[(tamres - 1)] = calculated + '0';
            /* Preparar a proxima casa do algarismo dinamico */
            tamdin = addZero(numerodin, tamdin);
            numerodin[1] = numerao1[pos];
            tamdin = cleanZeros(numerodin, tamdin);
            pos--;
        } while (pos >= 0);
    /* Caso o numerao 2 tenha mais algarismops que o numerão 1 ele tem resultado zero */
    } else {
        tamres = 2;
        resultado[1] = '0';
    } /* Liberar espaço dos vetores utilizados */
    free(numerocpy);
    free(numerodin);
    /* Copiar o resultado para o numerão 1 e liberar o vetor resultado */
    tam1 = tamres;
    for (i = 1; i < tamres; i++) {
        numerao1[i] = resultado[(tamres - i)];
    }
    free(resultado);
    /* Retirar zeros a esquerda */
    tam1 = cleanZeros(numerao1, tam1);
    /* Colocar o sinal no numerao final */
    if (sinal == '+') {
        numerao1[0] = ' ';
    } else {
        numerao1[0] = '-';
    }
    return tam1;
}

/*
  Recebe:
   char numerao1: vetor de char correspondente ao primeiro numero
   int n1: tamanho do vetor numerao1
   char numerao2: vetor de char corresponde ao segundo numero
   int n2: tamanho do vetor numerao2
  Retorna:
   int tam: novo tamanho do numerao1  */
int resto(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2){
    int i, tamcpy1, tamcpy2;
    char sinal, *numerocpy1, *numerocpy2;
    /* Verificar os sinais */
    sinal = numerao1[0] == ' ' ? '+' : '-'; 
    /* Remover os sinais para evitar conflitos no calculo */
    numerao1[0] = ' ';
    numerao2[0] = ' ';
    /* Copiar o numerão 1 para um ponteiro de vetor */
    numerocpy1 = malloc(MAX_SIZE * sizeof(char));
    tamcpy1 = tam1;
    for (i = 0; i < tam1; i++) {
        numerocpy1[i] = numerao1[i];
    }
    /* Copiar o numerão 2 para um ponteiro de vetor */
    numerocpy2 = malloc(tam2 * sizeof(char));
    tamcpy2 = tam2;
    for (i = 0; i < tam2; i++) {
        numerocpy2[i] = numerao2[i];
    }
    /* Dividir o numero e multiplicar para opter o valor inteiro */
    tamcpy1 = divide(numerocpy1, tamcpy1, numerocpy2, tamcpy2);
    tam2 = multiplicacao(numerao2, tam2, numerocpy1, tamcpy1);
    /* Liberar as cópias dos ponteiros de vetores */
    free(numerocpy1);
    free(numerocpy2);
    /* Subtrair o numerão 1 com o numero inteiro da multiplicação para obter o resto */
    tam1 = subtracao(numerao1, tam1, numerao2, tam2);
    /* Colocar o sinal no numerao final */
    if (sinal == '+') {
        numerao1[0] = ' ';
    } else {
        numerao1[0] = '-';
    }
    return tam1;
}
