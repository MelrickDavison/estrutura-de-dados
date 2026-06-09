#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int get_next_char() {
    int c;
    while ((c = getchar()) != EOF) {
        if (!isspace(c)) {
            return c;
        }
    }
    return EOF;
}

void parse_tree(int target, int current_sum, int *is_empty, int *found) {
    int c = get_next_char();

    if (c != '(') return; 

    c = get_next_char();

    if (c == ')') {
        *is_empty = 1;
        return;
    }

    int sign = 1;

    if (c == '-') {
        sign = -1;
        c = get_next_char(); 
    }
    
    int value = 0;
    while (isdigit(c)) {
        value = value * 10 + (c - '0');
        c = getchar();
    }
    value *= sign;
    ungetc(c, stdin);
    current_sum += value;

    int left_empty = 0;
    int right_empty = 0;

    parse_tree(target, current_sum, &left_empty, found);
    parse_tree(target, current_sum, &right_empty, found);

    c = get_next_char(); 

    if (left_empty && right_empty) {
        if (current_sum == target) {
            *found = 1;
        }
    }

    *is_empty = 0;
}

int main() {
    int target;
    
    while (scanf("%d", &target) == 1) {
        if (target == -1000) {
            break;
        }

        int is_empty = 0;
        int found = 0;
        
        parse_tree(target, 0, &is_empty, &found);

        if (found) {
            printf("sim\n");
        } else {
            printf("nao\n");
        }
    }

    return 0;
}