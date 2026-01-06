#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    size_t capacity;
    int* data;
} Queue;

Queue* queue_create(size_t capacity) {
    Queue* q = malloc(sizeof(Queue));
    if (!q) return NULL;
    q->capacity = capacity > 0 ? capacity : 4;
    q->head = q->tail = q->size = 0;
    q->data = malloc(q->capacity * sizeof(int));
    if (!q->data) {
        free(q);
        return NULL;
    }
    return q;
}

void queue_destroy(Queue* q) {
    if (!q) return;
    free(q->data);
    free(q);
}

static int queue_resize(Queue* q, size_t new_capacity) {
    int* new_data = malloc(new_capacity * sizeof(int));
    if (!new_data) return 0;
    for (size_t i = 0; i < q->size; ++i) {
        new_data[i] = q->data[(q->head + i) % q->capacity];
    }
    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->head = 0;
    q->tail = q->size;
    return 1;
}

int queue_enqueue(Queue* q, int value) {
    if (q->size == q->capacity) {
        if (!queue_resize(q, q->capacity * 2)) return 0;
    }
    q->data[q->tail] = value;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return 1;
}

int queue_dequeue(Queue* q, int* out_value) {
    if (q->size == 0) return 0;
    *out_value = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return 1;
}

int queue_peek(Queue* q, int* out_value) {
    if (q->size == 0) return 0;
    *out_value = q->data[q->head];
    return 1;
}

int queue_is_empty(Queue* q) {
    return q->size == 0;
}

void queue_print(Queue* q) {
    printf("[size=%zu, capacity=%zu, head=%zu, tail=%zu] [", q->size, q->capacity, q->head, q->tail);
    for (size_t i = 0; i < q->size; ++i) {
        printf("%d", q->data[(q->head + i) % q->capacity]);
        if (i + 1 < q->size) printf(", ");
    }
    printf("]\\n");
}

void queue_debug(Queue* q, const char* label) {
    if (label) printf("%s: ", label);
    queue_print(q);
}
