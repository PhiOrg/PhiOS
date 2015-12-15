#include <bitmap.h>

void bitmap_setBit(p_size_t *frame, p_cuint8 rangBit)
{
    *frame |= ((p_size_t)0x1 << rangBit);
}

void bitmap_freeBit(p_size_t *frame, p_cuint8 rangBit)
{
    *frame &= ~((p_size_t)0x1 << rangBit);
}

p_size_t bitmap_testBit(p_size_t frame, p_cuint8 rangBit)
{
    return (frame & ((p_size_t)0x1 << rangBit));
}

