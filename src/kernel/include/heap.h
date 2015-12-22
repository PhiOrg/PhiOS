#ifndef PhiOS_heap
#define PhiOS_heap

#include <sys/types.h>
#include <list.h>
#include <vmm.h>

typedef struct heap
{
    p_size_t size, used;
    List *head;
} Heap;

Heap* heap_create(PageDirectory*);
void* heap_malloc(Heap*, p_size_t, PageDirectory*);

#endif

