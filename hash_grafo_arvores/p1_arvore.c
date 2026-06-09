#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int H;

    if (scanf("%d", &H) != 1) return 0;

    int num_nodes = (1 << H) - 1;

    unsigned long long *V = (unsigned long long *)malloc((num_nodes + 1) * sizeof(unsigned long long));
    unsigned long long *P = (unsigned long long *)malloc((num_nodes + 1) * sizeof(unsigned long long));

    for (int i = 1; i <= num_nodes; i++) {
        scanf("%llu", &V[i]);
    }

    for (int i = num_nodes; i >= 1; i--) {
        int left_child = 2 * i;
        int right_child = 2 * i + 1;

        if (left_child > num_nodes) {
            P[i] = V[i];
        } else {
            unsigned long long pl = V[i] * P[left_child];
            unsigned long long pr = V[i] * P[right_child];
            P[i] = MAX(pl, pr);
        }
    }

    printf("%llu\n", P[1]);


    free(V);
    free(P);

    return 0;
}