#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct {
    Node** table;
    int size;
    int total_elements;
} HashTable;

HashTable* create_hash_table(int m) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = m;
    ht->total_elements = 0;
    ht->table = (Node**)malloc(m * sizeof(Node*));
    for (int i = 0; i < m; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void insert(HashTable* ht, int k) {
    int idx = k % ht->size;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = k;
    new_node->next = NULL;
    
    ht->total_elements++;
    
    if (ht->table[idx] == NULL || ht->table[idx]->key >= k) {
        new_node->next = ht->table[idx];
        ht->table[idx] = new_node;
        return;
    }
    
    Node* curr = ht->table[idx];
    while (curr->next != NULL && curr->next->key < k) {
        curr = curr->next;
    }
    
    new_node->next = curr->next;
    curr->next = new_node;
}

void remove_key(HashTable* ht, int k) {
    int idx = k % ht->size;
    Node* curr = ht->table[idx];
    Node* prev = NULL;
    
    while (curr != NULL && curr->key != k) {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr == NULL) {
        return;
    }

    if (prev == NULL) {
        ht->table[idx] = curr->next;
    } else {
        prev->next = curr->next;
    }
    
    free(curr);
    ht->total_elements--;
}

void print_table(HashTable* ht) {
    printf("imprimindo tabela hash:\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] == NULL) {
            printf("[%d]:Lista vazia!\n", i);
        } else {
            printf("[%d]:", i);
            Node* curr = ht->table[i];
            while (curr != NULL) {
                printf("%d=>", curr->key);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

void search(HashTable* ht, int k) {
    int idx = k % ht->size;
    Node* curr = ht->table[idx];
    int accesses = 0;
    int found = 0;
    
    while (curr != NULL) {
        accesses++;
        if (curr->key == k) {
            found = 1;
            break; 
        }
        curr = curr->next;
    }
    
    printf("BUSCA POR %d\n", k);
    printf("numero de elementos da tabela hash: %d\n", ht->total_elements);
    if (found) {
        printf("elemento %d encontrado!\n", k);
    } else {
        printf("elemento nao encontrado!\n");
    }
    printf("numero de elementos acessados na tabela hash: %d\n", accesses);
}

void free_table(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* curr = ht->table[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

int main() {
    int m;
    
    if (scanf("%d", &m) != 1) {
        return 0;
    }
    
    HashTable* ht = create_hash_table(m);
    
    char op;
    int k;

    while (scanf(" %c", &op) == 1) {
        if (op == 'f') {
            break;
        } else if (op == 'a') {
            scanf("%d", &k);
            insert(ht, k);
        } else if (op == 'r') {
            scanf("%d", &k);
            remove_key(ht, k);
        } else if (op == 'i') {
            print_table(ht);
        } else if (op == 'p') {
            scanf("%d", &k);
            search(ht, k);
        }
    }
    
    free_table(ht);
    return 0;
}