#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void dequeue(queue *q){
  if(is_empty(q)){
    printf("IS EMPTY");
  } else {
    node *node = q->head;
    q->head = q->head->next;
    node->next = NULL;
    free(node);
  }
}

void print(queue *q){
   if(!is_empty(q)){
     node *current = q->head;
     while (current != NULL){
       printf("%d ", current->item);
       current = current->next;
     }
     printf("\n");
  }else{
    printf("IS EMPTY");
  }
}
void soma(queue *q){
   if(!is_empty(q)){
     int soma = 0;
     node *current = q->head;
     while (current != NULL){
       soma += current->item;
       current = current->next;
      }
      printf("%d", soma);
     printf("\n");
  }else{
    printf("IS EMPTY");
  }
}

int main(){
  queue *q = (queue*) malloc(sizeof(queue));
  q->head = NULL;
  char comando[100];
  int value;
  scanf("%s", comando);
  while(strcmp(comando, "exit")){
    if(!strcmp(comando, "push")){
      scanf("%d", &value);
      enqueue(q, value);
    }else if(!strcmp(comando, "print")){
      print(q);
    }else if(!strcmp(comando, "sum")){
      soma(q);
    }else{
      dequeue(q);
    }
    scanf("%s", comando);
  }
  return 0;
}