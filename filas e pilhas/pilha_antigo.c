#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct node{
  int item;
  struct node *next;
} Node;

typedef struct {
  Node *top;
  double length;
} Stack;



Stack* create_stack(){
  Stack *new_stack = (Stack *)malloc(sizeof(Stack));
  new_stack->top = NULL;
  return new_stack;
}


int is_empty(Stack *stack){
  return stack->top == NULL;
}

void print(Stack *s){
   if(!is_empty(s)){
    int *array_temp = (int *)malloc(s->length * sizeof(int));
    int i = 0;
    Node *current = s->top;
    while (current != NULL)
    {
      array_temp[i] = current->item;
      current = current->next;
      i++;
    }

    for (int j = 0; j < i-1; j++){
      printf("%d ", array_temp[j]);
    }
    printf("%d", array_temp[i-1]);
      printf("\n");
  }
}



void push(Stack *stack, int item){
  Node *new_top = (Node*) malloc(sizeof(Node));
  new_top->item = item;
  new_top->next = stack->top;
  stack->top = new_top;
  stack->length++;
  print(stack);
}



void pop(Stack *stack){
  if(is_empty(stack)){
    return;
  }

  Node *node = stack->top;
  stack->top = stack->top->next;
  stack->length--;
  free(node);
  print(stack);
}


int peek_node(Stack *stack){
  if(is_empty(stack)){
    return -1;
  }
  return stack->top->item;
}


int main(){

  Stack *s = create_stack();
  char comando[100];
  int value;
  scanf("%s", comando);
  while(strcmp(comando, "Fim")){
    if(!strcmp(comando, "Empilhar")){
      scanf("%d", &value);
      push(s, value);
    }else if(!strcmp(comando, "Desempilhar")){
      pop(s);
    }
    scanf("%s", comando);
  }
  return 0;
}