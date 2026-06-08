#include <stdio.h>
#include <stdlib.h>

typedef struct adj_list {
    int item;
    struct adj_list *next;
} adj_list;

typedef struct graph {
    int num_vertices;
    adj_list **vertices;
    int *visited;
} graph;

adj_list* create_adj_list(int item) {
    adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
    new_adj_list->item = item;
    new_adj_list->next = NULL;
    return new_adj_list;
}

graph* create_graph(int num_vertices) {
    graph *new_graph = (graph*) malloc(sizeof(graph));

    new_graph->num_vertices = num_vertices;

    new_graph->vertices = (adj_list**) malloc(num_vertices * sizeof(adj_list*));
    new_graph->visited = (int*) malloc(num_vertices * sizeof(int));

    for (int i = 0; i < num_vertices; i++) {
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = 0;
    }

    return new_graph;
}

void add_edge(graph *g, int origin, int dest) {
    adj_list *new_node = create_adj_list(dest);

    if (g->vertices[origin] == NULL ||
        g->vertices[origin]->item > dest) {

        new_node->next = g->vertices[origin];
        g->vertices[origin] = new_node;
        return;
    }

    adj_list *current = g->vertices[origin];

    while (current->next != NULL &&
           current->next->item < dest) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

void bfs(graph *g, int source, int dist[], int pred[]) {
    int n = g->num_vertices;

    for (int i = 0; i < n; i++) {
        g->visited[i] = 0;
        dist[i] = -1;
        pred[i] = -1;
    }

    int queue[n];
    int front = 0;
    int rear = 0;

    queue[rear++] = source;
    g->visited[source] = 1;
    dist[source] = 0;

    while (front < rear) {
        int u = queue[front++];

        printf("Iniciando busca em largura a partir de %d\n", u);

        adj_list *current = g->vertices[u];

        while (current != NULL) {
            int v = current->item;

            if (!g->visited[v]) {
                g->visited[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;

                queue[rear++] = v;
            }

            current = current->next;
        }
    }
}
void print_path(int origin, int dest, int pred[]) {
    int path[10000];
    int size = 0;

    int current = dest;

    while (current != -1) {
        path[size++] = current;
        current = pred[current];
    }

    printf("Caminho entre %d e %d: ", origin, dest);

    for (int i = size - 1; i >= 0; i--) {
        printf("%d", path[i]);

        if (i > 0) {
            printf(" => ");
        }
    }
    printf("\n");
}

void free_graph(graph *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        adj_list *current = g->vertices[i];

        while (current != NULL) {
            adj_list *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(g->vertices);
    free(g->visited);
    free(g);
}

int main() {
    int v, a, t;

    scanf("%d %d %d", &v, &a, &t);

    graph *g = create_graph(v);

    for (int i = 0; i < a; i++) {
        int o, d;
        scanf("%d %d", &o, &d);
        add_edge(g, o, d);
    }

    for (int caso = 1; caso <= t; caso++) {

        int origem, destino;

        scanf("%d %d", &origem, &destino);

        int dist[v];
        int pred[v];

        printf("--------\n\n");
        printf("Caso de Teste #%d - BFS(%d)\n\n", caso, origem);

        bfs(g, origem, dist, pred);

        printf("\n");

        for (int i = 0; i < v; i++) {

            printf("%d | ", i);

            if (dist[i] == -1)
                printf("- | ");
            else
                printf("%d | ", dist[i]);

            if (pred[i] == -1)
                printf("-\n");
            else
                printf("%d\n", pred[i]);
        }

        printf("\n");

        if (dist[destino] == -1) {
            printf("Sem caminho entre %d e %d\n", origem, destino);
        } else {
            print_path(origem, destino, pred);
        }
        printf("\n");
    }

    printf("--------\n");
    free_graph(g);

    return 0;
}