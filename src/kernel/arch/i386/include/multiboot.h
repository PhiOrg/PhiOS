#ifndef PhiOS_multiboot
#define PhiOS_multiboot

#include <sys/types.h>

typedef struct p_multiboot
{
    p_uint32 flags;
    p_uint32 mem_lower;
    p_uint32 mem_upper;
    p_uint32 boot_device;
    p_uint32 cmdline;
    p_uint32 mods_count;
    p_uint32 mods_addr;
    p_uint32 num;
    p_uint32 size;
    p_uint32 addr;
    p_uint32 shndx;
    p_uint32 mmap_length;
    p_uint32 mmap_addr;
    p_uint32 drives_length;
    p_uint32 drives_addr;
    p_uint32 config_table;
    p_uint32 boot_loader_name;
    p_uint32 apm_table;
    p_uint32 vbe_control_info;
    p_uint32 vbe_mode_info;
    p_uint32 vbe_mode;
    p_uint32 vbe_interface_seg;
    p_uint32 vbe_interface_off;
    p_uint32 vbe_interface_len;
} Multiboot;

#endif

