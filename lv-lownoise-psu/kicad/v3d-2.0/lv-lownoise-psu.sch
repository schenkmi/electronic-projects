EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Ultra Low Noise PSU"
Date "2021-10-15"
Rev "v3d-2.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5F959844
P 900 5000
F 0 "J2" H 818 4775 50  0000 C CNN
F 1 "GND" H 818 4866 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 900 5000 50  0001 C CNN
F 3 "~" H 900 5000 50  0001 C CNN
	1    900  5000
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5F95A600
P 11300 4300
F 0 "RV1" H 11231 4346 50  0000 R CNN
F 1 "200k" H 11231 4255 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 11300 4300 50  0001 C CNN
F 3 "~" H 11300 4300 50  0001 C CNN
	1    11300 4300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5F95CBEB
P 10000 10150
F 0 "H1" H 10100 10196 50  0000 L CNN
F 1 "MountingHole" H 10100 10105 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10000 10150 50  0001 C CNN
F 3 "~" H 10000 10150 50  0001 C CNN
	1    10000 10150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5F95D7C8
P 10900 10150
F 0 "H3" H 11000 10196 50  0000 L CNN
F 1 "MountingHole" H 11000 10105 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10900 10150 50  0001 C CNN
F 3 "~" H 10900 10150 50  0001 C CNN
	1    10900 10150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5F95D9CD
P 10000 10550
F 0 "H2" H 10100 10596 50  0000 L CNN
F 1 "MountingHole" H 10100 10505 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10000 10550 50  0001 C CNN
F 3 "~" H 10000 10550 50  0001 C CNN
	1    10000 10550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5F95DB8E
P 10900 10550
F 0 "H4" H 11000 10596 50  0000 L CNN
F 1 "MountingHole" H 11000 10505 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10900 10550 50  0001 C CNN
F 3 "~" H 10900 10550 50  0001 C CNN
	1    10900 10550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 5F95F176
P 900 4200
F 0 "J1" H 818 3975 50  0000 C CNN
F 1 "AC" H 818 4066 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 900 4200 50  0001 C CNN
F 3 "~" H 900 4200 50  0001 C CNN
	1    900  4200
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 5F95F6D2
P 900 5800
F 0 "J3" H 818 5575 50  0000 C CNN
F 1 "AC" H 818 5666 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 900 5800 50  0001 C CNN
F 3 "~" H 900 5800 50  0001 C CNN
	1    900  5800
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C1
U 1 1 5F961063
P 5500 4050
F 0 "C1" H 5618 4096 50  0000 L CNN
F 1 "2200uF" H 5618 4005 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D16.0mm_P7.50mm" H 5538 3900 50  0001 C CNN
F 3 "~" H 5500 4050 50  0001 C CNN
	1    5500 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5F96796D
P 2200 5150
F 0 "#PWR01" H 2200 4900 50  0001 C CNN
F 1 "GND" H 2205 4977 50  0000 C CNN
F 2 "" H 2200 5150 50  0001 C CNN
F 3 "" H 2200 5150 50  0001 C CNN
	1    2200 5150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 5F96866D
P 13450 4850
F 0 "J5" H 13530 4892 50  0000 L CNN
F 1 "GND" H 13530 4801 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 4850 50  0001 C CNN
F 3 "~" H 13450 4850 50  0001 C CNN
	1    13450 4850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 5F968F41
P 13450 3250
F 0 "J4" H 13530 3292 50  0000 L CNN
F 1 "+15V" H 13530 3201 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 3250 50  0001 C CNN
F 3 "~" H 13450 3250 50  0001 C CNN
	1    13450 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 5F96951B
P 13450 6550
F 0 "J6" H 13530 6592 50  0000 L CNN
F 1 "-15V" H 13530 6501 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 6550 50  0001 C CNN
F 3 "~" H 13450 6550 50  0001 C CNN
	1    13450 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	13250 3250 12550 3250
Wire Wire Line
	9700 3250 9700 3750
Wire Wire Line
	12550 3250 12550 3750
$Comp
L power:GND #PWR02
U 1 1 5F981F2D
P 5250 5000
F 0 "#PWR02" H 5250 4750 50  0001 C CNN
F 1 "GND" H 5255 4827 50  0000 C CNN
F 2 "" H 5250 5000 50  0001 C CNN
F 3 "" H 5250 5000 50  0001 C CNN
	1    5250 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5F98959C
