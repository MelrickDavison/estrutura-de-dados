#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

typedef struct binary_tree {
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right){
    binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
    new_binary_tree->item = item;  
    new_binary_tree->left = left;
    new_binary_tree->right = right;
    return new_binary_tree;
}

binary_tree* parse_tree(char **str) {
    while (**str == ' '){
      (*str)++;
    } 

    if (**str == '('){
      (*str)++;
    }
      if (**str == ')') {
        (*str)++; 
        return NULL;
    }

    int numero = 0;
    while (isdigit(**str)) {
        numero = numero * 10 + (**str - '0');
        (*str)++;
    }
    binary_tree *node = create_binary_tree(numero, NULL, NULL);

    node->left = parse_tree(str);
    node->right = parse_tree(str);

    while (**str == ' '){
      (*str)++;
    } 
    if (**str == ')'){
      (*str)++;
    } 
    return node;
}

int is_bst_inorder(binary_tree *node, binary_tree **prev) {
    if (node == NULL) {
        return 1;
    }

    if (!is_bst_inorder(node->left, prev)) {
        return 0;
    }

    if (*prev != NULL && node->item <= (*prev)->item) {
        return 0; 
    }
    
    *prev = node;
    return is_bst_inorder(node->right, prev);
}

int check_binary_tree(binary_tree *bt){
    binary_tree *prev = NULL;
    return is_bst_inorder(bt, &prev);
}

int main() {
    char entrada[10000]; 

    if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strcspn(entrada, "\n")] = 0;

        char *ptr = entrada;
        binary_tree *bt = parse_tree(&ptr);

        if(check_binary_tree(bt)){
            printf("VERDADEIRO\n");
        }else{
            printf("FALSO\n");
        }
    }

    return 0;
}