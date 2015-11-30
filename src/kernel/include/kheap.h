#ifndef PhiOS_kheap
#define PhiOS_kheap

#include <sys/types.h>

/*
 * Allocate a chunk of memory of size @size. The chunk must be
 * page aligned.
 */
p_size_t kheap_kmalloc_a(p_size_t size);

/*
 * Allocate a chunk of memory of size @size. The physical address
 * is returned in phys. Phys MUST be a valid pointer to p_size_t!
 */
p_size_t kheap_kmalloc_p(p_size_t size, p_size_t *phys);

/*
 * Allocate a chunk of memory of size @size. The physical address
 * is returned in phys. It must be page-aligned.
 */
p_size_t kheap_kmalloc_ap(p_size_t size, p_size_t *phys);

/*
 * Allocate a chunk of memory of size @size..
 */
p_size_t kheap_kmalloc(p_size_t size);

void kheap_mallocPageTable_init(p_size_t);
p_size_t kheap_mallocPageTable(p_size_t, p_size_t*);

#endif

