/*
 *  pmm - physical memory manager
 */

#ifndef PhiOS_pmm
#define PhiOS_pmm

#include <sys/types.h>

p_size_t pmm_allocFrame(p_size_t);
p_size_t pmm_getFreeFrame(void);
p_size_t pmm_freeFrame(p_size_t);
p_size_t pmm_getFramesNumber(void);
p_size_t pmm_getFreeFramesNumber(void);
void pmm_init(p_size_t);

#endif

