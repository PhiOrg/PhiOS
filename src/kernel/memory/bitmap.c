#include <bitmap.h>

void bitmap_setBit(p_uint32 *frame, p_cuint8 rangBit)
{
    *frame |= ((p_uint32)0x1 << rangBit);
}

void bitmap_freeBit(p_uint32 *frame, p_cuint8 rangBit)
{
    *frame &= ~((p_uint32)0x1 << rangBit);
}

p_uint32 bitmap_testBit(p_cuint32 frame, p_cuint8 rangBit)
{
    return (frame & ((p_uint32)0x1 << rangBit));
}

