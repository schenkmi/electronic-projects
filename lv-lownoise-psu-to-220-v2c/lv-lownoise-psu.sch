EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "lv-lownoise-psu-to-220-v2c"
Date ""
Rev "V2C"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Linear:LT1761-BYP U1
U 1 1 5F9572E9
P 6550 2400
F 0 "U1" H 6550 2767 50  0000 C CNN
F 1 "LT1761-BYP" H 6550 2676 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-5" H 6550 2750 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1761sff.pdf" H 6550 2400 50  0001 C CNN
	1    6550 2400
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LT1964-BYP U2
U 1 1 5F957B72
P 6550 4700
F 0 "U2" H 6550 4451 50  0000 C CNN
F 1 "LT1964-BYP" H 6550 4360 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-5" H 6550 4400 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1964fb.pdf" H 6550 4700 50  0001 C CNN
	1    6550 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F95888A
P 7850 3050
F 0 "R1" H 7920 3096 50  0000 L CNN
F 1 "15k" H 7920 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7780 3050 50  0001 C CNN
F 3 "~" H 7850 3050 50  0001 C CNN
	1    7850 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5F959844
P 1350 3550
F 0 "J2" H 1268 3325 50  0000 C CNN
F 1 "GND" H 1268 3416 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 1350 3550 50  0001 C CNN
F 3 "~" H 1350 3550 50  0001 C CNN
	1    1350 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5F95A600
P 7850 2550
F 0 "RV1" H 7781 2596 50  0000 R CNN
F 1 "250k" H 7781 2505 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 7850 2550 50  0001 C CNN
F 3 "~" H 7850 2550 50  0001 C CNN
	1    7850 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5F95AC77
P 5900 2950
F 0 "C3" H 6015 2996 50  0000 L CNN
F 1 "1u" H 6015 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5938 2800 50  0001 C CNN
F 3 "~" H 5900 2950 50  0001 C CNN
	1    5900 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5F95B397
P 7250 2400
F 0 "C5" H 7365 2446 50  0000 L CNN
F 1 "10n" H 7365 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7288 2250 50  0001 C CNN
F 3 "~" H 7250 2400 50  0001 C CNN
	1    7250 2400
	0    1    1    0   
$EndComp
$Comp
L Device:CP C7
U 1 1 5F95BFDC
P 8400 2950
F 0 "C7" H 8518 2996 50  0000 L CNN
F 1 "10u" H 8518 2905 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-12_Kemet-T_Pad1.50x2.35mm_HandSolder" H 8438 2800 50  0001 C CNN
F 3 "~" H 8400 2950 50  0001 C CNN
	1    8400 2950
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5F95CBEB
P 4450 6650
F 0 "H1" H 4550 6696 50  0000 L CNN
F 1 "MountingHole" H 4550 6605 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 4450 6650 50  0001 C CNN
F 3 "~" H 4450 6650 50  0001 C CNN
	1    4450 6650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5F95D7C8
P 5350 6650
F 0 "H3" H 5450 6696 50  0000 L CNN
F 1 "MountingHole" H 5450 6605 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5350 6650 50  0001 C CNN
F 3 "~" H 5350 6650 50  0001 C CNN
	1    5350 6650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5F95D9CD
P 4450 7050
F 0 "H2" H 4550 7096 50  0000 L CNN
F 1 "MountingHole" H 4550 7005 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 4450 7050 50  0001 C CNN
F 3 "~" H 4450 7050 50  0001 C CNN
	1    4450 7050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5F95DB8E
P 5350 7050
F 0 "H4" H 5450 7096 50  0000 L CNN
F 1 "MountingHole" H 5450 7005 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5350 7050 50  0001 C CNN
F 3 "~" H 5350 7050 50  0001 C CNN
	1    5350 7050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 5F95F176
P 1350 2900
F 0 "J1" H 1268 2675 50  0000 C CNN
F 1 "AC" H 1268 2766 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 1350 2900 50  0001 C CNN
F 3 "~" H 1350 2900 50  0001 C CNN
	1    1350 2900
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 5F95F6D2
P 1350 4250
F 0 "J3" H 1268 4025 50  0000 C CNN
F 1 "AC" H 1268 4116 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 1350 4250 50  0001 C CNN
F 3 "~" H 1350 4250 50  0001 C CNN
	1    1350 4250
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C1
U 1 1 5F961063
P 3850 2950
F 0 "C1" H 3968 2996 50  0000 L CNN
F 1 "2200uF" H 3968 2905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D16.0mm_P7.50mm" H 3888 2800 50  0001 C CNN
F 3 "~" H 3850 2950 50  0001 C CNN
	1    3850 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5F96796D
