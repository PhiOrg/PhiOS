/*
 * vmm - virtual memory manager
 */

#ifndef PhiOS_vmm
#define PhiOS_vmm

#include <sys/types.h>

#ifdef PhiArchi386
#include <isr.h>
#endif

#define PAGE_PRESENT 0x1
#define PAGE_READ_WRITE 0x2
#define PAGE_USER_MODE 0x4

// PageTable == 4mb virtual memory
typedef struct page_table_t
{
    p_uint32 pages[1024];
} PageTable;

// PageDirectory == 4gb virtual memory
typedef struct page_directory_t
{
    PageTable *tables[1024];        // 1024 pointers to PageTable
    p_uint32 physicalTables[1024];  // physical addresss of the tables
    p_uint32 physicalAddress;       // the physical address of physicalTables
} PageDirectory;

void vmm_init();
void vmm_pageFault(Registers);
void vmm_switchPageDirectory(PageDirectory*);
void vmm_enablePaging();
void vmm_allocPage(p_uint32, p_uint32, PageDirectory*);
void vmm_freePage(p_uint32, PageDirectory*);
void vmm_allocArea(p_uint32, p_uint32, p_uint32, PageDirectory*);
void vmm_disablePaging();
p_uint32* vmm_getFreePage(PageDirectory*);

#endif

