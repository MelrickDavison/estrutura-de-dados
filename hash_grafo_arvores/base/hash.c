#include <stdio.h>
#include <stdlib.h>

// Estruturas base para a Tabela Hash
typedef struct element {
    int key;
    int value;
} element;

typedef struct hash_table {
    element *table[11];
} hash_table;

// Inicializa a tabela hash com nulos
hash_table* create_hash_table() {
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
    int i;
    for (i = 0; i < 11; i++) {
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

// Insere um elemento usando tentativa linear para colisões
void put(hash_table *ht, int key, int value) {
    int h = key % 11;
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            ht->table[h]->value = value;
            break;
        }
        h = (h + 1) % 11;
    }
    
    if (ht->table[h] == NULL) {
        element *new_element = (element*) malloc(sizeof(element));
        new_element->key = key;
        new_element->value = value;
        ht->table[h] = new_element;
    }
}

// Busca um elemento na tabela
int get(hash_table *ht, int key) {
    int h = key % 11;
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            return ht->table[h]->value;
        }
        h = (h + 1) % 11;
    }
    return -100; // Retorna -100 se a chave não for encontrada
}

// Remove um elemento (versão corrigida utilizando flag -1)
void remove_key(hash_table *ht, int key) {
    int h = key % 11;
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            ht->table[h]->key = -1;
        }
        h = (h + 1) % 11;
    }
}