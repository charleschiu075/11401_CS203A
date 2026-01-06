#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    int* data;
} DynamicArray;

DynamicArray* da_create(size_t initial_capacity) {
    DynamicArray* arr = malloc(sizeof(DynamicArray));
    if (!arr) return NULL;
    arr->capacity = initial_capacity > 0 ? initial_capacity : 1;
    arr->size = 0;
    arr->data = malloc(arr->capacity * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    return arr;
}

void da_destroy(DynamicArray* arr) {
    if (!arr) return;
    free(arr->data);
    free(arr);
}

static int da_resize(DynamicArray* arr, size_t new_capacity) {
    int* new_data = realloc(arr->data, new_capacity * sizeof(int));
    if (!new_data) return 0;
    arr->data = new_data;
    arr->capacity = new_capacity;
    return 1;
}

int da_append(DynamicArray* arr, int value) {
    if (arr->size == arr->capacity) {
        if (!da_resize(arr, arr->capacity * 2)) return 0;
    }
    arr->data[arr->size++] = value;
    return 1;
}

int da_pop(DynamicArray* arr, int* out_value) {
    if (arr->size == 0) return 0;
    *out_value = arr->data[--arr->size];
    if (arr->size > 0 && arr->size <= arr->capacity / 4) {
        size_t new_capacity = arr->capacity / 2;
        if (new_capacity < 1) new_capacity = 1;
        da_resize(arr, new_capacity);
    }
    return 1;
}

int da_get(DynamicArray* arr, size_t index, int* out_value) {
    if (index >= arr->size) return 0;
    *out_value = arr->data[index];
    return 1;
}

int da_set(DynamicArray* arr, size_t index, int value) {
    if (index >= arr->size) return 0;
    arr->data[index] = value;
    return 1;
}

void da_print(DynamicArray* arr) {
    printf("[size=%zu, capacity=%zu] [", arr->size, arr->capacity);
    for (size_t i = 0; i < arr->size; ++i) {
        printf("%d", arr->data[i]);
        if (i + 1 < arr->size) printf(", ");
    }
    printf("]\\n");
}

void da_debug(DynamicArray* arr, const char* label) {
    if (label) printf("%s: ", label);
    da_print(arr);
}
