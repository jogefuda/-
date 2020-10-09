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
    int len1 = len;
    while (len --> 0 && change) {
        change = 0;
        for (size_t j = 0; j < len; ++j) {
            print_arr(arr, len1);
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

    i = a, j = b;
    for (k = a; k < c; k++) {
        if (i < b && (j>=c || arr[i] <= arr[j])) {
            out[k] = arr[i];
            i = i + 1;
        } else {
            out[k] = arr[j];
            j = j + 1;
        }
    }
}

void
_merge_sort(int *arr, int a, int c, int *out) {
    if (c-a <= 1)
        return;
    int b = (c + a) / 2;              // iMiddle = mid point
    _merge_sort(out, a, b, arr);
    _merge_sort(out, b, c, arr);
    merge(arr, a, b, c, out);
}

void
merge_sort(int *arr, int *out, int len) {
    memcpy(out, arr, len * sizeof(arr[0]));
    _merge_sort(out, 0, len, arr);
}

void TopDownMergeSort(int A[], int B[], int n)
{
    memcpy(B, A, n * sizeof(A[0]));
    _merge_sort(B, 0, n, A);   // sort data from B[] into A[]
}

int
main(int argc, char **argv) {
    //int arr[] = {2,4,1,5,3};
    int arr[] = {45, 9};
    //int arr[] = {1,2,3,6,5};
    int len = sizeof(arr) / sizeof(arr[0]);
    int out[100] = {0};
    merge_sort(arr, out, len);
    printf("--------\n");
    print_arr(arr, len);
    print_arr(out, len);
    return 0;
}
