#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack(){
  STACK* s = (STACK *)malloc(sizeof(STACK));
  s->head = NULL;
  return s;
};

//Recebe um elemento e cria e retorna um novo node
// com o elemento passado
NODE* create_node(int element){
  NODE *n = (NODE *)malloc(sizeof(NODE));
  n->element = element;
  n->next = NULL;
  return n;
};

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack){
  return stack->head == NULL;
};

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack){
  if(IS_EMPTY(stack)){
    return -1;
  }

  NODE *top = stack->head;
  int element = top->element;
  stack->head = top->next;
  free(top);
  return element;

};

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element){
  NODE *node = create_node(element);
  node->next = stack->head;
  stack->head = node;
};

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char operation){
  int num1 = POP(stack);
  int num2 = POP(stack);
  if(operation == '+'){
    PUSH(stack, num1 + num2);
  }else if(operation =='-'){
    PUSH(stack, num2 - num1);
  }else if(operation == '/'){
    PUSH(stack, num2 / num1);
  }else if(operation =='*' || operation == 'x'){
    PUSH(stack, num1 * num2);
  }
 
};

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size){
  char token[20];
  for (int i = 0; i < size; i++){
    scanf(" %s", &token);
    if((token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == 'x') && token[1] == '\0'){
      result(calculadora, token[0]);
    }else{
      PUSH(calculadora, atoi(token));
    }
  }
  
};

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));

}