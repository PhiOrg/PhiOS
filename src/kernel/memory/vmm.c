#include <vmm.h>
#include <phimem.h>
#include <kheap.h>
#include <vga.h>
#include <pmm.h>

extern p_uint32 kernel_end;

PageDirectory *vmm_kernelDirectory, *vmm_currentDirectory;

static p_uint32* __vmm_getPage(p_uint32 address, p_uint32 make,
                               p_uint32 flags, PageDirectory *pg)
{
    address /= 0x1000;
    p_uint32 tableIndex = address / 1024;

    if (pg->tables[tableIndex])
    {
        return &pg->tables[tableIndex]->pages[address % 1024];
    }
    else
        if (make)
        {
            p_uint32 phys;
            pg->tables[tableIndex] = (PageTable*) kheap_kmalloc_ap(sizeof(PageTable),
                                                                   &phys);
            phimem_set(pg->tables[tableIndex], sizeof(PageTable));
            pg->physicalTables[tableIndex] = phys | flags;

            return &pg->tables[tableIndex]->pages[address % 1024];
        }
        else
            return 0x0;
}

void vmm_allocPage(p_uint32 virtualAddress, p_uint32 flags, PageDirectory *pg)
{
    p_uint32 frameIndex = pmm_getFreeFrame();
    p_uint32 physicalAddress = frameIndex * 0x1000;
    pmm_allocFrame(frameIndex);

    p_uint32 pageIndex = (virtualAddress / 0x1000) % 1024;
    p_uint32 tableIndex = (virtualAddress / 0x1000) / 1024;

    p_uint32 *page = __vmm_getPage(virtualAddress, 1, flags, pg);
    *page = physicalAddress | flags;
}

void vmm_freePage(p_uint32 virtualAddress, PageDirectory *pg)
{
    p_uint32 pageIndex = (virtualAddress / 0x1000) % 1024;
    p_uint32 tableIndex = (virtualAddress / 0x1000) / 1024;

    p_uint32 physicalAddress = pg->tables[tableIndex]->pages[pageIndex] & 0xFFFFF000;
    pmm_freeFrame(physicalAddress / 0x1000);

    pg->tables[tableIndex]->pages[pageIndex] = 0x0;
}

void vmm_allocArea(p_uint32 fromVirtualAddress, p_uint32 toVirtualAddress,
                   p_uint32 flags, PageDirectory *pg)
{
    for (p_uint32 i = fromVirtualAddress; i < toVirtualAddress; i += 0x1000)
    {
        vmm_allocPage(i, flags, pg);
    }
}

void vmm_init()
{
    vmm_kernelDirectory = (PageDirectory*) kheap_kmalloc_a(sizeof(PageDirectory));
    phimem_set(vmm_kernelDirectory, sizeof(PageDirectory));
    vmm_currentDirectory = vmm_kernelDirectory;

    vmm_allocArea(0x0, ((p_uint32) &kernel_end) + 0x100000,
                  PAGE_READ_WRITE | PAGE_PRESENT, vmm_kernelDirectory);

    isr_registerInterruptHandler(14, vmm_pageFault);
    vmm_switchPageDirectory(vmm_kernelDirectory);
    vmm_enablePaging();
}

void vmm_pageFault(Registers regs)
{
    p_uint32 cr2;
    asm volatile("mov %%cr2, %0" : "=r"(cr2));
    vga_putString("Page fault: ");
    vga_putAddress(cr2, 1, 1);
    vga_putChar('\n');
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
}

