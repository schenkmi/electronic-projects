EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
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
L hv-power-supply-v1-rescue:BYV26C-PSU6SN7-hv-power-supply-v1-rescue D1
U 1 1 5D44FFF5
P 2200 1600
F 0 "D1" H 2200 1816 50  0000 C CNN
F 1 "BYG20J" H 2200 1725 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 2200 1425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2200 1600 50  0001 C CNN
	1    2200 1600
	-1   0    0    1   
$EndComp
$Comp
L hv-power-supply-v1-rescue:BYV26C-PSU6SN7-hv-power-supply-v1-rescue D2
U 1 1 5D450671
P 2200 3500
F 0 "D2" H 2200 3716 50  0000 C CNN
F 1 "BYG20J" H 2200 3625 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 2200 3325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2200 3500 50  0001 C CNN
	1    2200 3500
	1    0    0    -1  
$EndComp
$Comp
L hv-power-supply-v1-rescue:BYV26C-PSU6SN7-hv-power-supply-v1-rescue D3
U 1 1 5D4509EB
P 2200 4300
F 0 "D3" H 2200 4516 50  0000 C CNN
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
L Diode_Bridge:MB6S D5
U 1 1 5D45A532
P 2100 9100
F 0 "D5" H 2444 9146 50  0000 L CNN
F 1 "MB6S" H 2444 9055 50  0000 L CNN
F 2 "Diodes_SMD:Diode_Bridge_TO-269AA" H 2250 9225 50  0001 L CNN
F 3 "http://www.vishay.com/docs/88573/dfs.pdf" H 2100 9100 50  0001 C CNN
	1    2100 9100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5D45B2C2
P 2800 9050
F 0 "C1" H 2918 9096 50  0000 L CNN
F 1 "470uF/16V" H 2918 9005 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 2838 8900 50  0001 C CNN
F 3 "~" H 2800 9050 50  0001 C CNN
	1    2800 9050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5D45BEFD
P 3500 9050
F 0 "C3" H 3615 9096 50  0000 L CNN
F 1 "100nF/50V" H 3615 9005 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 3538 8900 50  0001 C CNN
F 3 "~" H 3500 9050 50  0001 C CNN
	1    3500 9050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 8800 1450 8800
Wire Wire Line
	1450 8800 1450 9050
Wire Wire Line
	2100 9400 2100 9500
Wire Wire Line
	2100 9500 1600 9500
Wire Wire Line
	1450 9500 1450 9150
Wire Wire Line
	1800 9100 1800 9600
Wire Wire Line
	1800 9600 2800 9600
Wire Wire Line
	2800 9600 2800 9200
Wire Wire Line
	2400 9100 2400 8500
Wire Wire Line
	2400 8500 2800 8500
Wire Wire Line
	2800 8500 2800 8900
Wire Wire Line
	3500 8500 3500 8900
Wire Wire Line
	3500 8500 3950 8500
Connection ~ 3500 8500
Wire Wire Line
	3500 9200 3500 9600
Wire Wire Line
	4250 8800 4250 9600
Wire Wire Line
	4250 9600 3500 9600
Connection ~ 3500 9600
$Comp
L Device:C C4
U 1 1 5D4699C7
P 5350 9050
F 0 "C4" H 5465 9096 50  0000 L CNN
F 1 "100nF/50V" H 5465 9005 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5388 8900 50  0001 C CNN
F 3 "~" H 5350 9050 50  0001 C CNN
	1    5350 9050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5D46B613
P 4700 9050
F 0 "C2" H 4818 9096 50  0000 L CNN
F 1 "15uF/25V" H 4818 9005 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-T_EIA-3528-12_Hand" H 4738 8900 50  0001 C CNN
F 3 "~" H 4700 9050 50  0001 C CNN
	1    4700 9050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 8500 4700 8500
Wire Wire Line
	4700 8500 4700 8900
Wire Wire Line
	5350 8900 5350 8500
Connection ~ 4700 8500
Wire Wire Line
	4700 9200 4700 9600
Wire Wire Line
	4700 9600 4250 9600
Connection ~ 4250 9600
Wire Wire Line
	5350 9200 5350 9600
Wire Wire Line
	5350 9600 4700 9600
Connection ~ 4700 9600
$Comp
L hv-power-supply-v1-rescue:TLC555CDR-dk_Clock-Timing-Programmable-Timers-and-Oscillators-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue U2
U 1 1 5D470D45
P 7900 9050
F 0 "U2" H 7900 9603 60  0000 C CNN
F 1 "TLC555CDR" H 7900 9497 60  0000 C CNN
F 2 "digikey-footprints:SOIC-8_W3.9mm" H 8100 9250 60  0001 L CNN
F 3 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Ftlc555" H 8100 9350 60  0001 L CNN
F 4 "296-1336-1-ND" H 8100 9450 60  0001 L CNN "Digi-Key_PN"
F 5 "TLC555CDR" H 8100 9550 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 8100 9650 60  0001 L CNN "Category"
F 7 "Clock/Timing - Programmable Timers and Oscillators" H 8100 9750 60  0001 L CNN "Family"
F 8 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Ftlc555" H 8100 9850 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/TLC555CDR/296-1336-1-ND/404959" H 8100 9950 60  0001 L CNN "DK_Detail_Page"
F 10 "IC OSC SGL TIMER 2.1MHZ 8-SOIC" H 8100 10050 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 8100 10150 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8100 10250 60  0001 L CNN "Status"
	1    7900 9050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D471DEA
