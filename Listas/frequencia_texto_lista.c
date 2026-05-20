#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
  char letra;
  int qtd;
  struct node *next;
}node;

typedef struct{
  node *head;
}queue;

int is_empty(queue *q){
  return q->head == NULL;
}


void enqueue(queue *q, char l, int i){
  node *new_node = (node*) malloc(sizeof(node));
  new_node->qtd = i;
  new_node->letra = l;
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
  char temp_letra;
  int temp_qtd;

  while (current != NULL){
    next = current->next;
    while (next != NULL){
      if(current->letra < next->letra){
        temp_letra = current->letra;
        temp_qtd = current->qtd;
        current->letra = next->letra;
        current->qtd = next->qtd;
        next->letra = temp_letra;
        next->qtd = temp_qtd;
      }
      next = next->next;
    }
    current = current->next;
  }

  
}

int contarLetra(char *str, char c){
  int contador = 0;
  for (int i = 0; i < strlen(str); i++){
    if (c == str[i]) {
          contador++;
        }
  }
  return contador;
}

int jaFoi(char *str, int i){
    for (int j = 0; j < i; j++){ // dqa aa
      if (str[i] == str[j]){
        return 1;
      }
  }
  return 0;
}



int main() {
  char linha[100000];
  
  queue *q = malloc(sizeof(queue));
  q->head = NULL;

  fgets(linha, sizeof(linha), stdin);
  linha[strcspn(linha, "\n")] = '\0';
  int contador = 0;
  for (int i = 0; i < strlen(linha); i++){
    if(!jaFoi(linha, i)){
      //printf("%c\n", linha[i]);
      enqueue(q, linha[i], contarLetra(linha, linha[i]));
    }
  }

  sort(q);
  while (!is_empty(q)){
    node *node = dequeue(q);
    printf("%c %d\n", node->letra, node->qtd);
  }
  
}