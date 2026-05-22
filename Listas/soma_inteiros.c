#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Removi a math.h pois não estava sendo usada

typedef struct node {
    int digito;
    struct node *next;
    struct node *prev;
} node;

typedef struct {
    node *head;
    node *tail;
} lista;

void inicializar(lista *l) {
    l->head = NULL;
    l->tail = NULL;
}

node* criarNo(int item, node *ant, node *prox) {
    node* pNovo = (node*) malloc(sizeof(node));
    pNovo->digito = item;
    pNovo->prev = ant;
    pNovo->next = prox;
    return pNovo;
}

void add(lista *l, int digito) {
    
    node *novo = criarNo(digito, l->tail, NULL);

    if (l->head == NULL) { 
        l->head = novo;
    } else {              
        l->tail->next = novo; 
    }
    
    l->tail = novo; 
}

void exibirListaCabecaCauda(lista *l) {
    node* p = l->tail;
    while (p) {
        printf("%d ", p->digito);
        p = p->prev;
    }
    printf("\n");
}

void somar(lista *l1, lista *l2, lista *l3){
  node *current1 = l1->tail;
  node *current2 = l2->tail;
  int vai_um = 0;

  while(current1 != NULL || current2 != NULL || vai_um > 0){
    int d1 = 0;
    int d2 = 0;
    
    if(current1 != NULL){
      d1 = current1->digito;
      current1 = current1->prev;
    }

    if(current2 != NULL){
      d2 = current2->digito;
      current2 = current2->prev;
    }

    int soma = d1 + d2 + vai_um;
    int resto = soma % 10;
    vai_um = soma/10;
    add(l3, resto);
  }

}

int main() {
  // freopen("entrada.txt", "r", stdin);
  lista l1, l2, l3;

  inicializar(&l1);
  inicializar(&l2);
  inicializar(&l3);

  char digito[10];
  int lista = 1;
  
  int flag2 = 1;
  int flag1 = 1;
  while (scanf("%s", digito) != EOF) {
    if (digito[0] == '+'){
      lista = 2;
      continue;
    }

    if(digito[0] == '='){
      break;
    }
    
    int valor = digito[0] - '0';
    if(lista == 1){
      if(flag1 && valor == 0){
        continue;
      }
      flag1 = 0;
      add(&l1, valor);
    }else{
         if(flag2 && valor == 0){
        continue;
      }
      flag2 = 0;
      add(&l2, valor);
      }
  }

  if(l1.head == NULL && l2.head == NULL){
    printf("Lista vazia!\n");
  }else{
    somar(&l1, &l2, &l3);
    exibirListaCabecaCauda(&l3);
  }
  return 0;
}