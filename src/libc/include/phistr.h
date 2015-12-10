#ifndef PhiOS_str
#define PhiOS_str

#include <sys/types.h>

/*
 * Return the size of the str.
 */
p_size_t phistr_len(const char*);

/*
 * Return:
 *  -2 if a == NULL || b == NULL
 *  -1 if a < b
 *  0 if a == b
 *  1 if a > b
 */
p_sint8 phistr_cmp(const char *a, const char *b);

/*
 * Reverses the string.
 */
void phistr_rev(char*);

#endif

