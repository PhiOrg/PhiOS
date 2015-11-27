/*
 * vmm - virtual memory manager
 */

#ifndef PhiOS_vmm
#define PhiOS_vmm

#include <sys/types.h>

// Page = 4kb physical memory
typedef struct page_t
{
    p_uint8 present :1;  // Page present in memory
    p_uint8 rw      :1;  // 1 for read-write, 0 read-only
    p_uint8 user    :1;  // Supervisor level only if clear
    p_uint8 accesed :1;  // Has the page been accessed since last refresh?
    p_uint8 dirty   :1;  // Has the page been written since last refresh?
    p_uint8 unused  :7;  // Amalgamation of unused and reserved bits
    p_uint32 frame  :20; // Frame address (shifted >> 12 bits)
} Page;

// PageTable == 4mb physical memory
typedef struct page_table_t
{
    Page pages[1024];
} PageTable;

// PageDirectory == 4gb physical memory
typedef struct page_directory_t
{
    PageTable *tables[1024];        // 1024 pointers to PageTable
    p_uint32 physicalTables[1024];  // physical addresss of the tables
    p_uint32 physicalAddress;       // the physical address of physicalTables
} PageDirectory;

#endif

