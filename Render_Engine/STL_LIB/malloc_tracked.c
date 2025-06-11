#include "malloc_tracked.h"
#include <malloc/malloc.h>

void *malloc_tracked(size_t size, size_t *used_mamory_total) {
    void *ptr = malloc(size);
    *used_mamory_total += malloc_size(ptr);
    return ptr;
}

void free_tracked(void *ptr, size_t *used_mamory_total) {
    *used_mamory_total -= malloc_size(ptr);
    free(ptr);
}