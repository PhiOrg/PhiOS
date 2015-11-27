#include <pmm.h>
#include <kheap.h>
#include <bitmap.h>

#define FRAME_SIZE_IN_KB 4
#define FRAME_SIZE 4096
#define BITS 32

p_uint32 pmm_framesNumber, *pmm_frames, pmm_freeFramesNumber;

void pmm_init(p_uint32 ramSize)
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

p_sint32 pmm_allocFrame(p_uint32 index)
{
    if (index >= pmm_framesNumber)
        return -1;

    pmm_freeFramesNumber--;
    bitmap_setBit(&pmm_frames[index / BITS], BITS - 1 - index % BITS);

    return 0;
}

p_uint32 pmm_getFreeFrame()
{
    if (pmm_freeFramesNumber == 0)
        return 0xFFFFFFFF;

    for (p_uint32 i = 0; i < pmm_framesNumber; i++)
        if (!bitmap_testBit(pmm_frames[i / BITS], BITS - 1 - i % BITS))
            return i;

    return 0xFFFFFFFF;
}

p_sint32 pmm_freeFrame(p_uint32 index)
{
    if (index >= pmm_framesNumber)
        return -1;

    pmm_freeFramesNumber++;
    bitmap_freeBit(&pmm_frames[index / BITS], BITS - 1 - index % BITS);

    return 0;
}

p_uint32 pmm_getFramesNumber()
{
    return pmm_framesNumber;
}

p_uint32 pmm_getFreeFramesNumber()
{
    return pmm_freeFramesNumber;
}

