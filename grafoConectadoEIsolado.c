#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100

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

// Inserir aresta
void addEdge(Graph* graph, int src, int dest) {
    if (src < 0 || dest < 0 || src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Vértices inválidos.\n");
        return;
    }
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Multiplicação de matrizes
void multiplyMatrix(int size, int A[MAX_VERTICES][MAX_VERTICES], int B[MAX_VERTICES][MAX_VERTICES], int C[MAX_VERTICES][MAX_VERTICES]) {
    int temp[MAX_VERTICES][MAX_VERTICES] = {0};
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                temp[i][j] += A[i][k] * B[k][j];

    memcpy(C, temp, sizeof(temp));
}

// Soma de matrizes
void addMatrix(int size, int C[MAX_VERTICES][MAX_VERTICES], int A[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] += A[i][j];
}

// Verificar se o grafo é conexo
void checkIfConnected(Graph* graph) {
    int n = graph->numVertices;
    int A[MAX_VERTICES][MAX_VERTICES];
    int power[MAX_VERTICES][MAX_VERTICES];
    int B[MAX_VERTICES][MAX_VERTICES] = {0};

    memcpy(A, graph->adjMatrix, sizeof(A));
    memcpy(power, A, sizeof(power));

    for (int p = 1; p < n; p++) {
        addMatrix(n, B, power);
        int nextPower[MAX_VERTICES][MAX_VERTICES];
        multiplyMatrix(n, power, A, nextPower);
        memcpy(power, nextPower, sizeof(power));
    }

    int connected = 1;
    for (int i = 0; i < n && connected; i++)
        for (int j = 0; j < n; j++)
            if (i != j && B[i][j] == 0) {
                connected = 0;
                break;
            }

    if (connected)
        printf("\nO grafo é CONEXO (todos os vértices estão conectados direta ou indiretamente).\n");
    else
        printf("\nO grafo NÃO é CONEXO.\n");
}

// Listar vértices isolados (grau 0)
void listIsolatedVertices(Graph* graph) {
    int found = 0;
    printf("\nVértices isolados (grau 0): ");
    for (int i = 0; i < graph->numVertices; i++) {
        int grau = 0;
        for (int j = 0; j < graph->numVertices; j++) {
            grau += graph->adjMatrix[i][j];
        }
        if (grau == 0) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found)
        printf("Nenhum");
    printf("\n");
}

// Exibir matriz
void printMatrix(Graph* graph) {
    printf("\nMatriz de Adjacência:\n   ");
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
        printf("2. Exibir matriz de adjacência\n");
        printf("3. Verificar se o grafo é conexo\n");
        printf("4. Listar vértices isolados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite os vértices (origem destino): ");
                scanf("%d %d", &v1, &v2);
                addEdge(graph, v1, v2);
                break;
            case 2:
                printMatrix(graph);
                break;
            case 3:
                checkIfConnected(graph);
                break;
            case 4:
                listIsolatedVertices(graph);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    int vertices;
    printf("Digite o número de vértices do grafo (max %d): ", MAX_VERTICES);
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Número de vértices inválido!\n");
        return 1;
    }

    Graph* graph = createGraph(vertices);
    menu(graph);

    free(graph);
    return 0;
}
