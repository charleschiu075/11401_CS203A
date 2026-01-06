#include <stdio.h>
#include <stdlib.h>

typedef enum { EMPTY, OCCUPIED, DELETED } BucketState;

typedef struct {
    int key;
    int value;
    BucketState state;
} Bucket;

typedef struct {
    size_t size;
    size_t capacity;
    Bucket* buckets;
} HashTable;

static size_t hash_int(int key, size_t capacity) {
    return (size_t)(key >= 0 ? key : -key) % capacity;
}

HashTable* ht_create(size_t capacity) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) return NULL;
    table->capacity = capacity > 0 ? capacity : 8;
    table->size = 0;
    table->buckets = malloc(table->capacity * sizeof(Bucket));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    for (size_t i = 0; i < table->capacity; ++i) {
        table->buckets[i].state = EMPTY;
    }
    return table;
}

static int ht_resize(HashTable* table, size_t new_capacity) {
    Bucket* old_buckets = table->buckets;
    size_t old_capacity = table->capacity;
    table->buckets = malloc(new_capacity * sizeof(Bucket));
    if (!table->buckets) {
        table->buckets = old_buckets;
        return 0;
    }
    table->capacity = new_capacity;
    table->size = 0;
    for (size_t i = 0; i < new_capacity; ++i) table->buckets[i].state = EMPTY;
    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_buckets[i].state == OCCUPIED) {
            // reinsert
            size_t index = hash_int(old_buckets[i].key, table->capacity);
            while (table->buckets[index].state == OCCUPIED) {
                index = (index + 1) % table->capacity;
            }
            table->buckets[index].key = old_buckets[i].key;
            table->buckets[index].value = old_buckets[i].value;
            table->buckets[index].state = OCCUPIED;
            table->size++;
        }
    }
    free(old_buckets);
    return 1;
}

static void ht_maybe_resize(HashTable* table) {
    if ((double)table->size / table->capacity > 0.7) {
        ht_resize(table, table->capacity * 2);
    }
}

int ht_insert(HashTable* table, int key, int value) {
    ht_maybe_resize(table);
    size_t index = hash_int(key, table->capacity);
    size_t first_deleted = (size_t)-1;
    for (size_t i = 0; i < table->capacity; ++i) {
        Bucket* bucket = &table->buckets[index];
        if (bucket->state == EMPTY) {
            Bucket* target = (first_deleted != (size_t)-1) ? &table->buckets[first_deleted] : bucket;
            target->key = key;
            target->value = value;
            target->state = OCCUPIED;
            table->size++;
            return 1;
        }
        if (bucket->state == DELETED && first_deleted == (size_t)-1) {
            first_deleted = index;
        } else if (bucket->state == OCCUPIED && bucket->key == key) {
            bucket->value = value;
            return 1;
        }
        index = (index + 1) % table->capacity;
    }
    return 0;
}

int ht_search(HashTable* table, int key, int* out_value) {
    size_t index = hash_int(key, table->capacity);
    for (size_t i = 0; i < table->capacity; ++i) {
        Bucket* bucket = &table->buckets[index];
        if (bucket->state == EMPTY) return 0;
        if (bucket->state == OCCUPIED && bucket->key == key) {
            *out_value = bucket->value;
            return 1;
        }
        index = (index + 1) % table->capacity;
    }
    return 0;
}

int ht_delete(HashTable* table, int key) {
    size_t index = hash_int(key, table->capacity);
    for (size_t i = 0; i < table->capacity; ++i) {
        Bucket* bucket = &table->buckets[index];
        if (bucket->state == EMPTY) return 0;
        if (bucket->state == OCCUPIED && bucket->key == key) {
            bucket->state = DELETED;
            table->size--;
            return 1;
        }
        index = (index + 1) % table->capacity;
    }
    return 0;
}

void ht_destroy(HashTable* table) {
    if (!table) return;
    free(table->buckets);
    free(table);
}

void ht_print(HashTable* table) {
    printf("[size=%zu, capacity=%zu] {", table->size, table->capacity);
    int first = 1;
    for (size_t i = 0; i < table->capacity; ++i) {
        if (table->buckets[i].state == OCCUPIED) {
            if (!first) printf(", ");
            printf("%d: %d", table->buckets[i].key, table->buckets[i].value);
            first = 0;
        }
    }
    printf("}\\n");
}

void ht_debug(HashTable* table, const char* label) {
    if (label) printf("%s: ", label);
    ht_print(table);
}