P 1750 3700
F 0 "#PWR01" H 1750 3450 50  0001 C CNN
F 1 "GND" H 1755 3527 50  0000 C CNN
F 2 "" H 1750 3700 50  0001 C CNN
F 3 "" H 1750 3700 50  0001 C CNN
	1    1750 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 5F96866D
P 9750 3550
F 0 "J5" H 9830 3592 50  0000 L CNN
F 1 "GND" H 9830 3501 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 3550 50  0001 C CNN
F 3 "~" H 9750 3550 50  0001 C CNN
	1    9750 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 5F968F41
P 9750 2300
F 0 "J4" H 9830 2342 50  0000 L CNN
F 1 "+15V" H 9830 2251 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 2300 50  0001 C CNN
F 3 "~" H 9750 2300 50  0001 C CNN
	1    9750 2300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 5F96951B
P 9750 4800
F 0 "J6" H 9830 4842 50  0000 L CNN
F 1 "-15V" H 9830 4751 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 4800 50  0001 C CNN
F 3 "~" H 9750 4800 50  0001 C CNN
	1    9750 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2300 5900 2300
Wire Wire Line
	7850 2400 7850 2300
Wire Wire Line
	7850 2300 7500 2300
Wire Wire Line
	6950 2500 7050 2500
$Comp
L Device:C C9
U 1 1 5F973298
P 8850 2950
F 0 "C9" H 8965 2996 50  0000 L CNN
F 1 "100n" H 8965 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8888 2800 50  0001 C CNN
F 3 "~" H 8850 2950 50  0001 C CNN
	1    8850 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 2300 8850 2300
Connection ~ 7850 2300
Connection ~ 8400 2300
Wire Wire Line
	8400 2300 7850 2300
Connection ~ 8850 2300
Wire Wire Line
	8850 2300 8400 2300
Wire Wire Line
	7050 2500 7050 2800
Wire Wire Line
	7850 2700 7850 2800
Wire Wire Line
	7850 2800 8100 2800
Wire Wire Line
	8100 2800 8100 2550
Wire Wire Line
	8100 2550 8000 2550
Connection ~ 7850 2800
Wire Wire Line
	7850 2800 7850 2900
Wire Wire Line
	7850 2800 7050 2800
Wire Wire Line
	3850 2300 3850 2800
Wire Wire Line
	5900 2300 5900 2800
Wire Wire Line
	5900 3550 5900 3100
Wire Wire Line
	3850 3100 3850 3550
Connection ~ 5900 3550
Wire Wire Line
	8400 3550 8400 3100
Wire Wire Line
	8400 3550 8850 3550
Wire Wire Line
	8850 3550 8850 3100
Connection ~ 8400 3550
Wire Wire Line
	6550 2700 6550 3550
Connection ~ 6550 3550
Wire Wire Line
	6550 3550 5900 3550
Wire Wire Line
	8400 2300 8400 2800
Wire Wire Line
	8850 2300 8850 2800
$Comp
L power:GND #PWR02
U 1 1 5F981F2D
P 3600 3700
F 0 "#PWR02" H 3600 3450 50  0001 C CNN
F 1 "GND" H 3605 3527 50  0000 C CNN
F 2 "" H 3600 3700 50  0001 C CNN
F 3 "" H 3600 3700 50  0001 C CNN
	1    3600 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5F989596
P 5900 4200
F 0 "C4" H 6015 4246 50  0000 L CNN
F 1 "1u" H 6015 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5938 4050 50  0001 C CNN
F 3 "~" H 5900 4200 50  0001 C CNN
	1    5900 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5F98959C
P 3850 4200
F 0 "C2" H 3968 4246 50  0000 L CNN
F 1 "2200uF" H 3968 4155 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D16.0mm_P7.50mm" H 3888 4050 50  0001 C CNN
F 3 "~" H 3850 4200 50  0001 C CNN
	1    3850 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4800 5900 4350
Wire Wire Line
	3850 4350 3850 4800
Wire Wire Line
	6150 4800 5900 4800
Wire Wire Line
	3850 4050 3850 3550
