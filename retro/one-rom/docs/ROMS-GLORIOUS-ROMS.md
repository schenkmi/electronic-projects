# ROMs Glorious ROMs

Everything you wanted to know about 23 and 27 series ROMs but were afraid to ask.

If you're looking for detailed pin-outs for all of the 23 and 27 series ROMs, you can find them at [ROM-TYPES.md](./ROM-TYPES.md).

# 23 Series

The 23 series ROMs are factory "mask" programmed ROMs, and came in sizes from 2KB to 64KB.  They were not reprogrammable after factory programming.

They were used in many, many systems in the early days of home computing, including in systems like the Apple II, Commodore PET, TI-99, VIC-20, C64, Atari 800XL, ZX Spectrum, and more ... the list is long.

23 series ROMs are numbered 23 followed by the number of Kbits - so a 2KB ROM is 2316, 64KB 23512.

They come as 24 and 28 pin packages, depending on the size - 2/4/8KB came as 24 pin, while 16/32/64KB came as 28 pin.

They have varying number of chip select lines, from 1 to 3.  All chip select lines have to be active for the ROM to be enabled, and the chip select lines were mask programmed either active high or active low - with up to 8 different combinations possible on a chip with 3 CS lines.  The same manufacturer often used different combinations on different chips/machines.  For example, the C64's character ROM is a 2332 with CS1 active low and CS2 active high, while the VIC-20 character ROM is a 2332 with CS1 and CS2 active low.

While the 23256/23512 (32KB/64KB) datasheets sometimes label the CS lines as CE/OE like the 27 series chips, they were sometimes still mask programmable active high or low.  One ROM thus refers to 23256/23512 CS lines as CS1/CS2, not CE/OE.

Different versions of 23 series ROMs have different access times, and the early chips tended to be labelled by their address active time - time taken from address valid to data valid.  However, for One ROM's purpose, the chip select access time is more important, as this is when One ROM decides to lookup and serve the byte.  While the address active time tended to be between 450-300ns, the chip select access time was 200-100ns.

All 23 series ROMs are powered by 5V.

| Model | Size | Pins | # CS | One ROM Support |
|-------|------|------|------|-----------------|
| 2316  | 2KB  | 24   | 3    | yes             |
| 2332  | 4KB  | 24   | 2    | yes             |
| 2364  | 8KB  | 24   | 1    | yes             |
| 23128 | 16KB | 28   | 3    | in progress     |
| 23256 | 32KB | 28   | 2    | in progress     |
| 23512 | 64KB | 28   | 2    | in progress     |

# 27 Series

The 27 series ROMs are EPROMS, meaning Erasable Programmable Read Only Memory, coming in sizes from 0.5KB to 64KB.  Erasable here refers to the ability to erase the contents of the chip by exposing it to UV light, and then reprogram it electrically.  They can be easily identified as they have a window on the top of the chip package, which is normally covered with a sticker after programming to prevent accidental erasure by UV light.

Some computers of the vintage used a combination of 23 and 27 series ROMs, with 27 series being reserved for ROMs which were more likely to be upgraded later (or 23 series ROMs were replaced with vendor or user updated replacement 27 series ROMs).

Like 23 series ROMs, 27 series ROMs are numbered 27 followed by the number of Kbits - so a 0.5KB ROM is 2704, 64KB 27512, etc.

They also come as 24 and 28 pin packages, depending on the size - 0.5/1/2/4 came as 24 pin, while 8/16/32/64KB came as 28 pin.  Note that 8KB being a 28 pin package - the 8KB 23 series ROM was a 24 pin package.  This was presumably to enable both programming voltage (VPP) and program (PGM) pins to be included on the 8KB chip.

It is still possible to buy 27 series EPROMs today, but they are typically pulled from old equipment as they are no longer manufactured.  They are also often repainted and reprinted, often with different brand names/part numbers, which can make it a fiddly business to identify the chip for programming.  It may also mean supported access times are different to those advertised.  This author's experience is that most are relabeled, and around 20% appear to be faulty.

EPROMs should not be confused with EEPROMs, which are Electrically Erasable Programmable Read Only Memory, and can be erased and reprogrammed electrically, without the need for UV.

Like 23 series ROMs, 27 series ROMs have varying access times.  Specifically in the EPROM case, /CE and /OE access times are specified separately, with /CE typically being more lenient.  The /CE and /OE access times for the fastest ST M2764A(-1) are specified as 180ns/65ns respectively.  This means One ROM needs to act on the /CE line going low and be ready to serve the byte as soon as /OE goes low.

Most, but not all 27 series ROMs were powere solely by 5V.  However, the 2704/2708 models also required -5V (VBB) and +12V (VDD) on pins 21 and 19 respectively, including for read operation.  Therefore, if using a One ROM to replace a 2704/2708, you must ensure that these pins are not populated, as One ROM would be damaged by these voltages.

It is also important to note that, as 27 series ROMs were reprogrammable, they accepted a programming voltage on a programming pin.  Again, when using a One ROM to replace a 27 series ROM, you must ensure that the programming pin is not going to receive in excess of 5V, as One ROM would be damaged by this voltage.

| Model | Size | Pins | One ROM Support |
|-------|------|------|-----------------|
| 2704  | 0.5KB| 24   | maybe*          |
| 2708  | 1KB  | 24   | maybe*          |
| 2716  | 2KB  | 24   | maybe*          |
| 2732  | 4KB  | 24   | yes+            |
| 2764  | 8KB  | 28   | in progress     |
| 27128 | 16KB | 28   | in progress     |
| 27256 | 32KB | 28   | in progress     |
| 27512 | 64KB | 28   | in progress     |

(*) It is likely that One ROM can be programmed to emulate these chips by ensuring a compatible ROM image is written, and an appropriate 23 type selected in its config.  Raise a github issue if you'd like to understand how to do this.

(+) The 2732 is pin compatible with the 2332 (excepting the programming voltage, see above), so One ROM can emulate it using `type=2332,cs1=0,cs2=0`.

# 23 and 27 compatibility

The 23 and 27 series ROMs are largely but not entirely pin compatible.  The key differences are:
- 8KB 23 series ROMs are 24 pin, while 8KB 27 series ROMs are 28 pin
- 23 series have varying numbers of CS lines, with varying active high/low configurations, while 27 series have 2 active low CS lines (/CE and /OE)

A very common replacement strategy for 23 series ROMs is to use a 27 series ROM, and an adapter board.  This is a well established practice, and there are many such adapter boards available.  However, you often require different adapter boards, or different hardware versions, for the different sizes and CS configurations of 23 series ROMs.

One ROM aims to simplify this by allowing a single 24 pin hardware variant to emulate all 24 pin 23 and 27 series ROMs, and a single 28 pin hardware variant to emulate all 28 pin 23 and 27 series ROMs like so:

One ROM (24):
- 2316
- 2332
- 2364
- 2704 (maybe*)
- 2708 (maybe*)
- 2716 (maybe*)
- 2732

One ROM (28) - in progress:
- 23128
- 23256
- 23512
- 2764
- 27128
- 27256
- 27512

# Other Series

The Apple I and early Apple IIs used a 2513 ROM as character ROM.  This was replaced on later models with a 2716.  The 2513 has a different pinout to the 2316/2716, and has -12V pull-downs on the address lines, so it is electrically incompatible with the 2316/2716, and incompatible with One ROM.

There are dedicated 2513 replacements available, as well as adapter boards to take 2316/2716 ROMs (which One ROM could emulate).

NEVER connect a One ROM directly into a 2513 ROM socket - you will damage the One ROM.
