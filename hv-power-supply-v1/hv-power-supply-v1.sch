EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Discrete HV Supply"
Date "2021-02-05"
Rev "V1a"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L hv-power-supply-v1-rescue:Mounting_Hole_PAD-Mechanical-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue MK1
U 1 1 5A6CFED2
P 15100 700
F 0 "MK1" H 15200 751 50  0000 L CNN
F 1 "Mounting_Hole_PAD" H 15200 660 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 15100 700 50  0001 C CNN
F 3 "" H 15100 700 50  0001 C CNN
	1    15100 700 
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:Mounting_Hole_PAD-Mechanical-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue MK2
U 1 1 5A6CFF98
P 15100 1000
F 0 "MK2" H 15200 1051 50  0000 L CNN
F 1 "Mounting_Hole_PAD" H 15200 960 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 15100 1000 50  0001 C CNN
F 3 "" H 15100 1000 50  0001 C CNN
	1    15100 1000
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:Mounting_Hole_PAD-Mechanical-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue MK3
U 1 1 5A6CFFFA
P 15100 1300
F 0 "MK3" H 15200 1351 50  0000 L CNN
F 1 "Mounting_Hole_PAD" H 15200 1260 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 15100 1300 50  0001 C CNN
F 3 "" H 15100 1300 50  0001 C CNN
	1    15100 1300
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:Mounting_Hole_PAD-Mechanical-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue MK4
U 1 1 5A6D003F
P 15100 1600
F 0 "MK4" H 15200 1651 50  0000 L CNN
F 1 "Mounting_Hole_PAD" H 15200 1560 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 15100 1600 50  0001 C CNN
F 3 "" H 15100 1600 50  0001 C CNN
	1    15100 1600
	1    0    0    -1  
$EndComp
NoConn ~ 15100 800 
NoConn ~ 15100 1100
NoConn ~ 15100 1400
NoConn ~ 15100 1700
$Comp
L hv-power-supply-v1-rescue:BYV26C-PSU6SN7-hv-power-supply-v1-rescue D3
U 1 1 5D44FFF5
P 2200 1600
F 0 "D3" H 2200 1816 50  0000 C CNN
F 1 "BYG20J" H 2200 1725 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 2200 1425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2200 1600 50  0001 C CNN
	1    2200 1600
	-1   0    0    1   
$EndComp
$Comp
L hv-power-supply-v1-rescue:BYV26C-PSU6SN7-hv-power-supply-v1-rescue D5
U 1 1 5D450671
P 2200 3500
F 0 "D5" H 2200 3716 50  0000 C CNN
F 1 "BYG20J" H 2200 3625 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 2200 3325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2200 3500 50  0001 C CNN
	1    2200 3500
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:BYV26C-PSU6SN7-hv-power-supply-v1-rescue D6
U 1 1 5D4509EB
P 2200 4300
F 0 "D6" H 2200 4516 50  0000 C CNN
F 1 "BYG20J" H 2200 4425 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 2200 4125 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2200 4300 50  0001 C CNN
	1    2200 4300
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:BYV26C-PSU6SN7-hv-power-supply-v1-rescue D4
U 1 1 5D450EAA
P 2200 2400
F 0 "D4" H 2200 2616 50  0000 C CNN
F 1 "BYG20J" H 2200 2525 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 2200 2225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2200 2400 50  0001 C CNN
	1    2200 2400
	-1   0    0    1   
$EndComp
$Comp
L Device:C C14
U 1 1 5D45BEFD
P 5000 9500
F 0 "C14" H 5115 9546 50  0000 L CNN
F 1 "330nF/50V" H 5115 9455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5038 9350 50  0001 C CNN
F 3 "~" H 5000 9500 50  0001 C CNN
	1    5000 9500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 5D4699C7
P 6700 9500
F 0 "C19" H 6815 9546 50  0000 L CNN
F 1 "100nF/50V" H 6815 9455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6738 9350 50  0001 C CNN
F 3 "~" H 6700 9500 50  0001 C CNN
	1    6700 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 8500 6050 8500
Connection ~ 6050 8500
$Comp
L hv-power-supply-v1-rescue:TLC555CDR-dk_Clock-Timing-Programmable-Timers-and-Oscillators-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue U6
U 1 1 5D470D45
P 9250 9050
F 0 "U6" H 9250 9603 60  0000 C CNN
F 1 "TLC555CDR" H 9250 9497 60  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9450 9250 60  0001 L CNN
F 3 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Ftlc555" H 9450 9350 60  0001 L CNN
F 4 "296-1336-1-ND" H 9450 9450 60  0001 L CNN "Digi-Key_PN"
F 5 "TLC555CDR" H 9450 9550 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 9450 9650 60  0001 L CNN "Category"
F 7 "Clock/Timing - Programmable Timers and Oscillators" H 9450 9750 60  0001 L CNN "Family"
F 8 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Ftlc555" H 9450 9850 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/TLC555CDR/296-1336-1-ND/404959" H 9450 9950 60  0001 L CNN "DK_Detail_Page"
F 10 "IC OSC SGL TIMER 2.1MHZ 8-SOIC" H 9450 10050 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 9450 10150 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9450 10250 60  0001 L CNN "Status"
	1    9250 9050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5D471DEA
P 7800 9500
F 0 "R4" H 7870 9546 50  0000 L CNN
F 1 "1Meg 1/8W" H 7870 9455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7730 9500 50  0001 C CNN
F 3 "~" H 7800 9500 50  0001 C CNN
	1    7800 9500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5D47247E
P 10200 9750
F 0 "R13" H 10270 9796 50  0000 L CNN
F 1 "2.49k 1/8W" H 10270 9705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 10130 9750 50  0001 C CNN
F 3 "~" H 10200 9750 50  0001 C CNN
	1    10200 9750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 5D473526
P 10550 10100
F 0 "R14" H 10620 10146 50  0000 L CNN
F 1 "2.49k 1/8W" H 10620 10055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 10480 10100 50  0001 C CNN
F 3 "~" H 10550 10100 50  0001 C CNN
	1    10550 10100
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:MMBT3904-TP-dk_Transistors-Bipolar-BJT-Single-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue Q2
U 1 1 5D4746D0
P 11050 9750
F 0 "Q2" H 11238 9803 60  0000 L CNN
F 1 "MMBT3904-TP" H 11238 9697 60  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 11250 9950 60  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMBT3904(SOT-23).pdf" H 11250 10050 60  0001 L CNN
F 4 "MMBT3904TPMSCT-ND" H 11250 10150 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT3904-TP" H 11250 10250 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 11250 10350 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 11250 10450 60  0001 L CNN "Family"
F 8 "https://www.mccsemi.com/pdf/Products/MMBT3904(SOT-23).pdf" H 11250 10550 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/micro-commercial-co/MMBT3904-TP/MMBT3904TPMSCT-ND/717395" H 11250 10650 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.2A SOT23" H 11250 10750 60  0001 L CNN "Description"
F 11 "Micro Commercial Co" H 11250 10850 60  0001 L CNN "Manufacturer"
F 12 "Active" H 11250 10950 60  0001 L CNN "Status"
	1    11050 9750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C23
U 1 1 5D480494
P 7800 8800
F 0 "C23" H 7918 8846 50  0000 L CNN
F 1 "15uF/25V" H 7918 8755 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D_Pad2.25x2.55mm_HandSolder" H 7838 8650 50  0001 C CNN
F 3 "~" H 7800 8800 50  0001 C CNN
	1    7800 8800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C24
U 1 1 5D481DFE
P 8450 9500
F 0 "C24" H 8565 9546 50  0000 L CNN
F 1 "100nF/50V" H 8565 9455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8488 9350 50  0001 C CNN
F 3 "~" H 8450 9500 50  0001 C CNN
	1    8450 9500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C28
U 1 1 5D4821E7
P 9950 8750
F 0 "C28" H 10065 8796 50  0000 L CNN
F 1 "100nF/50V" H 10065 8705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 9988 8600 50  0001 C CNN
F 3 "~" H 9950 8750 50  0001 C CNN
	1    9950 8750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 10500 9250 9500
Wire Wire Line
	9250 10500 8450 10500
Wire Wire Line
	8450 10500 8450 9650
