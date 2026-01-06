#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    int* data;
} Stack;

Stack* stack_create(size_t capacity) {
    Stack* s = malloc(sizeof(Stack));
    if (!s) return NULL;
    s->capacity = capacity > 0 ? capacity : 4;
    s->size = 0;
    s->data = malloc(s->capacity * sizeof(int));
    if (!s->data) {
        free(s);
        return NULL;
    }
    return s;
}

void stack_destroy(Stack* s) {
    if (!s) return;
    free(s->data);
    free(s);
}

int stack_push(Stack* s, int value) {
    if (s->size == s->capacity) {
        size_t new_capacity = s->capacity * 2;
        int* new_data = realloc(s->data, new_capacity * sizeof(int));
        if (!new_data) return 0;
        s->data = new_data;
        s->capacity = new_capacity;
    }
    s->data[s->size++] = value;
    return 1;
}

int stack_pop(Stack* s, int* out_value) {
    if (s->size == 0) return 0;
    *out_value = s->data[--s->size];
    return 1;
}

int stack_peek(Stack* s, int* out_value) {
    if (s->size == 0) return 0;
    *out_value = s->data[s->size - 1];
    return 1;
}

int stack_is_empty(Stack* s) {
    return s->size == 0;
}

void stack_print(Stack* s) {
    printf("[size=%zu, capacity=%zu] [", s->size, s->capacity);
    for (size_t i = 0; i < s->size; ++i) {
        printf("%d", s->data[i]);
        if (i + 1 < s->size) printf(", ");
    }
    printf("]\\n");
}

void stack_debug(Stack* s, const char* label) {
    if (label) printf("%s: ", label);
    stack_print(s);
}
