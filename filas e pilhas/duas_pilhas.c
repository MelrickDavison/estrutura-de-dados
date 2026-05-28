#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct pilha_dupla {
    ITEM vet[TAM];
    int topo1, topo2;
} TPilhaDupla;

void create(TPilhaDupla *pd) {
  pd->topo1 = -1;
  pd->topo2 = 50;
}

void destroy(TPilhaDupla *pd) {
  pd->topo1 = -1;
  pd->topo2 = 50;
}

int isfull(TPilhaDupla *pd) {
	if(pd->topo1+1 == pd->topo2){
    return 1;
  }else{
    return 0;
  }
}

int isempty(TPilhaDupla *pd, int topo) {
	if(pd->topo1 == -1 && topo == 1){
    return 1;
  }

  if(pd->topo2 == 50 && topo == 2){
    return 1;
  }

  return 0;
}

void push(TPilhaDupla *pd, ITEM x, int topo) {
	
  if(!isfull(pd)){
    if(topo == 1){
      pd->topo1++;
      pd->vet[pd->topo1] = x;
    }

    if(topo == 2){
      pd->topo2--;
      pd->vet[pd->topo2] = x;
    }
  }

}

ITEM pop(TPilhaDupla *pd, int topo) {
	  if(!isempty(pd, topo)){
    if(topo == 1){
      int i = pd->topo1;
      pd->topo1 = i-1;
      return pd->vet[i];
    }

    if(topo == 2){
      int i = pd->topo2;
      pd->topo2 = i+1;
      return pd->vet[i];
    }
  }
}

ITEM top(TPilhaDupla *pd, int topo) {
	 if(!isempty(pd, topo)){
    if(topo == 1){
      int i = pd->topo1 - 1;
      return pd->vet[i];
    }

    if(topo == 2){
      int i = pd->topo2 + 1;
      return pd->vet[i];
    }
  }
}

void preenche(TPilhaDupla *pd) {
    ITEM x;
    int topo, qtd, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &topo);
        push(pd, x, topo);
    }
}

void exibe(TPilhaDupla *pd) {
    int topo;

    while( scanf("%d", &topo) != EOF )
        printf("TOPO %d = %c\n", topo, pop(pd, topo));
}

int main(void) {
    TPilhaDupla pd;

    create(&pd);
    preenche(&pd);
    exibe(&pd);
    destroy(&pd);

    return 0;
}
