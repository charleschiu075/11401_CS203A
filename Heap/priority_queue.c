#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    int* data; /* min-heap */
} PriorityQueue;

PriorityQueue* pq_create(size_t capacity) {
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    if (!pq) return NULL;
    pq->capacity = capacity > 0 ? capacity : 8;
    pq->size = 0;
    pq->data = malloc(pq->capacity * sizeof(int));
    if (!pq->data) {
        free(pq);
        return NULL;
    }
    return pq;
}

void pq_destroy(PriorityQueue* pq) {
    if (!pq) return;
    free(pq->data);
    free(pq);
}

static void pq_swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void pq_sift_up(PriorityQueue* pq, size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (pq->data[parent] <= pq->data[idx]) break;
        pq_swap(&pq->data[parent], &pq->data[idx]);
        idx = parent;
    }
}

static void pq_sift_down(PriorityQueue* pq, size_t idx) {
    while (1) {
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;
        size_t smallest = idx;
        if (left < pq->size && pq->data[left] < pq->data[smallest]) smallest = left;
        if (right < pq->size && pq->data[right] < pq->data[smallest]) smallest = right;
        if (smallest == idx) break;
        pq_swap(&pq->data[idx], &pq->data[smallest]);
        idx = smallest;
    }
}

int pq_push(PriorityQueue* pq, int value) {
    if (pq->size == pq->capacity) {
        size_t new_capacity = pq->capacity * 2;
        int* new_data = realloc(pq->data, new_capacity * sizeof(int));
        if (!new_data) return 0;
        pq->data = new_data;
        pq->capacity = new_capacity;
    }
    pq->data[pq->size] = value;
    pq_sift_up(pq, pq->size);
    pq->size++;
    return 1;
}

int pq_pop(PriorityQueue* pq, int* out_value) {
    if (pq->size == 0) return 0;
    *out_value = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    pq_sift_down(pq, 0);
    return 1;
}

int pq_peek(PriorityQueue* pq, int* out_value) {
    if (pq->size == 0) return 0;
    *out_value = pq->data[0];
    return 1;
}

void pq_print(PriorityQueue* pq) {
    printf("[size=%zu, capacity=%zu] [", pq->size, pq->capacity);
    for (size_t i = 0; i < pq->size; ++i) {
        printf("%d", pq->data[i]);
        if (i + 1 < pq->size) printf(", ");
    }
    printf("]\\n");
}
