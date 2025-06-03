#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct No {
    int vertice;
    struct No* prox;
} No;

No* adj[MAX_VERTICES];
int visitado[MAX_VERTICES];
int numUsuarios = 0;

int adicionarUsuario() {
    if (numUsuarios >= MAX_VERTICES) {
        printf("Limite maximo de usuarios atingido.\n");
        return -1;
    }
    adj[numUsuarios] = NULL;
    printf("Usuario %d adicionado.\n", numUsuarios);
    return numUsuarios++;
}

void adicionarConexao(int u, int v) {
    if (u >= numUsuarios || v >= numUsuarios) {
        printf("Usuario invalido.\n");
        return;
    }
    // Verifica se já existe conexão para evitar duplicatas
    No* atual = adj[u];
    while(atual != NULL) {
        if(atual->vertice == v) {
            printf("Conexao ja existe entre %d e %d.\n", u, v);
            return;
        }
        atual = atual->prox;
    }
    // Adiciona v na lista de u
    No* novo = (No*)malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = adj[u];
    adj[u] = novo;

    // Adiciona u na lista de v
    novo = (No*)malloc(sizeof(No));
    novo->vertice = u;
    novo->prox = adj[v];
    adj[v] = novo;

    printf("Conexao adicionada entre %d e %d.\n", u, v);
}

void visualizarAmigos(int u) {
    if (u >= numUsuarios) {
        printf("Usuario invalido.\n");
        return;
    }
    printf("Amigos do usuario %d: ", u);
    No* atual = adj[u];
    if (atual == NULL) {
        printf("Nenhum amigo.\n");
        return;
    }
    while (atual != NULL) {
        printf("%d ", atual->vertice);
        atual = atual->prox;
    }
    printf("\n");
}

void dfs(int v) {
    visitado[v] = 1;
    printf("%d ", v);
    No* atual = adj[v];
    while (atual != NULL) {
        if (!visitado[atual->vertice]) {
            dfs(atual->vertice);
        }
        atual = atual->prox;
    }
}

typedef struct {
    int itens[MAX_VERTICES];
    int frente;
    int tras;
} Fila;

void inicializarFila(Fila *f) {
    f->frente = -1;
    f->tras = -1;
}

int estaVazia(Fila *f) {
    return f->frente == -1;
}

void enfileirar(Fila *f, int valor) {
    if (f->tras == MAX_VERTICES - 1) return;
    if (f->frente == -1) f->frente = 0;
    f->tras++;
    f->itens[f->tras] = valor;
}

int desenfileirar(Fila *f) {
    if (estaVazia(f)) return -1;
    int valor = f->itens[f->frente];
    f->frente++;
    if (f->frente > f->tras) f->frente = f->tras = -1;
    return valor;
}

void bfs(int inicio) {
    int visitadoBFS[MAX_VERTICES] = {0};
    Fila f;
    inicializarFila(&f);

    visitadoBFS[inicio] = 1;
    enfileirar(&f, inicio);

    printf("BFS a partir do usuario %d: ", inicio);

    while (!estaVazia(&f)) {
        int atual = desenfileirar(&f);
        printf("%d ", atual);

        No* temp = adj[atual];
        while (temp != NULL) {
            if (!visitadoBFS[temp->vertice]) {
                visitadoBFS[temp->vertice] = 1;
                enfileirar(&f, temp->vertice);
            }
            temp = temp->prox;
        }
    }
    printf("\n");
}

void sugestaoAmigos(int u) {
    if (u >= numUsuarios) {
        printf("Usuario invalido.\n");
        return;
    }

    int visitado[MAX_VERTICES] = {0};
    int nivel[MAX_VERTICES] = {-1};  // Nível da BFS (distância)
    Fila f;
    inicializarFila(&f);

    enfileirar(&f, u);
    visitado[u] = 1;
    nivel[u] = 0;

    // Marcar amigos diretos para evitar sugestão redundante
    int amigosDiretos[MAX_VERTICES] = {0};
    No* temp = adj[u];
    while (temp != NULL) {
        amigosDiretos[temp->vertice] = 1;
        temp = temp->prox;
    }

    printf("Sugestoes de amigos para o usuario %d (amigos de amigos): ", u);
    int encontrou = 0;

    while (!estaVazia(&f)) {
        int atual = desenfileirar(&f);

        No* vizinho = adj[atual];
        while (vizinho != NULL) {
            int v = vizinho->vertice;
            if (!visitado[v]) {
                nivel[v] = nivel[atual] + 1;
                visitado[v] = 1;
                enfileirar(&f, v);

                // Sugerir se está no nível 2 (distância 2), e não é amigo direto nem ele mesmo
                if (nivel[v] == 2 && !amigosDiretos[v] && v != u) {
                    printf("%d ", v);
                    encontrou = 1;
                }
            }
            vizinho = vizinho->prox;
        }
    }

    if (!encontrou)
        printf("Nenhuma sugestao disponivel.");
    printf("\n");
}

void limparVisitado() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        visitado[i] = 0;
    }
}

void explorarGrupo(int u) {
    if (u >= numUsuarios) {
        printf("Usuario invalido.\n");
        return;
    }

    limparVisitado();
    printf("Usuarios conectados ao %d (grupo): ", u);
    dfs(u);
    printf("\n");
}

int main() {
    // Inicializa o grafo
    for (int i = 0; i < MAX_VERTICES; i++) {
        adj[i] = NULL;
    }

    int opcao;
    int u, v;

    printf("=== Rede Social ===\n");

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar usuario\n");
        printf("2. Criar conexao (amizade)\n");
        printf("3. Visualizar amigos de um usuario\n");
        printf("4. Sugerir amigos (via BFS)\n");
        printf("5. Explorar grupos/conectividade (via DFS)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarUsuario();
                break;

            case 2:
                printf("Digite o ID do usuario 1: ");
                scanf("%d", &u);
                printf("Digite o ID do usuario 2: ");
                scanf("%d", &v);
                adicionarConexao(u, v);
                break;

            case 3:
                printf("Digite o ID do usuario: ");
                scanf("%d", &u);
                visualizarAmigos(u);
                break;

            case 4:
                printf("Digite o ID do usuario para sugestoes: ");
                scanf("%d", &u);
                sugestaoAmigos(u);
                break;

            case 5:
                printf("Digite o ID do usuario para explorar grupo: ");
                scanf("%d", &u);
                explorarGrupo(u);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
