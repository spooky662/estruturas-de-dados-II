#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100

// Estrutura do grafo
typedef struct {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Criar grafo
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    memset(graph->adjMatrix, 0, sizeof(graph->adjMatrix));
    return graph;
}

// Inserir aresta (grafo não direcionado)
void addEdge(Graph* graph, int src, int dest) {
    if (src < 0 || dest < 0 || src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Vertices invalidos.\n");
        return;
    }
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Multiplica duas matrizes (C = A * B)
void multiplyMatrix(int size, int A[MAX_VERTICES][MAX_VERTICES], int B[MAX_VERTICES][MAX_VERTICES], int C[MAX_VERTICES][MAX_VERTICES]) {
    int temp[MAX_VERTICES][MAX_VERTICES] = {0};

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < size; k++) {
                temp[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Copia resultado para C
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = temp[i][j];
}

// Soma duas matrizes (C += A)
void addMatrix(int size, int C[MAX_VERTICES][MAX_VERTICES], int A[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] += A[i][j];
}

// Verifica se o grafo é conectado usando A + A² + ... + Aⁿ⁻¹
void checkIfConnected(Graph* graph) {
    int n = graph->numVertices;
    int A[MAX_VERTICES][MAX_VERTICES];
    int power[MAX_VERTICES][MAX_VERTICES];
    int B[MAX_VERTICES][MAX_VERTICES] = {0};

    // Inicializa A
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = graph->adjMatrix[i][j];

    // power = A
    memcpy(power, A, sizeof(power));

    // B = A + A^2 + ... + A^(n-1)
    for (int p = 1; p < n; p++) {
        addMatrix(n, B, power);
        int nextPower[MAX_VERTICES][MAX_VERTICES];
        multiplyMatrix(n, power, A, nextPower);
        memcpy(power, nextPower, sizeof(power));
    }

    // Verifica se há zeros fora da diagonal principal
    int connected = 1;
    for (int i = 0; i < n && connected; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && B[i][j] == 0) {
                connected = 0;
                break;
            }
        }
    }

    if (connected)
        printf("\nO grafo e CONECTADO.\n");
    else
        printf("\nO grafo NAO e CONECTADO.\n");
}

// Exibir matriz de adjacência
void printMatrix(Graph* graph) {
    printf("\nMatriz de Adjacencia:\n   ");
    for (int i = 0; i < graph->numVertices; i++)
        printf("%d ", i);
    printf("\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Menu
void menu(Graph* graph) {
    int opcao, v1, v2;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir aresta\n");
        printf("2. Exibir matriz de adjacencia\n");
        printf("3. Verificar se o grafo e conectado\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite os vertices (origem destino): ");
                scanf("%d %d", &v1, &v2);
                addEdge(graph, v1, v2);
                break;
            case 2:
                printMatrix(graph);
                break;
            case 3:
                checkIfConnected(graph);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// Main
int main() {
    int vertices;
    printf("Digite o numero de vertices do grafo (max %d): ", MAX_VERTICES);
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Numero de vertices invalido!\n");
        return 1;
    }

    Graph* graph = createGraph(vertices);
    menu(graph);

    free(graph);
    return 0;
}
