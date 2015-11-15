#ifndef PhiOS_mem
#define PhiOS_mem

#include <sys/types.h>

void phimem_cpy(const void*, void*, p_size_t);

void phimem_swap(void*, void*, p_size_t);

void phimem_set(void*, p_size_t);

#endif

