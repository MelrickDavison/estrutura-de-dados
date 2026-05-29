#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int itens[MAX];
    int topo;
} TPilha;

void inicializa(TPilha *p) {
    p->topo = -1;
}

int vazia(TPilha *p) {
    return (p->topo == -1);
}

void empilha(TPilha *p, int x) {
    if (p->topo < MAX - 1) {
        p->topo++;
        p->itens[p->topo] = x;
    }
}

int desempilha(TPilha *p) {
    if (!vazia(p)) {
        int x = p->itens[p->topo];
        p->topo--;
        return x;
    }
  return -1;
}
char *hexadecimal(int n) {
    char *resultado = (char *)malloc(20 * sizeof(char));
    if (n == 0) {
        resultado[0] = '0';
        resultado[1] = '\0';
        return resultado;
    }

    TPilha p;
    inicializa(&p);
    while (n > 0) {
        empilha(&p, n % 16);
        n = n / 16;
    }

    int i = 0;
    
    while (!vazia(&p)) {
        int digito = desempilha(&p);
        
        if (digito < 10) {
            resultado[i] = digito + '0';
        } else {
            resultado[i] = (digito - 10) + 'A';
        }
        i++;
    }
    resultado[i] = '\0'; 

    return resultado;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {

        char *str_hex = hexadecimal(n);

      printf("%s\n", str_hex);
        free(str_hex);
    }
    
    return 0;
}