/**************************
@ Author: Felix
@ Version: 1.0
@ MCU: CH579M
****************************/

OUTPUT_FORMAT(elf32-littlearm)

/*---------Flash Configuration-------*/
__ROM_BASE = 0x00000000;
__ROM_SIZE = 0x0007FFFF;

/*---------Embedded RAM Configuration------*/
__RAM_BASE = 0x20000000;
__RAM_SIZE = 0x00007FFF;

/*-----------Stack / Heap Configuration----------*/
__STACK_SIZE = 0x00000800;
__HEAP_SIZE  = 0x00000000;

MEMORY
{
  ROM   (rx)  : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
  RAM   (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

/*-------------Define Entry Function---------------*/
ENTRY(Reset_Handler)

/*-------------Define Sections of Memory------------------*/
SECTIONS
{
    .vectors :
    {
        . = ALIGN(4);
        KEEP(*(vectors));
        . = ALIGN(4);
    }>ROM
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.text*));
        *(.init);
        *(.fini);
        *(.rodata*);
        *(.eh_frame*);
        *(.ARM.attributes);
        *(.comment);
        *(.debug_frame);
        *(.ARM.exidx* .gnu.linkonce.armexidx.*);
        _exit = .;
        . = ALIGN(4);
    }>ROM
    _lvmdata = .;
    .data :
    {
        . = ALIGN(8);
        _sdata  = .;
        KEEP(*(.data*));
        *(SORT(.init_array.*));
        *(.init_array);
        *(.fini_array);
        . = ALIGN(8);
        _edata = .;
    }>RAM AT>ROM

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss);
        *(.bss*);
        *(COMMON);
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    }>RAM

    .heap :
    {
        . = ALIGN(8);
        _Heap_Base = .;
        . = . + __HEAP_SIZE;
        . = ALIGN(8);
    } >RAM AT>ROM
    
    .stack (__RAM_BASE + __RAM_SIZE -__STACK_SIZE):
    {
        . = ALIGN(8);
        . = . + __STACK_SIZE;
        . = ALIGN(8);
        _Stack_Top = .;
        end = _Stack_Top;
        PROVIDE(end = .);
    } AT>ROM
}