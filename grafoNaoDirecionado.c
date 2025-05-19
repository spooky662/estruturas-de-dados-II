#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura do grafo
typedef struct {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Criar o grafo
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Inicializa com 0 (sem conexões)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Inserir aresta
void addEdge(Graph* graph, int src, int dest) {
    if (src < 0 || dest < 0 || src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Vertices invalidos.\n");
        return;
    }

    graph->adjMatrix[src][dest]++;
    graph->adjMatrix[dest][src]++;  // Grafo não direcionado
    printf("Aresta adicionada entre %d e %d.\n", src, dest);
}

// Exibir matriz de adjacência
void printAdjacencyMatrix(Graph* graph) {
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

// Calcular grau de cada vértice
void calculateDegrees(Graph* graph) {
    printf("\nGrau dos vertices:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        int degree = 0;
        for (int j = 0; j < graph->numVertices; j++) {
            degree += graph->adjMatrix[i][j];
        }
        printf("Vertice %d: grau %d\n", i, degree);
    }
}

// Verificar se o grafo é completo
void checkIfComplete(Graph* graph) {
    int complete = 1;
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (i != j && graph->adjMatrix[i][j] == 0) {
                complete = 0;
                break;
            }
        }
        if (!complete) break;
    }

    if (complete)
        printf("\nO grafo e completo.\n");
    else
        printf("\nO grafo NAO e completo.\n");
}

// Verificar se o grafo é simples
void checkIfSimple(Graph* graph) {
    int simple = 1;

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[i][i] != 0) {
            simple = 0; // Laço encontrado
            break;
        }
        for (int j = 0; j < graph->numVertices; j++) {
            if (i != j && graph->adjMatrix[i][j] > 1) {
                simple = 0; // Aresta múltipla encontrada
                break;
            }
        }
        if (!simple) break;
    }

    if (simple)
        printf("\nO grafo e simples.\n");
    else
        printf("\nO grafo NAO e simples (possui laco ou arestas multiplas).\n");
}

// Menu de operações
void menu(Graph* graph) {
    int option, v1, v2;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir aresta\n");
        printf("2. Exibir matriz de adjacencia\n");
        printf("3. Calcular grau de cada vertice\n");
        printf("4. Verificar se o grafo e completo\n");
        printf("5. Verificar se o grafo e simples\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("Digite os vertices (origem destino): ");
                scanf("%d %d", &v1, &v2);
                addEdge(graph, v1, v2);
                break;
            case 2:
                printAdjacencyMatrix(graph);
                break;
            case 3:
                calculateDegrees(graph);
                break;
            case 4:
                checkIfComplete(graph);
                break;
            case 5:
                checkIfSimple(graph);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(option != 0);
}

// Função principal
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
