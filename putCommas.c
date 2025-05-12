#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao recursiva que insere virgulas em numeros grandes
void putCommas(int n, char* result) {
    if (n < 1000) {
        sprintf(result, "%d", n); // Base da recursao: menor que 1000
        return;
    }

    // Processa recursivamente a parte superior
    putCommas(n / 1000, result);

    // Adiciona virgula e os últimos 3 dígitos formatados
    char temp[5];
    sprintf(temp, ",%03d", n % 1000);
    strcat(result, temp);
}

int main() {
    int numero;
    char resultado[50] = ""; 

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Numero deve ser positivo.\n");
        return 1;
    }

    putCommas(numero, resultado);

    printf("Numero formatado: %s\n", resultado);
    return 0;
}
