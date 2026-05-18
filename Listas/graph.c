#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10;

typedef struct node{
  int v;
  struct node *next;
}node;

typedef struct graph{
  node **vertices;
  int size;
}graph;

node *add_node(int v){
  node *new_node = (node *)malloc(sizeof(node));
  new_node->v = v;
  new_node->next = NULL;
  return new_node;
}

graph *create_graph(int n){
  graph *g = (graph *)malloc(sizeof(graph));
  g->vertices = (node *)calloc(n, sizeof(node*));
  g->size = n;
  return g;
}

void add_edge(graph *g, int v1, int v2){
  node *new_vertice = add_node(v2);
  new_vertice->next = g->vertices[v1];
  g->vertices[v1] = new_vertice;
}

