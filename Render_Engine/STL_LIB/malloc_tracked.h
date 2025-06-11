#ifndef MALLOC_TRACKED_H
#define MALLOC_TRACKED_H
#include <stdlib.h>

void *malloc_tracked(size_t size, size_t *used_mamory_total);
void free_tracked(void *ptr, size_t *used_mamory_total);

#endif //MALLOC_TRACKED_H
