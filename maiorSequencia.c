#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
  char valor;
  struct node *next;
}node;

typedef struct{
  node *head;
}queue;

int is_empty(queue *q){
  return q->head == NULL;
}


void enqueue(queue *q, char v){
  node *new_node = (node*) malloc(sizeof(node));
  new_node->valor = v;
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

void limpar_fila(queue *q) {
    node *current = q->head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    q->head = NULL;
}


void contar_zeros(queue *q){
 node *current = q->head;

  int contador = 0, contadorGeral = 0, indiceMaior, i = 0;
  while(current != NULL){
    if(current->valor == '0'){
      contador++;
    }else{
      if(contadorGeral < contador){
        contadorGeral = contador;
        indiceMaior = i-1;
      }
      contador = 0;
    }
    i++;
    current = current->next;
  }

  if (contador > contadorGeral) {
        contadorGeral = contador;
        indiceMaior = i - 1;
    }

    int indiceInicio = indiceMaior - contadorGeral + 1;

  printf("%d %d\n", indiceInicio, indiceMaior);
}



int main() {
  char linha[100000];
  
  queue *q = malloc(sizeof(queue));
  q->head = NULL;

    while (scanf("%s", linha) != EOF) {
      if(!strcmp(linha, "0")){
        break;
      }

      for (int i = 0; i < strlen(linha); i++){
        enqueue(q, linha[i]);
      }
      contar_zeros(q);
      limpar_fila(q);
    }
    return 0;
}

