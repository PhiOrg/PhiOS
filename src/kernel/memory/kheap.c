#include <kheap.h>
#include <memory/defines.h>

extern p_size_t kernel_end;
p_size_t kheap_placementAddress = (p_size_t) &kernel_end;
p_size_t kheap_mallocPageTable_placementAddress;
p_size_t kheap_mallocPageTable_maxAddress;

static p_size_t __kheap_kmalloc(p_size_t size, p_uint8 align, p_size_t *phys)
{
    if (kheap_placementAddress & CHECK_ALIGN)
    {
        if (align == 1 && (kheap_placementAddress & MAGIC_ALIGN))
        {
            kheap_placementAddress &= MAGIC_ALIGN;
            kheap_placementAddress += FRAME_SIZE;
        }
    }

    if (phys)
    {
        *phys = kheap_placementAddress;
    }

    p_size_t tmp = kheap_placementAddress;
    kheap_placementAddress += size;

    return tmp;
}

p_size_t kheap_kmalloc_a(p_size_t size)
{
    return __kheap_kmalloc(size, 1, 0);
}

p_size_t kheap_kmalloc_p(p_size_t size, p_size_t *phys)
{
    return __kheap_kmalloc(size, 0, phys);
}

p_size_t kheap_kmalloc_ap(p_size_t size, p_size_t *phys)
{
    return __kheap_kmalloc(size, 1, phys);
}

p_size_t kheap_kmalloc(p_size_t size)
{
    return __kheap_kmalloc(size, 0, 0);
}

p_size_t kheap_mallocPageTable(p_size_t size, p_size_t *phys)
{
    if (kheap_mallocPageTable_placementAddress == kheap_mallocPageTable_maxAddress)
        return 0x0;

    p_size_t tmp = kheap_mallocPageTable_placementAddress;
    *phys = kheap_mallocPageTable_placementAddress;
    kheap_mallocPageTable_placementAddress += size;

    return tmp;
}

void kheap_mallocPageTable_init(p_size_t size)
{
    if (kheap_placementAddress & CHECK_ALIGN)
        kheap_mallocPageTable_placementAddress = (kheap_placementAddress &
                                                  MAGIC_ALIGN) + FRAME_SIZE;
    else
        kheap_mallocPageTable_placementAddress = kheap_placementAddress;

    kheap_mallocPageTable_maxAddress = kheap_mallocPageTable_placementAddress +
                                       MAX_PAGE_TABLES * size;
    kheap_placementAddress = kheap_mallocPageTable_maxAddress;
}