Connection ~ 3850 3550
Wire Wire Line
	5900 4050 5900 3550
Wire Wire Line
	6550 4400 6550 3550
$Comp
L Device:CP C8
U 1 1 5F9919EC
P 8400 4200
F 0 "C8" H 8518 4246 50  0000 L CNN
F 1 "10u" H 8518 4155 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-12_Kemet-T_Pad1.50x2.35mm_HandSolder" H 8438 4050 50  0001 C CNN
F 3 "~" H 8400 4200 50  0001 C CNN
	1    8400 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5F9919F2
P 8850 4200
F 0 "C10" H 8965 4246 50  0000 L CNN
F 1 "100n" H 8965 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8888 4050 50  0001 C CNN
F 3 "~" H 8850 4200 50  0001 C CNN
	1    8850 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4800 8400 4350
Wire Wire Line
	8400 4800 8850 4800
Wire Wire Line
	8850 4800 8850 4350
Connection ~ 8400 4800
$Comp
L Device:C C6
U 1 1 5F996810
P 7250 4700
F 0 "C6" H 7365 4746 50  0000 L CNN
F 1 "10n" H 7365 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7288 4550 50  0001 C CNN
F 3 "~" H 7250 4700 50  0001 C CNN
	1    7250 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_POT RV2
U 1 1 5F998C09
P 7850 4550
F 0 "RV2" H 7781 4596 50  0000 R CNN
F 1 "250k" H 7781 4505 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 7850 4550 50  0001 C CNN
F 3 "~" H 7850 4550 50  0001 C CNN
	1    7850 4550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5F99C2E1
P 7850 4050
F 0 "R2" H 7920 4096 50  0000 L CNN
F 1 "15k" H 7920 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7780 4050 50  0001 C CNN
F 3 "~" H 7850 4050 50  0001 C CNN
	1    7850 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3550 3600 3550
Wire Wire Line
	3600 3550 3600 3700
Wire Wire Line
	7850 3900 7850 3550
Wire Wire Line
	8400 4050 8400 3550
Wire Wire Line
	8850 4050 8850 3550
Connection ~ 8850 3550
Wire Wire Line
	7850 4400 7850 4300
Connection ~ 7850 4300
Wire Wire Line
	7850 4300 7850 4200
Wire Wire Line
	7850 4700 7850 4800
Wire Wire Line
	6950 4600 7050 4600
Wire Wire Line
	7050 4600 7050 4300
Wire Wire Line
	9550 3550 8850 3550
Wire Wire Line
	9550 4800 8850 4800
Connection ~ 8850 4800
Connection ~ 7850 3550
Wire Wire Line
	7850 3550 8400 3550
Connection ~ 7850 4800
Wire Wire Line
	7850 4800 8400 4800
Wire Wire Line
	6950 4800 7550 4800
Wire Wire Line
	7050 4300 7550 4300
Wire Wire Line
	2050 4800 3850 4800
Wire Wire Line
	1750 3700 1750 3550
Wire Wire Line
	1750 3550 1550 3550
Wire Wire Line
	2300 3550 2050 3550
Wire Wire Line
	2050 3550 2050 4800
Wire Wire Line
	3250 3550 3250 2300
Wire Wire Line
	3250 2300 3850 2300
Wire Wire Line
	2900 3550 3250 3550
Wire Wire Line
	1550 2900 2600 2900
Wire Wire Line
	2600 2900 2600 3250
Wire Wire Line
	1550 4250 2600 4250
Wire Wire Line
	2600 4250 2600 3850
Wire Wire Line
	7850 3200 7850 3550
$Comp
L Transistor_BJT:BD140 Q2
U 1 1 5F9AEA9D
P 5200 4700
F 0 "Q2" V 5437 4700 50  0000 C CNN
F 1 "BD680" V 5528 4700 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-126-3_Vertical" H 5400 4625 50  0001 L CIN
F 3 "http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00001225.pdf" H 5200 4700 50  0001 L CNN
	1    5200 4700
	0    -1   1    0   
$EndComp
$Comp
L Transistor_BJT:BD139 Q1
U 1 1 5F9AF8DE
P 5200 2400
F 0 "Q1" V 5529 2400 50  0000 C CNN
F 1 "BD679" V 5438 2400 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-126-3_Vertical" H 5400 2325 50  0001 L CIN
F 3 "http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00001225.pdf" H 5200 2400 50  0001 L CNN
	1    5200 2400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 5F9B9329
