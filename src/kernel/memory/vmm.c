#include <vmm.h>
#include <phimem.h>
#include <kheap.h>
#include <vga.h>
#include <pmm.h>

extern p_uint32 kernel_end;
extern p_size_t kheap_placementAddress;
extern p_uint32 pmm_framesNumber, pmm_freeFramesNumber;

PageDirectory *vmm_kernelDirectory, *vmm_currentDirectory;
p_uint32 vmm_enabledPaging = 0;

static p_uint32* __vmm_getPage(p_uint32 address, p_uint32 make, PageDirectory *pg)
{
    address /= FRAME_SIZE;
    p_uint32 tableIndex = address / MAX_PAGE_TABLES;

    if (pg->tables[tableIndex])
    {
        return &pg->tables[tableIndex]->pages[address % MAX_PAGES_IN_TABLE];
    }
    else
        if (make)
        {
            p_uint32 phys;
            pg->tables[tableIndex] = (PageTable*) kheap_mallocPageTable(sizeof(PageTable), &phys);
            phimem_set(pg->tables[tableIndex], sizeof(PageTable));
            pg->physicalTables[tableIndex] = phys | PHYSICAL_TABLES_FLAGS;

            return &pg->tables[tableIndex]->pages[address % MAX_PAGES_IN_TABLE];
        }
        else
            return 0x0;
}

static void __vmm_initKernelDirectory()
{
    for (p_uint32 i = 0; i < MAX_PAGE_TABLES; i++)
        __vmm_getPage(i * MAX_PAGES_IN_TABLE * FRAME_SIZE, p_true, vmm_kernelDirectory);
}

p_uint32* vmm_getFreePage(PageDirectory *pg)
{
    for (p_uint32 i = 0; i < MAX_PAGE_TABLES; i++)
        if (pg->tables[i])
        {
            for (p_uint32 j = 0; j < MAX_PAGES_IN_TABLE; j++)
                if (pg->tables[i]->pages[j] == 0)
                    return &pg->tables[i]->pages[j];
        }
        else
        {
            p_uint32 phys;
            pg->tables[i] = (PageTable*) kheap_mallocPageTable(sizeof(PageTable), &phys);
            phimem_set(pg->tables[i], sizeof(PageTable));
            pg->physicalTables[i] = phys | PHYSICAL_TABLES_FLAGS;

            return &pg->tables[i]->pages[0];
        }
}

void vmm_allocPage(p_uint32 virtualAddress, p_uint32 flags, PageDirectory *pg)
{
    p_uint32 *page = __vmm_getPage(virtualAddress, 1, pg);

    if (*page != 0)
        return;

    p_uint32 frameIndex = pmm_getFreeFrame();
    p_uint32 physicalAddress = frameIndex * FRAME_SIZE;
    pmm_allocFrame(frameIndex);

    *page = physicalAddress | flags;
}

void vmm_freePage(p_uint32 virtualAddress, PageDirectory *pg)
{
    p_uint32 pageIndex = (virtualAddress / FRAME_SIZE) % MAX_PAGES_IN_TABLE;
    p_uint32 tableIndex = (virtualAddress / FRAME_SIZE) / MAX_PAGE_TABLES;

    p_uint32 physicalAddress = pg->tables[tableIndex]->pages[pageIndex] & MAGIC_ALIGN;
    pmm_freeFrame(physicalAddress / FRAME_SIZE);

    pg->tables[tableIndex]->pages[pageIndex] = 0x0;
}

void vmm_allocArea(p_uint32 fromVirtualAddress, p_uint32 toVirtualAddress,
                   p_uint32 flags, PageDirectory *pg)
{
    for (p_uint32 i = fromVirtualAddress; i < toVirtualAddress; i += FRAME_SIZE)
    {
        vmm_allocPage(i, flags, pg);
    }
}

void vmm_freeArea(p_uint32 fromVirtualAddress, p_uint32 toVirtualAddress,
                  PageDirectory *pg)
{
    for (p_uint32 i = fromVirtualAddress; i < toVirtualAddress; i += FRAME_SIZE)
        vmm_freePage(i, pg);
}

void vmm_init()
{
    vmm_kernelDirectory = (PageDirectory*) kheap_kmalloc_a(sizeof(PageDirectory));
    phimem_set(vmm_kernelDirectory, sizeof(PageDirectory));
    vmm_currentDirectory = vmm_kernelDirectory;

    kheap_mallocPageTable_init(sizeof(PageTable));
    vmm_allocArea(0x0, kheap_placementAddress,
                  PAGE_READ_WRITE | PAGE_PRESENT, vmm_kernelDirectory);

    __vmm_initKernelDirectory();

    isr_registerInterruptHandler(14, vmm_pageFault);
    vmm_switchPageDirectory(vmm_kernelDirectory);
    vmm_enablePaging();
}

void vmm_disablePaging()
{
    p_uint32 cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= 0x7FFFFFFF;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));

    vmm_enabledPaging = 0;
}

void vmm_pageFault(Registers regs)
{
    p_uint32 cr2;
    asm volatile("mov %%cr2, %0" : "=r"(cr2));
    vga_putString("Page fault: ");
    vga_putAddress(cr2, 1, 1);
    vga_putChar('\n');

    vmm_disablePaging();
}

void vmm_switchPageDirectory(PageDirectory *pg)
{
    vmm_currentDirectory = pg;
    asm volatile("mov %0, %%cr3" :: "r"(pg->physicalTables));
}

void vmm_enablePaging()
{
    p_uint32 cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));

    vmm_enabledPaging = 1;
}