P 5500 5700
F 0 "C2" H 5618 5746 50  0000 L CNN
F 1 "2200uF" H 5618 5655 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D16.0mm_P7.50mm" H 5538 5550 50  0001 C CNN
F 3 "~" H 5500 5700 50  0001 C CNN
	1    5500 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5150 2200 5000
$Comp
L Device:R_POT RV2
U 1 1 5FABA31D
P 11300 5350
F 0 "RV2" H 11231 5396 50  0000 R CNN
F 1 "200k" H 11231 5305 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 11300 5350 50  0001 C CNN
F 3 "~" H 11300 5350 50  0001 C CNN
	1    11300 5350
	-1   0    0    1   
$EndComp
$Comp
L Device:C C11
U 1 1 5FABDFF8
P 12050 2400
F 0 "C11" H 12165 2446 50  0000 L CNN
F 1 "100nF" H 12165 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 12088 2250 50  0001 C CNN
F 3 "~" H 12050 2400 50  0001 C CNN
	1    12050 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5FABDFFE
P 10950 2650
F 0 "#PWR03" H 10950 2400 50  0001 C CNN
F 1 "GND" H 10955 2477 50  0000 C CNN
F 2 "" H 10950 2650 50  0001 C CNN
F 3 "" H 10950 2650 50  0001 C CNN
	1    10950 2650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J9
U 1 1 5FABE004
P 13450 2200
F 0 "J9" H 13530 2242 50  0000 L CNN
F 1 "+5V" H 13530 2151 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 2200 50  0001 C CNN
F 3 "~" H 13450 2200 50  0001 C CNN
	1    13450 2200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J10
U 1 1 5FABE00A
P 13450 2600
F 0 "J10" H 13530 2642 50  0000 L CNN
F 1 "GND" H 13530 2551 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 2600 50  0001 C CNN
F 3 "~" H 13450 2600 50  0001 C CNN
	1    13450 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5FABE010
P 12550 1700
F 0 "R3" H 12620 1746 50  0000 L CNN
F 1 "240R" H 12620 1655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 12480 1700 50  0001 C CNN
F 3 "~" H 12550 1700 50  0001 C CNN
	1    12550 1700
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 5FABE016
P 13450 1700
F 0 "J7" H 13530 1742 50  0000 L CNN
F 1 "LED" H 13530 1651 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 1700 50  0001 C CNN
F 3 "~" H 13450 1700 50  0001 C CNN
	1    13450 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 5FABE01C
P 13450 1950
F 0 "J8" H 13530 1992 50  0000 L CNN
F 1 "GND" H 13530 1901 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 1950 50  0001 C CNN
F 3 "~" H 13450 1950 50  0001 C CNN
	1    13450 1950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5FABE022
P 13100 1950
F 0 "#PWR05" H 13100 1700 50  0001 C CNN
F 1 "GND" H 13105 1777 50  0000 C CNN
F 2 "" H 13100 1950 50  0001 C CNN
F 3 "" H 13100 1950 50  0001 C CNN
	1    13100 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	13250 1950 13100 1950
Wire Wire Line
	13250 1700 12700 1700
Wire Wire Line
	12400 1700 12050 1700
Wire Wire Line
	12550 2600 12550 2550
Wire Wire Line
	12550 2600 12050 2600
Wire Wire Line
	12050 2600 12050 2550
Connection ~ 12550 2600
Wire Wire Line
	12050 2250 12050 2200
Connection ~ 12050 2200
Wire Wire Line
	12050 2200 12550 2200
Wire Wire Line
	12050 2200 12050 1700
Wire Wire Line
	12550 2250 12550 2200
Connection ~ 12550 2200
Wire Wire Line
	12550 2200 13250 2200
Wire Wire Line
	12550 2600 13250 2600
$Comp
L Device:C C10
U 1 1 5FABE04B
P 10950 7350
F 0 "C10" H 11065 7396 50  0000 L CNN
F 1 "330nF" H 11065 7305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 10988 7200 50  0001 C CNN
F 3 "~" H 10950 7350 50  0001 C CNN
	1    10950 7350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5FABE051
P 12050 7350
F 0 "C12" H 12165 7396 50  0000 L CNN
F 1 "100nF" H 12165 7305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 12088 7200 50  0001 C CNN
F 3 "~" H 12050 7350 50  0001 C CNN
	1    12050 7350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5FABE057