P 4600 2700
F 0 "R5" H 4670 2746 50  0000 L CNN
F 1 "3.16k" H 4670 2655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 2700 50  0001 C CNN
F 3 "~" H 4600 2700 50  0001 C CNN
	1    4600 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5F9B9F9C
P 4600 3100
F 0 "R6" H 4670 3146 50  0000 L CNN
F 1 "21k" H 4670 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 3100 50  0001 C CNN
F 3 "~" H 4600 3100 50  0001 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5F9D4A3F
P 4600 3950
F 0 "R7" H 4670 3996 50  0000 L CNN
F 1 "21k" H 4670 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 3950 50  0001 C CNN
F 3 "~" H 4600 3950 50  0001 C CNN
	1    4600 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5F9D4A45
P 4600 4350
F 0 "R8" H 4670 4396 50  0000 L CNN
F 1 "3.16k" H 4670 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 4350 50  0001 C CNN
F 3 "~" H 4600 4350 50  0001 C CNN
	1    4600 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2850 4600 2900
Wire Wire Line
	4600 4100 4600 4150
Wire Wire Line
	3850 3550 4600 3550
Wire Wire Line
	3850 2300 4600 2300
Wire Wire Line
	4600 2300 4600 2550
Connection ~ 3850 2300
Wire Wire Line
	4600 2300 5000 2300
Connection ~ 4600 2300
Wire Wire Line
	4600 3250 4600 3550
Connection ~ 4600 3550
Wire Wire Line
	4600 3550 5900 3550
Wire Wire Line
	4600 3550 4600 3800
Wire Wire Line
	5400 2300 5900 2300
Connection ~ 5900 2300
Wire Wire Line
	5200 2600 5200 2900
Wire Wire Line
	5200 2900 4600 2900
Connection ~ 4600 2900
Wire Wire Line
	4600 2900 4600 2950
Wire Wire Line
	5200 4500 5200 4150
Wire Wire Line
	5200 4150 4600 4150
Connection ~ 4600 4150
Wire Wire Line
	4600 4150 4600 4200
Wire Wire Line
	5000 4800 4600 4800
Wire Wire Line
	4600 4800 4600 4500
Wire Wire Line
	4600 4800 3850 4800
Connection ~ 4600 4800
Connection ~ 3850 4800
Wire Wire Line
	5400 4800 5900 4800
Connection ~ 5900 4800
Wire Wire Line
	6950 2400 7100 2400
Wire Wire Line
	7400 2400 7500 2400
Wire Wire Line
	7500 2400 7500 2300
Connection ~ 7500 2300
Wire Wire Line
	7500 2300 6950 2300
Wire Wire Line
	6550 3550 7850 3550
Wire Wire Line
	6950 4700 7100 4700
Wire Wire Line
	7400 4700 7550 4700
Wire Wire Line
	7550 4700 7550 4800
Connection ~ 7550 4800
Wire Wire Line
	7550 4800 7850 4800
Wire Wire Line
	7700 4550 7550 4550
Wire Wire Line
	7550 4550 7550 4300
Connection ~ 7550 4300
Wire Wire Line
	7550 4300 7850 4300
$Comp
L Device:CP C13
U 1 1 5FA95285
P 8850 1450
F 0 "C13" H 8968 1496 50  0000 L CNN
F 1 "100uF" H 8968 1405 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 8888 1300 50  0001 C CNN
F 3 "~" H 8850 1450 50  0001 C CNN
	1    8850 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5FA9528B
P 6850 1450
F 0 "C11" H 6965 1496 50  0000 L CNN
F 1 "330nF" H 6965 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6888 1300 50  0001 C CNN
F 3 "~" H 6850 1450 50  0001 C CNN
	1    6850 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5FA95291
P 8350 1450
F 0 "C12" H 8465 1496 50  0000 L CNN
F 1 "100nF" H 8465 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8388 1300 50  0001 C CNN
F 3 "~" H 8350 1450 50  0001 C CNN
	1    8350 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5FA95297
P 6850 1700
F 0 "#PWR03" H 6850 1450 50  0001 C CNN
F 1 "GND" H 6855 1527 50  0000 C CNN
F 2 "" H 6850 1700 50  0001 C CNN
F 3 "" H 6850 1700 50  0001 C CNN
	1    6850 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 5FA9529D