Connection ~ 9250 10500
Wire Wire Line
	8450 10500 7800 10500
Wire Wire Line
	7800 10500 7800 9650
Connection ~ 8450 10500
Wire Wire Line
	7800 10500 7300 10500
Wire Wire Line
	7300 10500 7300 9950
Connection ~ 7800 10500
Wire Wire Line
	7800 9350 7800 9150
Wire Wire Line
	7300 9150 7800 9150
Connection ~ 7800 9150
Wire Wire Line
	7800 9150 7800 8950
Wire Wire Line
	8750 9150 7800 9150
Wire Wire Line
	8750 9250 8450 9250
Wire Wire Line
	8450 9250 8450 9350
Wire Wire Line
	8750 9050 8600 9050
Wire Wire Line
	8600 9050 8600 8950
Wire Wire Line
	8600 8500 7800 8500
Connection ~ 6700 8500
Wire Wire Line
	8750 8950 8600 8950
Connection ~ 8600 8950
Wire Wire Line
	8600 8950 8600 8500
Wire Wire Line
	7800 8650 7800 8500
Connection ~ 7800 8500
Wire Wire Line
	7800 8500 6700 8500
Wire Wire Line
	7300 9150 7300 9650
Wire Wire Line
	9250 8700 9250 8500
Wire Wire Line
	9250 8500 8600 8500
Connection ~ 8600 8500
Wire Wire Line
	11150 9550 11150 9450
Wire Wire Line
	10650 9200 10650 9450
Wire Wire Line
	10650 9450 11150 9450
Connection ~ 11150 9450
Wire Wire Line
	11150 9450 11150 9350
Wire Wire Line
	11150 8750 11150 8650
Wire Wire Line
	11150 8500 9950 8500
Connection ~ 9250 8500
Wire Wire Line
	10650 8900 10650 8650
Wire Wire Line
	10650 8650 11150 8650
Connection ~ 11150 8650
Wire Wire Line
	11150 8650 11150 8500
Wire Wire Line
	11150 9950 11150 10500
Wire Wire Line
	9250 10500 9950 10500
Wire Wire Line
	9750 9150 9800 9150
Wire Wire Line
	9800 9150 9800 9750
Wire Wire Line
	9800 9750 10050 9750
Wire Wire Line
	10350 9750 10550 9750
Wire Wire Line
	10550 9950 10550 9750
Connection ~ 10550 9750
Wire Wire Line
	10550 9750 10850 9750
Wire Wire Line
	10550 10250 10550 10500
Connection ~ 10550 10500
Wire Wire Line
	10550 10500 11150 10500
Wire Wire Line
	9950 8900 9950 10500
Connection ~ 9950 10500
Wire Wire Line
	9950 10500 10550 10500
Wire Wire Line
	9950 8600 9950 8500
Connection ~ 9950 8500
Wire Wire Line
	9950 8500 9250 8500
Connection ~ 7300 10500
Text GLabel 8000 8100 2    50   Input ~ 0
+5VDC
Wire Wire Line
	8000 8100 7800 8100
Wire Wire Line
	7800 8100 7800 8500
Text GLabel 14000 8700 0    50   Input ~ 0
GND_LV
$Comp
L Device:R R27
U 1 1 5D48140A
P 14400 8500
F 0 "R27" H 14470 8546 50  0000 L CNN
F 1 "470R 1/8W" H 14470 8455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 14330 8500 50  0001 C CNN
F 3 "~" H 14400 8500 50  0001 C CNN
	1    14400 8500
	0    -1   -1   0   
$EndComp
Text GLabel 14000 8500 0    50   Input ~ 0
+5VDC
$Comp
L Regulator_Linear:LM317_3PinPackage U5
U 1 1 5D487A64
P 8250 6850
F 0 "U5" H 8250 7092 50  0000 C CNN
F 1 "LM317_3PinPackage" H 8250 7001 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 8250 7100 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 8250 6850 50  0001 C CNN
	1    8250 6850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Heatsink HS2
U 1 1 5D48855B
P 8900 6500
F 0 "HS2" H 9042 6621 50  0000 L CNN
F 1 "Heatsink" H 9042 6530 50  0000 L CNN
F 2 "Heatsinks:Heatsink_Fischer_SK104-STC-STIC_35x13mm_2xDrill2.5mm" H 8912 6500 50  0001 C CNN
F 3 "~" H 8912 6500 50  0001 C CNN
	1    8900 6500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5D48E456
P 9050 7100
F 0 "R10" H 9120 7146 50  0000 L CNN
F 1 "240R 1/8W" H 9120 7055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8980 7100 50  0001 C CNN
F 3 "~" H 9050 7100 50  0001 C CNN
	1    9050 7100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C22
U 1 1 5D48ECCD
P 7350 7350
F 0 "C22" H 7465 7396 50  0000 L CNN
F 1 "100nF/50V" H 7465 7305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7388 7200 50  0001 C CNN
F 3 "~" H 7350 7350 50  0001 C CNN
	1    7350 7350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C30
U 1 1 5D48EFEC
P 10350 7350
F 0 "C30" H 10465 7396 50  0000 L CNN
F 1 "100nF/50V" H 10465 7305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 10388 7200 50  0001 C CNN
F 3 "~" H 10350 7350 50  0001 C CNN
	1    10350 7350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5D48F2A8
P 8250 7500
F 0 "R7" H 8320 7546 50  0000 L CNN
F 1 "976R 1/8W" H 8320 7455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8180 7500 50  0001 C CNN
F 3 "~" H 8250 7500 50  0001 C CNN
	1    8250 7500
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM317_3PinPackage U4
U 1 1 5D4A937E
P 8250 5250
F 0 "U4" H 8250 5492 50  0000 C CNN
F 1 "LM317_3PinPackage" H 8250 5401 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 8250 5500 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 8250 5250 50  0001 C CNN
	1    8250 5250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Heatsink HS1
U 1 1 5D4A973A
P 8900 4900
F 0 "HS1" H 9042 5021 50  0000 L CNN
F 1 "Heatsink" H 9042 4930 50  0000 L CNN
F 2 "Heatsinks:Heatsink_Fischer_SK104-STC-STIC_35x13mm_2xDrill2.5mm" H 8912 4900 50  0001 C CNN
F 3 "~" H 8912 4900 50  0001 C CNN
	1    8900 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5D4B31F6
P 9050 5500
F 0 "R9" H 9120 5546 50  0000 L CNN
F 1 "240R 1/8W" H 9120 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8980 5500 50  0001 C CNN
F 3 "~" H 9050 5500 50  0001 C CNN
	1    9050 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5D4B3671
P 8250 5900
F 0 "R6" H 8320 5946 50  0000 L CNN
F 1 "976R 1/8W" H 8320 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8180 5900 50  0001 C CNN
F 3 "~" H 8250 5900 50  0001 C CNN
	1    8250 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C21
U 1 1 5D4B3A82
P 7350 5750
F 0 "C21" H 7465 5796 50  0000 L CNN
F 1 "100nF/50V" H 7465 5705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7388 5600 50  0001 C CNN
F 3 "~" H 7350 5750 50  0001 C CNN
	1    7350 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C29
U 1 1 5D4B3D7C
P 10350 5750
F 0 "C29" H 10465 5796 50  0000 L CNN
F 1 "100nF/50V" H 10465 5705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 10388 5600 50  0001 C CNN
F 3 "~" H 10350 5750 50  0001 C CNN
	1    10350 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C33
U 1 1 5D4B3FF1
P 11050 5750
F 0 "C33" H 11168 5796 50  0000 L CNN
F 1 "1uF/25V" H 11168 5705 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 11088 5600 50  0001 C CNN
F 3 "~" H 11050 5750 50  0001 C CNN
	1    11050 5750
	1    0    0    -1  
$EndComp
NoConn ~ 9750 9050
$Comp
L Device:C C1
U 1 1 5D48C954
P 1050 4800
F 0 "C1" H 1165 4846 50  0000 L CNN
F 1 "2.2nF 2kV" H 1165 4755 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L18.0mm_W5.0mm_P15.00mm_FKS3_FKP3" H 1088 4650 50  0001 C CNN
F 3 "~" H 1050 4800 50  0001 C CNN
	1    1050 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D48D965