P 6450 9500
F 0 "R1" H 6520 9546 50  0000 L CNN
F 1 "1Meg 1/8W" H 6520 9455 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6380 9500 50  0001 C CNN
F 3 "~" H 6450 9500 50  0001 C CNN
	1    6450 9500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D47247E
P 8850 9750
F 0 "R2" H 8920 9796 50  0000 L CNN
F 1 "2.49k 1/8W" H 8920 9705 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8780 9750 50  0001 C CNN
F 3 "~" H 8850 9750 50  0001 C CNN
	1    8850 9750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5D473526
P 9200 10100
F 0 "R3" H 9270 10146 50  0000 L CNN
F 1 "2.49k 1/8W" H 9270 10055 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9130 10100 50  0001 C CNN
F 3 "~" H 9200 10100 50  0001 C CNN
	1    9200 10100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148WT D6
U 1 1 5D47396F
P 5950 9800
F 0 "D6" H 5950 10017 50  0000 C CNN
F 1 "1N4148WT" H 5950 9926 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-523" H 5950 9625 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30396.pdf" H 5950 9800 50  0001 C CNN
	1    5950 9800
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148WT D7
U 1 1 5D473E91
P 9300 9050
F 0 "D7" H 9300 9267 50  0000 C CNN
F 1 "1N4148WT" H 9300 9176 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-523" H 9300 8875 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30396.pdf" H 9300 9050 50  0001 C CNN
	1    9300 9050
	0    1    1    0   
$EndComp
$Comp
L hv-power-supply-v1-rescue:MMBT3904-TP-dk_Transistors-Bipolar-BJT-Single-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue Q1
U 1 1 5D4746D0
P 9700 9750
F 0 "Q1" H 9888 9803 60  0000 L CNN
F 1 "MMBT3904-TP" H 9888 9697 60  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9900 9950 60  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMBT3904(SOT-23).pdf" H 9900 10050 60  0001 L CNN
F 4 "MMBT3904TPMSCT-ND" H 9900 10150 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT3904-TP" H 9900 10250 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 9900 10350 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 9900 10450 60  0001 L CNN "Family"
F 8 "https://www.mccsemi.com/pdf/Products/MMBT3904(SOT-23).pdf" H 9900 10550 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/micro-commercial-co/MMBT3904-TP/MMBT3904TPMSCT-ND/717395" H 9900 10650 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.2A SOT23" H 9900 10750 60  0001 L CNN "Description"
F 11 "Micro Commercial Co" H 9900 10850 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9900 10950 60  0001 L CNN "Status"
	1    9700 9750
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:MC78M05_TO252 U1
U 1 1 5D47856C
P 4250 8500
F 0 "U1" H 4250 8742 50  0000 C CNN
F 1 "MC78M05_TO252" H 4250 8651 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-252-2" H 4250 8725 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM78M05.pdf" H 4250 8450 50  0001 C CNN
	1    4250 8500
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 5D480494
P 6450 8800
F 0 "C5" H 6568 8846 50  0000 L CNN
F 1 "15uF/25V" H 6568 8755 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-T_EIA-3528-12_Hand" H 6488 8650 50  0001 C CNN
F 3 "~" H 6450 8800 50  0001 C CNN
	1    6450 8800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5D481DFE
P 7100 9500
F 0 "C6" H 7215 9546 50  0000 L CNN
F 1 "100nF/50V" H 7215 9455 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 7138 9350 50  0001 C CNN
F 3 "~" H 7100 9500 50  0001 C CNN
	1    7100 9500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5D4821E7
P 8600 8750
F 0 "C7" H 8715 8796 50  0000 L CNN
F 1 "100nF/50V" H 8715 8705 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 8638 8600 50  0001 C CNN
F 3 "~" H 8600 8750 50  0001 C CNN
	1    8600 8750
	1    0    0    -1  
$EndComp
Text GLabel 2950 9850 0    50   Input ~ 0
GND_LV
Wire Wire Line
	3500 9600 3500 9850
Wire Wire Line
	3500 9850 2950 9850
Wire Wire Line
	7900 10500 7900 9500
Wire Wire Line
	7900 10500 7100 10500
Wire Wire Line
	7100 10500 7100 9650
Connection ~ 7900 10500
Wire Wire Line
	7100 10500 6450 10500
Wire Wire Line
	6450 10500 6450 9650
Connection ~ 7100 10500
Wire Wire Line
	6450 10500 5950 10500
Wire Wire Line
	5950 10500 5950 9950
