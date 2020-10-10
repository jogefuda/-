#include <string.h>

static void _merge(int *arr,
            int begin, int middle, int end,
            int *out) {
    int i, j, k;
    
    i = begin, j = begin, k = middle;
    while (i < end) {
        if (j < middle && (k >= end || arr[k] >= arr[j]))
            out[i++] = arr[j++];
        else
            out[i++] = arr[k++];
    }
}

static void _merge_sort(int *arr,
                        int begin, int middle, int end,
                        int *out) {
    if (end - begin <= 1)
        return;
    
    _merge_sort(out, begin, (begin + middle) / 2, middle, arr);
    _merge_sort(out, middle, (middle + end) / 2, end, arr);
    _merge(arr, begin, middle, end, out);
}

static void merge_sort(int *arr, int *out, int len) {
    memcpy(out, arr, len * sizeof(int));
    _merge_sort(arr, 0, len / 2, len, out);
}

