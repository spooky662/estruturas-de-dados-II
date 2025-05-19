#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura do grafo
typedef struct {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Função para criar o grafo
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Inicializa matriz de adjacência com 0
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Função para adicionar uma aresta
void addEdge(Graph* graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices || src < 0 || dest < 0) {
        printf("Vertices invalidos!\n");
        return;
    }
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1; // Grafo não direcionado
    printf("Aresta adicionada entre %d e %d.\n", src, dest);
}

// Função para exibir a matriz de adjacência
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

// Função para verificar se há ligação entre dois vértices
void checkConnection(Graph* graph, int v1, int v2) {
    if (v1 >= graph->numVertices || v2 >= graph->numVertices || v1 < 0 || v2 < 0) {
        printf("Vertices invalidos!\n");
        return;
    }

    if (graph->adjMatrix[v1][v2] == 1)
        printf("Ha ligacao entre %d e %d.\n", v1, v2);
    else
        printf("Nao ha ligacao entre %d e %d.\n", v1, v2);
}

// Menu de operações
void menu(Graph* graph) {
    int option, v1, v2;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir aresta\n");
        printf("2. Exibir matriz de adjacencia\n");
        printf("3. Verificar ligacao entre dois vertices\n");
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
                printf("Digite os dois vertices: ");
                scanf("%d %d", &v1, &v2);
                checkConnection(graph, v1, v2);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção invalida!\n");
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
