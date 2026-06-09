#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node* parse_tree(const char **str) {
    while (**str == ' ' || **str == '\n' || **str == '\r') {
        (*str)++;
    }

    if (**str == '\0') return NULL;

    if (**str == '(') {
        (*str)++; 
        while (**str == ' ' || **str == '\n' || **str == '\r') (*str)++;

        if (**str == ')') {
            (*str)++;
            return NULL;
        }

        int val = 0;
        int sign = 1;
        if (**str == '-') {
            sign = -1;
            (*str)++;
        }
        while (**str >= '0' && **str <= '9') {
            val = val * 10 + (**str - '0');
            (*str)++;
        }
        val *= sign;

        Node *node = (Node*)malloc(sizeof(Node));
        node->value = val;
        node->left = parse_tree(str);
        node->right = parse_tree(str);

        while (**str == ' ' || **str == '\n' || **str == '\r') (*str)++;

        if (**str == ')') {
            (*str)++;
        }

        return node;
    }
    return NULL;
}

int get_height_and_count(Node* root, int *count) {
    if (!root) {
        *count = 0;
        return -1;
    }
    
    int left_count = 0, right_count = 0;
    int hl = get_height_and_count(root->left, &left_count);
    int hr = get_height_and_count(root->right, &right_count);
    
    *count = 1 + left_count + right_count;
    
    return 1 + (hl > hr ? hl : hr);
}

void print_one_child_nodes(Node *root) {
    if (!root) return;
    
    print_one_child_nodes(root->left);

    int children = 0;
    if (root->left) children++;
    if (root->right) children++;

    if (children == 1) {
        printf(" %d", root->value);
    }

    print_one_child_nodes(root->right);
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    char *buffer = (char*)malloc(2000005 * sizeof(char));
    if (!buffer) return 1;

    if (fgets(buffer, 2000005, stdin) != NULL) {
        const char *ptr = buffer;
        Node *root = parse_tree(&ptr);

        if (root) {
            int count = 0;
            int h = get_height_and_count(root, &count);

            long long expected_nodes = (1LL << (h + 1)) - 1;

            if (count == expected_nodes) {
                printf("completa\n");
                printf("total de nos: %d\n", count);
            } else {
                printf("nao completa\n");
                printf("nos com um filho:");
                print_one_child_nodes(root);
                printf("\n");
            }
        }
        free_tree(root);
    }
    
    free(buffer);
    return 0;
}