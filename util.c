#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void randn(int *arr, int len) {
    for (size_t i = 0; i < len; ++i)
        arr[i] = rand() % 10;
}

void dump(int *arr, int len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%d", arr[i]);

        if (i!=len-1)
            printf(" -> ");
    } 
    printf("\n");
}
