#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
  int item;
  struct node *next;
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
    current->next = new_node;
  }

}

node *dequeue(queue *q){
    node *node = q->head;
    q->head = q->head->next;
    node->next = NULL;
    return node;
}

void sort(queue *q){

  if(is_empty(q)){
    return;
  }
  node *current = q->head;
  node *next = NULL;
  int temp;

  while (current != NULL){
    next = current->next;
    while (next != NULL){
      if(current->item > next->item){
        temp = current->item;
        current->item = next->item;
        next->item = temp;
      }
      next = next->next;
    }
    current = current->next;
  }

  
}


int main() {
  char linha[100000];
  
  queue *q = malloc(sizeof(queue));
  q->head = NULL;

  fgets(linha, sizeof(linha), stdin);
  int i = 0;
  char *token = strtok(linha, " \n");
while (token != NULL){
    enqueue(q, atoi(token));
    token = strtok(NULL, " \n");
  }
  
  sort(q);

  while (!is_empty(q)){
    node *node = dequeue(q);
    printf("%d ", node->item);
  }
  
}