Connection ~ 6450 10500
$Comp
L hv-power-supply-v1-rescue:22-23-2021-dk_Rectangular-Connectors-Headers-Male-Pins-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue J2
U 1 1 5D48B827
P 14650 6350
F 0 "J2" V 14425 6358 50  0000 C CNN
F 1 "22-23-2021" V 14516 6358 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 14850 6550 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 14850 6650 60  0001 L CNN
F 4 "WM4200-ND" H 14850 6750 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 14850 6850 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 14850 6950 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 14850 7050 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 14850 7150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/molex/22-23-2021/WM4200-ND/26667" H 14850 7250 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 14850 7350 60  0001 L CNN "Description"
F 11 "Molex" H 14850 7450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 14850 7550 60  0001 L CNN "Status"
	1    14650 6350
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 9350 6450 9150
Wire Wire Line
	5950 9150 6450 9150
Connection ~ 6450 9150
Wire Wire Line
	6450 9150 6450 8950
Wire Wire Line
	7400 9150 6450 9150
Wire Wire Line
	7400 9250 7100 9250
Wire Wire Line
	7100 9250 7100 9350
Wire Wire Line
	7400 9050 7250 9050
Wire Wire Line
	7250 9050 7250 8950
Wire Wire Line
	7250 8500 6450 8500
Connection ~ 5350 8500
Wire Wire Line
	7400 8950 7250 8950
Connection ~ 7250 8950
Wire Wire Line
	7250 8950 7250 8500
Wire Wire Line
	6450 8650 6450 8500
Connection ~ 6450 8500
Wire Wire Line
	6450 8500 5350 8500
Wire Wire Line
	5950 9150 5950 9650
Wire Wire Line
	7900 8700 7900 8500
Wire Wire Line
	7900 8500 7250 8500
Connection ~ 7250 8500
Wire Wire Line
	9800 9550 9800 9450
Wire Wire Line
	9300 9200 9300 9450
Wire Wire Line
	9300 9450 9800 9450
Connection ~ 9800 9450
Wire Wire Line
	9800 9450 9800 9350
Wire Wire Line
	9800 8750 9800 8650
Wire Wire Line
	9800 8500 8600 8500
Connection ~ 7900 8500
Wire Wire Line
	9300 8900 9300 8650
Wire Wire Line
	9300 8650 9800 8650
Connection ~ 9800 8650
Wire Wire Line
	9800 8650 9800 8500
Wire Wire Line
	9800 9950 9800 10500
Wire Wire Line
	7900 10500 8600 10500
Wire Wire Line
	8400 9150 8450 9150
Wire Wire Line
	8450 9150 8450 9750
Wire Wire Line
	8450 9750 8700 9750
Wire Wire Line
	9000 9750 9200 9750
Wire Wire Line
	9200 9950 9200 9750
Connection ~ 9200 9750
Wire Wire Line
	9200 9750 9500 9750
Wire Wire Line
	9200 10250 9200 10500
Connection ~ 9200 10500
Wire Wire Line
	9200 10500 9800 10500
Wire Wire Line
	8600 8900 8600 10500
Connection ~ 8600 10500
Wire Wire Line
	8600 10500 9200 10500
Wire Wire Line
	8600 8600 8600 8500
Connection ~ 8600 8500
Wire Wire Line
	8600 8500 7900 8500
Wire Wire Line
	5950 10500 5350 10500
Wire Wire Line
	5350 10500 5350 9600
Connection ~ 5950 10500
Connection ~ 5350 9600
Text GLabel 15000 6450 2    50   Input ~ 0
GND_LV
Text GLabel 6650 8100 2    50   Input ~ 0
+5VDC
Wire Wire Line
	6650 8100 6450 8100
Wire Wire Line
	6450 8100 6450 8500
Text GLabel 15000 6350 2    50   Input ~ 0
+5VDC
Wire Wire Line
	15000 6350 14750 6350
Wire Wire Line
	15000 6450 14750 6450
$Comp
L hv-power-supply-v1-rescue:22-23-2021-dk_Rectangular-Connectors-Headers-Male-Pins-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue J3
U 1 1 5D480FF0
P 14650 5700
F 0 "J3" V 14425 5708 50  0000 C CNN
F 1 "22-23-2021" V 14516 5708 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 14850 5900 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 14850 6000 60  0001 L CNN
F 4 "WM4200-ND" H 14850 6100 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 14850 6200 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 14850 6300 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 14850 6400 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 14850 6500 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/molex/22-23-2021/WM4200-ND/26667" H 14850 6600 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 14850 6700 60  0001 L CNN "Description"
F 11 "Molex" H 14850 6800 60  0001 L CNN "Manufacturer"
F 12 "Active" H 14850 6900 60  0001 L CNN "Status"
	1    14650 5700
	0    1    1    0   
$EndComp
Text GLabel 15000 5800 2    50   Input ~ 0
GND_LV
$Comp
L Device:R R4
U 1 1 5D48140A
P 15100 5700
F 0 "R4" H 15170 5746 50  0000 L CNN
F 1 "470R 1/8W" H 15170 5655 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 15030 5700 50  0001 C CNN
F 3 "~" H 15100 5700 50  0001 C CNN
	1    15100 5700
	0    -1   -1   0   
$EndComp
Text GLabel 15400 5700 2    50   Input ~ 0
+5VDC
Wire Wire Line
	15400 5700 15250 5700
Wire Wire Line
	14950 5700 14750 5700
Wire Wire Line
	15000 5800 14750 5800
