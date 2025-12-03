/* Data to be copied from flash to RAM */
_sidata = LOADADDR(.data);
.data : AT(LOADADDR(.sdrr_runtime_info) + SIZEOF(.sdrr_runtime_info))
{
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
} >RAM

_flash_firmware_end = LOADADDR(.data) + SIZEOF(.data);

/* Uninitialized data */
.bss :
{
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
} >RAM