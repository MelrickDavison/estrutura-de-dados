#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Constante auxiliar sugerida para o tamanho do array

// Estruturas base para o Grafo 
typedef struct adj_list {
    int item;
    struct adj_list *next;
} adj_list;

typedef struct graph {
    adj_list *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
} graph;

// Cria um novo nó para a lista de adjacência
adj_list* create_adj_list(int item) {
    adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
    new_adj_list->item = item;
    new_adj_list->next = NULL;
    return new_adj_list;
}

// Inicializa o grafo
graph* create_graph() {
    graph *new_graph = (graph*) malloc(sizeof(graph));
    int i;
    for (i = 1; i < MAX_SIZE; i++) {
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = 0;
    }
    return new_graph;
}

// Adiciona uma aresta (grafo não-direcionado)
void add_edge(graph *g, int vertex1, int vertex2) {
    adj_list *vertex = create_adj_list(vertex2);
    vertex->next = g->vertices[vertex1];
    g->vertices[vertex1] = vertex;

    // Grafo não-direcionado: adiciona a aresta na outra direção também
    vertex = create_adj_list(vertex1);
    vertex->next = g->vertices[vertex2];
    g->vertices[vertex2] = vertex;
}

// Algoritmo DFS (Busca em Profundidade)
void dfs(graph *g, int source) {
    g->visited[source] = 1;
    printf("%d\n", source);
    
    adj_list *adj = g->vertices[source];
    
    while (adj != NULL) {
        if (!g->visited[adj->item]) {
            dfs(g, adj->item);
        }
        adj = adj->next;
    }
}

// Algoritmo BFS (Busca em Largura) [cite: 756, 758, 761, 762, 763, 765, 766, 767, 769, 770, 771, 772, 773, 775]
/*
void bfs(graph *g, int source) {
    queue *q = create_queue();
    int dequeued;
    
    adj_list *adj = g->vertices[source];
    g->visited[source] = 1;
    enqueue(q, source);

    while (!is_empty(q)) {
        dequeued = dequeue(q);
        adj = g->vertices[dequeued];

        while (adj != NULL) {
            if (!g->visited[adj->item]) {
                printf("%d\n", adj->item);
                g->visited[adj->item] = 1;
                enqueue(q, adj->item);
            }
            adj = adj->next;
        }
    }
}
*/