$Comp
L Regulator_Linear:LM317_3PinPackage U3
U 1 1 5D487A64
P 5050 6950
F 0 "U3" H 5050 7192 50  0000 C CNN
F 1 "LM317_3PinPackage" H 5050 7101 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 5050 7200 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 5050 6950 50  0001 C CNN
	1    5050 6950
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Heatsink HS1
U 1 1 5D48855B
P 5050 6600
F 0 "HS1" H 5192 6721 50  0000 L CNN
F 1 "Heatsink" H 5192 6630 50  0000 L CNN
F 2 "Heatsinks:Heatsink_Fischer_SK104-STC-STIC_35x13mm_2xDrill2.5mm" H 5062 6600 50  0001 C CNN
F 3 "~" H 5062 6600 50  0001 C CNN
	1    5050 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C8
U 1 1 5D48C89B
P 3350 7500
F 0 "C8" H 3468 7546 50  0000 L CNN
F 1 "4700uF/16V" H 3468 7455 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D16.0mm_P7.50mm" H 3388 7350 50  0001 C CNN
F 3 "~" H 3350 7500 50  0001 C CNN
	1    3350 7500
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C13
U 1 1 5D48D366
P 6950 7500
F 0 "C13" H 7068 7546 50  0000 L CNN
F 1 "1000uF/16V" H 7068 7455 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D10.0mm_P5.00mm" H 6988 7350 50  0001 C CNN
F 3 "~" H 6950 7500 50  0001 C CNN
	1    6950 7500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5D48E456
P 5600 7300
F 0 "R7" H 5670 7346 50  0000 L CNN
F 1 "240R 1/8W" H 5670 7255 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5530 7300 50  0001 C CNN
F 3 "~" H 5600 7300 50  0001 C CNN
	1    5600 7300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5D48ECCD
P 4100 7500
F 0 "C9" H 4215 7546 50  0000 L CNN
F 1 "100nF/50V" H 4215 7455 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4138 7350 50  0001 C CNN
F 3 "~" H 4100 7500 50  0001 C CNN
	1    4100 7500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5D48EFEC
P 6250 7500
F 0 "C11" H 6365 7546 50  0000 L CNN
F 1 "100nF/50V" H 6365 7455 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6288 7350 50  0001 C CNN
F 3 "~" H 6250 7500 50  0001 C CNN
	1    6250 7500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5D48F2A8
P 5050 7600
F 0 "R6" H 5120 7646 50  0000 L CNN
F 1 "976R 1/8W" H 5120 7555 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4980 7600 50  0001 C CNN
F 3 "~" H 5050 7600 50  0001 C CNN
	1    5050 7600
	1    0    0    -1  
$EndComp
$Comp
L Diode_Bridge:MB6S D8
U 1 1 5D48FD95
P 2100 7450
F 0 "D8" H 2444 7496 50  0000 L CNN
F 1 "CDBHM2100L-HF" H 2444 7405 50  0000 L CNN
F 2 "Diodes_SMD:Diode_Bridge_TO-269AA" H 2250 7575 50  0001 L CNN
F 3 "http://www.vishay.com/docs/88573/dfs.pdf" H 2100 7450 50  0001 C CNN
	1    2100 7450
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM317_3PinPackage U4
U 1 1 5D4A937E
P 5050 5350
F 0 "U4" H 5050 5592 50  0000 C CNN
F 1 "LM317_3PinPackage" H 5050 5501 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 5050 5600 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 5050 5350 50  0001 C CNN
	1    5050 5350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Heatsink HS2
U 1 1 5D4A973A
P 5050 5000
F 0 "HS2" H 5192 5121 50  0000 L CNN
F 1 "Heatsink" H 5192 5030 50  0000 L CNN
F 2 "Heatsinks:Heatsink_Fischer_SK104-STC-STIC_35x13mm_2xDrill2.5mm" H 5062 5000 50  0001 C CNN
F 3 "~" H 5062 5000 50  0001 C CNN
	1    5050 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5D4B31F6
P 5600 5700
F 0 "R8" H 5670 5746 50  0000 L CNN
F 1 "240R 1/8W" H 5670 5655 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5530 5700 50  0001 C CNN
F 3 "~" H 5600 5700 50  0001 C CNN
	1    5600 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5D4B3671
P 5050 6000
F 0 "R5" H 5120 6046 50  0000 L CNN
F 1 "976R 1/8W" H 5120 5955 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4980 6000 50  0001 C CNN
F 3 "~" H 5050 6000 50  0001 C CNN
	1    5050 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5D4B3A82
P 4150 5850
F 0 "C10" H 4265 5896 50  0000 L CNN
F 1 "100nF/50V" H 4265 5805 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4188 5700 50  0001 C CNN
F 3 "~" H 4150 5850 50  0001 C CNN
	1    4150 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5D4B3D7C
P 6250 5850
F 0 "C12" H 6365 5896 50  0000 L CNN
F 1 "100nF/50V" H 6365 5805 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6288 5700 50  0001 C CNN
F 3 "~" H 6250 5850 50  0001 C CNN
	1    6250 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C14
