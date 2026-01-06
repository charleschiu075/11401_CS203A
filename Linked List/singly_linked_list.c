#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} SinglyLinkedList;

SinglyLinkedList* sll_create(void) {
    SinglyLinkedList* list = malloc(sizeof(SinglyLinkedList));
    if (!list) return NULL;
    list->head = list->tail = NULL;
    return list;
}

void sll_destroy(SinglyLinkedList* list) {
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int sll_append(SinglyLinkedList* list, int value) {
    Node* node = malloc(sizeof(Node));
    if (!node) return 0;
    node->value = value;
    node->next = NULL;
    if (!list->head) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    return 1;
}

int sll_prepend(SinglyLinkedList* list, int value) {
    Node* node = malloc(sizeof(Node));
    if (!node) return 0;
    node->value = value;
    node->next = list->head;
    list->head = node;
    if (!list->tail) list->tail = node;
    return 1;
}

Node* sll_find(SinglyLinkedList* list, int value) {
    for (Node* cur = list->head; cur; cur = cur->next) {
        if (cur->value == value) return cur;
    }
    return NULL;
}

int sll_delete(SinglyLinkedList* list, int value) {
    Node* prev = NULL;
    Node* cur = list->head;
    while (cur) {
        if (cur->value == value) {
            if (prev) prev->next = cur->next;
            else list->head = cur->next;
            if (cur == list->tail) list->tail = prev;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

void sll_print(SinglyLinkedList* list) {
    printf("[head=%p, tail=%p] ", (void*)list->head, (void*)list->tail);
    printf("[");
    for (Node* cur = list->head; cur; cur = cur->next) {
        printf("%d", cur->value);
        if (cur->next) printf(" -> ");
    }
    printf("]\\n");
}

void sll_debug(SinglyLinkedList* list, const char* label) {
    if (label) printf("%s: ", label);
    sll_print(list);
}