P 10950 7100
F 0 "#PWR04" H 10950 6850 50  0001 C CNN
F 1 "GND" H 10955 6927 50  0000 C CNN
F 2 "" H 10950 7100 50  0001 C CNN
F 3 "" H 10950 7100 50  0001 C CNN
	1    10950 7100
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J11
U 1 1 5FABE05D
P 13450 7150
F 0 "J11" H 13530 7192 50  0000 L CNN
F 1 "GND" H 13530 7101 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 7150 50  0001 C CNN
F 3 "~" H 13450 7150 50  0001 C CNN
	1    13450 7150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J12
U 1 1 5FABE063
P 13450 7550
F 0 "J12" H 13530 7592 50  0000 L CNN
F 1 "-5V" H 13530 7501 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 13450 7550 50  0001 C CNN
F 3 "~" H 13450 7550 50  0001 C CNN
	1    13450 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	12550 7550 12550 7500
Wire Wire Line
	12550 7550 12050 7550
Wire Wire Line
	12050 7550 12050 7500
Connection ~ 12550 7550
Wire Wire Line
	12050 7200 12050 7150
Wire Wire Line
	12050 7150 12550 7150
Wire Wire Line
	12550 7200 12550 7150
Connection ~ 12550 7150
Wire Wire Line
	12550 7150 13250 7150
Wire Wire Line
	12550 7550 13250 7550
Wire Wire Line
	11550 2600 11550 2500
Wire Wire Line
	11850 2200 12050 2200
Wire Wire Line
	11550 2600 12050 2600
Connection ~ 12050 2600
$Comp
L Device:C C8
U 1 1 5FABDFF2
P 10950 2400
F 0 "C8" H 11065 2446 50  0000 L CNN
F 1 "330nF" H 11065 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 10988 2250 50  0001 C CNN
F 3 "~" H 10950 2400 50  0001 C CNN
	1    10950 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 2600 10950 2600
Wire Wire Line
	10950 2600 10950 2550
Connection ~ 11550 2600
Wire Wire Line
	10950 2650 10950 2600
Connection ~ 10950 2600
Wire Wire Line
	10950 2250 10950 2200
Connection ~ 10950 2200
Wire Wire Line
	10950 2200 11250 2200
Wire Wire Line
	11850 7550 12050 7550
Connection ~ 12050 7550
Wire Wire Line
	12050 7150 11550 7150
Wire Wire Line
	11550 7150 11550 7250
Connection ~ 12050 7150
Wire Wire Line
	11250 7550 10950 7550
Wire Wire Line
	10950 7550 10950 7500
Wire Wire Line
	10950 7200 10950 7150
Wire Wire Line
	11550 7150 10950 7150
Connection ~ 11550 7150
Connection ~ 10950 7150
Wire Wire Line
	10950 7150 10950 7100
$Comp
L Device:CP C17
U 1 1 5FE98FC2
P 12550 3900
F 0 "C17" H 12668 3946 50  0000 L CNN
F 1 "33uF" H 12668 3855 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D_Pad2.25x2.55mm_HandSolder" H 12588 3750 50  0001 C CNN
F 3 "~" H 12550 3900 50  0001 C CNN
	1    12550 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C18
U 1 1 5FEBD2E5
P 12550 5700
F 0 "C18" H 12668 5746 50  0000 L CNN
F 1 "33uF" H 12668 5655 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D_Pad2.25x2.55mm_HandSolder" H 12588 5550 50  0001 C CNN
F 3 "~" H 12550 5700 50  0001 C CNN
	1    12550 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:D D1
U 1 1 5FEDADDC
P 3250 4650
F 0 "D1" V 3204 4730 50  0000 L CNN
F 1 "BYG20D" V 3295 4730 50  0000 L CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 3250 4650 50  0001 C CNN
F 3 "~" H 3250 4650 50  0001 C CNN
	1    3250 4650
	0    1    1    0   
$EndComp
$Comp
L Device:D D2
U 1 1 5FEFA226
P 3250 5050
F 0 "D2" V 3296 4970 50  0000 R CNN
F 1 "BYG20D" V 3205 4970 50  0000 R CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 3250 5050 50  0001 C CNN
F 3 "~" H 3250 5050 50  0001 C CNN
	1    3250 5050
	0    -1   -1   0   
