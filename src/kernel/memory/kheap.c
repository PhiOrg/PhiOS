#include <kheap.h>
#include <memory/defines.h>

extern p_size_t kernel_end;
p_size_t kheap_placementAddress = (p_size_t) &kernel_end;

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

