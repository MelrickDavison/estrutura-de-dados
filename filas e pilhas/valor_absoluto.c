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
  int maior;
  int menor;
} Stack;



Stack* create_stack(){
  Stack *new_stack = (Stack *)malloc(sizeof(Stack));
  new_stack->top = NULL;
  return new_stack;
}


int is_empty(Stack *stack){
  return stack->top == NULL;
}

void procuraMenor(Stack *stack){
  Node *current = stack->top;
  stack->menor = stack->maior;
  while (current!= NULL){
    if(stack->menor > current->item){
      stack->menor = current->item;
    }
    current = current->next;
  }
}

void procuraMaior(Stack *stack){
  Node *current = stack->top;
  stack->maior = -1;
  while (current!= NULL){
    if(stack->maior < current->item){
      stack->maior = current->item;
    }
    current = current->next;
  }
}

void push(Stack *stack, int item){
  if(is_empty(stack)){
    stack->maior = item;
    stack->menor = item;
  }
  Node *new_top = (Node*) malloc(sizeof(Node));
  new_top->item = item;
  new_top->next = stack->top;
  stack->top = new_top;
  stack->length++;
  procuraMaior(stack);
  procuraMenor(stack);
}

int calcula_abs(Stack *stack){
  return stack->maior - stack->menor;
}

int peek_node(Stack *stack){
  if(is_empty(stack)){
    return -1;
  }
  return stack->top->item;
}


void pop(Stack *stack){
  if(is_empty(stack)){
    return;
  }

  printf("%d\n", peek_node(stack));
  Node *node = stack->top;
  stack->top = stack->top->next;
  stack->length--;
  free(node);
  procuraMaior(stack);
  procuraMenor(stack);
}

int main(){

  Stack *s = create_stack();
  s->length = 0;
  s->maior = 0;
  s->menor = 0;
  char comando[100];
  int value;
  while(scanf("%s", comando) != EOF){
    if(!strcmp(comando, "push")){
      scanf("%d", &value);
      push(s, value);
    }else if(!strcmp(comando, "pop")){
      pop(s);
    }else{
      printf("%d\n", calcula_abs(s));
    }
  }
  return 0;
}