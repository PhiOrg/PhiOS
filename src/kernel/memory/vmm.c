#include <vmm.h>
#include <phimem.h>
#include <kheap.h>
#include <vga.h>
#include <pmm.h>
#include <phiio.h>

extern p_size_t kernel_end;
extern p_size_t kheap_placementAddress;
extern p_size_t pmm_framesNumber, pmm_freeFramesNumber;

PageDirectory *vmm_kernelDirectory, *vmm_currentDirectory;
p_uint32 vmm_enabledPaging = 0;

static p_size_t* __vmm_getPage(p_size_t address, p_size_t make, PageDirectory *pg)
{
    address /= FRAME_SIZE;
    p_size_t tableIndex = address / MAX_PAGE_TABLES;

    if (pg->tables[tableIndex])
    {
        return &pg->tables[tableIndex]->pages[address % MAX_PAGES_IN_TABLE];
    }

    return P_NULL;
}

static void __vmm_initKernelDirectory(void)
{
    p_size_t phys;
    for (p_size_t i = 0; i < MAX_PAGE_TABLES; i++)
    {
        vmm_kernelDirectory->tables[i] = (PageTable*) kheap_kmalloc_ap(sizeof(PageTable), &phys);
        phimem_set(vmm_kernelDirectory->tables[i], sizeof(PageTable));
        vmm_kernelDirectory->physicalTables[i] = phys | PHYSICAL_TABLES_FLAGS;
    }
}

p_size_t vmm_getNFreePages(p_size_t size)
{
    if (pmm_getFreeFramesNumber() < size)
        return ALLOC_ERROR;

    p_size_t *pointer = (p_size_t*) vmm_kernelDirectory->tables[0];

    for (p_size_t index = 0; index < MAX_PAGES; index++)
        if (pointer[index] == 0)
        {
            p_size_t __size = size - 1, __index = index;
            index++;

            while (pointer[index] == 0 && __size != 0)
            {
                index++;
                __size--;
            }

            if (__size == 0)
                return __index;
        }

    return ALLOC_ERROR;
}

void vmm_allocPage(p_size_t virtualAddress, p_size_t flags, PageDirectory *pg)
{
    p_size_t *page = __vmm_getPage(virtualAddress, 1, pg);

    if (*page != 0)
        return;

    p_size_t frameIndex = pmm_getFreeFrame();
    p_size_t physicalAddress = frameIndex * FRAME_SIZE;
    pmm_allocFrame(frameIndex);

    *page = physicalAddress | flags;
}

void vmm_freePage(p_size_t virtualAddress, PageDirectory *pg)
{
    p_size_t pageIndex = (virtualAddress / FRAME_SIZE) % MAX_PAGES_IN_TABLE;
    p_size_t tableIndex = (virtualAddress / FRAME_SIZE) / MAX_PAGE_TABLES;

    p_size_t physicalAddress = pg->tables[tableIndex]->pages[pageIndex] & MAGIC_ALIGN;
    pmm_freeFrame(physicalAddress / FRAME_SIZE);

    pg->tables[tableIndex]->pages[pageIndex] = 0x0;
}

void vmm_allocArea(p_size_t fromVirtualAddress, p_size_t toVirtualAddress,
                   p_size_t flags, PageDirectory *pg)
{
    for (p_size_t i = fromVirtualAddress; i < toVirtualAddress; i += FRAME_SIZE)
        vmm_allocPage(i, flags, pg);
}

void vmm_freeArea(p_size_t fromVirtualAddress, p_size_t toVirtualAddress,
                  PageDirectory *pg)
{
    for (p_size_t i = fromVirtualAddress; i < toVirtualAddress; i += FRAME_SIZE)
        vmm_freePage(i, pg);
}

void vmm_init(void)
{
    vmm_kernelDirectory = (PageDirectory*) kheap_kmalloc_a(sizeof(PageDirectory));
    phimem_set(vmm_kernelDirectory, sizeof(PageDirectory));
    __vmm_initKernelDirectory();

    vmm_allocArea(0x0, kheap_placementAddress,
                  PAGE_READ_WRITE | PAGE_PRESENT, vmm_kernelDirectory);

    isr_registerInterruptHandler(14, vmm_pageFault);
    vmm_switchPageDirectory(vmm_kernelDirectory);
    vmm_enablePaging();
}

void vmm_disablePaging(void)
{
    p_size_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= 0x7FFFFFFF;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));

    vmm_enabledPaging = 0;
}

void vmm_pageFault(Registers regs)
{
    p_size_t cr2;
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

void vmm_enablePaging(void)
{
    p_size_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));

    vmm_enabledPaging = 1;
}