P 9750 1250
F 0 "J7" H 9830 1292 50  0000 L CNN
F 1 "+5V" H 9830 1201 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 1250 50  0001 C CNN
F 3 "~" H 9750 1250 50  0001 C CNN
	1    9750 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 5FA952AE
P 9750 1650
F 0 "J8" H 9830 1692 50  0000 L CNN
F 1 "GND" H 9830 1601 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 1650 50  0001 C CNN
F 3 "~" H 9750 1650 50  0001 C CNN
	1    9750 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5FAA7DD8
P 8850 750
F 0 "R3" H 8920 796 50  0000 L CNN
F 1 "330R" H 8920 705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8780 750 50  0001 C CNN
F 3 "~" H 8850 750 50  0001 C CNN
	1    8850 750 
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J9
U 1 1 5FAA89B1
P 9750 750
F 0 "J9" H 9830 792 50  0000 L CNN
F 1 "LED" H 9830 701 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 750 50  0001 C CNN
F 3 "~" H 9750 750 50  0001 C CNN
	1    9750 750 
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J10
U 1 1 5FAA8F72
P 9750 1000
F 0 "J10" H 9830 1042 50  0000 L CNN
F 1 "GND" H 9830 951 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 1000 50  0001 C CNN
F 3 "~" H 9750 1000 50  0001 C CNN
	1    9750 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5FAA9434
P 9400 1000
F 0 "#PWR04" H 9400 750 50  0001 C CNN
F 1 "GND" H 9405 827 50  0000 C CNN
F 2 "" H 9400 1000 50  0001 C CNN
F 3 "" H 9400 1000 50  0001 C CNN
	1    9400 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	9550 1000 9400 1000
Wire Wire Line
	9550 750  9000 750 
Wire Wire Line
	8700 750  8350 750 
Wire Wire Line
	8850 1650 8850 1600
Wire Wire Line
	8850 1650 8350 1650
Wire Wire Line
	8350 1650 8350 1600
Connection ~ 8850 1650
Wire Wire Line
	8350 1300 8350 1250
Connection ~ 8350 1250
Wire Wire Line
	8350 1250 8850 1250
Wire Wire Line
	8350 1250 8350 750 
Wire Wire Line
	8850 1300 8850 1250
Connection ~ 8850 1250
Wire Wire Line
	8850 1250 9550 1250
Wire Wire Line
	8850 1650 9550 1650
$Comp
L Device:CP C16
U 1 1 5FBAAF51
P 8850 5650
F 0 "C16" H 8968 5696 50  0000 L CNN
F 1 "100uF" H 8968 5605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 8888 5500 50  0001 C CNN
F 3 "~" H 8850 5650 50  0001 C CNN
	1    8850 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 5FBAAF57
P 6800 5650
F 0 "C14" H 6915 5696 50  0000 L CNN
F 1 "330nF" H 6915 5605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6838 5500 50  0001 C CNN
F 3 "~" H 6800 5650 50  0001 C CNN
	1    6800 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 5FBAAF5D
P 8350 5650
F 0 "C15" H 8465 5696 50  0000 L CNN
F 1 "100nF" H 8465 5605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8388 5500 50  0001 C CNN
F 3 "~" H 8350 5650 50  0001 C CNN
	1    8350 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5FBAAF63
P 6800 5400
F 0 "#PWR05" H 6800 5150 50  0001 C CNN
F 1 "GND" H 6805 5227 50  0000 C CNN
F 2 "" H 6800 5400 50  0001 C CNN
F 3 "" H 6800 5400 50  0001 C CNN
	1    6800 5400
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J11
U 1 1 5FBAAF69
P 9750 5450
F 0 "J11" H 9830 5492 50  0000 L CNN
F 1 "GND" H 9830 5401 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 5450 50  0001 C CNN
F 3 "~" H 9750 5450 50  0001 C CNN
	1    9750 5450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J12
U 1 1 5FBAAF6F
P 9750 5850
F 0 "J12" H 9830 5892 50  0000 L CNN
F 1 "-5V" H 9830 5801 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 9750 5850 50  0001 C CNN
F 3 "~" H 9750 5850 50  0001 C CNN
	1    9750 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 5850 8850 5800
Wire Wire Line
	8850 5850 8350 5850
Wire Wire Line
	8350 5850 8350 5800
Connection ~ 8850 5850
Wire Wire Line
	8350 5500 8350 5450
Wire Wire Line
	8350 5450 8850 5450
