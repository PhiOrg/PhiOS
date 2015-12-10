#ifndef PhiOS_list
#define PhiOS_list

#include <sys/types.h>

typedef struct list
{
    struct list *next;
    p_size_t size;
} List;

#endif

