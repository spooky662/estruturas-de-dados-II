#include <stdio.h>

void imprimirImparesCrescente(int n) {
    if (n < 1)
        return;

    imprimirImparesCrescente(n - 1);  // Chamada recursiva antes para ordem crescente

    if (n % 2 != 0)
        printf("%d ", n);
}

void imprimirImparesDecrescente(int n) {
    if (n < 1)
        return;

    if (n % 2 != 0)
        printf("%d ", n);

    imprimirImparesDecrescente(n - 1);  // Chamada recursiva depois para ordem decrescente
}

int main() {
    int n;
    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &n);

    printf("\nImpares entre 1 e %d:\n", n);
    imprimirImparesCrescente(n);

    printf("\n\nImpares entre %d e 1:\n", n);
    imprimirImparesDecrescente(n);

    return 0;
}
