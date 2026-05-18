#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int item;
  node *next;
}node;

typedef struct{
  node *head;
}queue;

int is_empty(queue *q){
  return q->head == NULL;
}


void enqueue(queue *q, int i){
  node *new_node = (node*) malloc(sizeof(node));
  new_node->item = i;
  new_node->next = NULL;

  if(is_empty(q)){
    new_node->next = q->head;
    q->head = new_node;
  } else{
    node *current = q->head;
    while(current->next != NULL){
      current = current->next;
    }
    new_node->next = new_node->next;
    current->next = new_node;
  }
}

node * dequeue(queue *q){
  if(is_empty(q)){
    printf("IS EMPTY");
    return NULL;
  } else {
    node *node = q->head;
    q->head = q->head->next;
    node->next = NULL;
    return node;
  }
}