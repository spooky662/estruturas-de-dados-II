#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_NOME 100

// Estrutura para um nó na lista de adjacência
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Estrutura do grafo
typedef struct {
    int numVertices;
    char nomes[MAX_VERTICES][MAX_NOME]; // Nomes das paradas
    Node* adjLists[MAX_VERTICES];
} Graph;

// Função para criar um novo nó
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Retorna o índice de uma parada pelo nome
int getParadaIndex(Graph* graph, char nome[]) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcmp(graph->nomes[i], nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Adiciona uma parada (vértice)
void adicionarParada(Graph* graph, char nome[]) {
    if (graph->numVertices >= MAX_VERTICES) {
        printf("Limite de paradas atingido.\n");
        return;
    }
    if (getParadaIndex(graph, nome) != -1) {
        printf("Parada ja cadastrada.\n");
        return;
    }

    strcpy(graph->nomes[graph->numVertices], nome);
    graph->numVertices++;
    printf("Parada '%s' adicionada com sucesso!\n", nome);
}

// Adiciona uma aresta entre duas paradas
void adicionarRota(Graph* graph, char origem[], char destino[]) {
    int src = getParadaIndex(graph, origem);
    int dest = getParadaIndex(graph, destino);

    if (src == -1 || dest == -1) {
        printf("Parada(s) nao encontrada(s).\n");
        return;
    }

    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;

    printf("Rota entre '%s' e '%s' adicionada!\n", origem, destino);
}

// Imprime o grafo em forma de lista de adjacência
void mostrarMapa(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%s: ", graph->nomes[i]);
        Node* temp = graph->adjLists[i];
        while (temp) {
            printf("%s -> ", graph->nomes[temp->vertex]);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Busca em largura (BFS)
void buscarRota(Graph* graph, char origem[], char destino[]) {
    int start = getParadaIndex(graph, origem);
    int end = getParadaIndex(graph, destino);

    if (start == -1 || end == -1) {
        printf("Parada(s) nao encontrada(s).\n");
        return;
    }

    int visited[MAX_VERTICES] = {0};
    int prev[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) prev[i] = -1;

    int queue[MAX_VERTICES], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        Node* temp = graph->adjLists[current];

        while (temp) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                prev[temp->vertex] = current;
                queue[rear++] = temp->vertex;

                if (temp->vertex == end) break;
            }
            temp = temp->next;
        }
    }

    // Caminho encontrado
    if (!visited[end]) {
        printf("Nenhuma rota encontrada entre '%s' e '%s'.\n", origem, destino);
        return;
    }

    // Reconstruir caminho
    int path[MAX_VERTICES], pathSize = 0;
    for (int at = end; at != -1; at = prev[at]) {
        path[pathSize++] = at;
    }

    printf("Rota encontrada: ");
    for (int i = pathSize - 1; i >= 0; i--) {
        printf("%s", graph->nomes[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\n");
}

// DFS auxiliar
void dfsUtil(Graph* graph, int v, int visited[]) {
    visited[v] = 1;
    printf("%s ", graph->nomes[v]);

    Node* temp = graph->adjLists[v];
    while (temp) {
        if (!visited[temp->vertex]) {
            dfsUtil(graph, temp->vertex, visited);
        }
        temp = temp->next;
    }
}

// Função para listar paradas acessíveis via DFS
void listarParadasDFS(Graph* graph, char nome[]) {
    int index = getParadaIndex(graph, nome);
    if (index == -1) {
        printf("Parada nao encontrada.\n");
        return;
    }

    int visited[MAX_VERTICES] = {0};
    printf("Paradas acessiveis a partir de '%s': ", nome);
    dfsUtil(graph, index, visited);
    printf("\n");
}

// Menu principal
void menu(Graph* graph) {
    int opcao;
    char nome1[MAX_NOME], nome2[MAX_NOME];

    do {
        printf("\n=== Sistema de Rotas Urbanas ===\n");
        printf("1. Adicionar parada\n");
        printf("2. Adicionar rota entre paradas\n");
        printf("3. Mostrar mapa de rotas (lista de adjacencia)\n");
        printf("4. Buscar rota entre duas paradas (BFS)\n");
        printf("5. Listar paradas acessiveis (DFS)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                printf("Nome da parada: ");
                fgets(nome1, MAX_NOME, stdin);
                nome1[strcspn(nome1, "\n")] = '\0'; // Remover \n
                adicionarParada(graph, nome1);
                break;
            case 2:
                printf("Parada de origem: ");
                fgets(nome1, MAX_NOME, stdin);
                nome1[strcspn(nome1, "\n")] = '\0';

                printf("Parada de destino: ");
                fgets(nome2, MAX_NOME, stdin);
                nome2[strcspn(nome2, "\n")] = '\0';

                adicionarRota(graph, nome1, nome2);
                break;
            case 3:
                mostrarMapa(graph);
                break;
            case 4:
                printf("Parada de origem: ");
                fgets(nome1, MAX_NOME, stdin);
                nome1[strcspn(nome1, "\n")] = '\0';

                printf("Parada de destino: ");
                fgets(nome2, MAX_NOME, stdin);
                nome2[strcspn(nome2, "\n")] = '\0';

                buscarRota(graph, nome1, nome2);
                break;
            case 5:
                printf("Parada de origem: ");
                fgets(nome1, MAX_NOME, stdin);
                nome1[strcspn(nome1, "\n")] = '\0';

                listarParadasDFS(graph, nome1);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// Programa principal
int main() {
    Graph* graph = createGraph();
    menu(graph);
    return 0;
}