U 1 1 5D4B3FF1
P 6950 5850
F 0 "C14" H 7068 5896 50  0000 L CNN
F 1 "1000uF/16V" H 7068 5805 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D10.0mm_P5.00mm" H 6988 5700 50  0001 C CNN
F 3 "~" H 6950 5850 50  0001 C CNN
	1    6950 5850
	1    0    0    -1  
$EndComp
NoConn ~ 8400 9050
$Comp
L Device:C C15
U 1 1 5D48C954
P 1050 4800
F 0 "C15" H 1165 4846 50  0000 L CNN
F 1 "2.2nF 2kV" H 1165 4755 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L18.0mm_W5.0mm_P15.00mm_FKS3_FKP3" H 1088 4650 50  0001 C CNN
F 3 "~" H 1050 4800 50  0001 C CNN
	1    1050 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5D48D965
P 1800 4800
F 0 "R9" H 1870 4846 50  0000 L CNN
F 1 "100R/2W" H 1870 4755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 1730 4800 50  0001 C CNN
F 3 "~" H 1800 4800 50  0001 C CNN
	1    1800 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5D4A4E5B
P 8150 7150
F 0 "J1" H 8230 7142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 8230 7051 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 8150 7150 50  0001 C CNN
F 3 "~" H 8150 7150 50  0001 C CNN
	1    8150 7150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 5D562AD4
P 8150 5550
F 0 "J5" H 8230 5542 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 8230 5451 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 8150 5550 50  0001 C CNN
F 3 "~" H 8150 5550 50  0001 C CNN
	1    8150 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 7650 3350 7850
Wire Wire Line
	3350 7850 4100 7850
Wire Wire Line
	7950 7850 7950 7250
Wire Wire Line
	6950 7650 6950 7850
Connection ~ 6950 7850
Wire Wire Line
	6950 7850 7950 7850
Wire Wire Line
	6250 7650 6250 7850
Connection ~ 6250 7850
Wire Wire Line
	6250 7850 6950 7850
Wire Wire Line
	5600 7450 5050 7450
Wire Wire Line
	5050 7250 5050 7450
Connection ~ 5050 7450
Wire Wire Line
	5350 6950 5600 6950
Wire Wire Line
	5600 6950 5600 7150
Wire Wire Line
	5600 6950 6250 6950
Wire Wire Line
	6250 6950 6250 7350
Connection ~ 5600 6950
Wire Wire Line
	6250 6950 6950 6950
Wire Wire Line
	6950 6950 6950 7350
Connection ~ 6250 6950
Wire Wire Line
	4750 6950 4100 6950
Wire Wire Line
	2350 6950 2350 7450
Wire Wire Line
	2350 7450 2400 7450
Wire Wire Line
	1800 7450 1800 7850
Wire Wire Line
	1800 7850 3350 7850
Connection ~ 3350 7850
Wire Wire Line
	3350 7350 3350 6950
Connection ~ 3350 6950
Wire Wire Line
	3350 6950 2350 6950
Wire Wire Line
	4100 7350 4100 6950
Connection ~ 4100 6950
Wire Wire Line
	4100 6950 3350 6950
Wire Wire Line
	4100 7650 4100 7850
Connection ~ 4100 7850
Wire Wire Line
	4100 7850 5050 7850
Wire Wire Line
	5050 7750 5050 7850
Connection ~ 5050 7850
Wire Wire Line
	5050 7850 6250 7850
Wire Wire Line
	6950 6950 7950 6950
Wire Wire Line
	7950 6950 7950 7150
Connection ~ 6950 6950
Wire Wire Line
	1800 7450 1800 6300
Wire Wire Line
	1800 6300 4150 6300
Wire Wire Line
	7950 6300 7950 5650
Connection ~ 1800 7450
Wire Wire Line
	2100 7750 1600 7750
Wire Wire Line
	1600 7750 1600 9500
Connection ~ 1600 9500
Wire Wire Line
	1600 9500 1450 9500
Wire Wire Line
	2100 7150 1450 7150
Wire Wire Line
	1450 7150 1450 8800
Connection ~ 1450 8800
Wire Wire Line
	2350 6950 2350 5350
Wire Wire Line
	2350 5350 4150 5350
Connection ~ 2350 6950
Wire Wire Line
	4150 5700 4150 5350
Connection ~ 4150 5350
Wire Wire Line
	4150 5350 4750 5350
Wire Wire Line
	4150 6000 4150 6300
Connection ~ 4150 6300
Wire Wire Line
	4150 6300 5050 6300
Wire Wire Line
	5050 6150 5050 6300
Connection ~ 5050 6300
Wire Wire Line
	5050 6300 6250 6300
Wire Wire Line
	5050 5850 5050 5650
Wire Wire Line
	5600 5850 5050 5850
Connection ~ 5050 5850
Wire Wire Line
	5600 5550 5600 5350
Wire Wire Line
	5600 5350 5350 5350
Wire Wire Line
	6250 5700 6250 5350
Wire Wire Line
	6250 5350 5600 5350
Connection ~ 5600 5350
Wire Wire Line
	6950 5700 6950 5350
Wire Wire Line
	6950 5350 6250 5350
Connection ~ 6250 5350
Wire Wire Line
	6250 6000 6250 6300
Connection ~ 6250 6300
Wire Wire Line
	6250 6300 6950 6300
