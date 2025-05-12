#include <stdio.h>

// Função recursiva para resolver o problema da Torre de Hanoi
void torreDeHanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }

    // Move n-1 discos da origem para o auxiliar
    torreDeHanoi(n - 1, origem, auxiliar, destino);

    // Move o maior disco da origem para o destino
    printf("Mover disco %d de %c para %c\n", n, origem, destino);

    // Move os n-1 discos do auxiliar para o destino
    torreDeHanoi(n - 1, auxiliar, destino, origem);
}

// Programa principal
int main() {
    int n;
    printf("Digite o numero de discos: ");
    scanf("%d", &n);

    printf("\nSequencia de movimentos:\n");
    torreDeHanoi(n, 'A', 'C', 'B'); // A = origem, C = destino, B = auxiliar
    return 0;
}
