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
    p_size_t pages[MAX_PAGES_IN_TABLE];
} PageTable;

// PageDirectory == 4gb virtual memory
typedef struct page_directory_t
{
    PageTable *tables[MAX_PAGE_TABLES];        // 1024 pointers to PageTable
    p_size_t physicalTables[MAX_PAGE_TABLES];  // physical addresss of the tables
    p_size_t physicalAddress;                  // the physical address of physicalTables
} PageDirectory;

void vmm_init(void);
void vmm_pageFault(Registers);
void vmm_switchPageDirectory(PageDirectory*);
void vmm_enablePaging(void);
void vmm_allocPage(p_size_t, p_size_t, PageDirectory*);
void vmm_freePage(p_size_t, PageDirectory*);
void vmm_allocArea(p_size_t, p_size_t, p_size_t, PageDirectory*);
void vmm_disablePaging(void);
void vmm_freeArea(p_size_t, p_size_t, PageDirectory*);

/**
 *  Search n free page in PageDirectory and returns the virtual address.
 */
p_size_t vmm_getNFreePages(p_size_t, PageDirectory*);

#endif