P 1800 4800
F 0 "R1" H 1870 4846 50  0000 L CNN
F 1 "100R/2W" H 1870 4755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 1730 4800 50  0001 C CNN
F 3 "~" H 1800 4800 50  0001 C CNN
	1    1800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 6850 8650 6850
Wire Wire Line
	7950 6850 7800 6850
Wire Wire Line
	8250 7650 8250 7750
Connection ~ 8250 7750
Wire Wire Line
	7350 5600 7350 5250
Connection ~ 7350 5250
Wire Wire Line
	7350 5900 7350 6200
Wire Wire Line
	7350 6200 8250 6200
Wire Wire Line
	8250 6050 8250 6200
Connection ~ 8250 6200
Wire Wire Line
	8250 5750 8250 5550
Connection ~ 8250 5750
Wire Wire Line
	10350 5600 10350 5250
Wire Wire Line
	11050 5600 11050 5250
Wire Wire Line
	10350 5900 10350 6200
Wire Wire Line
	11050 5900 11050 6200
Text GLabel 6150 7750 0    50   Input ~ 0
GND_LV
$Comp
L Device:C C4
U 1 1 5D78BBA2
P 2200 1400
F 0 "C4" V 1948 1400 50  0000 C CNN
F 1 "10nF/630V" V 2039 1400 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 1250 50  0001 C CNN
F 3 "~" H 2200 1400 50  0001 C CNN
	1    2200 1400
	0    1    1    0   
$EndComp
$Comp
L Device:C C5
U 1 1 5D7B11F4
P 2200 2150
F 0 "C5" V 1948 2150 50  0000 C CNN
F 1 "10nF/630V" V 2039 2150 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 2000 50  0001 C CNN
F 3 "~" H 2200 2150 50  0001 C CNN
	1    2200 2150
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 5D7B1C4E
P 2200 3100
F 0 "C6" V 1948 3100 50  0000 C CNN
F 1 "10nF/630V" V 2039 3100 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 2950 50  0001 C CNN
F 3 "~" H 2200 3100 50  0001 C CNN
	1    2200 3100
	0    1    1    0   
$EndComp
$Comp
L Device:C C7
U 1 1 5D7B2C2A
P 2200 3900
F 0 "C7" V 1948 3900 50  0000 C CNN
F 1 "10nF/630V" V 2039 3900 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 3750 50  0001 C CNN
F 3 "~" H 2200 3900 50  0001 C CNN
	1    2200 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	2050 1600 1950 1600
Wire Wire Line
	2350 2400 2450 2400
Wire Wire Line
	2600 2400 2600 1600
Wire Wire Line
	2600 1600 2450 1600
Wire Wire Line
	2050 2400 1950 2400
Wire Wire Line
	1400 3500 1950 3500
Wire Wire Line
	1650 4300 1950 4300
Wire Wire Line
	2350 3500 2450 3500
Wire Wire Line
	2600 3500 2600 4300
Wire Wire Line
	2600 4300 2450 4300
Wire Wire Line
	2050 1400 1950 1400
Wire Wire Line
	1950 1400 1950 1600
Connection ~ 1950 1600
Wire Wire Line
	1950 1600 1400 1600
Wire Wire Line
	2350 1400 2450 1400
Wire Wire Line
	2450 1400 2450 1600
Connection ~ 2450 1600
Wire Wire Line
	2450 1600 2350 1600
Wire Wire Line
	2050 2150 1950 2150
Wire Wire Line
	1950 2150 1950 2400
Connection ~ 1950 2400
Wire Wire Line
	1950 2400 1650 2400
Wire Wire Line
	2350 2150 2450 2150
Wire Wire Line
	2450 2150 2450 2400
Connection ~ 2450 2400
Wire Wire Line
	2450 2400 2600 2400
Wire Wire Line
	2050 3100 1950 3100
Wire Wire Line
	1950 3100 1950 3500
Connection ~ 1950 3500
Wire Wire Line
	1950 3500 2050 3500
Wire Wire Line
	2350 3100 2450 3100
Wire Wire Line
	2450 3100 2450 3500
Connection ~ 2450 3500
Wire Wire Line
	2450 3500 2600 3500
Wire Wire Line
	2050 3900 1950 3900
Wire Wire Line
	1950 3900 1950 4300
Connection ~ 1950 4300
Wire Wire Line
	1950 4300 2050 4300
Wire Wire Line
	2350 3900 2450 3900
Wire Wire Line
	2450 3900 2450 4300
Connection ~ 2450 4300
Wire Wire Line
	2450 4300 2350 4300
$Comp
L Device:C C11
U 1 1 5D4A1C15
P 3650 2950
F 0 "C11" V 3398 2950 50  0000 C CNN
F 1 "100nF/630V" V 3489 2950 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L18.0mm_W5.0mm_P15.00mm_FKS3_FKP3" H 3688 2800 50  0001 C CNN
F 3 "~" H 3650 2950 50  0001 C CNN
	1    3650 2950
	-1   0    0    1   
$EndComp
Connection ~ 2600 2400
Connection ~ 2600 3500
Wire Wire Line
	3650 3100 3650 3500
Text GLabel 3350 3650 0    50   Input ~ 0
GND_HV
$Comp
L hv-power-supply-v1-rescue:IRF510PBF-dk_Transistors-FETs-MOSFETs-Single-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue Q4
U 1 1 5D4EC925
P 12650 2400
F 0 "Q4" H 12758 2453 60  0000 L CNN
F 1 "IRF840" H 12758 2347 60  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 12850 2600 60  0001 L CNN
F 3 "http://www.vishay.com/docs/91015/sihf510.pdf" H 12850 2700 60  0001 L CNN
F 4 "IRF510PBF-ND" H 12850 2800 60  0001 L CNN "Digi-Key_PN"
F 5 "IRF510PBF" H 12850 2900 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 12850 3000 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 12850 3100 60  0001 L CNN "Family"
F 8 "http://www.vishay.com/docs/91015/sihf510.pdf" H 12850 3200 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/vishay-siliconix/IRF510PBF/IRF510PBF-ND/811710" H 12850 3300 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 100V 5.6A TO-220AB" H 12850 3400 60  0001 L CNN "Description"
F 11 "Vishay Siliconix" H 12850 3500 60  0001 L CNN "Manufacturer"
F 12 "Active" H 12850 3600 60  0001 L CNN "Status"
	1    12650 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5D4F27BA
P 12650 3200
F 0 "R18" H 12720 3246 50  0000 L CNN
F 1 "12R/0.6W" H 12720 3155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 12580 3200 50  0001 C CNN
F 3 "~" H 12650 3200 50  0001 C CNN
	1    12650 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R19
U 1 1 5D4F3205
P 12650 3850
F 0 "R19" H 12720 3896 50  0000 L CNN
F 1 "402K/0.6W" H 12720 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 12580 3850 50  0001 C CNN
F 3 "~" H 12650 3850 50  0001 C CNN
	1    12650 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R20
U 1 1 5D4F3A1B
P 12650 4350
F 0 "R20" H 12720 4396 50  0000 L CNN
F 1 "10K/0.6W" H 12720 4305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 12580 4350 50  0001 C CNN
F 3 "~" H 12650 4350 50  0001 C CNN
	1    12650 4350
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:MMBT3904-TP-dk_Transistors-Bipolar-BJT-Single-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue Q3
U 1 1 5D4F56E1
P 11500 2900
F 0 "Q3" H 11688 2953 60  0000 L CNN
F 1 "MMBT3904-TP" H 11688 2847 60  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 11700 3100 60  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMBT3904(SOT-23).pdf" H 11700 3200 60  0001 L CNN
F 4 "MMBT3904TPMSCT-ND" H 11700 3300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT3904-TP" H 11700 3400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 11700 3500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 11700 3600 60  0001 L CNN "Family"
F 8 "https://www.mccsemi.com/pdf/Products/MMBT3904(SOT-23).pdf" H 11700 3700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/micro-commercial-co/MMBT3904-TP/MMBT3904TPMSCT-ND/717395" H 11700 3800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.2A SOT23" H 11700 3900 60  0001 L CNN "Description"
F 11 "Micro Commercial Co" H 11700 4000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 11700 4100 60  0001 L CNN "Status"
	1    11500 2900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D50AAEA