$EndComp
$Comp
L Device:D D3
U 1 1 5FEFB2AB
P 3800 4650
F 0 "D3" V 3846 4570 50  0000 R CNN
F 1 "BYG20D" V 3755 4570 50  0000 R CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 3800 4650 50  0001 C CNN
F 3 "~" H 3800 4650 50  0001 C CNN
	1    3800 4650
	0    -1   -1   0   
$EndComp
$Comp
L Device:D D4
U 1 1 5FF083C7
P 3800 5050
F 0 "D4" V 3754 5130 50  0000 L CNN
F 1 "BYG20D" V 3845 5130 50  0000 L CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 3800 5050 50  0001 C CNN
F 3 "~" H 3800 5050 50  0001 C CNN
	1    3800 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 5200 3250 5250
Wire Wire Line
	3250 5250 3550 5250
Wire Wire Line
	3800 5250 3800 5200
Wire Wire Line
	3800 4500 3800 4450
Wire Wire Line
	3800 4450 3550 4450
Wire Wire Line
	3250 4450 3250 4500
Wire Wire Line
	5250 5000 5250 4850
Wire Wire Line
	3550 4200 3550 4450
Connection ~ 3550 4450
Wire Wire Line
	3550 4450 3250 4450
Connection ~ 3550 5250
Wire Wire Line
	3550 5250 3800 5250
$Comp
L Regulator_Linear:LM7805_TO220 U1
U 1 1 600F2C85
P 11550 2200
F 0 "U1" H 11550 2442 50  0000 C CNN
F 1 "LM7805_TO220" H 11550 2351 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 11550 2425 50  0001 C CIN
F 3 "https://www.onsemi.cn/PowerSolutions/document/MC7800-D.PDF" H 11550 2150 50  0001 C CNN
	1    11550 2200
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7905_TO220 U2
U 1 1 600F43DF
P 11550 7550
F 0 "U2" H 11550 7401 50  0000 C CNN
F 1 "LM7905_TO220" H 11550 7310 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 11550 7350 50  0001 C CIN
F 3 "https://www.onsemi.com/pub/Collateral/MC7900-D.PDF" H 11550 7550 50  0001 C CNN
	1    11550 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4800 3800 4850
Wire Wire Line
	3250 4800 3250 4850
$Comp
L Device:C C3
U 1 1 613D53B2
P 1250 4550
F 0 "C3" H 1100 4650 50  0000 L CNN
F 1 "Cx/10nF/50V" V 1400 4300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1288 4400 50  0001 C CNN
F 3 "~" H 1250 4550 50  0001 C CNN
	1    1250 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 613D6164
P 1250 5400
F 0 "C4" H 1100 5500 50  0000 L CNN
F 1 "Cx/10nF/50V" V 1400 5150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1288 5250 50  0001 C CNN
F 3 "~" H 1250 5400 50  0001 C CNN
	1    1250 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 613D6591
P 1650 4400
F 0 "C5" H 1765 4446 50  0000 L CNN
F 1 "Cs/50V" H 1765 4355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1688 4250 50  0001 C CNN
F 3 "~" H 1650 4400 50  0001 C CNN
	1    1650 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 613D6A45
P 1650 4750
F 0 "R5" H 1720 4796 50  0000 L CNN
F 1 "Rs/1/8W" H 1720 4705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1580 4750 50  0001 C CNN
F 3 "~" H 1650 4750 50  0001 C CNN
	1    1650 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 613D8B5F
P 1650 5250
F 0 "C6" H 1765 5296 50  0000 L CNN
F 1 "Cs/50V" H 1765 5205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1688 5100 50  0001 C CNN
F 3 "~" H 1650 5250 50  0001 C CNN
	1    1650 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 613D93AB
P 1650 5600
F 0 "R6" H 1720 5646 50  0000 L CNN
F 1 "Rs/1/8W" H 1720 5555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1580 5600 50  0001 C CNN
F 3 "~" H 1650 5600 50  0001 C CNN
	1    1650 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 5000 1250 5000
Wire Wire Line
	1650 5000 1650 4900
Wire Wire Line
	1650 5100 1650 5000
Connection ~ 1650 5000
Wire Wire Line
	1650 5000 2200 5000
Wire Wire Line
	1650 4250 1650 4200
