#include <stdio.h>
#include <string.h>
#include <math.h>
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

void add_edge(graph *g, int vertex1, int vertex2) {
    adj_list *vertex = create_adj_list(vertex2);
    vertex->next = g->vertices[vertex1];
    g->vertices[vertex1] = vertex;

    vertex = create_adj_list(vertex1);
    vertex->next = g->vertices[vertex2];
    g->vertices[vertex2] = vertex;
}

void dfs(graph *g, int source) {
    g->visited[source] = 1;
    
    adj_list *adj = g->vertices[source];
    
    while (adj != NULL) {
        if (!g->visited[adj->item]) {
            dfs(g, adj->item);
        }
        adj = adj->next;
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
    int v, p;
    scanf("%d %d", &v, &p);

    graph *g = create_graph(v);
    for (int i = 0; i < p; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        add_edge(g, v1, v2);
    }

    int s, d;
    scanf("%d %d", &s, &d);
    dfs(g, s);
    if (g->visited[d] == 1) {
        printf("EXISTE");
    } else {
        printf("NAO EXISTE");
    }

    free_graph(g);

    return 0;
}