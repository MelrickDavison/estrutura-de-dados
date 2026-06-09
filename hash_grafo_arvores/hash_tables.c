#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

int main() {
    int N;
    
    if (scanf("%d", &N) != 1) return 0;

    for (int t = 0; t < N; t++) {
        int M, C;
        scanf("%d %d", &M, &C);

        Node** table = (Node**)malloc(M * sizeof(Node*));
        for (int i = 0; i < M; i++) {
            table[i] = NULL; 
        }


        for (int i = 0; i < C; i++) {
            int key;
            scanf("%d", &key);
            

            int idx = key % M;

            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->key = key;
            new_node->next = NULL;

            if (table[idx] == NULL) {
                table[idx] = new_node;
            } else {
                Node* curr = table[idx];
                while (curr->next != NULL) {
                    curr = curr->next;
                }
                curr->next = new_node;
            }
        }

        for (int i = 0; i < M; i++) {
            printf("%d -> ", i);
            Node* curr = table[i];
            while (curr != NULL) {
                printf("%d -> ", curr->key);
                curr = curr->next;
            }
            printf("\\\n");
        }

        if (t < N - 1) {
            printf("\n");
        }

        for (int i = 0; i < M; i++) {
            Node* curr = table[i];
            while (curr != NULL) {
                Node* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(table);
    }

    return 0;
}