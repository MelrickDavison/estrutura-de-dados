#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100


//Define Node
typedef struct node{
  int item;
  struct node *next;
} Node;

//Stack with node
typedef struct {
  Node *top;
} Stack_node;


//Define Stack
typedef struct {
  int current_size;
  int items[MAX_STACK_SIZE];
} Stack;

//Criar Stack
Stack* create_stack(){
  Stack *new_stack = (Stack*)malloc(sizeof(Stack));
  new_stack->current_size = 0;
  return new_stack;
}

//Criar Stack with Node
Stack_node* create_stack(){
  Stack_node *new_stack = (Stack_node *)malloc(sizeof(Stack_node));
  new_stack->top = NULL;
  return new_stack;
}

//Push function
void push(Stack *stack, int item){
  if(stack->current_size == MAX_STACK_SIZE){
    printf("Stack overflow");
  } else{
    stack->items[stack->current_size++] = item;
  }
}

//Push function with Node
void push_node(Stack_node *stack, int item){
  Node *new_top = (Node*) malloc(sizeof(Node));
  new_top->item = item;
  new_top->next = stack->top;
  stack->top = new_top;
}

int is_empty(Stack *stack){
  return stack->current_size == 0;
}

int is_empty_node(Stack_node *stack){
  return stack->top == NULL;
}

//Pop function
void pop(Stack *stack){
  if (is_empty(stack)) {
    printf("Stack underflow");
  } else {
    stack->current_size--;
  }
}

void pop_node(Stack_node *stack){
  if(is_empty_node(stack)){
    pritnf("stack underflow");
    return;
  }

  Node *node = stack->top;
  stack->top = stack->top->next;
  free(node);
}

int peek(Stack *stack){
  return stack->items[stack->current_size - 1];
}

int peek_node(Stack_node *stack){
  if(is_empty_node(stack)){
    return -1;
  }
  return stack->top->item;
}