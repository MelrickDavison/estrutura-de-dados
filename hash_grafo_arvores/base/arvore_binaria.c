#include <stdio.h>


typedef struct binary_tree {
 int item;
 binary_tree *left;
 binary_tree *right;
}binary_tree;

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right){
 binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
  new_binary_tree->item = item;  
  new_binary_tree->left = left;
  new_binary_tree->right = right;
  return new_binary_tree;
}


void print_in_order(binary_tree *bt){
  if (!is_empty(bt)) {
    print_in_order(bt->left);
    printf("%d", bt->item);
    print_in_order(bt->right);
  }
}

 void print_pre_order(binary_tree *bt){
  if (!is_empty(bt)) {
    printf("%d", bt->item);
    print_pre_order(bt->left);
    print_pre_order(bt->right);
  }
 }

 void print_post_order(binary_tree *bt){
  if (!is_empty(bt)) {
    print_post_order(bt->left);
    print_post_order(bt->right);
  }
}

binary_tree* search(binary_tree *bt, int item){
  if ((bt == NULL) || (bt->item == item)) {
    return bt;
  } else if (bt->item > item) {
    return search(bt->left, item);
  } else {
    return search(bt->right, item);
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

binary_tree* remove(binary_tree *bt, int item){
  if (bt == NULL) {
    return NULL;
  }
  if (bt->item < item) {
    bt->right = remove(bt->right, item);
  } else if (bt->item > item) {
    bt->left = remove(bt->left, item);
  } else {
  if (bt->right == NULL && bt->left == NULL) {
    free(bt);
    bt = NULL;
  } else if (bt->right == NULL) {
    binary_tree* temp = bt;
    bt = bt->left;
    free(temp);
  } else if (bt->left == NULL) {
  binary_tree* temp = bt;
    bt = bt->right;
    free(temp);
  } else {
    binary_tree* successor = find_successor(bt->right);
    bt->item = successor->item;
    bt->right = remove(bt->right, successor->item);
  }
  }
    return bt;
}