P 4350 1950
F 0 "R2" H 4420 1996 50  0000 L CNN
F 1 "100k/2W" H 4420 1905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 4280 1950 50  0001 C CNN
F 3 "~" H 4350 1950 50  0001 C CNN
	1    4350 1950
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM321 U3
U 1 1 5D789BFC
P 6950 3500
F 0 "U3" H 7294 3546 50  0000 L CNN
F 1 "LM321" H 7294 3455 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 6950 3500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm321.pdf" H 6950 3500 50  0001 C CNN
	1    6950 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 5D51B86E
P 5500 3300
F 0 "C15" H 5615 3346 50  0000 L CNN
F 1 "100nF/50V" H 5615 3255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5538 3150 50  0001 C CNN
F 3 "~" H 5500 3300 50  0001 C CNN
	1    5500 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3650 3650 3650
Wire Wire Line
	3650 3650 3650 3500
Connection ~ 3650 3500
Wire Wire Line
	3650 3500 4050 3500
Wire Wire Line
	4050 3500 4050 4600
Wire Wire Line
	4050 4600 4350 4600
Wire Wire Line
	4350 3950 4350 4600
$Comp
L Device:R R8
U 1 1 5D6391A7
P 8500 3500
F 0 "R8" H 8570 3546 50  0000 L CNN
F 1 "100R 1/8W" H 8570 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8430 3500 50  0001 C CNN
F 3 "~" H 8500 3500 50  0001 C CNN
	1    8500 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	8650 3500 8800 3500
$Comp
L Device:R R11
U 1 1 5D6D0C3D
P 9100 2100
F 0 "R11" H 9170 2146 50  0000 L CNN
F 1 "470k/0.6W" H 9170 2055 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 9030 2100 50  0001 C CNN
F 3 "~" H 9100 2100 50  0001 C CNN
	1    9100 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5D77CB36
P 11850 3850
F 0 "R15" H 11920 3896 50  0000 L CNN
F 1 "200k/0.6W" H 11920 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 11780 3850 50  0001 C CNN
F 3 "~" H 11850 3850 50  0001 C CNN
	1    11850 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 5D7EA431
P 12250 2900
F 0 "R17" H 12320 2946 50  0000 L CNN
F 1 "4.99k,1/8W" H 12320 2855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 12180 2900 50  0001 C CNN
F 3 "~" H 12250 2900 50  0001 C CNN
	1    12250 2900
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_TRIM RV1
U 1 1 5D7FEB17
P 6050 3600
F 0 "RV1" H 5980 3646 50  0000 R CNN
F 1 "100k" H 5980 3555 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 6050 3600 50  0001 C CNN
F 3 "~" H 6050 3600 50  0001 C CNN
	1    6050 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	12650 4500 12650 4600
Wire Wire Line
	12650 3550 11400 3550
Connection ~ 11850 4600
Wire Wire Line
	11850 4600 12650 4600
$Comp
L Device:CP C13
U 1 1 5DB70D19
P 4950 3500
F 0 "C13" H 5068 3546 50  0000 L CNN
F 1 "10uF/25V" H 5068 3455 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 4988 3350 50  0001 C CNN
F 3 "~" H 4950 3500 50  0001 C CNN
	1    4950 3500
	1    0    0    -1  
$EndComp
Connection ~ 5500 4600
Connection ~ 4350 4600
Wire Wire Line
	4350 4600 4950 4600
Connection ~ 5500 2500
Wire Wire Line
	4350 2500 4950 2500
Connection ~ 4950 2500
Wire Wire Line
	4950 2500 5500 2500
Connection ~ 4950 4600
Wire Wire Line
	4950 4600 5500 4600
Text GLabel 13050 9750 0    50   Input ~ 0
GND_HV
Wire Wire Line
	11950 9550 11950 9350
Wire Wire Line
	11950 9550 11550 9550
Wire Wire Line
	11550 9550 11550 9350
Wire Wire Line
	13050 9750 13300 9750
Text GLabel 14450 3550 2    50   Input ~ 0
HV
Text GLabel 12050 8150 1    50   Input ~ 0
HV
Wire Wire Line
	12050 8750 12050 8400
Wire Wire Line
	11650 8750 11650 8400
Wire Wire Line
	11650 8400 12050 8400
Connection ~ 12050 8400
Wire Wire Line
	12050 8400 12050 8150
Text GLabel 13650 7250 0    50   Input ~ 0
GND_HV
Text GLabel 15100 7250 2    50   Input ~ 0
GND_LV
$Comp
L Device:R R24
U 1 1 5DC91072
P 14350 6850
F 0 "R24" V 14143 6850 50  0000 C CNN
F 1 "1R/0.5W" V 14234 6850 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 14280 6850 50  0001 C CNN
F 3 "~" H 14350 6850 50  0001 C CNN
	1    14350 6850
	0    1    1    0   
$EndComp
$Comp
L Device:R R25
U 1 1 5DC915C0
P 14350 7250
F 0 "R25" V 14143 7250 50  0000 C CNN
F 1 "1R/0.5W" V 14234 7250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 14280 7250 50  0001 C CNN
F 3 "~" H 14350 7250 50  0001 C CNN
	1    14350 7250
	0    1    1    0   
$EndComp
$Comp
L Device:R R26
U 1 1 5DC9199A
P 14350 7700
F 0 "R26" V 14143 7700 50  0000 C CNN
F 1 "1R/0.5W" V 14234 7700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 14280 7700 50  0001 C CNN
F 3 "~" H 14350 7700 50  0001 C CNN
	1    14350 7700
	0    1    1    0   
$EndComp
Wire Wire Line
	15100 7250 14850 7250
Wire Wire Line
	14850 7250 14850 6850
Wire Wire Line
	14850 6850 14500 6850
Wire Wire Line
	14500 7250 14850 7250
Connection ~ 14850 7250
Wire Wire Line
	14500 7700 14850 7700
Wire Wire Line
	14200 6850 13900 6850
Wire Wire Line
	13900 6850 13900 7250
Wire Wire Line
	13900 7250 13650 7250
Wire Wire Line
	13900 7250 14200 7250
Connection ~ 13900 7250
Wire Wire Line
	14200 7700 13900 7700
Text GLabel 2150 5050 2    50   Input ~ 0
GND_HV
Wire Wire Line
	2150 5050 1800 5050
Wire Wire Line
	1050 5050 1050 4950
Wire Wire Line
	1800 4650 1800 4450
Wire Wire Line
	1800 4450 1050 4450
Wire Wire Line
	1050 4450 1050 4650
Wire Wire Line
	1800 4950 1800 5050
Connection ~ 1800 5050
Wire Wire Line
	1800 5050 1050 5050
Wire Wire Line
	6050 8500 6700 8500
Wire Wire Line
	13900 7700 13900 7250
Wire Wire Line
	14850 7700 14850 7250
Wire Wire Line
	2600 2400 2900 2400
Wire Wire Line
	2600 3500 2900 3500
$Comp
L Device:CP C8
U 1 1 5D4A04F9
P 2900 2950
F 0 "C8" H 3018 2996 50  0000 L CNN
F 1 "680uF/450V" H 3018 2905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D35.0mm_P10.00mm_SnapIn" H 2938 2800 50  0001 C CNN
F 3 "~" H 2900 2950 50  0001 C CNN
	1    2900 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3100 2900 3500
Connection ~ 2900 3500
Wire Wire Line
	2900 3500 3650 3500
Wire Wire Line
	2900 2800 2900 2400
Connection ~ 2900 2400
Wire Wire Line
	2900 2400 3650 2400
Wire Wire Line
	3650 2800 3650 2400
$Comp
L Reference_Voltage:LM4040DBZ-10 U1
U 1 1 602372BD
P 4350 3800
F 0 "U1" V 4396 3712 50  0000 R CNN
F 1 "LM4040DBZ-10" V 4305 3712 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4350 3600 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm4040-n.pdf" H 4350 3800 50  0001 C CIN
	1    4350 3800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 2500 6050 2500
Wire Wire Line
	5500 4600 6050 4600
Connection ~ 6050 2500
Wire Wire Line
	6050 2500 6850 2500