Wire Wire Line
	6950 6000 6950 6300
Connection ~ 6950 6300
Wire Wire Line
	6950 6300 7950 6300
Wire Wire Line
	6950 5350 7950 5350
Wire Wire Line
	7950 5350 7950 5550
Connection ~ 6950 5350
Text GLabel 3250 8050 0    50   Input ~ 0
GND_LV
Wire Wire Line
	3350 7850 3350 8050
Wire Wire Line
	3350 8050 3250 8050
$Comp
L Device:C C16
U 1 1 5D78BBA2
P 2200 1400
F 0 "C16" V 1948 1400 50  0000 C CNN
F 1 "10nF/630V" V 2039 1400 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 1250 50  0001 C CNN
F 3 "~" H 2200 1400 50  0001 C CNN
	1    2200 1400
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J6
U 1 1 5D78CC04
P 850 2850
F 0 "J6" H 768 3167 50  0000 C CNN
F 1 "Screw_Terminal_01x03" H 768 3076 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-3_P5.00mm" H 850 2850 50  0001 C CNN
F 3 "~" H 850 2850 50  0001 C CNN
	1    850  2850
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 5D7B11F4
P 2200 2150
F 0 "C17" V 1948 2150 50  0000 C CNN
F 1 "10nF/630V" V 2039 2150 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 2000 50  0001 C CNN
F 3 "~" H 2200 2150 50  0001 C CNN
	1    2200 2150
	0    1    1    0   
$EndComp
$Comp
L Device:C C18
U 1 1 5D7B1C4E
P 2200 3100
F 0 "C18" V 1948 3100 50  0000 C CNN
F 1 "10nF/630V" V 2039 3100 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 2950 50  0001 C CNN
F 3 "~" H 2200 3100 50  0001 C CNN
	1    2200 3100
	0    1    1    0   
$EndComp
$Comp
L Device:C C19
U 1 1 5D7B2C2A
P 2200 3900
F 0 "C19" V 1948 3900 50  0000 C CNN
F 1 "10nF/630V" V 2039 3900 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W4.0mm_P10.00mm_FKS3_FKP3_MKS4" H 2238 3750 50  0001 C CNN
F 3 "~" H 2200 3900 50  0001 C CNN
	1    2200 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 2750 1400 2750
Wire Wire Line
	2050 1600 1950 1600
Wire Wire Line
	1400 1600 1400 2750
Wire Wire Line
	2350 2400 2450 2400
Wire Wire Line
	2600 2400 2600 1600
Wire Wire Line
	2600 1600 2450 1600
Wire Wire Line
	1650 2850 1050 2850
Wire Wire Line
	2050 2400 1950 2400
Wire Wire Line
	1650 2400 1650 2850
Wire Wire Line
	1400 2750 1400 3500
Wire Wire Line
	1400 3500 1950 3500
Connection ~ 1400 2750
Wire Wire Line
	1650 2850 1650 4300
Wire Wire Line
	1650 4300 1950 4300
Connection ~ 1650 2850
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
L Device:C C21
U 1 1 5D4A1C15
P 3650 2950
F 0 "C21" V 3398 2950 50  0000 C CNN
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
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 12850 2600 60  0001 L CNN
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
L Device:R R10
U 1 1 5D4F27BA
P 12650 3200
F 0 "R10" H 12720 3246 50  0000 L CNN
F 1 "12R/0.6W" H 12720 3155 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 12580 3200 50  0001 C CNN
F 3 "~" H 12650 3200 50  0001 C CNN
	1    12650 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5D4F3205
P 12650 3850
F 0 "R11" H 12720 3896 50  0000 L CNN
F 1 "402K/0.6W" H 12720 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 12580 3850 50  0001 C CNN
F 3 "~" H 12650 3850 50  0001 C CNN
	1    12650 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 5D4F3A1B
P 12650 4350
F 0 "R12" H 12720 4396 50  0000 L CNN
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
F 2 "TO_SOT_Packages_SMD:SOT-23" H 11700 3100 60  0001 L CNN
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
L Device:R R13
U 1 1 5D50AAEA
P 4350 1950
F 0 "R13" H 4420 1996 50  0000 L CNN
F 1 "100k/2W" H 4420 1905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 4280 1950 50  0001 C CNN
F 3 "~" H 4350 1950 50  0001 C CNN
	1    4350 1950
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM321 U5
U 1 1 5D789BFC
P 6950 3500
F 0 "U5" H 7294 3546 50  0000 L CNN
F 1 "LM321" H 7294 3455 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 6950 3500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm321.pdf" H 6950 3500 50  0001 C CNN
	1    6950 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C23
U 1 1 5D51B86E
P 5500 3300
F 0 "C23" H 5615 3346 50  0000 L CNN
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
L Device:R R15
U 1 1 5D6391A7
P 8500 3500
F 0 "R15" H 8570 3546 50  0000 L CNN
F 1 "100R 1/8W" H 8570 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8430 3500 50  0001 C CNN
F 3 "~" H 8500 3500 50  0001 C CNN
	1    8500 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	8650 3500 8800 3500
