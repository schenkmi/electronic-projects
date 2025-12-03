# Raspberry Pi Pico as a Programmer

To use a stock Raspberry Pi Pico as a programmer for One ROM, download the `debugprobe_on_pico.uf2` file from the [Releases](https://github.com/raspberrypi/debugprobe/releases) page of Raspberry Pi's `debugprobe` repository.

Mount your Raspberry Pi Pico in BOOTSEL mode and copy the `debugprobe_on_pico.uf2` file to the Raspberry Pi Pico's file system.

The required pins on the Pico are:

- CLK - GP2 (pin 4)
- DIO - GP3 (pin 5)
- GND - any GND pin (3, 8, 13, 18, 23, 28, 33, 38)
- 5V - (if **not** connected to a retro system) - VBUS (pin 40)

Note that some Pico clone boards may have different pin numbering.  Usually GP2/GP3/GND are marked on the board using silkscreen.