Connection ~ 6050 4600
$Comp
L Device:C C20
U 1 1 602CB214
P 7200 2950
F 0 "C20" H 7315 2996 50  0000 L CNN
F 1 "10nF/50V" H 7315 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7238 2800 50  0001 C CNN
F 3 "~" H 7200 2950 50  0001 C CNN
	1    7200 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 602CC6FF
P 7650 2950
F 0 "R3" H 7720 2996 50  0000 L CNN
F 1 "0R 1/8W" H 7720 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7580 2950 50  0001 C CNN
F 3 "~" H 7650 2950 50  0001 C CNN
	1    7650 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R21
U 1 1 6036D06F
P 13400 3850
F 0 "R21" H 13470 3896 50  0000 L CNN
F 1 "750/0.6W" H 13470 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 13330 3850 50  0001 C CNN
F 3 "~" H 13400 3850 50  0001 C CNN
	1    13400 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R22
U 1 1 6036E649
P 14100 3550
F 0 "R22" H 14170 3596 50  0000 L CNN
F 1 "330R2W" H 14170 3505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 14030 3550 50  0001 C CNN
F 3 "~" H 14100 3550 50  0001 C CNN
	1    14100 3550
	0    1    1    0   
$EndComp
$Comp
L Device:C C35
U 1 1 60370030
P 13400 4250
F 0 "C35" H 13515 4296 50  0000 L CNN
F 1 "470pF/500V" H 13515 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 13438 4100 50  0001 C CNN
F 3 "~" H 13400 4250 50  0001 C CNN
	1    13400 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 60389831
P 7850 4050
F 0 "R5" H 7920 4096 50  0000 L CNN
F 1 "10K 1/8W" H 7920 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7780 4050 50  0001 C CNN
F 3 "~" H 7850 4050 50  0001 C CNN
	1    7850 4050
	0    1    1    0   
$EndComp
$Comp
L hv-power-supply-v1-rescue:IRF510PBF-dk_Transistors-FETs-MOSFETs-Single-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue Q1
U 1 1 603EDCB9
P 9100 3400
F 0 "Q1" H 9208 3453 60  0000 L CNN
F 1 "IRF840" H 9208 3347 60  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9300 3600 60  0001 L CNN
F 3 "http://www.vishay.com/docs/91015/sihf510.pdf" H 9300 3700 60  0001 L CNN
F 4 "IRF510PBF-ND" H 9300 3800 60  0001 L CNN "Digi-Key_PN"
F 5 "IRF510PBF" H 9300 3900 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 9300 4000 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 9300 4100 60  0001 L CNN "Family"
F 8 "http://www.vishay.com/docs/91015/sihf510.pdf" H 9300 4200 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/vishay-siliconix/IRF510PBF/IRF510PBF-ND/811710" H 9300 4300 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 100V 5.6A TO-220AB" H 9300 4400 60  0001 L CNN "Description"
F 11 "Vishay Siliconix" H 9300 4500 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9300 4600 60  0001 L CNN "Status"
	1    9100 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2400 3650 1600
Wire Wire Line
	3650 1600 4350 1600
Connection ~ 3650 2400
Wire Wire Line
	4350 2100 4350 2500
Wire Wire Line
	4350 1800 4350 1600
Connection ~ 4350 2500
Wire Wire Line
	4350 2500 4350 3650
Wire Wire Line
	6650 3600 6200 3600
Wire Wire Line
	6050 2500 6050 3450
Wire Wire Line
	6050 3750 6050 4600
Wire Wire Line
	6850 3800 6850 4600
Wire Wire Line
	6850 2500 6850 3200
Wire Wire Line
	7250 3500 8050 3500
Wire Wire Line
	7500 2950 7350 2950
Wire Wire Line
	7800 2950 8050 2950
Wire Wire Line
	8050 2950 8050 3500
Connection ~ 8050 3500
Wire Wire Line
	8050 3500 8350 3500
Connection ~ 6300 4600
Wire Wire Line
	6050 4600 6300 4600
Wire Wire Line
	6300 4600 6850 4600
NoConn ~ 6300 4000
$Comp
L Diode:BAT54C D9
U 1 1 6039085C
P 6300 4300
F 0 "D9" V 6346 4388 50  0000 L CNN
F 1 "BAT54C" V 6255 4388 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6375 4425 50  0001 L CNN
F 3 "http://www.diodes.com/_files/datasheets/ds11005.pdf" H 6220 4300 50  0001 C CNN
	1    6300 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6500 4300 6500 4050
Wire Wire Line
	6500 3400 6650 3400
Wire Wire Line
	6500 3400 6500 2950
Wire Wire Line
	6500 2950 7050 2950
Connection ~ 6500 3400
$Comp
L Mechanical:Heatsink HS3
U 1 1 5D4EB32D
P 12850 2200
F 0 "HS3" H 12992 2321 50  0000 L CNN
F 1 "Heatsink" H 12992 2230 50  0000 L CNN
F 2 "Heatsinks:Heatsink_Fischer_SK104-STC-STIC_35x13mm_2xDrill2.5mm" H 12862 2200 50  0001 C CNN
F 3 "~" H 12862 2200 50  0001 C CNN
	1    12850 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 605CAE8D
P 9100 4350
F 0 "R12" H 9170 4396 50  0000 L CNN
F 1 "2.7k 1/8W" H 9170 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 9030 4350 50  0001 C CNN
F 3 "~" H 9100 4350 50  0001 C CNN
	1    9100 4350
	-1   0    0    1   
$EndComp
$Comp
L Device:C C27
U 1 1 605CBEBE
P 9350 4350
F 0 "C27" H 9465 4396 50  0000 L CNN
F 1 "0pF/50V" H 9465 4305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 9388 4200 50  0001 C CNN
F 3 "~" H 9350 4350 50  0001 C CNN
	1    9350 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 2500 9800 2950
Wire Wire Line
	9800 3250 9800 3550
$Comp
L Device:C C31
U 1 1 6064FFD8
P 10450 3100
F 0 "C31" H 10565 3146 50  0000 L CNN
F 1 "1nF/50V" H 10565 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 10488 2950 50  0001 C CNN
F 3 "~" H 10450 3100 50  0001 C CNN
	1    10450 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 2950 10450 2500
Connection ~ 10450 2500
Wire Wire Line
	10450 2500 9800 2500
Wire Wire Line
	10450 3250 10450 3550
Connection ~ 10450 3550
Wire Wire Line
	10450 3550 9800 3550
Wire Wire Line
	10450 3550 10950 3550
Connection ~ 11400 3550
Wire Wire Line
	11400 3100 11400 3550
Wire Wire Line
	11400 2700 11400 2500
Wire Wire Line
	11400 2500 10450 2500
Wire Wire Line
	12100 2900 11850 2900
Wire Wire Line
	12400 2900 12650 2900
Wire Wire Line
	12650 3050 12650 2900
Wire Wire Line
	9800 2500 9100 2500
Wire Wire Line
	9100 2500 9100 2250
Connection ~ 9800 2500
Wire Wire Line
	9100 2500 9100 3200
Connection ~ 9100 2500
Wire Wire Line
	9100 1950 9100 1600
Wire Wire Line
	9100 1600 4350 1600
Connection ~ 4350 1600
Wire Wire Line
	12650 2200 12650 1600
Wire Wire Line
	12650 1600 9100 1600
Connection ~ 9100 1600
Wire Wire Line
	8000 4050 10950 4050
Wire Wire Line
	12650 4050 12650 4000
Wire Wire Line
	12650 4050 12650 4200
Connection ~ 12650 4050
Wire Wire Line
	12650 3700 12650 3550
Wire Wire Line
	12650 3550 12650 3350
Connection ~ 12650 3550
Wire Wire Line
	11850 3700 11850 2900
Connection ~ 11850 2900
Wire Wire Line
	11850 2900 11700 2900
Wire Wire Line
	11850 4000 11850 4600
Wire Wire Line
	7700 4050 6500 4050
Connection ~ 6500 4050
Wire Wire Line
	6500 4050 6500 3400
Wire Wire Line
	6850 4600 9100 4600
Connection ~ 6850 4600
Wire Wire Line
	9100 4200 9100 4100
Wire Wire Line
	9350 4200 9350 4100
