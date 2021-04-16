EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Xilinx CPLD CoolRunner-II XC2C64A"
Date "2021-04-16"
Rev "V1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L kicad-snk:XC2C64A-xVQ44 U?
U 1 1 60A9A972
P 6300 3700
F 0 "U?" H 6300 2211 50  0000 C CNN
F 1 "XC2C64A-xVQ44" H 6300 2120 50  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 6300 1900 50  0001 C CNN
F 3 "https://www.xilinx.com/support/documentation/data_sheets/ds311.pdf" H 7200 2250 50  0001 C CNN
	1    6300 3700
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:TPS7A0518PDBV U?
U 1 1 60A9E22C
P 2850 6850
F 0 "U?" H 2850 7217 50  0000 C CNN
F 1 "TPS7A2018" H 2850 7126 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 2850 7200 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tps7a05.pdf" H 2850 7350 50  0001 C CNN
	1    2850 6850
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:TPS7A0533PDBV U?
U 1 1 60A9F306
P 1600 6000
F 0 "U?" H 1600 6367 50  0000 C CNN
F 1 "TPS7A0533PDBV" H 1600 6276 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 1600 6350 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tps7a05.pdf" H 1600 6500 50  0001 C CNN
	1    1600 6000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