$Comp
L Device:R R16
U 1 1 5D6D0C3D
P 9100 2100
F 0 "R16" H 9170 2146 50  0000 L CNN
F 1 "470k/0.6W" H 9170 2055 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 9030 2100 50  0001 C CNN
F 3 "~" H 9100 2100 50  0001 C CNN
	1    9100 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 5D77CB36
P 11850 3850
F 0 "R17" H 11920 3896 50  0000 L CNN
F 1 "200k/0.6W" H 11920 3805 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 11780 3850 50  0001 C CNN
F 3 "~" H 11850 3850 50  0001 C CNN
	1    11850 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5D7EA431
P 12250 2900
F 0 "R18" H 12320 2946 50  0000 L CNN
F 1 "4.99k,1/8W" H 12320 2855 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 12180 2900 50  0001 C CNN
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
L Device:CP C25
U 1 1 5DB70D19
P 4950 3500
F 0 "C25" H 5068 3546 50  0000 L CNN
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
$Comp
L Connector:Screw_Terminal_01x02 J7
U 1 1 5DC091D8
P 12350 9600
F 0 "J7" H 12430 9592 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 12430 9501 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 12350 9600 50  0001 C CNN
F 3 "~" H 12350 9600 50  0001 C CNN
	1    12350 9600
	1    0    0    -1  
$EndComp
Text GLabel 11700 9650 0    50   Input ~ 0
GND_HV
Wire Wire Line
	11950 9550 10700 9550
Wire Wire Line
	10700 9550 10700 9350
Wire Wire Line
	10700 9550 10300 9550
Wire Wire Line
	10300 9550 10300 9350
Connection ~ 10700 9550
Wire Wire Line
	11700 9650 11950 9650
Text GLabel 14450 3550 2    50   Input ~ 0
HV
Text GLabel 10600 8150 1    50   Input ~ 0
HV
Wire Wire Line
	10600 8750 10600 8400
Wire Wire Line
	10200 8750 10200 8400
Wire Wire Line
	10200 8400 10600 8400
Connection ~ 10600 8400
Wire Wire Line
	10600 8400 10600 8150
Text GLabel 10650 5550 0    50   Input ~ 0
GND_HV
Text GLabel 12100 5550 2    50   Input ~ 0
GND_LV
$Comp
L Device:R R19
U 1 1 5DC91072
P 11350 5150
F 0 "R19" V 11143 5150 50  0000 C CNN
F 1 "1R/0.5W" V 11234 5150 50  0000 C CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" V 11280 5150 50  0001 C CNN
F 3 "~" H 11350 5150 50  0001 C CNN
	1    11350 5150
	0    1    1    0   
$EndComp
$Comp
L Device:R R20
U 1 1 5DC915C0
P 11350 5550
F 0 "R20" V 11143 5550 50  0000 C CNN
F 1 "1R/0.5W" V 11234 5550 50  0000 C CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" V 11280 5550 50  0001 C CNN
F 3 "~" H 11350 5550 50  0001 C CNN
	1    11350 5550
	0    1    1    0   
$EndComp
$Comp
L Device:R R21
U 1 1 5DC9199A
P 11350 6000
F 0 "R21" V 11143 6000 50  0000 C CNN
F 1 "1R/0.5W" V 11234 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" V 11280 6000 50  0001 C CNN
F 3 "~" H 11350 6000 50  0001 C CNN
	1    11350 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	12100 5550 11850 5550
Wire Wire Line
	11850 5550 11850 5150
Wire Wire Line
	11850 5150 11500 5150
Wire Wire Line
	11500 5550 11850 5550
Connection ~ 11850 5550
Wire Wire Line
	11500 6000 11850 6000
Wire Wire Line
	11200 5150 10900 5150
Wire Wire Line
	10900 5150 10900 5550
Wire Wire Line
	10900 5550 10650 5550
Wire Wire Line
	10900 5550 11200 5550
Connection ~ 10900 5550
Wire Wire Line
	11200 6000 10900 6000
Text GLabel 2150 5050 2    50   Input ~ 0
GND_HV
Wire Wire Line
	1050 2950 1050 4450
Wire Wire Line
	2150 5050 1800 5050
Wire Wire Line
	1050 5050 1050 4950
Wire Wire Line
	1800 4650 1800 4450
Wire Wire Line
	1800 4450 1050 4450
Connection ~ 1050 4450
Wire Wire Line
	1050 4450 1050 4650
Wire Wire Line
	1800 4950 1800 5050
Connection ~ 1800 5050
Wire Wire Line
	1800 5050 1050 5050
Wire Wire Line
	4700 8500 5350 8500
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 5DF0B7C6
P 850 9150
F 0 "J4" H 930 9142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 350 8900 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 850 9150 50  0001 C CNN
F 3 "~" H 850 9150 50  0001 C CNN
	1    850  9150
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 9050 1050 9050
Wire Wire Line
	1450 9150 1050 9150
Connection ~ 2800 8500
Connection ~ 2800 9600
Wire Wire Line
	2800 8500 3500 8500
Wire Wire Line
	2800 9600 3500 9600
Wire Wire Line
	10900 6000 10900 5550
Wire Wire Line
	11850 6000 11850 5550
Wire Wire Line
	2600 2400 2900 2400
