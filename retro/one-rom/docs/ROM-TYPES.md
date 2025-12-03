# ROM Type Specifications

This document provides detailed specifications for the different ROM types One ROM supports, and aims to support in future, including pinouts, control lines, and programming requirements.

The document is auto-generated from the [json/rom-types.json](/rust/config/json/rom-types.json) configuration file.  That file was created by researching datasheets for the various ROM types.

Some of the pin names have been modified from the datasheet values for consistency beween ROM types:

- /OE on 2704/2408 is called Program, but serves as /OE when in read mode.  Other 27xx ROMs use /OE for that pin, hence the /OE name is used here. 
- Similarly /CE on 2704/2708 ROMs is called /CS, but is called /CE for consistency with other ROM types.
- 23256/23512 chip select lines are often called CE/OE on datasheets, but are mask programmable to be active high or low, hence these are referred to within this doc as CS lines, like the other 23xx ROMs.

There are also some other inconsistencies between types:

- 2332's CS2 is pin 21 and pin 18 is A11.  On the 2316, CS2 is pin 18, and CS3 pin 21.
- The 2332's A11 is pin18, but the 2732's A11 is pin 21.

## Contents

- [24-pin Mask ROM Family (23xx)](#24-pin-mask-rom-family-23xx)
- [28-pin Mask ROM Family (23xxx)](#28-pin-mask-rom-family-23xx)
- [24-pin EPROM Family (27xx)](#24-pin-eprom-family-27xx)
- [28-pin EPROM Family (2764 and 27xxx)](#28-pin-eprom-family-27xx)
- [Pin Function Comparison](#pin-function-comparison)
- [Detailed Pinouts](#detailed-pinouts)

## 24-pin Mask ROM Family (23xx)

| ROM Type | Size | Address Lines | Control Lines | Programming |
|----------|------|---------------|---------------|-------------|
| 2316 | 2KB | 11 (A0-A10) | CS1 (pin 20), CS2 (pin 18), CS3 (pin 21) | None |
| 2332 | 4KB | 12 (A0-A11) | CS1 (pin 20), CS2 (pin 21) | None |
| 2364 | 8KB | 13 (A0-A12) | CS1 (pin 20) | None |

## 28-pin Mask ROM Family (23xx)

| ROM Type | Size | Address Lines | Control Lines | Programming |
|----------|------|---------------|---------------|-------------|
| 23128 | 16KB | 14 (A0-A13) | CS1 (pin 20), CS2 (pin 22), CS3 (pin 27) | None |
| 23256 | 32KB | 15 (A0-A14) | CS1 (pin 20), CS2 (pin 22) | None |
| 23512 | 64KB | 16 (A0-A15) | CS1 (pin 20), CS2 (pin 22) | None |

## 24-pin EPROM Family (27xx)

| ROM Type | Size | Address Lines | Control Lines | Programming |
|----------|------|---------------|---------------|-------------|
| 2704 | 512B | 9 (A0-A8) | /CE (pin 18), /OE (pin 20) | VPP: pin 18 (Low during read) |
| 2708 | 1KB | 10 (A0-A9) | /CE (pin 18), /OE (pin 20) | VPP: pin 18 (Low during read) |
| 2716 | 2KB | 11 (A0-A10) | /CE (pin 18), /OE (pin 20) | VPP: pin 21 (VCC during read) |
| 2732 | 4KB | 12 (A0-A11) | /CE (pin 18), /OE (pin 20) | VPP: pin 20 (Acts as /OE) |

## 28-pin EPROM Family (27xx)

| ROM Type | Size | Address Lines | Control Lines | Programming |
|----------|------|---------------|---------------|-------------|
| 2764 | 8KB | 13 (A0-A12) | /CE (pin 20), /OE (pin 22) | VPP: pin 1 (VCC during read); /PGM: pin 27 (High during read) |
| 27128 | 16KB | 14 (A0-A13) | /CE (pin 20), /OE (pin 22) | VPP: pin 1 (VCC during read); /PGM: pin 27 (High during read) |
| 27256 | 32KB | 15 (A0-A14) | /CE (pin 20), /OE (pin 22) | VPP: pin 1 (VCC during read) |
| 27512 | 64KB | 16 (A0-A15) | /CE (pin 20), /OE (pin 22) | VPP: pin 22 (VCC during read) |

## Pin Function Comparison

### 24-pin Package

| Pin | 2316 | 2332 | 2364 | 2704 | 2708 | 2716 | 2732 |
|-----|------|------|------|------|------|------|------|
| 1 | A7 | A7 | A7 | A7 | A7 | A7 | A7 |
| 2 | A6 | A6 | A6 | A6 | A6 | A6 | A6 |
| 3 | A5 | A5 | A5 | A5 | A5 | A5 | A5 |
| 4 | A4 | A4 | A4 | A4 | A4 | A4 | A4 |
| 5 | A3 | A3 | A3 | A3 | A3 | A3 | A3 |
| 6 | A2 | A2 | A2 | A2 | A2 | A2 | A2 |
| 7 | A1 | A1 | A1 | A1 | A1 | A1 | A1 |
| 8 | A0 | A0 | A0 | A0 | A0 | A0 | A0 |
| 9 | D0 | D0 | D0 | D0 | D0 | D0 | D0 |
| 10 | D1 | D1 | D1 | D1 | D1 | D1 | D1 |
| 11 | D2 | D2 | D2 | D2 | D2 | D2 | D2 |
| 12 | GND | GND | GND | GND | GND | GND | GND |
| 13 | D3 | D3 | D3 | D3 | D3 | D3 | D3 |
| 14 | D4 | D4 | D4 | D4 | D4 | D4 | D4 |
| 15 | D5 | D5 | D5 | D5 | D5 | D5 | D5 |
| 16 | D6 | D6 | D6 | D6 | D6 | D6 | D6 |
| 17 | D7 | D7 | D7 | D7 | D7 | D7 | D7 |
| 18 | CS2 | A11 | A11 | /CE+VPP | /CE+VPP | /CE | /CE+PE |
| 19 | A10 | A10 | A10 | VDD | VDD | A10 | A10 |
| 20 | CS1 | CS1 | CS1 | /OE+PE | /OE+PE | /OE+PE | /OE+VPP |
| 21 | CS3 | CS2 | A12 | VBB | VBB | VPP | A11 |
| 22 | A9 | A9 | A9 | GND | A9 | A9 | A9 |
| 23 | A8 | A8 | A8 | A8 | A8 | A8 | A8 |
| 24 | VCC | VCC | VCC | VCC | VCC | VCC | VCC |

### 28-pin Package

| Pin | 23128 | 23256 | 23512 | 2764 | 27128 | 27256 | 27512 |
|-----|------|------|------|------|------|------|------|
| 1 | NC | NC | A15 | VPP | VPP | VPP | A15 |
| 2 | A12 | A12 | A12 | A12 | A12 | A12 | A12 |
| 3 | A7 | A7 | A7 | A7 | A7 | A7 | A7 |
| 4 | A6 | A6 | A6 | A6 | A6 | A6 | A6 |
| 5 | A5 | A5 | A5 | A5 | A5 | A5 | A5 |
| 6 | A4 | A4 | A4 | A4 | A4 | A4 | A4 |
| 7 | A3 | A3 | A3 | A3 | A3 | A3 | A3 |
| 8 | A2 | A2 | A2 | A2 | A2 | A2 | A2 |
| 9 | A1 | A1 | A1 | A1 | A1 | A1 | A1 |
| 10 | A0 | A0 | A0 | A0 | A0 | A0 | A0 |
| 11 | D0 | D0 | D0 | D0 | D0 | D0 | D0 |
| 12 | D1 | D1 | D1 | D1 | D1 | D1 | D1 |
| 13 | D2 | D2 | D2 | D2 | D2 | D2 | D2 |
| 14 | GND | GND | GND | GND | GND | GND | GND |
| 15 | D3 | D3 | D3 | D3 | D3 | D3 | D3 |
| 16 | D4 | D4 | D4 | D4 | D4 | D4 | D4 |
| 17 | D5 | D5 | D5 | D5 | D5 | D5 | D5 |
| 18 | D6 | D6 | D6 | D6 | D6 | D6 | D6 |
| 19 | D7 | D7 | D7 | D7 | D7 | D7 | D7 |
| 20 | CS1 | CS1 | CS1 | /CE | /CE | /CE | /CE+PE |
| 21 | A10 | A10 | A10 | A10 | A10 | A10 | A10 |
| 22 | CS2 | CS2 | CS2 | /OE | /OE | /OE+PE | /OE+VPP |
| 23 | A11 | A11 | A11 | A11 | A11 | A11 | A11 |
| 24 | A9 | A9 | A9 | A9 | A9 | A9 | A9 |
| 25 | A8 | A8 | A8 | A8 | A8 | A8 | A8 |
| 26 | A13 | A13 | A13 | NC | A13 | A13 | A13 |
| 27 | CS3 | A14 | A14 | /PGM | /PGM | A14 | A14 |
| 28 | VCC | VCC | VCC | VCC | VCC | VCC | VCC |

## Detailed Pinouts

### 2316 - 2KB mask ROM with 3 configurable CS lines

**Package:** 24-pin DIP  
**Capacity:** 2048 bytes  
**Control:** 3 configurable CS lines  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A10) | 8,7,6,5,4,3,2,1,23,22,19 | 11 address lines |
| Data (D0-D7) | 9,10,11,13,14,15,16,17 | 8 data lines |
| CS1 | 20 | Configurable polarity |
| CS2 | 18 | Configurable polarity |
| CS3 | 21 | Configurable polarity |
| VCC | 24 | +5V |
| GND | 12 | 0V |

### 2332 - 4KB mask ROM with 2 configurable CS lines

**Package:** 24-pin DIP  
**Capacity:** 4096 bytes  
**Control:** 2 configurable CS lines  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A11) | 8,7,6,5,4,3,2,1,23,22,19,18 | 12 address lines |
| Data (D0-D7) | 9,10,11,13,14,15,16,17 | 8 data lines |
| CS1 | 20 | Configurable polarity |
| CS2 | 21 | Configurable polarity |
| VCC | 24 | +5V |
| GND | 12 | 0V |

### 2364 - 8KB mask ROM with 1 configurable CS line

**Package:** 24-pin DIP  
**Capacity:** 8192 bytes  
**Control:** 1 configurable CS line  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A12) | 8,7,6,5,4,3,2,1,23,22,19,18,21 | 13 address lines |
| Data (D0-D7) | 9,10,11,13,14,15,16,17 | 8 data lines |
| CS1 | 20 | Configurable polarity |
| VCC | 24 | +5V |
| GND | 12 | 0V |

### 23128 - 16KB mask ROM with 3 configurable CS lines

**Package:** 28-pin DIP  
**Capacity:** 16384 bytes  
**Control:** 3 configurable CS lines  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A13) | 10,9,8,7,6,5,4,3,25,24,21,23,2,26 | 14 address lines |
| Data (D0-D7) | 11,12,13,15,16,17,18,19 | 8 data lines |
| CS1 | 20 | Configurable polarity |
| CS2 | 22 | Configurable polarity |
| CS3 | 27 | Configurable polarity |
| VCC | 28 | +5V |
| GND | 14 | 0V |

### 23256 - 32KB mask ROM with 2 configurable CS lines

**Package:** 28-pin DIP  
**Capacity:** 32768 bytes  
**Control:** 2 configurable CS lines  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A14) | 10,9,8,7,6,5,4,3,25,24,21,23,2,26,27 | 15 address lines |
| Data (D0-D7) | 11,12,13,15,16,17,18,19 | 8 data lines |
| CS1 | 20 | Configurable polarity |
| CS2 | 22 | Configurable polarity |
| VCC | 28 | +5V |
| GND | 14 | 0V |

### 23512 - 64KB mask ROM with 2 configurable CS lines

**Package:** 28-pin DIP  
**Capacity:** 65536 bytes  
**Control:** 2 configurable CS lines  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A15) | 10,9,8,7,6,5,4,3,25,24,21,23,2,26,27,1 | 16 address lines |
| Data (D0-D7) | 11,12,13,15,16,17,18,19 | 8 data lines |
| CS1 | 20 | Configurable polarity |
| CS2 | 22 | Configurable polarity |
| VCC | 28 | +5V |
| GND | 14 | 0V |

