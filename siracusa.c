#include <stdio.h>

// Funcao recursiva para imprimir a sequencia de Siracusa
void siracusa(int n) {
    printf("%d ", n);

    if (n == 1)
        return;

    if (n % 2 == 0)
        siracusa(n / 2);
    else
        siracusa(3 * n + 1);
}

int main() {
    int n;

    printf("Digite o numero inicial da sequencia de Siracusa: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Digite um numero inteiro positivo.\n");
        return 1;
    }

    printf("Sequencia de Siracusa: ");
    siracusa(n);
    printf("\n");

    return 0;
}
