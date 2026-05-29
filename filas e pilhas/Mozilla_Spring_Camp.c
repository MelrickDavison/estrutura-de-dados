#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
  int item;
  struct node *next;
} Node;

typedef struct {
  Node *top;
  int length; 
} Stack;

Stack* create_stack() {
  Stack *new_stack = (Stack *)malloc(sizeof(Stack));
  new_stack->top = NULL;
  new_stack->length = 0;
  return new_stack;
}

void push(Stack *stack, int item) {
  Node *new_top = (Node*) malloc(sizeof(Node));
  new_top->item = item;
  new_top->next = stack->top;
  stack->top = new_top;
  stack->length++;
}

int is_empty(Stack *stack) {
  return stack->top == NULL;
}

void pop(Stack *stack) {
  if (is_empty(stack)) {
    return;
  }
  Node *node = stack->top;
  stack->top = stack->top->next;
  stack->length--;
  free(node);
}

int main() {
  Stack *back_stack = create_stack();
  Stack *forward_stack = create_stack();
  char comando[20];
  int pagina_atual = 0; 

  while (scanf("%s", comando) != EOF) {
    if (strcmp(comando, "ENTER") == 0) {
      if (pagina_atual != 0) {
        push(back_stack, pagina_atual);
      }
      pagina_atual = 1; 
      while (!is_empty(forward_stack)) {
        pop(forward_stack);
      }
      
    } else if (strcmp(comando, "BACK") == 0) {
      if (!is_empty(back_stack)) {
        push(forward_stack, pagina_atual);
        pop(back_stack);
      }
      
    } else if (strcmp(comando, "FORWARD") == 0) {
      if (!is_empty(forward_stack)) {
        push(back_stack, pagina_atual);
        pop(forward_stack);
      }
    }
  }

  // Impressão final estritamente fora do loop de leitura
  printf("BACK: %d\n", back_stack->length);
  printf("FORWARD: %d\n", forward_stack->length);

  return 0;
}