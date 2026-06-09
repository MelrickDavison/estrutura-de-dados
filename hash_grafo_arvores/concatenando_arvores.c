#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* duplicate_string(const char* s) {
    char* d = (char*)malloc(strlen(s) + 1);
    if (d != NULL) strcpy(d, s);
    return d;
}

char* replace_leaf(char *base, const char *incoming) {

    char root_str[100];
    int r = 0;
    int i = 1;

    while (incoming[i] != '(' && incoming[i] != ')' && incoming[i] != '\0') {
        root_str[r++] = incoming[i++];
    }
    root_str[r] = '\0';

    char search_str[150];
    sprintf(search_str, "(%s()())", root_str);

    char *pos = strstr(base, search_str);
    
    if (!pos) {
        return base;
    }

    int prefix_len = pos - base;
    int new_len = strlen(base) - strlen(search_str) + strlen(incoming) + 1;
    char *new_base = (char*)malloc(new_len);

    strncpy(new_base, base, prefix_len);
    new_base[prefix_len] = '\0';
    strcat(new_base, incoming);              
    strcat(new_base, pos + strlen(search_str));

    free(base);
    return new_base;
}

int main() {
    char *buffer = (char*)malloc(2000000 * sizeof(char));
    if (!buffer) return 1;

    char *base_tree = NULL;

    if (scanf("%s", buffer) != 1) {
        free(buffer);
        return 0;
    }
    base_tree = duplicate_string(buffer);

    while (scanf("%s", buffer) == 1) {
        if (strcmp(buffer, "()") == 0) {
            break;
        }
        base_tree = replace_leaf(base_tree, buffer);
    }

    printf("%s\n", base_tree);
    free(base_tree);
    free(buffer);

    return 0;
}