Wire Wire Line
	1650 4200 1250 4200
Wire Wire Line
	1100 5800 1250 5800
Wire Wire Line
	1650 5800 1650 5750
Wire Wire Line
	1250 5250 1250 5000
Connection ~ 1250 5000
Wire Wire Line
	1250 5000 1650 5000
Wire Wire Line
	1250 5550 1250 5800
Connection ~ 1250 5800
Wire Wire Line
	1250 5800 1650 5800
Wire Wire Line
	1250 4700 1250 5000
Wire Wire Line
	1250 4400 1250 4200
Connection ~ 1250 4200
Wire Wire Line
	1250 4200 1100 4200
Wire Wire Line
	1650 4600 1650 4550
Wire Wire Line
	1650 5450 1650 5400
Text Notes 1100 4000 0    50   ~ 0
Snubber
Text Notes 1100 6100 0    50   ~ 0
Cs=100nF/50\nRs=25.8R/0.125W
Wire Notes Line
	1100 4100 2050 4100
Wire Notes Line
	2050 4100 2050 5900
Wire Notes Line
	2050 5900 1100 5900
Wire Notes Line
	1100 5900 1100 4100
$Comp
L Diode:Z1SMAxxx D5
U 1 1 613ACE63
P 7350 3900
F 0 "D5" V 7304 3980 50  0000 L CNN
F 1 "MMSZ5232B/5.6V" V 7395 3980 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 7350 3725 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/z1sma1.pdf" H 7350 3900 50  0001 C CNN
	1    7350 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 613AF448
P 7350 3500
F 0 "R7" H 7420 3546 50  0000 L CNN
F 1 "430R/0.6W" H 7420 3455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7280 3500 50  0001 C CNN
F 3 "~" H 7350 3500 50  0001 C CNN
	1    7350 3500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BD139 Q1
U 1 1 613B0ED5
P 8200 3350
F 0 "Q1" V 8529 3350 50  0000 C CNN
F 1 "BD139" V 8438 3350 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-126-3_Vertical" H 8400 3275 50  0001 L CIN
F 3 "http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00001225.pdf" H 8200 3350 50  0001 L CNN
	1    8200 3350
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C7
U 1 1 613B1E1A
P 8200 3900
F 0 "C7" H 8315 3946 50  0000 L CNN
F 1 "4.7uF/50V" H 8315 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 8238 3750 50  0001 C CNN
F 3 "~" H 8200 3900 50  0001 C CNN
	1    8200 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3750 7350 3700
Connection ~ 7350 3700
Wire Wire Line
	7350 3700 7350 3650
Wire Wire Line
	8200 3700 8200 3550
Wire Wire Line
	7350 3700 8200 3700
Wire Wire Line
	8200 3700 8200 3750
Connection ~ 8200 3700
Wire Wire Line
	8000 3250 7350 3250
Wire Wire Line
	7350 3250 7350 3350
$Comp
L Transistor_BJT:BD140 Q2
U 1 1 613FC744
P 8200 6450
F 0 "Q2" V 8437 6450 50  0000 C CNN
F 1 "BD140" V 8528 6450 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-126-3_Vertical" H 8400 6375 50  0001 L CIN
F 3 "http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00001225.pdf" H 8200 6450 50  0001 L CNN
	1    8200 6450
	0    -1   1    0   
$EndComp
$Comp
L Diode:Z1SMAxxx D6
U 1 1 61438832
P 7350 5800
F 0 "D6" V 7304 5880 50  0000 L CNN
F 1 "MMSZ5232B/5.6V" V 7395 5880 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 7350 5625 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/z1sma1.pdf" H 7350 5800 50  0001 C CNN
	1    7350 5800
	0    1    1    0   
$EndComp
$Comp
L Device:C C9
U 1 1 6143A1DA
P 8200 5900
F 0 "C9" H 8315 5946 50  0000 L CNN
F 1 "4.7uF/50V" H 8315 5855 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 8238 5750 50  0001 C CNN
F 3 "~" H 8200 5900 50  0001 C CNN
	1    8200 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3250 7350 2200
Wire Wire Line
	7350 2200 10950 2200
Connection ~ 7350 3250
Wire Wire Line
	7350 6150 7350 6100
Wire Wire Line
	8200 6050 8200 6100
