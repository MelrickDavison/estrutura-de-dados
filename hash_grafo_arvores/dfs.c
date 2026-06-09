#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node *next;
} Node;

typedef struct {
    int id;
    char name[20];
} Leaf;

int cmp_leaves(const void *a, const void *b) {
    return strcmp(((Leaf*)a)->name, ((Leaf*)b)->name);
}

int main() {
    int n;
    
    while (scanf("%d", &n) == 1) {
        char names[205][20];
        int num_nodes = 0;
        
        int out_degree[205] = {0};
        Node *rev_adj[205] = {NULL}; 
        int removed[205] = {0};

        for (int i = 0; i < n; i++) {
            char s1[20], s2[20];
            scanf("%s %s", s1, s2);

            int u = -1, v = -1;

            for (int j = 0; j < num_nodes; j++) {
                if (strcmp(names[j], s1) == 0) { u = j; break; }
            }
            if (u == -1) { strcpy(names[num_nodes], s1); u = num_nodes++; }

            for (int j = 0; j < num_nodes; j++) {
                if (strcmp(names[j], s2) == 0) { v = j; break; }
            }
            if (v == -1) { strcpy(names[num_nodes], s2); v = num_nodes++; }

            out_degree[u]++;

            Node *newNode = (Node *)malloc(sizeof(Node));
            newNode->id = u;
            newNode->next = rev_adj[v];
            rev_adj[v] = newNode;
        }

        int nodes_left = num_nodes;

        while (nodes_left > 0) {
            Leaf current_leaves[205];
            int count = 0;

            for (int i = 0; i < num_nodes; i++) {
                if (!removed[i] && out_degree[i] == 0) {
                    current_leaves[count].id = i;
                    strcpy(current_leaves[count].name, names[i]);
                    count++;
                }
            }

            qsort(current_leaves, count, sizeof(Leaf), cmp_leaves);

            for (int i = 0; i < count; i++) {
                int id_to_remove = current_leaves[i].id;

                printf("%s\n", current_leaves[i].name);
                
                removed[id_to_remove] = 1;
                nodes_left--;

                Node *curr = rev_adj[id_to_remove];
                while (curr != NULL) {
                    out_degree[curr->id]--;
                    curr = curr->next;
                }
            }
        }

        for (int i = 0; i < num_nodes; i++) {
            Node *curr = rev_adj[i];
            while (curr != NULL) {
                Node *temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
    }
    return 0;
}