/*
 *  pmm - physical memory manager
 */

#ifndef PhiOS_pmm
#define PhiOS_pmm

#include <sys/types.h>

p_sint32 pmm_allocFrame(p_uint32);
p_uint32 pmm_getFreeFrame();
p_sint32 pmm_freeFrame(p_uint32);
p_uint32 pmm_getFramesNumber();
p_uint32 pmm_getFreeFramesNumber();

#endif