$Comp
L Device:R R8
U 1 1 6143946E
P 7350 6300
F 0 "R8" H 7420 6346 50  0000 L CNN
F 1 "430R/0.6W" H 7420 6255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7280 6300 50  0001 C CNN
F 3 "~" H 7350 6300 50  0001 C CNN
	1    7350 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 6100 8200 6100
Connection ~ 7350 6100
Wire Wire Line
	7350 6100 7350 5950
Connection ~ 8200 6100
Wire Wire Line
	8200 6100 8200 6250
Wire Wire Line
	8000 6550 7350 6550
Wire Wire Line
	7350 6550 7350 6450
Wire Wire Line
	10950 7550 7350 7550
Wire Wire Line
	7350 7550 7350 6550
Connection ~ 10950 7550
Connection ~ 7350 6550
Wire Wire Line
	3800 4850 4900 4850
Connection ~ 3800 4850
Wire Wire Line
	3800 4850 3800 4900
Wire Wire Line
	2850 4850 3250 4850
Connection ~ 3250 4850
Wire Wire Line
	3250 4850 3250 4900
Wire Wire Line
	1650 4200 3550 4200
Connection ~ 1650 4200
Wire Wire Line
	1650 5800 3550 5800
Wire Wire Line
	3550 5250 3550 5800
Connection ~ 1650 5800
Wire Wire Line
	7350 3250 6500 3250
Wire Wire Line
	7350 6550 6500 6550
$Comp
L Device:C C13
U 1 1 613EABD6
P 12550 2400
F 0 "C13" H 12665 2446 50  0000 L CNN
F 1 "10uF/25V" H 12665 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 12588 2250 50  0001 C CNN
F 3 "~" H 12550 2400 50  0001 C CNN
	1    12550 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 613EB46E
P 12550 7350
F 0 "C14" H 12665 7396 50  0000 L CNN
F 1 "10uF/25V" H 12665 7305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 12588 7200 50  0001 C CNN
F 3 "~" H 12550 7350 50  0001 C CNN
	1    12550 7350
	1    0    0    -1  
$EndComp
$Comp
L Diode:Z1SMAxxx D7
U 1 1 6147D653
P 7350 4250
F 0 "D7" V 7304 4330 50  0000 L CNN
F 1 "MMSZ5232B/5.6V" V 7395 4330 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 7350 4075 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/z1sma1.pdf" H 7350 4250 50  0001 C CNN
	1    7350 4250
	0    1    1    0   
$EndComp
$Comp
L Diode:Z1SMAxxx D8
U 1 1 6147DF30
P 7350 4600
F 0 "D8" V 7304 4680 50  0000 L CNN
F 1 "MMSZ5232B/5.6V" V 7395 4680 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 7350 4425 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/z1sma1.pdf" H 7350 4600 50  0001 C CNN
	1    7350 4600
	0    1    1    0   
$EndComp
$Comp
L Diode:Z1SMAxxx D10
U 1 1 6148EEA1
P 7350 5450
F 0 "D10" V 7304 5530 50  0000 L CNN
F 1 "MMSZ5232B/5.6V" V 7395 5530 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 7350 5275 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/z1sma1.pdf" H 7350 5450 50  0001 C CNN
	1    7350 5450
	0    1    1    0   
$EndComp
$Comp
L Diode:Z1SMAxxx D9
U 1 1 6148F85C
P 7350 5100
F 0 "D9" V 7304 5180 50  0000 L CNN
F 1 "MMSZ5232B/5.6V" V 7395 5180 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 7350 4925 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/z1sma1.pdf" H 7350 5100 50  0001 C CNN
	1    7350 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 4850 4900 3250
Wire Wire Line
	2850 4850 2850 6550
Wire Wire Line
	7350 4100 7350 4050
Wire Wire Line
	7350 4450 7350 4400
Wire Wire Line
	7350 4750 7350 4850
Connection ~ 7350 4850
Wire Wire Line
	7350 4850 8200 4850
Wire Wire Line
	7350 4950 7350 4850
Wire Wire Line
	7350 5300 7350 5250
Wire Wire Line
	7350 5650 7350 5600
Wire Wire Line
	8200 4850 8200 5750
Connection ~ 8200 4850
Wire Wire Line
	8200 4050 8200 4850
Wire Wire Line
	9700 4050 9700 4850
Connection ~ 9700 4850
Connection ~ 11550 4850
Wire Wire Line
	11550 4850 11800 4850
