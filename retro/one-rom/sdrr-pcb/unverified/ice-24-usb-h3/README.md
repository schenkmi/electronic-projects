# One ROM Ice USB H2 24 Pin 

**Unverified**: Very similar electrically to H2.

Very similar to [rev H2](../stm32f4-24-pin-rev-h/README.md) but with the following changes:
- Make holes for BOOT0/3V3 jumpers larger to make them easier to jump.
- Added inline resistor between VBUS and PA9, to avoid potential ESD damage to STM32F4.
- Various components moved around to make space for the new resistor.
- Now a single drill file, combining PTH and NPTH.

There is a single set of gerbers, one CPL/POS file and one BOM file for the STM32F411RET6 MCU.

To create the BOM for an alternate MCU, replace the microcontroller part number.  For the STM32F405RET6, you must also replace RC4/RC5/C9 - see the schematic for details.

## Contents

- [Schematic](ice-24-h3-schematic.pdf)
- [Fab Files](fab/)
- [KiCad Design Files](kicad/)
- [Errata](#errata)
- [Notes](#notes)
- [Changelog](#changelog)
- [BOM](#bom)

## Errata

## Notes

## Changelog

See above

## BOM

See fab files.