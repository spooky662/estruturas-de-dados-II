#include <stdio.h>
#include <math.h>

// Função recursiva baseada no método de Napier
void logarithm(double n, double m, double logn, double logm, double eps) {
    double k = sqrt(n * m); // média geométrica
    double logk = (logn + logm) / 2; // média aritmética

    printf("Aproximacao: log(%.5f) = %.5f\n", k, logk);

    if (fabs(logn - logk) < eps || fabs(logk - logm) < eps)
        return;

    // Recursivamente processa os dois lados
    logarithm(n, k, logn, logk, eps);
    logarithm(k, m, logk, logm, eps);
}

void logarithmDe(double n, double m, double logn, double logm, double x, double eps) {
    double k = sqrt(n * m);
    double logk = (logn + logm) / 2;

    if (fabs(k - x) < eps) {
        printf("log(%.5f) ≈ %.5f\n", x, logk);
        return;
    }

    if (x < k)
        logarithmDe(n, k, logn, logk, x, eps);
    else
        logarithmDe(k, m, logk, logm, x, eps);
}

void logBase10Napier(double x, double eps) {
    if (x <= 0) {
        printf("Erro: x deve ser positivo.\n");
        return;
    }

    // Determina a potência de 10 mais próxima
    int a = 0;
    while (x >= pow(10, a + 1)) a++;
    while (x < pow(10, a)) a--;

    double n = pow(10, a);
    double m = pow(10, a + 1);

    double logn = (double)a;
    double logm = (double)(a + 1);

    printf("Aproximando log10(%.5f) usando intervalo [%.0f, %.0f]\n", x, n, m);
    logarithmDe(n, m, logn, logm, x, eps);
}

int main() {
    double x, eps;

    printf("Digite um numero positivo para calcular o logaritmo: ");
    scanf("%lf", &x);

    printf("Digite a precisao desejada (ex: 0.0001): ");
    scanf("%lf", &eps);

    logBase10Napier(x, eps);
    return 0;
}
