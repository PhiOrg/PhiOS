#ifndef PhiOS_bitmap
#define PhiOS_bitmap

#include <sys/types.h>

void bitmap_setBit(p_uint32*, p_cuint8);

void bitmap_freeBit(p_uint32*, p_cuint8);

p_uint32 bitmap_testBit(p_cuint32, p_cuint8);

#endif

