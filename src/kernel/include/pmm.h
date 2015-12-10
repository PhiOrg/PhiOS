/*
 *  pmm - physical memory manager
 */

#ifndef PhiOS_pmm
#define PhiOS_pmm

#include <sys/types.h>

p_uint32 pmm_allocFrame(p_cuint32);
p_uint32 pmm_getFreeFrame(void);
p_uint32 pmm_freeFrame(p_cuint32);
p_uint32 pmm_getFramesNumber(void);
p_uint32 pmm_getFreeFramesNumber(void);
void pmm_init(p_cuint32);

#endif

