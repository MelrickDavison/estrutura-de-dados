#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
  char *item;
  int priority;
   struct node *next;
} node;

typedef struct{
  node *head;
}priority_queue;

int is_empty(priority_queue *pq){
  return pq->head == NULL;
}

void enqueue(priority_queue *pq, char i[], int p){
  node *new_node = (node*) malloc(sizeof(node));
  new_node->item = malloc(strlen(i) + 1);
  strcpy(new_node->item, i);
  
  new_node->priority = p;
  new_node->next = NULL;
  
  if((is_empty(pq)) || (p <= pq->head->priority)){
    new_node->next = pq->head;
    pq->head = new_node;
  } else{
    node *current = pq->head;
    while(current->next != NULL && current->next->priority < p){
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

node * dequeue(priority_queue *pq){
  printf("\n");
   node *current = pq->head;
    while(current != NULL){
        printf("%d. %s\n", current->priority, current->item);
        current = current->next;
    }
}

int main(){
  int entrada;
  char tarefa[1000];
  priority_queue *pq = (priority_queue*)malloc(sizeof(priority_queue));
  pq->head = NULL;
  scanf("%d", &entrada);

  while(entrada != 0){
    if(entrada == 1){
      while(getchar() != '\n');
      fgets(tarefa, sizeof(tarefa), stdin);
      tarefa[strcspn(tarefa, "\n")] = 0;
      int prioridade;
      scanf("%d", &prioridade);
      enqueue(pq, tarefa, prioridade);
    }else{
      if(!is_empty(pq)){
        dequeue(pq);
      }
    }
    scanf("%d", &entrada);
  }
}