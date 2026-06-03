#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct binary_tree {
  int item;
  struct binary_tree *left;
  struct binary_tree *right;
} binary_tree;

binary_tree* create_empty_binary_tree(){
  return NULL;
}

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right){
  binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
  new_binary_tree->item = item;  
  new_binary_tree->left = left;
  new_binary_tree->right = right;
  return new_binary_tree;
}

void print_pre_order(binary_tree *bt){
  if (bt != NULL) {
    printf(" ( %d ", bt->item); 
    
    if(bt->left == NULL){
      printf(" () ");
    }else{
      print_pre_order(bt->left);
    }

    if(bt->right == NULL){
      printf(" () ");
    }else{
      print_pre_order(bt->right);
    }
    
    printf(") "); 
  }
}

binary_tree* add(binary_tree *bt, int item){
  if (bt == NULL) {
    bt = create_binary_tree(item, NULL, NULL);
  } else if (bt->item > item) {
    bt->left = add(bt->left, item);
  } else {
    bt->right = add(bt->right, item);
  }
  return bt;
}

int main() {
  char entrada[1000];

  binary_tree *bt = create_empty_binary_tree();

  if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
    entrada[strcspn(entrada, "\n")] = 0;
    char *token = strtok(entrada, " ");

    while(token != NULL){
      int numero = atoi(token);
      printf("----\n");
      printf("Adicionando %d\n", numero);
      bt = add(bt, numero);
      printf("  "); 
      print_pre_order(bt);
      printf("\n"); 

      token = strtok(NULL, " ");
    }
    printf("----\n");
  }
  
  return 0;
}