Wire Wire Line
	9350 4100 9100 4100
Connection ~ 9100 4100
Wire Wire Line
	9100 4100 9100 3600
Wire Wire Line
	9350 4500 9350 4600
Wire Wire Line
	9350 4600 11850 4600
Connection ~ 9350 4600
Wire Wire Line
	9100 4500 9100 4600
Connection ~ 9100 4600
Wire Wire Line
	9100 4600 9350 4600
Wire Wire Line
	4950 2500 4950 3350
Wire Wire Line
	5500 2500 5500 3150
Wire Wire Line
	5500 3450 5500 4600
Wire Wire Line
	4950 3650 4950 4600
Wire Wire Line
	13950 3550 13400 3550
Wire Wire Line
	13400 3700 13400 3550
Connection ~ 13400 3550
Wire Wire Line
	13400 3550 12650 3550
Wire Wire Line
	13400 4100 13400 4000
Wire Wire Line
	13400 4400 13400 4600
Wire Wire Line
	13400 4600 12650 4600
Connection ~ 12650 4600
Wire Wire Line
	14250 3550 14450 3550
$Comp
L Relay:G2RL-2-DC5 RL1
U 1 1 609FA731
P 11550 9050
F 0 "RL1" H 10921 9004 50  0000 R CNN
F 1 "G2RL-2-DC5" H 10921 9095 50  0000 R CNN
F 2 "Relay_THT:Relay_DPDT_Omron_G2RL" H 12200 9000 50  0001 L CNN
F 3 "https://omronfs.omron.com/en_US/ecb/products/pdf/en-g2rl.pdf" H 11550 9050 50  0001 C CNN
	1    11550 9050
	1    0    0    -1  
$EndComp
$Comp
L Diode:BZX84Cxx D15
U 1 1 60A33BA7
P 9800 3100
F 0 "D15" V 9754 3180 50  0000 L CNN
F 1 "BZX84C15" V 9845 3180 50  0000 L CNN
F 2 "Diode_SMD:D_SOT-23_ANK" H 9800 2925 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzx84c2v4.pdf" H 9800 3100 50  0001 C CNN
	1    9800 3100
	0    1    1    0   
$EndComp
$Comp
L Device:D D1
U 1 1 60ACEB89
P 2150 8900
F 0 "D1" H 2150 9117 50  0000 C CNN
F 1 "BYV98-200" H 2150 9026 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2150 8900 50  0001 C CNN
F 3 "~" H 2150 8900 50  0001 C CNN
	1    2150 8900
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 60AD0798
P 1400 8900
F 0 "C2" H 1515 8946 50  0000 L CNN
F 1 "10nF/50V" H 1515 8855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1438 8750 50  0001 C CNN
F 3 "~" H 1400 8900 50  0001 C CNN
	1    1400 8900
	1    0    0    -1  
$EndComp
$Comp
L Device:D D2
U 1 1 60B34A9A
P 2150 9300
F 0 "D2" H 2150 9517 50  0000 C CNN
F 1 "BYV98-200" H 2150 9426 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2150 9300 50  0001 C CNN
F 3 "~" H 2150 9300 50  0001 C CNN
	1    2150 9300
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C9
U 1 1 60B35693
P 3000 8900
F 0 "C9" H 3115 8946 50  0000 L CNN
F 1 "10nF/50V" H 3115 8855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3038 8750 50  0001 C CNN
F 3 "~" H 3000 8900 50  0001 C CNN
	1    3000 8900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 60B35EBD
P 1400 9300
F 0 "C3" H 1515 9346 50  0000 L CNN
F 1 "10nF/50V" H 1515 9255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1438 9150 50  0001 C CNN
F 3 "~" H 1400 9300 50  0001 C CNN
	1    1400 9300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 60B3625F
P 3000 9300
F 0 "C10" H 3115 9346 50  0000 L CNN
F 1 "10nF/50V" H 3115 9255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3038 9150 50  0001 C CNN
F 3 "~" H 3000 9300 50  0001 C CNN
	1    3000 9300
	1    0    0    -1  
$EndComp
$Comp
L Device:D D7
U 1 1 60B364B8
P 2650 8900
F 0 "D7" H 2650 9117 50  0000 C CNN
F 1 "BYV98-200" H 2650 9026 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2650 8900 50  0001 C CNN
F 3 "~" H 2650 8900 50  0001 C CNN
	1    2650 8900
	0    -1   -1   0   
$EndComp
$Comp
L Device:D D8
U 1 1 60B37B18
P 2650 9300
F 0 "D8" H 2650 9517 50  0000 C CNN
F 1 "BYV98-200" H 2650 9426 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2650 9300 50  0001 C CNN
F 3 "~" H 2650 9300 50  0001 C CNN
	1    2650 9300
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 9150 2150 9100
Wire Wire Line
	2650 9150 2650 9100
Wire Wire Line
	2650 9450 2650 9550
Wire Wire Line
	2650 9550 2400 9550
Wire Wire Line
	2150 9550 2150 9450
Wire Wire Line
	2650 8650 2400 8650
Wire Wire Line
	2150 8650 2150 8750
Wire Wire Line
	3000 9050 2650 9050
Connection ~ 2650 9050
Wire Wire Line
	2650 8650 2650 8750
Wire Wire Line
	3000 8750 2650 8750
Connection ~ 2650 8750
Wire Wire Line
	3000 9150 2650 9150
Connection ~ 2650 9150
Wire Wire Line
	3000 9450 2650 9450
Connection ~ 2650 9450
Wire Wire Line
	1400 8750 2150 8750
Connection ~ 2150 8750
Wire Wire Line
	1400 9050 2150 9050
Connection ~ 2150 9050
Wire Wire Line
	1400 9150 2150 9150
Connection ~ 2150 9150
Wire Wire Line
	1400 9450 2150 9450
Connection ~ 2150 9450
Wire Wire Line
	1050 8550 2400 8550
Wire Wire Line
	2400 8550 2400 8650
Connection ~ 2400 8650
Wire Wire Line
	2400 8650 2150 8650
Wire Wire Line
	1050 9650 2400 9650
Wire Wire Line
	2400 9650 2400 9550
Connection ~ 2400 9550
Wire Wire Line
	2400 9550 2150 9550
Connection ~ 11950 9550
$Comp
L Connector_Generic:Conn_01x01 J10
U 1 1 60E61BC6
P 13500 9550
F 0 "J10" H 13580 9592 50  0000 L CNN
F 1 "HV" H 13580 9501 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 13500 9550 50  0001 C CNN
F 3 "~" H 13500 9550 50  0001 C CNN
	1    13500 9550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J11
U 1 1 60E62DCA
P 13500 9750
F 0 "J11" H 13580 9792 50  0000 L CNN
F 1 "GND_HV" H 13580 9701 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 13500 9750 50  0001 C CNN
F 3 "~" H 13500 9750 50  0001 C CNN
	1    13500 9750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J12
U 1 1 60E9D7A5
P 14900 8500
F 0 "J12" H 14980 8542 50  0000 L CNN
F 1 "LED" H 14980 8451 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 14900 8500 50  0001 C CNN
F 3 "~" H 14900 8500 50  0001 C CNN
	1    14900 8500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J13
U 1 1 60ED5A55
P 14900 8700
F 0 "J13" H 14980 8742 50  0000 L CNN
F 1 "GND_LED" H 14980 8651 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 14900 8700 50  0001 C CNN
F 3 "~" H 14900 8700 50  0001 C CNN
	1    14900 8700
	1    0    0    -1  
$EndComp
Wire Wire Line
	14700 8700 14000 8700
Wire Wire Line
	14000 8500 14250 8500
Wire Wire Line
	14550 8500 14700 8500
Text GLabel 14000 9200 0    50   Input ~ 0
GND_LV
Text GLabel 14000 9000 0    50   Input ~ 0
+5VDC
$Comp
L Connector_Generic:Conn_01x01 J14
U 1 1 60F2C2B5
P 14900 9000
F 0 "J14" H 14980 9042 50  0000 L CNN
F 1 "+5V" H 14980 8951 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 14900 9000 50  0001 C CNN
F 3 "~" H 14900 9000 50  0001 C CNN
	1    14900 9000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J15
