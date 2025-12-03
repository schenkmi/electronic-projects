# Fire 24 USB Rev B

23xx Fire (RP2350 24 pin) USB One ROM PCB.

**Verified** - Individual ROMs, multi-ROM sets and dynamically banked ROMs have all been tested.  Testing has primarily taken place using the C64.  You should always check the gerbers, component lists and component orientations with your supplier before ordering.

## Contents

- [Schematic](./fire-24-usb-b-schematic.pdf)
- [Fab Files](fab/)
- [KiCad Design Files](kicad/)
- [Errata](#errata)
- [Notes](#notes)
- [Changelog](#changelog)

## Errata

None

## Notes

None

## Changelog

Substantial changes from Rev A:
- Add USB connector
  - VBUS connected to a GPIO
- VBUS current feeding VBUS_DET using 10k resistive divider
- Add additional jumper pin (other detects VBUS)
- Remove programming header
- Remove spare, single 3V3 pin
- Pins moved around, in particular D now pins 0-7, address pins 8-23.  Requires firmware v0.5.4 onwards.
