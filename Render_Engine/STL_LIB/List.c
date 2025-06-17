#include "List.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

ListNode *list_create_node(void* data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void list_init(List* list, size_t element_size) {
    list->head = NULL;
    list->tail = NULL;

    list->element_size = element_size;
    list->size = 0;
}

void list_push(List* list, void* data, bool stack_elem) {
    ListNode* node;

    if (stack_elem) {
        void *stack_data = malloc(list->element_size);
        if (!stack_data) return;
        memcpy(stack_data, data, list->element_size);
        node = list_create_node(stack_data);
    }else {
        node = list_create_node(data);
    }

    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }

    list->size++;
}

void *list_get(List* list, int index, bool get_node) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "list index out of bounds\n");
        return NULL;
    }


    ListNode *node = list->head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    if (get_node) return node;
    return node->data;
}

void list_update(List* list, int index, void* data) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "list index out of bounds\n");
        return;
    }

    ListNode *node = (ListNode*)list_get(list, index, true);
    node->data = data;
}

void list_remove(List* list, int index) {
    ListNode *node_remove = (ListNode*)list_get(list, index, true);
    if (list == NULL) return;

    if (node_remove == list->head)
        list->head = node_remove->next;

    if (node_remove == list->tail)
        list->tail = node_remove->prev;

    if (node_remove->prev)
        node_remove->prev->next = node_remove->next;
    if (node_remove->next)
        node_remove->next->prev = node_remove->prev;

    free(node_remove);
    list->size--;
}

void list_clear(List* list) {
    for (int i = list->size - 1; i >= 0; i--) {
        ListNode *node_remove = (ListNode*)list_get(list, i, true);
        free(node_remove->data);
        free(node_remove);
        list->size--;
    }
}

void list_free(List* list) {
    list_clear(list);
    free(list);
}

size_t list_size(List* list) {
    if (list == NULL) return sizeof(List);
    return (list->size * list->element_size) + sizeof(List);
}

void list_print(List *list) {
    for (int i = 0; i < list->size; i++) {
        int *data = (int*)list_get(list, i, false);
        printf("%d ", *data);
    }
}
