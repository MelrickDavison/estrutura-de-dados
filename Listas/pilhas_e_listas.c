#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
  int *lista;
  int tamanho;
  struct node *next;
} Node;

typedef struct {
  Node *top;
} Stack_node;

Stack_node* create_stack(){
  Stack_node *new_stack = (Stack_node *)malloc(sizeof(Stack_node));
  new_stack->top = NULL;
  return new_stack;
}

void push_node(Stack_node *stack, int *lista, int tamanho){
  Node *new_top = (Node*) malloc(sizeof(Node));
  new_top->lista = (int*) malloc(tamanho*sizeof(int));
  new_top->tamanho = tamanho;

  for (int i = 0; i < tamanho; i++){
    new_top->lista[i] = lista[i];
  }

  new_top->next = stack->top;
  stack->top = new_top;
}

int is_empty_node(Stack_node *stack){
  return stack->top == NULL;
}

void pop_node(Stack_node *stack){
  if(is_empty_node(stack)) return;

  Node *node = stack->top;
  stack->top = stack->top->next;

  free(node->lista);
  free(node);
}

void peek_node(Stack_node *stack){
  if(is_empty_node(stack)){
    printf("EMPTY STACK\n");
    return;
  }

  printf("%d",  stack->top->lista[0]);
  for (int i = 1; i < stack->top->tamanho; i++){
    printf(" %d", stack->top->lista[i]);
  }
  printf("\n");
}

int main() {
  char linha[100000];
  int lista[50000];

  Stack_node *stack = create_stack();

  while (fgets(linha, sizeof(linha), stdin) != NULL){
    linha[strcspn(linha, "\n")] = 0;
    
    if(strcmp(linha, "PUSH") == 0){
      
      if (fgets(linha, sizeof(linha), stdin) == NULL) break;

      int i = 0;
      char *token = strtok(linha, " \n");

      while (token != NULL){
        lista[i++] = atoi(token);
        token = strtok(NULL, " \n");
      }

      push_node(stack, lista, i);
    }

    else if(strcmp(linha, "POP") == 0){
      peek_node(stack);
      pop_node(stack);
    }
  }

  return 0;
}