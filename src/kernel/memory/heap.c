#include <heap.h>
#include <vmm.h>

Heap* heap_create(PageDirectory *pg)
{
    if (pg == P_NULL)
        return P_NULL;

    Heap *heap = (Heap*) vmm_getNFreePages(1, pg);
    if (heap == P_NULL)
        return P_NULL;

    vmm_allocPage((p_uint32) heap, PAGE_PRESENT, pg);

    heap->size = FRAME_SIZE;
    heap->used = 0;
    heap->head = P_NULL;

    return heap;
}

/**
 * Check if two addressed are in the same page.
 */
p_bool __heap_checkAddresses(p_size_t firstAddress, p_size_t secondAddress)
{
    if (firstAddress & MAGIC_ALIGN == secondAddress & MAGIC_ALIGN)
        return p_true;

    return p_false;
}

void* heap_malloc(Heap *heap, p_size_t size, PageDirectory* pg)
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

            p_uint32 frameIndex = vmm_getNFreePages(pagesNeededNumber, pg);
            if (frameIndex == ALLOC_ERROR)
                return P_NULL;

            heap->head = (List*) (frameIndex * FRAME_SIZE);
            heap->head->next = P_NULL;
            heap->head->size = size;
            heap->used += size;

            return (void*) ((p_uint8*)heap->head + sizeof(List));
        }
    }

 //   if ()
}

