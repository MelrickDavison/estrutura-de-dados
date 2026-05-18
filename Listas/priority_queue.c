#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int item;
  int priority;
   struct node *next;
} node;

typedef struct{
  node *head;
}priority_queue;

int is_empty(priority_queue *pq){
  return pq->head == NULL;
}

void enqueue(priority_queue *pq, int i, int p){
  node *new_node = (node*) malloc(sizeof(node));
  new_node->item = i;
  new_node->priority = p;
  new_node->next = NULL;

  if((is_empty(pq)) || (p > pq->head->priority)){
    new_node->next = pq->head;
    pq->head = new_node;
  } else{
    node *current = pq->head;
    while((current->next != NULL) && (current->next->priority > p)){
      current = current->next;
    }
    new_node->next = new_node->next;
    current->next = new_node;
  }
}

node * dequeue(priority_queue *pq){
  if(is_empty(pq)){
    printf("IS EMPTY");
    return NULL;
  } else {
    node *node = pq->head;
    pq->head = pq->head->next;
    node->next = NULL;
    return node;
  }
}

int maximum(priority_queue *pq){
  if(is_empty(pq)){
    printf("IS EMPTY");
    return -1;
  } else {
    return pq->head->item;
  }
}