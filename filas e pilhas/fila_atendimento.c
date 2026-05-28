#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
  int id;
  int idade;
  struct node *next;
}node;

typedef struct{
  node *head;
}queue;

int is_empty(queue *q){
  return q->head == NULL;
}

void enqueue(queue *q, int id, int idade){
  node *new_node = (node*) malloc(sizeof(node));
  new_node->id = id;
  new_node->idade = idade;
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
    return;
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
       printf("ID: %d IDADE: %d\n", current->id, current->idade);
       current = current->next;
     }
  }else{
    printf("fila vazia!\n");
  }
}

int main(){
  queue *q_idosos = (queue*) malloc(sizeof(queue));
  queue *q_nidosos = (queue *)malloc(sizeof(queue));
  q_idosos->head = NULL;
  q_nidosos->head = NULL;
  char comando[100];
  int id, idade;
  int n, i = 0;
  scanf("%d", &n);
  scanf("%s", comando);
  while(strcmp(comando, "f")){
    if(!strcmp(comando, "a")){
      scanf("%d %d", &id, &idade);
      if(idade > 60){
        enqueue(q_idosos, id, idade);
      }else{
        enqueue(q_nidosos, id, idade);
      }
    }else if(!strcmp(comando, "i")){
      printf("fila de idosos:\n");
      print(q_idosos);
      printf("fila de nao-idosos:\n");
      print(q_nidosos);
      printf("----------\n");
      printf("\n");
      }else{
      if(i < n){
        if(!is_empty(q_idosos)){
          dequeue(q_idosos);
          i++;
        }else{
          dequeue(q_nidosos);
          i = 0;
        }
      }else{
        if(!is_empty(q_nidosos)){
          dequeue(q_nidosos);
        }else{
          dequeue(q_idosos);
        }
        i = 0;
      }
    }
    scanf("%s", comando);
  }
  return 0;
}