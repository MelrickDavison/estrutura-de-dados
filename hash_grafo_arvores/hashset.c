#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int search_and_count(HashTable* ht, int k, int* found) {
    int idx = k % ht->size;
    Node* curr = ht->table[idx];
    int c = 0;
    *found = 0;
    
    while (curr != NULL) {
        c++;
        if (curr->key == k) {
            *found = 1;
            break;
        }
        curr = curr->next;
    }
    return c;
}

HashTable* rehash(HashTable* ht) {
    int new_m = 2 * ht->size - 1;
    HashTable* new_ht = create_hash_table(new_m);
    
    for (int i = 0; i < ht->size; i++) {
        Node* curr = ht->table[i];
        while (curr != NULL) {
            Node* next = curr->next;

            int idx = curr->key % new_m;
            curr->next = new_ht->table[idx];
            new_ht->table[idx] = curr;
            
            new_ht->total_elements++;
            curr = next;
        }
    }
    
    free(ht->table);
    free(ht);
    
    return new_ht;
}

void op_add(HashTable** ht_ptr, int k, int op_num) {
    HashTable* ht = *ht_ptr;
    int found;
    int c = search_and_count(ht, k, &found);
    
    if (found) {
        printf("%d 0 %d\n", op_num, c);
    } else {
        int idx = k % ht->size;
        
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->key = k;
        new_node->next = ht->table[idx];
        ht->table[idx] = new_node;
        
        ht->total_elements++;
        printf("%d 1 %d\n", op_num, c);
        
        if ((ht->total_elements * 4) >= (ht->size * 3)) {
            *ht_ptr = rehash(ht);
        }
    }
}

void op_del(HashTable* ht, int k, int op_num) {
    int idx = k % ht->size;
    Node* curr = ht->table[idx];
    Node* prev = NULL;
    int c = 0;
    int found = 0;
    
    while (curr != NULL) {
        c++;
        if (curr->key == k) {
            found = 1;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    
    if (found) {
        if (prev == NULL) {
            ht->table[idx] = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
        ht->total_elements--;
        printf("%d 1 %d\n", op_num, c);
    } else {
        printf("%d 0 %d\n", op_num, c);
    }
}

void op_has(HashTable* ht, int k, int op_num) {
    int found;
    int c = search_and_count(ht, k, &found);
    printf("%d %d %d\n", op_num, found, c);
}
 
void op_prt(HashTable* ht, int op_num) {
    int max_len = 0;
    for (int i = 0; i < ht->size; i++) {
        int len = 0;
        Node* curr = ht->table[i];
        while (curr != NULL) {
            len++;
            curr = curr->next;
        }
        if (len > max_len) {
            max_len = len;
        }
    }
    printf("%d %d %d %d\n", op_num, ht->size, ht->total_elements, max_len);
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
    HashTable* ht = create_hash_table(7); 
    
    char op[4];
    int k;
    int i = 0;
    
    while (scanf("%s", op) == 1) {
        if (strcmp(op, "ADD") == 0) {
            scanf("%d", &k);
            op_add(&ht, k, i);
        } else if (strcmp(op, "DEL") == 0) {
            scanf("%d", &k);
            op_del(ht, k, i);
        } else if (strcmp(op, "HAS") == 0) {
            scanf("%d", &k);
            op_has(ht, k, i);
        } else if (strcmp(op, "PRT") == 0) {
            op_prt(ht, i);
        }
        i++;
    }
    
    free_table(ht);
    return 0;
}