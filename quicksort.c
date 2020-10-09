#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void
print_arr(int *arr, int len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void
bubble_sort(int *arr, int len) {
    int change = 1;
    while (len --> 0 && change) {
        change = 0;
        for (size_t j = 0; j < len; ++j) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                change = 1;
            }
        }
    }
}

void
selection_sort(int *arr, int len) {
    for (size_t i = 0; i < len; ++i) {
        int min_idx = i;
        for (size_t j = i; j < len; ++j) {
            if (arr[min_idx] > arr[j]) {
                min_idx = j;
            }
        }
        int tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

void
insertion_sort(int *arr, int len) {
    for (size_t i = 1; i < len; ++i) {
        for (size_t j = i; j > 0; --j) {
            if (arr[j-1] > arr[j]) {
                int tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
            } else {
                break;
            }
        }
    }
}


void
merge(int *arr, int a, int b, int c, int *out) {
    int i, j, k;

    j = a, k = b;
    for (i = a; i < c; i++) {
        if (j < b && (k>=c || arr[j] <= arr[k])) {
            out[i] = arr[j];
            j = j + 1;
        } else {
            out[i] = arr[k];
            k = k + 1;
        }
    }
}

void
_merge_sort(int *arr, int a, int c, int *out) {
    if (c-a <= 1)
        return;
    int b = (c + a) / 2;              // imiddle = mid point
    _merge_sort(out, a, b, arr);
    _merge_sort(out, b, c, arr);
    merge(arr, a, b, c, out);
}

void
merge_sort(int *arr, int *out, int len) {
    memcpy(out, arr, len * sizeof(arr[0]));
    _merge_sort(arr, 0, len, out);
}

void gen_rand(int *arr, int len) {
    for (size_t i = 0; i < len; ++i) {
        arr[i] = rand() % 100;
    }
}
int
main(int argc, char **argv) {
    int len = 30000;
    int *arr = (int *)malloc(len * sizeof(int));
    int *out = (int *)malloc(len * sizeof(int));
    gen_rand(arr, len);
    merge_sort(arr, out, len);
    print_arr(out, len);
    free(arr);
    return 0;
}
