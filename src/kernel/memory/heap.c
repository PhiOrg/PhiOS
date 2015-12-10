#include <heap.h>
#include <vmm.h>

Heap* heap_create(PageDirectory *pg)
{
    if (pg == P_NULL)
        return P_NULL;

    p_uint32 frameIndex = vmm_getNFreePages(1);
    if (frameIndex == ALLOC_ERROR)
        return P_NULL;

    Heap *heap = (Heap*)(frameIndex * FRAME_SIZE);
    vmm_allocPage((p_uint32) heap, 1, pg);

    heap->size = FRAME_SIZE;
    heap->used = 0;
    heap->head = P_NULL;

    return heap;
}

void* heap_malloc(Heap *heap, p_size_t size)
{
    if (heap == P_NULL || size == 0)
        return P_NULL;

    if (heap->head == P_NULL)
    {
        if (size + sizeof(Heap) + sizeof(List) <= FRAME_SIZE)
        {
            heap->head = (List*)((p_uint8*)heap + sizeof(Heap));
            heap->head->next = P_NULL;
            heap->head->size = size;
            heap->used += size;

            return (void*) ((p_uint8*)heap->head + sizeof(List));
        }
        else
        {
            p_uint32 pagesNeededNumber = (size + sizeof(List)) / FRAME_SIZE;
            if ((size + sizeof(List)) % FRAME_SIZE)
                pagesNeededNumber++;

            p_uint32 frameIndex = vmm_getNFreePages(pagesNeededNumber);
            if (frameIndex == ALLOC_ERROR)
                return P_NULL;
        }
    }
    else
    {

    }
}