U 1 1 60F2C2BF
P 14900 9200
F 0 "J15" H 14980 9242 50  0000 L CNN
F 1 "GND_5V" H 14980 9151 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 14900 9200 50  0001 C CNN
F 3 "~" H 14900 9200 50  0001 C CNN
	1    14900 9200
	1    0    0    -1  
$EndComp
Wire Wire Line
	14700 9200 14000 9200
Wire Wire Line
	14000 9000 14700 9000
$Comp
L Diode:1N4148W D16
U 1 1 60FBAA5D
P 10650 9050
F 0 "D16" V 10604 9130 50  0000 L CNN
F 1 "1N4148W" V 10695 9130 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 10650 8875 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 10650 9050 50  0001 C CNN
	1    10650 9050
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148W D10
U 1 1 60FF3090
P 7300 9800
F 0 "D10" V 7254 9880 50  0000 L CNN
F 1 "1N4148W" V 7345 9880 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 7300 9625 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 7300 9800 50  0001 C CNN
	1    7300 9800
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D11
U 1 1 610606DC
P 8250 4900
F 0 "D11" H 8250 5117 50  0000 C CNN
F 1 "1N4007" H 8250 5026 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 8250 4725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8250 4900 50  0001 C CNN
	1    8250 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4900 8650 4900
Wire Wire Line
	8650 4900 8650 5250
Connection ~ 8650 5250
Wire Wire Line
	8650 5250 8550 5250
Wire Wire Line
	7350 5250 7800 5250
Wire Wire Line
	8100 4900 7800 4900
Wire Wire Line
	7800 4900 7800 5250
Connection ~ 7800 5250
Wire Wire Line
	7800 5250 7950 5250
$Comp
L Diode:1N4007 D12
U 1 1 6110B946
P 8250 6500
F 0 "D12" H 8250 6717 50  0000 C CNN
F 1 "1N4007" H 8250 6626 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 8250 6325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8250 6500 50  0001 C CNN
	1    8250 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 6500 8650 6500
Wire Wire Line
	8650 6500 8650 6850
Connection ~ 8650 6850
Wire Wire Line
	8100 6500 7800 6500
Wire Wire Line
	7800 6500 7800 6850
Connection ~ 7800 6850
$Comp
L Device:CP C12
U 1 1 6117EC9C
P 3800 9500
F 0 "C12" H 3918 9546 50  0000 L CNN
F 1 "22000uF/25V" H 3918 9455 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D30.0mm_P10.00mm_SnapIn" H 3838 9350 50  0001 C CNN
F 3 "~" H 3800 9500 50  0001 C CNN
	1    3800 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 9100 3550 9100
Wire Wire Line
	3550 9100 3550 8500
Wire Wire Line
	3550 8500 3800 8500
Connection ~ 2650 9100
Wire Wire Line
	2650 9100 2650 9050
Wire Wire Line
	2150 9100 1200 9100
Wire Wire Line
	1200 9100 1200 10500
Wire Wire Line
	1200 10500 3800 10500
Connection ~ 2150 9100
Wire Wire Line
	2150 9100 2150 9050
Wire Wire Line
	3800 9350 3800 8500
Connection ~ 3800 8500
Wire Wire Line
	3800 8500 5000 8500
Wire Wire Line
	3800 9650 3800 10500
Connection ~ 3800 10500
Wire Wire Line
	3800 10500 5000 10500
Wire Wire Line
	5000 9350 5000 8500
Connection ~ 5000 8500
Wire Wire Line
	5000 8500 5300 8500
Wire Wire Line
	5000 9650 5000 10500
Connection ~ 5000 10500
Wire Wire Line
	5000 10500 5600 10500
Text GLabel 6150 6200 0    50   Input ~ 0
GND_LV
Text GLabel 4850 10700 0    50   Input ~ 0
GND_LV
Wire Wire Line
	4850 10700 5000 10700
Wire Wire Line
	5000 10700 5000 10500
$Comp
L Device:CP C17
U 1 1 61254958
P 6700 5750
F 0 "C17" H 6818 5796 50  0000 L CNN
F 1 "10uF/25V" H 6818 5705 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 6738 5600 50  0001 C CNN
F 3 "~" H 6700 5750 50  0001 C CNN
	1    6700 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 7500 7350 7750
Wire Wire Line
	7350 7200 7350 6850
Wire Wire Line
	6150 6200 6700 6200
Connection ~ 7350 6200
$Comp
L Device:CP C18
U 1 1 612EDC08
P 6700 7350
F 0 "C18" H 6818 7396 50  0000 L CNN
F 1 "10uF/25V" H 6818 7305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 6738 7200 50  0001 C CNN
F 3 "~" H 6700 7350 50  0001 C CNN
	1    6700 7350
	1    0    0    -1  
$EndComp
Connection ~ 7350 6850
Wire Wire Line
	7350 6850 7800 6850
Connection ~ 7350 7750
Wire Wire Line
	7350 7750 8250 7750
Wire Wire Line
	6150 7750 6700 7750
Wire Wire Line
	3800 5250 3800 6850
Wire Wire Line
	3800 5250 6700 5250
Wire Wire Line
	3800 6850 6700 6850
Connection ~ 3800 6850
Wire Wire Line
	3800 6850 3800 8500
$Comp
L Device:CP C34
U 1 1 61368459
P 11050 7350
F 0 "C34" H 11168 7396 50  0000 L CNN
F 1 "1uF/25V" H 11168 7305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 11088 7200 50  0001 C CNN
F 3 "~" H 11050 7350 50  0001 C CNN
	1    11050 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11050 7200 11050 6850
Wire Wire Line
	11050 7500 11050 7750
Wire Wire Line
	10350 7200 10350 6850
Wire Wire Line
	10350 7500 10350 7750
$Comp
L Device:CP C16
U 1 1 613FFBB9
P 6050 9500
F 0 "C16" H 6168 9546 50  0000 L CNN
F 1 "10uF/25V" H 6168 9455 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 6088 9350 50  0001 C CNN
F 3 "~" H 6050 9500 50  0001 C CNN
	1    6050 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 8500 6700 9350
Wire Wire Line
	6050 8500 6050 9350
Wire Wire Line
	6050 9650 6050 10500
Connection ~ 6050 10500
Wire Wire Line
	6050 10500 6700 10500
Wire Wire Line
	6700 9650 6700 10500
Connection ~ 6700 10500
Wire Wire Line
	6700 10500 7300 10500
Wire Wire Line
	5600 8800 5600 10500
Connection ~ 5600 10500
Wire Wire Line
	5600 10500 6050 10500
$Comp
L Regulator_Linear:LM7805_TO220 U2
U 1 1 6149AF46
P 5600 8500
F 0 "U2" H 5600 8742 50  0000 C CNN
F 1 "LM7805_TO220" H 5600 8651 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5600 8725 50  0001 C CIN
F 3 "https://www.onsemi.cn/PowerSolutions/document/MC7800-D.PDF" H 5600 8450 50  0001 C CNN
	1    5600 8500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 614FB8AA
P 11350 5250
F 0 "J6" H 11430 5292 50  0000 L CNN
F 1 "LV1" H 11430 5201 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 11350 5250 50  0001 C CNN
F 3 "~" H 11350 5250 50  0001 C CNN
	1    11350 5250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 614FBF1E
P 11350 6850
F 0 "J8" H 11430 6892 50  0000 L CNN
F 1 "LV2" H 11430 6801 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 11350 6850 50  0001 C CNN
F 3 "~" H 11350 6850 50  0001 C CNN
	1    11350 6850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 614FC706
P 11350 6200
F 0 "J7" H 11430 6242 50  0000 L CNN
F 1 "GND_LV1" H 11430 6151 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 11350 6200 50  0001 C CNN
F 3 "~" H 11350 6200 50  0001 C CNN
	1    11350 6200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J9
U 1 1 614FCBF5
P 11350 7750
F 0 "J9" H 11430 7792 50  0000 L CNN
F 1 "GND_LV2" H 11430 7701 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 11350 7750 50  0001 C CNN
F 3 "~" H 11350 7750 50  0001 C CNN
	1    11350 7750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 614FD5E0
