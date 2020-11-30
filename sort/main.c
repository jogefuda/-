#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue {
    int size;
    int *data;
    int head;
    int tail;
    int curr;
} queue_t;

int isfull(queue_t *q) {
    return q->curr >= q->size;
}

int isempty(queue_t *q) {
    return q->curr == 0;
}

int enqueue(queue_t *q, int val) {
    if (q->tail >= q->size)
        q->tail = 0;
    if (isfull(q)) return -1;
    q->data[q->tail++] = val;
    ++q->curr;
    return q->tail - 1;
}

int dequeue(queue_t *q) {
    if (q->head >= q->size)
        q->head = 0;
    if(isempty(q)) return -1;
    --q->curr;
    return q->data[q->head++];
}

int add(queue_t *q) {
    if (q->curr < 2) return -1;
    return dequeue(q) + dequeue(q);
}

int sub(queue_t *q) {
    if (q->curr < 2) return -1;
    return dequeue(q) - dequeue(q);
}

void front_item(queue_t *q) {
    printf("FirstItem: %d\n", q->data[q->head]);
}

void dump(queue_t *q) {
    for (int i = 0; i < q->size; ++i) {
        printf("%d, ", q->data[i]);
    }
    putc('\n', stdout);
}

int main(int argc, char *argv[]) {
    queue_t q = {
        .head = 0,
        .tail = 0,
        .size = 10,
        .data = (int *)malloc(sizeof(int) * 10)
    };

    memset(q.data, 0, sizeof(int) * q.size);
    enqueue(&q, 100);
    front_item(&q);
    front_item(&q);
    front_item(&q);
    front_item(&q);
    front_item(&q);

    dump(&q);
    return 0;
}
