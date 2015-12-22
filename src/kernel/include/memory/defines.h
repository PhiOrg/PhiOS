#ifndef PhiOS_memory_defines
#define PhiOS_memory_defines

#define PAGE_PRESENT            0x1
#define PAGE_READ_WRITE         0x2
#define PAGE_USER_MODE          0x4

#ifdef PhiOS32
#define MAX_PAGES_IN_TABLE      1024
#define MAX_PAGES               1048576 // MAX_PAGES_IN_TABLE * MAX_PAGE_TABLES
#define MAX_PAGE_TABLES         1024

#define BITS                    32
#define FRAME_SIZE              4096
#define FRAME_SIZE_IN_KB        4

#define MAGIC_ALIGN             0xFFFFF000
#define CHECK_ALIGN             0x00000FFF

#endif

#define PHYSICAL_TABLES_FLAGS   PAGE_PRESENT | PAGE_READ_WRITE | PAGE_USER_MODE



/*
 * Errors codes.
 */
#define ALLOC_ERROR     0xFFFFFFFF
#define FREE_ERROR      0xFFFFFFFF
#define ALLOC_SUCCESS   0x00000000
#define FREE_SUCCESS    0x00000000

#endif