P 850 8550
F 0 "J4" H 768 8767 50  0000 C CNN
F 1 "AC-LV" H 768 8676 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 850 8550 50  0001 C CNN
F 3 "~" H 850 8550 50  0001 C CNN
	1    850  8550
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 61576AE8
P 850 9650
F 0 "J5" H 768 9867 50  0000 C CNN
F 1 "AC-LV" H 768 9776 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 850 9650 50  0001 C CNN
F 3 "~" H 850 9650 50  0001 C CNN
	1    850  9650
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 6159609F
P 850 2650
F 0 "J1" H 768 2867 50  0000 C CNN
F 1 "AC-HV" H 768 2776 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 850 2650 50  0001 C CNN
F 3 "~" H 850 2650 50  0001 C CNN
	1    850  2650
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 615964A4
P 850 3050
F 0 "J2" H 768 3267 50  0000 C CNN
F 1 "AC-HV" H 768 3176 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 850 3050 50  0001 C CNN
F 3 "~" H 850 3050 50  0001 C CNN
	1    850  3050
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 615965D0
P 850 3400
F 0 "J3" H 768 3617 50  0000 C CNN
F 1 "EARTH" H 768 3526 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 850 3400 50  0001 C CNN
F 3 "~" H 850 3400 50  0001 C CNN
	1    850  3400
	-1   0    0    -1  
$EndComp
Connection ~ 1050 4450
Wire Wire Line
	1050 3400 1050 4450
Wire Wire Line
	1400 1600 1400 2650
Wire Wire Line
	1050 2650 1400 2650
Connection ~ 1400 2650
Wire Wire Line
	1400 2650 1400 3500
Wire Wire Line
	1650 2400 1650 3050
Wire Wire Line
	1050 3050 1650 3050
Connection ~ 1650 3050
Wire Wire Line
	1650 3050 1650 4300
Wire Wire Line
	6700 5600 6700 5250
Connection ~ 6700 5250
Wire Wire Line
	6700 5250 7350 5250
Wire Wire Line
	6700 5900 6700 6200
Connection ~ 6700 6200
Wire Wire Line
	6700 6200 7350 6200
Wire Wire Line
	6700 7200 6700 6850
Connection ~ 6700 6850
Wire Wire Line
	6700 6850 7350 6850
Wire Wire Line
	6700 7500 6700 7750
Connection ~ 6700 7750
Wire Wire Line
	6700 7750 7350 7750
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 601F7DA3
P 12650 2750
F 0 "FB1" H 12750 2796 50  0000 L CNN
F 1 "600R@100MHz" H 12750 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 12580 2750 50  0001 C CNN
F 3 "~" H 12650 2750 50  0001 C CNN
	1    12650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	12650 2650 12650 2600
Wire Wire Line
	12650 2850 12650 2900
Connection ~ 12650 2900
$Comp
L Device:R R16
U 1 1 6021D1DE
P 11950 2500
F 0 "R16" H 12020 2546 50  0000 L CNN
F 1 "100R 1/8W" H 12020 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 11880 2500 50  0001 C CNN
F 3 "~" H 11950 2500 50  0001 C CNN
	1    11950 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	12350 2500 12100 2500
Wire Wire Line
	11800 2500 11400 2500
Connection ~ 11400 2500
$Comp
L Device:C C32
U 1 1 6029DB1D
P 10950 3800
F 0 "C32" H 11065 3846 50  0000 L CNN
F 1 "10pF/500V" H 11065 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 10988 3650 50  0001 C CNN
F 3 "~" H 10950 3800 50  0001 C CNN
	1    10950 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10950 3650 10950 3550
Connection ~ 10950 3550
Wire Wire Line
	10950 3550 11400 3550
Wire Wire Line
	10950 3950 10950 4050
Connection ~ 10950 4050
Wire Wire Line
	10950 4050 12650 4050
Wire Wire Line
	11950 9550 13300 9550
$Comp
L Device:R R23
U 1 1 6059050F
P 14350 6450
F 0 "R23" V 14143 6450 50  0000 C CNN
F 1 "1R/0.5W" V 14234 6450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 14280 6450 50  0001 C CNN
F 3 "~" H 14350 6450 50  0001 C CNN
	1    14350 6450
	0    1    1    0   
$EndComp
Wire Wire Line
	14850 6850 14850 6450
Wire Wire Line
	14850 6450 14500 6450
Connection ~ 14850 6850
Wire Wire Line
	14200 6450 13900 6450
Wire Wire Line
	13900 6450 13900 6850
Connection ~ 13900 6850
Wire Wire Line
	8250 6200 9050 6200
$Comp
L Device:CP C25
U 1 1 6074011C
P 9050 5950
F 0 "C25" H 9168 5996 50  0000 L CNN
F 1 "10uF/25V" H 9168 5905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 9088 5800 50  0001 C CNN
F 3 "~" H 9050 5950 50  0001 C CNN
	1    9050 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 5750 9050 5750
Wire Wire Line
	9050 5750 9050 5800
Wire Wire Line
	9050 6100 9050 6200
Connection ~ 9050 6200
$Comp
L Diode:1N4148W D13
U 1 1 6080505C
P 9650 5500
F 0 "D13" V 9604 5580 50  0000 L CNN
F 1 "1N4148W" V 9695 5580 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 9650 5325 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 9650 5500 50  0001 C CNN
	1    9650 5500
	0    1    1    0   
$EndComp
Connection ~ 10350 5250
Connection ~ 10350 6200
Connection ~ 11050 5250
Wire Wire Line
	11050 5250 11150 5250
Connection ~ 11050 6200
Wire Wire Line
	11050 6200 11150 6200
Wire Wire Line
	10350 5250 11050 5250
Wire Wire Line
	10350 6200 11050 6200
Wire Wire Line
	9050 6200 10350 6200
Connection ~ 10350 6850
Connection ~ 10350 7750
Connection ~ 11050 6850
Wire Wire Line
	11050 6850 11150 6850
Connection ~ 11050 7750
Wire Wire Line
	11050 7750 11150 7750
Wire Wire Line
	10350 6850 11050 6850
Wire Wire Line
	10350 7750 11050 7750
Wire Wire Line
	8250 7750 9050 7750
Wire Wire Line
	8650 5250 9050 5250
Wire Wire Line
	9050 5750 9050 5650
Connection ~ 9050 5750
Wire Wire Line
	9050 5350 9050 5250
Connection ~ 9050 5250
Wire Wire Line
	9050 5250 9650 5250
Wire Wire Line
	9650 5350 9650 5250
Connection ~ 9650 5250
Wire Wire Line
	9650 5250 10350 5250
Wire Wire Line
	9650 5650 9650 5750
Wire Wire Line
	9650 5750 9050 5750
Wire Wire Line
	8650 6850 9050 6850
$Comp
L Diode:1N4148W D14
U 1 1 60A06169
P 9650 7100
F 0 "D14" V 9604 7180 50  0000 L CNN
F 1 "1N4148W" V 9695 7180 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 9650 6925 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 9650 7100 50  0001 C CNN
	1    9650 7100
	0    1    1    0   
$EndComp
$Comp
L Device:CP C26
U 1 1 60A0917C
P 9050 7550
F 0 "C26" H 9168 7596 50  0000 L CNN
F 1 "10uF/25V" H 9168 7505 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 9088 7400 50  0001 C CNN
F 3 "~" H 9050 7550 50  0001 C CNN
	1    9050 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 7300 9050 7400
Wire Wire Line
	8250 7350 8250 7300
Wire Wire Line
	8250 7300 9050 7300
Wire Wire Line
	8250 7300 8250 7150
Connection ~ 8250 7300
Wire Wire Line
	9050 7300 9050 7250
Connection ~ 9050 7300
Wire Wire Line
	9050 6950 9050 6850
Connection ~ 9050 6850
Wire Wire Line
	9050 6850 9650 6850
Wire Wire Line
	9650 7250 9650 7300
Wire Wire Line
	9650 7300 9050 7300
Wire Wire Line
	9650 6950 9650 6850
Connection ~ 9650 6850
Wire Wire Line
	9650 6850 10350 6850
Wire Wire Line
	9050 7700 9050 7750
Connection ~ 9050 7750
Wire Wire Line
	9050 7750 10350 7750
$EndSCHEMATC
