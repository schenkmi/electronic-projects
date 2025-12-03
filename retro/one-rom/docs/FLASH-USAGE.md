# Flash Usage

Prior to v0.5.0 the One ROM firmware, the ROM image metadata, and the ROM images themselves where all built into a single monolothic binary, which was flashed to the base of the flash.

As of v0.5.0 One ROM's flash usage was modified in to separate the firmware, the ROM image metadata, and the ROM images themselves, so that they could be erased and updated independently.  This change slightly reduces the available flash space for ROM images, but improved the reliability of reprogramming One ROM, allowing just ROM metadata and images to be updated in the normal case, hence reducing the changes of a bricking event, that would require tedious recovery.  This is also faster, as it requires erasing and reprogramming a smaller section of flash.

The new flash layout is as follows, with all addresses relative to the flash base address, which varies between the STM32 (0x08000000) and RP2350 (0x10000000):

```ascii
+---------------------+ 0x00000000
| One ROM Firmware    |
+---------------------+ 0x0000C000
| One ROM Metadata    |
+---------------------+ 0x00010000
| ROM Images          |
+---------------------+ 16/64KB boundary
```

The first 48KB of flash is reserved for the One ROM firmware.  This includes the startup code, the main byte serving algorithm and USB handling code.

The next 16KB of flash is reserved for the ROM metadata, including the number of images, and the metadata associated with each image.

Address 64KB onwards is used by ROM images.  These are varying lengths - either 16KB or 64KB, depending on the MCU and image type:

- Fire/RP2350 - images are always 64KB.
- Ice/STM32F4 - images are either 16KB (single ROM image), or 64KB (banked switch or multi-ROM set).

ROM images are always stacked next to each other, with no gaps, and a pointer to the image (as well as its length) is stored in the metadata for this ROM.

This structure means a complete firmware + metadata + images binary file is always a multiple of 16KB on STM32, and always a 64KB multiple on the RP2350.

This layout is chosen to align with both STM32F4 and RP2350 flash sector sizes - that is the minimum size which can be erased at once.

The STM32F4's sector sizes are:

- 16KB for the first 4 sectors (0x0000 - 0x3FFF)
- 64KB for the 5th sector (0x4000 - 0xFFFF)
- 128KB for sectors 6-11 (0x10000 - 0x1FFFFF)

The RP2350's sector sizes are expected to be 4KB, although this does depends on the exact flash chip used.  The stock One ROM hardware uses Winbond W25Q16JV, which has 4KB sectors.

Hence, to erase and reflash the firmware:

- On the STM32F4, sectors 0-2 are erased (0x0000 - 0x2FFF)
- On the RP2350, sectors 0-11 are erased (0x0000 - 0x2FFF)

To modify the ROM images, the metadata and all ROM images must be erased, but the firmware can be left intact. Hence means leaving sectors 0-2 (STM32F4) or 0-11 (RP2350) intact, and erasing and re-programming the others.