### 2704 - 512B EPROM with multiple supply voltages

**Package:** 24-pin DIP  
**Capacity:** 512 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A8) | 8,7,6,5,4,3,2,1,23 | 9 address lines |
| Data (D0-D7) | 9,10,11,13,14,15,16,17 | 8 data lines |
| CE | 18 | Active low |
| OE | 20 | Active low |
| VPP | 18 | Low during read during read |
| PE | 20 | Low during read during read |
| VCC | 24 | +5V |
| VDD | 19 | +12V |
| VBB | 21 | -5V |
| GND | 12 | 0V |
| GND | 22 | 0V |

### 2708 - 1KB EPROM with multiple supply voltages

**Package:** 24-pin DIP  
**Capacity:** 1024 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A9) | 8,7,6,5,4,3,2,1,23,22 | 10 address lines |
| Data (D0-D7) | 9,10,11,13,14,15,16,17 | 8 data lines |
| CE | 18 | Active low |
| OE | 20 | Active low |
| VPP | 18 | Low during read during read |
| PE | 20 | Low during read during read |
| VCC | 24 | +5V |
| VDD | 19 | +12V |
| VBB | 21 | -5V |
| GND | 12 | 0V |

### 2716 - 2KB EPROM with fixed active-low CE/OE

**Package:** 24-pin DIP  
**Capacity:** 2048 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A10) | 8,7,6,5,4,3,2,1,23,22,19 | 11 address lines |
| Data (D0-D7) | 9,10,11,13,14,15,16,17 | 8 data lines |
| CE | 18 | Active low |
| OE | 20 | Active low |
| VPP | 21 | VCC during read during read |
| PE | 20 | Low during read during read |
| VCC | 24 | +5V |
| GND | 12 | 0V |

