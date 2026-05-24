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


void push(Stack *stack, int item){
  Node *new_top = (Node*) malloc(sizeof(Node));
  new_top->item = item;
  new_top->next = stack->top;
  stack->top = new_top;
  stack->length++;
}


int is_empty(Stack *stack){
  return stack->top == NULL;
}


void pop(Stack *stack){
  if(is_empty(stack)){
    return;
  }

  Node *node = stack->top;
  stack->top = stack->top->next;
  stack->length--;
  free(node);
}


int soma(Stack *s){
   if(!is_empty(s)){
     int soma = 0;
     Node *current = s->top;
     while (current != NULL){
       soma += current->item;
       current = current->next;
      }
      return soma;
  }else{
    return 0;
  }
}

double avg(Stack *s){
   if(!is_empty(s)){
    return soma(s)/s->length;
  }else{
    return 0;
  }
}

void pow_function(Stack *s){
   if(!is_empty(s)){
     int *array_temp = (int *)malloc(s->length * sizeof(int));
     Node *current = s->top;
     int i = 0;
     while (current != NULL){
       array_temp[i] = current->item;
       current = current->next;
       i++;
      }

      for(int j = i - 1; j >= 0; j--){
        printf("%.f ", pow(array_temp[j], 2));
      }
     printf("\n");
  }else{
    printf("\n");
  }
}


int peek_node(Stack *stack){
  if(is_empty(stack)){
    return -1;
  }
  return stack->top->item;
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

    for (int j = i-1; j >= 0; j--){
      printf("%d ", array_temp[j]);
    }
      printf("\n");
  }else{
    printf("\n");
  }
}


int main(){

  Stack *s = create_stack();
  char comando[100];
  int value;
  scanf("%s", comando);
  while(strcmp(comando, "exit")){
    if(!strcmp(comando, "push")){
      scanf("%d", &value);
      push(s, value);
    }else if(!strcmp(comando, "print")){
      print(s);
    }else if(!strcmp(comando, "sum")){
      printf("%d\n", soma(s));
    }else if(!strcmp(comando, "pop")){
      pop(s);
    }else if(!strcmp(comando, "pow")){
      pow_function(s);
    }else{
      printf("%.2f\n", avg(s));
    }
    scanf("%s", comando);
  }
  return 0;
}