Wire Wire Line
	8850 5500 8850 5450
Connection ~ 8850 5450
Wire Wire Line
	8850 5450 9550 5450
Wire Wire Line
	8850 5850 9550 5850
$Comp
L Device:R R4
U 1 1 5FB1421B
P 3850 1800
F 0 "R4" H 3920 1846 50  0000 L CNN
F 1 "0R" H 3920 1755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3780 1800 50  0001 C CNN
F 3 "~" H 3850 1800 50  0001 C CNN
	1    3850 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5FB14E9C
P 5900 1800
F 0 "R9" H 5970 1846 50  0000 L CNN
F 1 "0R" H 5970 1755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5830 1800 50  0001 C CNN
F 3 "~" H 5900 1800 50  0001 C CNN
	1    5900 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1250 8350 1250
Wire Wire Line
	8350 1650 7500 1650
Wire Wire Line
	7500 1650 7500 1550
Connection ~ 8350 1650
Wire Wire Line
	7500 1650 6850 1650
Connection ~ 7500 1650
Wire Wire Line
	6850 1700 6850 1650
Wire Wire Line
	3850 1250 5900 1250
Wire Wire Line
	5900 2300 5900 1950
Wire Wire Line
	5900 1650 5900 1250
Connection ~ 5900 1250
Wire Wire Line
	5900 1250 6850 1250
Wire Wire Line
	6850 1300 6850 1250
Connection ~ 6850 1250
Wire Wire Line
	6850 1250 7200 1250
Wire Wire Line
	6850 1600 6850 1650
Connection ~ 6850 1650
Wire Wire Line
	3850 1650 3850 1250
Wire Wire Line
	3850 2300 3850 1950
$Comp
L Device:R R10
U 1 1 5FB6F221
P 3850 5350
F 0 "R10" H 3920 5396 50  0000 L CNN
F 1 "0R" H 3920 5305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3780 5350 50  0001 C CNN
F 3 "~" H 3850 5350 50  0001 C CNN
	1    3850 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5FB7081C
P 5900 5350
F 0 "R11" H 5970 5396 50  0000 L CNN
F 1 "0R" H 5970 5305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5830 5350 50  0001 C CNN
F 3 "~" H 5900 5350 50  0001 C CNN
	1    5900 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5850 6800 5850
Wire Wire Line
	6800 5850 6800 5800
Wire Wire Line
	6800 5850 5900 5850
Wire Wire Line
	5900 5850 5900 5500
Connection ~ 6800 5850
Wire Wire Line
	5900 5850 3850 5850
Wire Wire Line
	3850 5850 3850 5500
Connection ~ 5900 5850
Wire Wire Line
	3850 5200 3850 4800
Wire Wire Line
	5900 5200 5900 4800
Wire Wire Line
	6800 5500 6800 5450
Wire Wire Line
	7800 5850 8350 5850
Connection ~ 8350 5850
Wire Wire Line
	8350 5450 7500 5450
Wire Wire Line
	7500 5450 7500 5550
Connection ~ 8350 5450
Wire Wire Line
	7500 5450 6800 5450
Connection ~ 7500 5450
Connection ~ 6800 5450
Wire Wire Line
	6800 5450 6800 5400
$Comp
L Diode_Bridge:DF06M D1
U 1 1 5FBA9D88
P 2600 3550
F 0 "D1" H 2944 3596 50  0000 L CNN
F 1 "DF06M" H 2944 3505 50  0000 L CNN
F 2 "Diode_THT:Diode_Bridge_DIP-4_W7.62mm_P5.08mm" H 2750 3675 50  0001 L CNN
F 3 "http://www.vishay.com/docs/88571/dfm.pdf" H 2600 3550 50  0001 C CNN
	1    2600 3550
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 U3
U 1 1 5FBE743C
P 7500 1250
F 0 "U3" H 7500 1492 50  0000 C CNN
F 1 "LM7805_TO220" H 7500 1401 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7500 1475 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 7500 1200 50  0001 C CNN
	1    7500 1250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7905_TO220 U4
U 1 1 5FBE979D
P 7500 5850
F 0 "U4" H 7500 5701 50  0000 C CNN
F 1 "LM7905_TO220" H 7500 5610 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7500 5650 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7905.pdf" H 7500 5850 50  0001 C CNN
	1    7500 5850
	1    0    0    -1  
$EndComp
$EndSCHEMATC