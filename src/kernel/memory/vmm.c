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

#ifdef PhiArch_i386
#define READ_CR0(x) asm volatile("mov %%cr0, %0" : "=r"(x))
#define READ_CR2(x) asm volatile("mov %%cr2, %0" : "=r"(x))
#define WRITE_CR0(x) asm volatile("mov %0, %%cr0" :: "r"(x))
#define WRITE_CR3(x) asm volatile("mov %0, %%cr3" :: "r"(x))
#endif

static p_size_t* __vmm_getPage(p_size_t address, PageDirectory *pg)
{
    address /= FRAME_SIZE;
    p_size_t tableIndex = address / MAX_PAGE_TABLES;

    if (pg->tables[tableIndex])
    {
        return &pg->tables[tableIndex]->pages[address % MAX_PAGES_IN_TABLE];
    }
    else
    {
        // something is wrong...
    }

    return P_NULL;
}

static void __vmm_initKernelDirectory(void)
{
#ifdef PhiOS32
    vmm_kernelDirectory = (PageDirectory*) kheap_kmalloc_a(sizeof(PageDirectory));
    phimem_set(vmm_kernelDirectory, sizeof(PageDirectory));

    p_size_t phys;
    for (p_size_t i = 0; i < MAX_PAGE_TABLES; i++)
    {
        vmm_kernelDirectory->tables[i] = (PageTable*) kheap_kmalloc_ap(sizeof(PageTable), &phys);
        phimem_set(vmm_kernelDirectory->tables[i], sizeof(PageTable));
        vmm_kernelDirectory->physicalTables[i] = phys | PHYSICAL_TABLES_FLAGS;
    }

    vmm_allocArea(0x0, kheap_placementAddress,
                  PAGE_READ_WRITE | PAGE_PRESENT, vmm_kernelDirectory);
#endif
}

p_size_t vmm_getNFreePages(p_size_t size, PageDirectory *pg)
{
    if (pg == P_NULL)
    {
        // something is wrong
        return ALLOC_ERROR;
    }
    if (pmm_getFreeFramesNumber() < size)
    {
        // something is wrong
        return ALLOC_ERROR;
    }

    p_size_t retAddress = P_NULL;
    p_size_t copyOfSize = size;

    for (p_size_t i = 0; i < MAX_PAGE_TABLES; i++)
    {
        if (pg->tables[i])
        {
            for (p_size_t j = 0; j < MAX_PAGES_IN_TABLE; j++)
            {
                if (pg->tables[i]->pages[j] == 0)
                {
                    if (copyOfSize == size)
                        retAddress = (i * MAX_PAGES_IN_TABLE + j) * FRAME_SIZE;

                    copyOfSize--;
                    if (copyOfSize == 0)
                        return retAddress;
                }
                else
                {
                    copyOfSize = size;
                }
            }
        }
        else
        {
            // alloc 4mb virtual memory
        }
    }

    // something is wrong
    return ALLOC_ERROR;
}

void vmm_allocPage(p_size_t virtualAddress, p_size_t flags, PageDirectory *pg)
{
    p_size_t *page = __vmm_getPage(virtualAddress, pg);

    if (page == P_NULL)
    {
        // something is wrong
        return;
    }

    if (*page != 0)
    {
        // something is wrong
        return;
    }

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
    __vmm_initKernelDirectory();

    isr_registerInterruptHandler(14, vmm_pageFault);
    vmm_switchPageDirectory(vmm_kernelDirectory);
    vmm_enablePaging();
}

void vmm_disablePaging(void)
{
    p_size_t cr0;
    READ_CR0(cr0);
    cr0 &= 0x7FFFFFFF;
    WRITE_CR0(cr0);

    vmm_enabledPaging = 0;
}

void vmm_pageFault(Registers regs)
{
    p_size_t cr2;
    READ_CR2(cr2);

    vga_putString("Page fault: ");
    vga_putAddress(cr2, 1, 1);
    vga_putChar('\n');

    vmm_disablePaging();
}

void vmm_switchPageDirectory(PageDirectory *pg)
{
    vmm_currentDirectory = pg;
    WRITE_CR3(pg->physicalTables);
}

void vmm_enablePaging(void)
{
    p_size_t cr0;
    READ_CR0(cr0);
    cr0 |= 0x80000000;
    WRITE_CR0(cr0);

    vmm_enabledPaging = 1;
}