Connection ~ 12550 4850
Wire Wire Line
	12550 4850 13250 4850
Wire Wire Line
	12550 4050 12550 4850
$Comp
L Device:CP C15
U 1 1 617F78DD
P 9700 3900
F 0 "C15" H 9818 3946 50  0000 L CNN
F 1 "4.7uF/35V" H 9818 3855 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-15_AVX-H_Pad1.50x2.35mm_HandSolder" H 9738 3750 50  0001 C CNN
F 3 "~" H 9700 3900 50  0001 C CNN
	1    9700 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C16
U 1 1 618163AA
P 10450 4300
F 0 "C16" H 10568 4346 50  0000 L CNN
F 1 "4.7uF/35V" H 10568 4255 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-15_AVX-H_Pad1.50x2.35mm_HandSolder" H 10488 4150 50  0001 C CNN
F 3 "~" H 10450 4300 50  0001 C CNN
	1    10450 4300
	1    0    0    -1  
$EndComp
$Comp
L kicad-snk:LT3045xDD-10DFN U3
U 1 1 6183CF0D
P 11550 3350
F 0 "U3" H 11550 3787 60  0000 C CNN
F 1 "LT3045xDD-10DFN" H 11550 3681 60  0000 C CNN
F 2 "Package_DFN_QFN:DFN-10-1EP_3x3mm_P0.5mm_EP1.65x2.38mm" H 11550 3850 60  0001 C CNN
F 3 "https://cds.linear.com/docs/en/datasheet/3045f.pdf" H 11550 3700 60  0001 C CNN
F 4 "Linear Technology" H 12300 3000 60  0001 C CNN "MFN"
F 5 "LT3045EDD" H 12150 2850 60  0001 C CNN "MFP"
	1    11550 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11300 3850 10450 3850
Connection ~ 11300 3850
Wire Wire Line
	11300 3850 11300 3800
Wire Wire Line
	10800 3250 10600 3250
Wire Wire Line
	10800 3350 10600 3350
Wire Wire Line
	10600 3350 10600 3250
Connection ~ 10600 3250
Wire Wire Line
	10600 3250 9700 3250
Wire Wire Line
	10800 3450 10600 3450
Wire Wire Line
	10600 3450 10600 3350
Connection ~ 10600 3350
Wire Wire Line
	12300 3250 12400 3250
Connection ~ 12550 3250
Wire Wire Line
	12300 3350 12400 3350
Wire Wire Line
	12400 3350 12400 3250
Connection ~ 12400 3250
Wire Wire Line
	12400 3250 12550 3250
NoConn ~ 12300 3450
Wire Wire Line
	11550 3800 11550 4850
Wire Wire Line
	11800 3800 11800 4850
Connection ~ 11800 4850
Wire Wire Line
	9700 4850 10450 4850
Wire Wire Line
	10450 4150 10450 3850
Wire Wire Line
	10450 4450 10450 4850
Connection ~ 10450 4850
Wire Wire Line
	11300 3850 11300 4150
Wire Wire Line
	11300 4450 11300 4500
Connection ~ 11300 4850
Wire Wire Line
	11300 4850 11550 4850
Wire Wire Line
	11450 4300 11500 4300
Wire Wire Line
	11500 4300 11500 4500
Wire Wire Line
	11500 4500 11300 4500
Connection ~ 11300 4500
Wire Wire Line
	11300 4500 11300 4850
Connection ~ 9700 3250
Wire Wire Line
	8400 3250 9700 3250
$Comp
L kicad-snk:LT3094xDD-12DFN U4
U 1 1 61AA6ED2
P 11550 6450
F 0 "U4" H 11550 6781 60  0000 C CNN
F 1 "LT3094xDD-12DFN" H 11550 6887 60  0000 C CNN
F 2 "Package_DFN_QFN:DFN-12-1EP_3x3mm_P0.45mm_EP1.66x2.38mm" H 11550 6950 60  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/LT3094.pdf" H 11550 6800 60  0001 C CNN
F 4 "Linear Technology" H 12300 6100 60  0001 C CNN "MFN"
F 5 "LT3094IDD" H 12150 5950 60  0001 C CNN "MFP"
	1    11550 6450
	1    0    0    1   
$EndComp
Wire Wire Line
	11800 4850 12550 4850