### 2732 - 4KB EPROM with fixed active-low CE and shared OE/VPP

**Package:** 24-pin DIP  
**Capacity:** 4096 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A11) | 8,7,6,5,4,3,2,1,23,22,19,21 | 12 address lines |
| Data (D0-D7) | 9,10,11,13,14,15,16,17 | 8 data lines |
| CE | 18 | Active low |
| OE | 20 | Active low |
| VPP | 20 | Acts as /OE during read |
| PE | 18 | Low during read during read |
| VCC | 24 | +5V |
| GND | 12 | 0V |

### 2764 - 8KB EPROM with fixed active-low CE/OE

**Package:** 28-pin DIP  
**Capacity:** 8192 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A12) | 10,9,8,7,6,5,4,3,25,24,21,23,2 | 13 address lines |
| Data (D0-D7) | 11,12,13,15,16,17,18,19 | 8 data lines |
| CE | 20 | Active low |
| OE | 22 | Active low |
| VPP | 1 | VCC during read during read |
| /PGM | 27 | High during read during read |
| VCC | 28 | +5V |
| GND | 14 | 0V |

### 27128 - 16KB EPROM with fixed active-low CE/OE

**Package:** 28-pin DIP  
**Capacity:** 16384 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A13) | 10,9,8,7,6,5,4,3,25,24,21,23,2,26 | 14 address lines |
| Data (D0-D7) | 11,12,13,15,16,17,18,19 | 8 data lines |
| CE | 20 | Active low |
| OE | 22 | Active low |
| VPP | 1 | VCC during read during read |
| /PGM | 27 | High during read during read |
| VCC | 28 | +5V |
| GND | 14 | 0V |

### 27256 - 32KB EPROM with fixed active-low CE/OE

**Package:** 28-pin DIP  
**Capacity:** 32768 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A14) | 10,9,8,7,6,5,4,3,25,24,21,23,2,26,27 | 15 address lines |
| Data (D0-D7) | 11,12,13,15,16,17,18,19 | 8 data lines |
| CE | 20 | Active low |
| OE | 22 | Active low |
| VPP | 1 | VCC during read during read |
| PE | 22 | Low during read during read |
| VCC | 28 | +5V |
| GND | 14 | 0V |

### 27512 - 64KB EPROM with fixed active-low CE/OE

**Package:** 28-pin DIP  
**Capacity:** 65536 bytes  
**Control:** /CE, /OE  

| Function | Pins | Notes |
|----------|------|-------|
| Address (A0-A15) | 10,9,8,7,6,5,4,3,25,24,21,23,2,26,27,1 | 16 address lines |
| Data (D0-D7) | 11,12,13,15,16,17,18,19 | 8 data lines |
| CE | 20 | Active low |
| OE | 22 | Active low |
| VPP | 22 | VCC during read during read |
| PE | 20 | Low during read during read |
| VCC | 28 | +5V |
| GND | 14 | 0V |