Wire Wire Line
	2600 3500 2900 3500
$Comp
L Device:CP C20
U 1 1 5D4A04F9
P 2900 2950
F 0 "C20" H 3018 2996 50  0000 L CNN
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
L Reference_Voltage:LM4040DBZ-10 U6
U 1 1 602372BD
P 4350 3800
F 0 "U6" V 4396 3712 50  0000 R CNN
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
L Device:C C22
U 1 1 602CB214
P 7200 2950
F 0 "C22" H 7315 2996 50  0000 L CNN
F 1 "10nF/50V" H 7315 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7238 2800 50  0001 C CNN
F 3 "~" H 7200 2950 50  0001 C CNN
	1    7200 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 602CC6FF
P 7650 2950
F 0 "R14" H 7720 2996 50  0000 L CNN
F 1 "0R 1/8W" H 7720 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7580 2950 50  0001 C CNN
F 3 "~" H 7650 2950 50  0001 C CNN
	1    7650 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R24
U 1 1 6036D06F
P 13400 3850
F 0 "R24" H 13470 3896 50  0000 L CNN
F 1 "750/0.6W" H 13470 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 13330 3850 50  0001 C CNN
F 3 "~" H 13400 3850 50  0001 C CNN
	1    13400 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R25
U 1 1 6036E649
P 14100 3550
F 0 "R25" H 14170 3596 50  0000 L CNN
F 1 "330R2W" H 14170 3505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 14030 3550 50  0001 C CNN
F 3 "~" H 14100 3550 50  0001 C CNN
	1    14100 3550
	0    1    1    0   
$EndComp
$Comp
L Device:C C27
U 1 1 60370030
P 13400 4250
F 0 "C27" H 13515 4296 50  0000 L CNN
F 1 "470pF/500V" H 13515 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 13438 4100 50  0001 C CNN
F 3 "~" H 13400 4250 50  0001 C CNN
	1    13400 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R22
U 1 1 60389831
P 7850 4050
F 0 "R22" H 7920 4096 50  0000 L CNN
F 1 "10K 1/8W" H 7920 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7780 4050 50  0001 C CNN
F 3 "~" H 7850 4050 50  0001 C CNN
	1    7850 4050
	0    1    1    0   
$EndComp
$Comp
L hv-power-supply-v1-rescue:IRF510PBF-dk_Transistors-FETs-MOSFETs-Single-PowerSupply-6SN7-rescue-hv-power-supply-v1-rescue Q2
U 1 1 603EDCB9
P 9100 3400
F 0 "Q2" H 9208 3453 60  0000 L CNN
F 1 "IRF840" H 9208 3347 60  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 9300 3600 60  0001 L CNN
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
L Diode:BAT54C D10
U 1 1 6039085C
P 6300 4300
F 0 "D10" V 6346 4388 50  0000 L CNN
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
L Device:R R23
U 1 1 605CAE8D
P 9100 4350
F 0 "R23" H 9170 4396 50  0000 L CNN
F 1 "2.7k 1/8W" H 9170 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 9030 4350 50  0001 C CNN
F 3 "~" H 9100 4350 50  0001 C CNN
	1    9100 4350
	-1   0    0    1   
$EndComp
$Comp
L Device:C C24
U 1 1 605CBEBE
P 9350 4350
F 0 "C24" H 9465 4396 50  0000 L CNN
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
L Device:C C26
U 1 1 6064FFD8
P 10450 3100
F 0 "C26" H 10565 3146 50  0000 L CNN
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
	10450 3550 11400 3550
Connection ~ 11400 3550
Wire Wire Line
	11400 3100 11400 3550
Wire Wire Line
	11400 2700 11400 2500
Connection ~ 11400 2500
Wire Wire Line
	11400 2500 10450 2500
Wire Wire Line
	11400 2500 12350 2500
Wire Wire Line
	12100 2900 11850 2900
Wire Wire Line
	12400 2900 12650 2900
Wire Wire Line
	12650 2900 12650 2600
Wire Wire Line
	12650 3050 12650 2900
Connection ~ 12650 2900
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
	8000 4050 12650 4050
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
L Relay:G2RL-2-DC5 RL?
U 1 1 609FA731
P 10200 9050
F 0 "RL?" H 9571 9004 50  0000 R CNN
F 1 "G2RL-2-DC5" H 9571 9095 50  0000 R CNN
F 2 "Relay_THT:Relay_DPDT_Omron_G2RL" H 10850 9000 50  0001 L CNN
F 3 "https://omronfs.omron.com/en_US/ecb/products/pdf/en-g2rl.pdf" H 10200 9050 50  0001 C CNN
	1    10200 9050
	1    0    0    1   
$EndComp
$Comp
L Diode:BZX84Cxx D?
U 1 1 60A33BA7
P 9800 3100
F 0 "D?" V 9754 3180 50  0000 L CNN
F 1 "BZX84C15" V 9845 3180 50  0000 L CNN
F 2 "Diode_SMD:D_SOT-23_ANK" H 9800 2925 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzx84c2v4.pdf" H 9800 3100 50  0001 C CNN
	1    9800 3100
	0    1    1    0   
$EndComp
$EndSCHEMATC