NoConn ~ 12300 6350
NoConn ~ 10800 6250
Wire Wire Line
	12300 6550 12400 6550
Wire Wire Line
	12300 6450 12400 6450
Wire Wire Line
	12400 6450 12400 6550
Connection ~ 12400 6550
Wire Wire Line
	11800 6000 11800 4850
Wire Wire Line
	11550 6000 11550 4850
Wire Wire Line
	10450 4850 11300 4850
$Comp
L Device:CP C20
U 1 1 61B9B8EB
P 10450 5350
F 0 "C20" H 10568 5396 50  0000 L CNN
F 1 "4.7uF/35V" H 10568 5305 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-15_AVX-H_Pad1.50x2.35mm_HandSolder" H 10488 5200 50  0001 C CNN
F 3 "~" H 10450 5350 50  0001 C CNN
	1    10450 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4850 9700 4850
$Comp
L Device:CP C19
U 1 1 61BBE72E
P 9700 5750
F 0 "C19" H 9818 5796 50  0000 L CNN
F 1 "4.7uF/35V" H 9818 5705 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-15_AVX-H_Pad1.50x2.35mm_HandSolder" H 9738 5600 50  0001 C CNN
F 3 "~" H 9700 5750 50  0001 C CNN
	1    9700 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	12400 6550 12550 6550
Wire Wire Line
	12550 5850 12550 6550
Connection ~ 12550 6550
Wire Wire Line
	12550 6550 13250 6550
Wire Wire Line
	12550 5550 12550 4850
Wire Wire Line
	11300 6000 11300 5950
Wire Wire Line
	11300 5200 11300 5100
Wire Wire Line
	11150 5350 11100 5350
Wire Wire Line
	11100 5350 11100 5100
Wire Wire Line
	11100 5100 11300 5100
Connection ~ 11300 5100
Wire Wire Line
	11300 5100 11300 4850
Wire Wire Line
	10450 5500 10450 5950
Wire Wire Line
	10450 5950 11300 5950
Connection ~ 11300 5950
Wire Wire Line
	11300 5950 11300 5500
Wire Wire Line
	10450 5200 10450 4850
Wire Wire Line
	10800 6550 10550 6550
Wire Wire Line
	10800 6450 10550 6450
Wire Wire Line
	10550 6450 10550 6550
Connection ~ 10550 6550
Wire Wire Line
	10550 6550 9700 6550
Wire Wire Line
	10800 6350 10550 6350
Wire Wire Line
	10550 6350 10550 6450
Connection ~ 10550 6450
Wire Wire Line
	9700 5900 9700 6550
Connection ~ 9700 6550
Wire Wire Line
	9700 6550 8400 6550
Wire Wire Line
	9700 5600 9700 4850
$Comp
L Device:C C21
U 1 1 61CA4EC6
P 6500 4050
F 0 "C21" H 6615 4096 50  0000 L CNN
F 1 "4.7uF/50V" H 6615 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 6538 3900 50  0001 C CNN
F 3 "~" H 6500 4050 50  0001 C CNN
	1    6500 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C22
U 1 1 61CA5321
P 6500 5700
F 0 "C22" H 6615 5746 50  0000 L CNN
F 1 "4.7uF/50V" H 6615 5655 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 6538 5550 50  0001 C CNN
F 3 "~" H 6500 5700 50  0001 C CNN
	1    6500 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4200 6500 4850
Connection ~ 6500 4850
Wire Wire Line
	6500 4850 7350 4850
Wire Wire Line
	6500 3900 6500 3250
Connection ~ 6500 3250
Wire Wire Line
	6500 5550 6500 4850
Wire Wire Line
	6500 5850 6500 6550
Connection ~ 6500 6550
Wire Wire Line
	2850 6550 5500 6550
Wire Wire Line
	5250 4850 5500 4850
Wire Wire Line
	4900 3250 5500 3250
Wire Wire Line
	5500 4200 5500 4850
Connection ~ 5500 4850
Wire Wire Line
	5500 4850 6500 4850
Wire Wire Line
	5500 5550 5500 4850
Wire Wire Line
	5500 3900 5500 3250
Connection ~ 5500 3250
Wire Wire Line
	5500 3250 6500 3250
Wire Wire Line
	5500 5850 5500 6550
Connection ~ 5500 6550
Wire Wire Line
	5500 6550 6500 6550
$EndSCHEMATC
