#include <pmm.h>
#include <kheap.h>
#include <bitmap.h>
#include <memory/defines.h>

static p_uint32 pmm_framesNumber;
static p_uint32 *pmm_frames;
static p_uint32 pmm_freeFramesNumber;

void pmm_init(p_cuint32 ramSize)
{
    pmm_framesNumber = ramSize / FRAME_SIZE_IN_KB;
    pmm_freeFramesNumber = pmm_framesNumber;

    p_uint32 n = pmm_framesNumber / BITS;
    if (pmm_framesNumber % BITS)
        n++;

    pmm_frames = (p_uint32*) kheap_kmalloc(n);

    for (p_uint32 i = 0; i < n; i++)
        pmm_frames[i] = 0x0;
}

p_uint32 pmm_allocFrame(p_cuint32 index)
{
    if (index >= pmm_framesNumber)
        return ALLOC_ERROR;

    if (bitmap_testBit(pmm_frames[index / BITS], BITS - 1 - index % BITS))
        return ALLOC_ERROR;

    pmm_freeFramesNumber--;
    bitmap_setBit(&pmm_frames[index / BITS], BITS - 1 - index % BITS);

    return ALLOC_SUCCESS;
}

p_uint32 pmm_getFreeFrame(void)
{
    if (pmm_freeFramesNumber == 0)
        return ALLOC_ERROR;

    for (p_uint32 i = 0; i < pmm_framesNumber; i++)
        if (!bitmap_testBit(pmm_frames[i / BITS], BITS - 1 - i % BITS))
            return i;

    return ALLOC_ERROR;
}

p_uint32 pmm_freeFrame(p_cuint32 index)
{
    if (index >= pmm_framesNumber)
        return FREE_ERROR;

    if (bitmap_testBit(pmm_frames[index / BITS], BITS - 1 - index % BITS))
        return FREE_ERROR;

    pmm_freeFramesNumber++;
    bitmap_freeBit(&pmm_frames[index / BITS], BITS - 1 - index % BITS);

    return FREE_SUCCESS;
}

p_uint32 pmm_getFramesNumber(void)
{
    return pmm_framesNumber;
}

p_uint32 pmm_getFreeFramesNumber(void)
{
    return pmm_freeFramesNumber;
}

