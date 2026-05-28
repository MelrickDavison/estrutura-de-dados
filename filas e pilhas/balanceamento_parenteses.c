#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct node{
  char item;
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


void push(Stack *stack, char item){
  Node *new_top = (Node*) malloc(sizeof(Node));
  new_top->item = item;
  new_top->next = stack->top;
  stack->top = new_top;
  stack->length++;
}


int is_empty(Stack *stack){
  return stack->top == NULL;
}


char pop(Stack *stack){
  Node *node = stack->top;
  stack->top = stack->top->next;
  char valor = node->item;
  stack->length--;
  free(node);
  return valor;
}

void destroy_stack(Stack *stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}

int peek_node(Stack *stack){
  if(is_empty(stack)){
    return -1;
  }
  return stack->top->item;
}



int balanceamento(const char *comando){
  Stack *s = create_stack();
for (int i = 0; i < strlen(comando); i++) {
  char c = comando[i];
  if (c == ' ' || c == '\n' || c == '\r') {
    continue;
  }
  
  if (c == '(' || c == '[') {
    push(s, c);
  } else if (c == ')' || c == ']') {
    if (is_empty(s)) {
      destroy_stack(s);
      return 0; 
    }
            
    char topo = pop(s);
    if ((c == ')' && topo != '(') || (c == ']' && topo != '[')) {
      destroy_stack(s);
      return 0;
      }
    }
  }

    int balanceado = is_empty(s);
    
    destroy_stack(s);
    
    return balanceado;
}


int main(){

  Stack *s = create_stack();
  int n;
  scanf("%d", &n);
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  char comando[300];

  for (int i = 0; i < n; i++) {
    if (fgets(comando, sizeof(comando), stdin) == NULL) {
      comando[0] = '\0';
    }
        
    if (balanceamento(comando)) {
        printf("Yes\n");
    } else {
      printf("No\n");
    }
    }
  return 0;
}