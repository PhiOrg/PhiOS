/*
 * vmm - virtual memory manager
 */

#ifndef PhiOS_vmm
#define PhiOS_vmm

#include <sys/types.h>
#include <memory/defines.h>

#ifdef PhiArch_i386
#include <isr.h>
#endif

// PageTable == 4mb virtual memory
typedef struct page_table_t
{
    p_uint32 pages[MAX_PAGES_IN_TABLE];
} PageTable;

// PageDirectory == 4gb virtual memory
typedef struct page_directory_t
{
    PageTable *tables[MAX_PAGE_TABLES];        // 1024 pointers to PageTable
    p_uint32 physicalTables[MAX_PAGE_TABLES];  // physical addresss of the tables
    p_uint32 physicalAddress;                  // the physical address of physicalTables
} PageDirectory;

void vmm_init();
void vmm_pageFault(Registers);
void vmm_switchPageDirectory(PageDirectory*);
void vmm_enablePaging();
void vmm_allocPage(p_uint32, p_uint32, PageDirectory*);
void vmm_freePage(p_uint32, PageDirectory*);
void vmm_allocArea(p_uint32, p_uint32, p_uint32, PageDirectory*);
void vmm_disablePaging();
void vmm_freeArea(p_uint32, p_uint32, PageDirectory*);
p_uint32* vmm_getFreePage(PageDirectory*);

/**
 *  Search n free page in vmm_kernelDirectory and returns the index of the first
 *  free page.
 */
p_uint32 vmm_getNFreePage(p_uint32);

#endif

