#ifndef PhiOS_memory_defines
#define PhiOS_memory_defines

#define PAGE_PRESENT            0x1
#define PAGE_READ_WRITE         0x2
#define PAGE_USER_MODE          0x4

#define MAX_PAGES_IN_TABLE      1024
#define MAX_PAGES               1048576 // MAX_PAGES_IN_TABLE * MAX_PAGE_TABLES
#define MAX_PAGE_TABLES         1024

#define BITS                    32
#define FRAME_SIZE              4096
#define FRAME_SIZE_IN_KB        4

#define MAGIC_ALIGN             0xFFFFF000
#define CHECK_ALIGN             0x00000FFF

#define PHYSICAL_TABLES_FLAGS   PAGE_PRESENT | PAGE_READ_WRITE | PAGE_USER_MODE

#endif

