bits 32

; multiboot header
MB_ALIGN        equ  1<<0
MB_MEMINFO      equ  1<<1
MB_FLAGS        equ  MB_ALIGN | MB_MEMINFO
MB_MAGIC        equ  0x1BADB002
MB_CHECKSUM     equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

; reserve space for kernel stack
section .bootstrap_stack
    align 4
global stack_bottom
stack_bottom:
    times 8192 db 0

global stack_top
stack_top:

; start kernel
section .text
global _start
_start:
    extern phi_main

    mov esp, stack_top ; set stack
    push esp ; push stack pointer
    push ebx ; push multiboot structure

    cli

    call phi_main

.hang:
    hlt
    jmp .hang ; stop the processor executing whatever rubbish is in the
              ; memory after kernel
