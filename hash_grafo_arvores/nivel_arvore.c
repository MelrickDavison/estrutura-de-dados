#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para usar INT_MAX e INT_MIN

typedef struct adj_list {
    int item;
    int value;
    struct adj_list *next;
} adj_list;

typedef struct graph {
    int num_vertices;
    adj_list **vertices;
    int *visited;
} graph;

adj_list* create_adj_list(int item, int value) {
    adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
    new_adj_list->item = item;
    new_adj_list->value = value;
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

void add_edge(graph *g, int value, int origin, int dest) {
    adj_list *new_node = create_adj_list(dest, value);

    if (g->vertices[origin] == NULL || g->vertices[origin]->item > dest) {
        new_node->next = g->vertices[origin];
        g->vertices[origin] = new_node;
        return;
    }

    adj_list *current = g->vertices[origin];

    while (current->next != NULL && current->next->item < dest) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

void bfs(graph *g, int source, int *node_values) {
    int n = g->num_vertices;
    int dist[n]; 

    for (int i = 0; i < n; i++) {
        g->visited[i] = 0;
        dist[i] = 0;
    }

    int queue[n];
    int front = 0;
    int rear = 0;

    int maior_nivel[n + 1];
    int menor_nivel[n + 1];
    
    for (int i = 0; i <= n; i++) {
        maior_nivel[i] = INT_MIN;
        menor_nivel[i] = INT_MAX;
    }

    int max_altura = 1;

    queue[rear++] = source;
    g->visited[source] = 1;
    dist[source] = 1;

    while (front < rear) {
        int u = queue[front++];
        int nivel_atual = dist[u];

        if (nivel_atual > max_altura) {
            max_altura = nivel_atual;
        }

        if (node_values[u] > maior_nivel[nivel_atual]) {
            maior_nivel[nivel_atual] = node_values[u];
        }
        if (node_values[u] < menor_nivel[nivel_atual]) {
            menor_nivel[nivel_atual] = node_values[u];
        }

        adj_list *current = g->vertices[u];

        while (current != NULL) {
            int v = current->item;
            if (!g->visited[v]) {
                g->visited[v] = 1;
                dist[v] = nivel_atual + 1;
                queue[rear++] = v;
            }
            current = current->next;
        }
    }
    for (int i = 1; i <= max_altura; i++) {
        printf("Nivel %d: Maior = %d, Menor = %d\n", i, maior_nivel[i], menor_nivel[i]);
    }
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
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    graph *g = create_graph(N);
    int node_values[N]; 

    for (int i = 0; i < N; i++) {
        int value, left, right;
        scanf("%d %d %d", &value, &left, &right);
        
        node_values[i] = value;
        
        if (left != -1) {
            add_edge(g, 0, i, left); 
        }
        if (right != -1) {
            add_edge(g, 0, i, right);
        }
    }

    bfs(g, 0, node_values);

    free_graph(g);
    return 0;
}