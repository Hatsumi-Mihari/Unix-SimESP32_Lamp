#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdbool.h>

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;

    void* data;
}ListNode;

typedef struct List {
    struct ListNode *head;
    struct ListNode *tail;

    size_t size;
    size_t element_size;
}List;

ListNode *list_create_node(void* data);
void list_init(List* list, size_t element_size);
void list_push(List* list, void* data, bool stack_elem);
void *list_get(List* list, int index, bool get_node);
void list_update(List* list, int index, void* data);
void list_remove(List* list, int index);
void list_clear(List* list);
void list_free(List* list);
void list_print(List* list);

#endif //LIST_H
