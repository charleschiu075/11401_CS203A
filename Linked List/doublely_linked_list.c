#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int value;
    struct DNode* prev;
    struct DNode* next;
} DNode;

typedef struct {
    DNode* head;
    DNode* tail;
} DoublyLinkedList;

DoublyLinkedList* dll_create(void) {
    DoublyLinkedList* list = malloc(sizeof(DoublyLinkedList));
    if (!list) return NULL;
    list->head = list->tail = NULL;
    return list;
}

void dll_destroy(DoublyLinkedList* list) {
    DNode* cur = list->head;
    while (cur) {
        DNode* next = cur->next;
        free(cur);
        cur = next;
    }
    free(list);
}

int dll_append(DoublyLinkedList* list, int value) {
    DNode* node = malloc(sizeof(DNode));
    if (!node) return 0;
    node->value = value;
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail) list->tail->next = node;
    else list->head = node;
    list->tail = node;
    return 1;
}

int dll_prepend(DoublyLinkedList* list, int value) {
    DNode* node = malloc(sizeof(DNode));
    if (!node) return 0;
    node->value = value;
    node->prev = NULL;
    node->next = list->head;
    if (list->head) list->head->prev = node;
    else list->tail = node;
    list->head = node;
    return 1;
}

int dll_delete(DoublyLinkedList* list, int value) {
    for (DNode* cur = list->head; cur; cur = cur->next) {
        if (cur->value == value) {
            if (cur->prev) cur->prev->next = cur->next;
            else list->head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            else list->tail = cur->prev;
            free(cur);
            return 1;
        }
    }
    return 0;
}

void dll_print(DoublyLinkedList* list) {
    printf("[head=%p, tail=%p] [", (void*)list->head, (void*)list->tail);
    for (DNode* cur = list->head; cur; cur = cur->next) {
        printf("%d", cur->value);
        if (cur->next) printf(" <-> ");
    }
    printf("]\n");
}

void dll_debug(DoublyLinkedList* list, const char* label) {
    if (label) printf("%s: ", label);
    dll_print(list);
}
