#ifndef PhiOS_bitmap
#define PhiOS_bitmap

#include <sys/types.h>

void bitmap_setBit(p_size_t*, p_cuint8);

void bitmap_freeBit(p_size_t*, p_cuint8);

p_size_t bitmap_testBit(p_size_t, p_cuint8);

#endif

