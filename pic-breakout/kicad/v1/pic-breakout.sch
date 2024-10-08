EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "PIC Break-Out Board"
Date "2021-05-24"
Rev "V1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6086F7A2
P 3600 10150
F 0 "#FLG0101" H 3600 10225 50  0001 C CNN
F 1 "PWR_FLAG" H 3600 10323 50  0000 C CNN
F 2 "" H 3600 10150 50  0001 C CNN
F 3 "~" H 3600 10150 50  0001 C CNN
	1    3600 10150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 9300 5950 9300
Wire Wire Line
	5950 9300 5950 10150
$Comp
L Regulator_Linear:TC1017-xCT U2
U 1 1 6086F7C0
P 4750 10250
F 0 "U2" H 4750 10617 50  0000 C CNN
F 1 "TC1185-5.0VCT713" H 4750 10526 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 4500 10600 50  0001 L CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21813F.pdf" H 4750 10150 50  0001 C CNN
	1    4750 10250
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 6086F7D2
P 5350 10400
F 0 "C6" H 5468 10446 50  0000 L CNN
F 1 "10uF/10V" H 5468 10355 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 5388 10250 50  0001 C CNN
F 3 "~" H 5350 10400 50  0001 C CNN
	1    5350 10400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 6086F7D9
P 3900 10400
F 0 "C5" H 4018 10446 50  0000 L CNN
F 1 "10uF/10V" H 4018 10355 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 3938 10250 50  0001 C CNN
F 3 "~" H 3900 10400 50  0001 C CNN
	1    3900 10400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 10250 4250 10250
Wire Wire Line
	4250 10250 4250 10150
Wire Wire Line
	3600 10150 3900 10150
Wire Wire Line
	3900 10250 3900 10150
Wire Wire Line
	4250 10150 4350 10150
Connection ~ 4250 10150
Wire Wire Line
	3900 10550 3900 10700
Wire Wire Line
	4750 10700 4750 10550
Wire Wire Line
	4750 10700 5350 10700
Wire Wire Line
	5350 10700 5350 10550
Connection ~ 4750 10700
Wire Wire Line
	5150 10150 5350 10150
Wire Wire Line
	5350 10250 5350 10150
Connection ~ 5350 10150
Wire Wire Line
	5350 10150 5950 10150
$Comp
L power:GND #PWR0122
U 1 1 6086F7F1
P 4750 10800
F 0 "#PWR0122" H 4750 10550 50  0001 C CNN
F 1 "GND" H 4755 10627 50  0000 C CNN
F 2 "" H 4750 10800 50  0001 C CNN
F 3 "" H 4750 10800 50  0001 C CNN
	1    4750 10800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 10800 4750 10700
$Comp
L power:GND #PWR0101
U 1 1 60831977
P 11900 3950
F 0 "#PWR0101" H 11900 3700 50  0001 C CNN
F 1 "GND" H 11905 3777 50  0000 C CNN
F 2 "" H 11900 3950 50  0001 C CNN
F 3 "" H 11900 3950 50  0001 C CNN
	1    11900 3950
	-1   0    0    1   
$EndComp
Text GLabel 3150 10150 0    50   Input ~ 0
VCCIN
Text GLabel 5400 9300 0    50   BiDi ~ 0
VCCOUT
Wire Wire Line
	3150 10150 3600 10150
Connection ~ 3600 10150
$Comp
L Device:C C8
U 1 1 60AF88EA
P 5700 3000
F 0 "C8" H 5815 3046 50  0000 L CNN
F 1 "100nF" H 5815 2955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5738 2850 50  0001 C CNN
F 3 "~" H 5700 3000 50  0001 C CNN
F 4 "CL10B104KB8NNNL" H 5815 3146 50  0001 C CNN "manf#"
	1    5700 3000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60AF88F0
P 5300 5450
F 0 "#PWR0102" H 5300 5200 50  0001 C CNN
F 1 "GND" H 5305 5277 50  0000 C CNN
F 2 "" H 5300 5450 50  0001 C CNN
F 3 "" H 5300 5450 50  0001 C CNN
	1    5300 5450
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 60AF88F6
P 5300 5300
F 0 "#FLG0102" H 5300 5375 50  0001 C CNN
F 1 "PWR_FLAG" V 5300 5428 50  0000 L CNN
F 2 "" H 5300 5300 50  0001 C CNN
F 3 "~" H 5300 5300 50  0001 C CNN
	1    5300 5300
	0    1    1    0   
$EndComp
$Comp
L MCU_Microchip_PIC16:PIC16F1829-IP U3
U 1 1 60AF88FD
P 5300 4400
F 0 "U3" H 4400 5200 50  0000 C CNN
F 1 "PIC16F18446T-I/SS" H 5900 5200 50  0000 C CNN
F 2 "Package_SO:SSOP-20_5.3x7.2mm_P0.65mm" H 5300 3850 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/41440C.pdf" H 5300 3850 50  0001 C CNN
F 4 "PIC16F18446-I/SO" H 4400 5300 50  0001 C CNN "manf#"
	1    5300 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 60AF8904
P 3250 5200
F 0 "R4" V 3043 5200 50  0000 C CNN
F 1 "4K99" V 3134 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3180 5200 50  0001 C CNN
F 3 "~" H 3250 5200 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 3043 5300 50  0001 C CNN "manf#"
	1    3250 5200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 60AF890B
P 3600 5200
F 0 "R5" V 3393 5200 50  0000 C CNN
F 1 "4K99" V 3484 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3530 5200 50  0001 C CNN
F 3 "~" H 3600 5200 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 3393 5300 50  0001 C CNN "manf#"
	1    3600 5200
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Male J4
U 1 1 60AF891D
P 3750 3000
F 0 "J4" V 3812 3244 50  0000 L CNN
F 1 "Conn_01x06_Male" V 3903 3244 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3750 3000 50  0001 C CNN
F 3 "~" H 3750 3000 50  0001 C CNN
	1    3750 3000
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 60AF8929
P 3750 3300
F 0 "#PWR0117" H 3750 3050 50  0001 C CNN
F 1 "GND" H 3755 3127 50  0000 C CNN
F 2 "" H 3750 3300 50  0001 C CNN
F 3 "" H 3750 3300 50  0001 C CNN
	1    3750 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 60AF8936
P 5700 3300
F 0 "#PWR0118" H 5700 3050 50  0001 C CNN
F 1 "GND" H 5705 3127 50  0000 C CNN
F 2 "" H 5700 3300 50  0001 C CNN
F 3 "" H 5700 3300 50  0001 C CNN
	1    5700 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 60AF8943
P 7200 5250
F 0 "D2" H 7193 5467 50  0000 C CNN
F 1 "LED" H 7193 5376 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 5250 50  0001 C CNN
F 3 "~" H 7200 5250 50  0001 C CNN
F 4 "LG R971-KN-1" H 7193 5567 50  0001 C CNN "manf#"
	1    7200 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 60AF894A
P 7200 5650
F 0 "D3" H 7193 5867 50  0000 C CNN
F 1 "LED" H 7193 5776 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 5650 50  0001 C CNN
F 3 "~" H 7200 5650 50  0001 C CNN
F 4 "LG R971-KN-1" H 7193 5967 50  0001 C CNN "manf#"
	1    7200 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 60AF8951
P 7750 5250
F 0 "R7" V 7543 5250 50  0000 C CNN
F 1 "330R" V 7634 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7680 5250 50  0001 C CNN
F 3 "~" H 7750 5250 50  0001 C CNN
F 4 "RT0603FRD07330RL" H 7543 5350 50  0001 C CNN "manf#"
	1    7750 5250
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 60AF8958
P 7750 5650
F 0 "R8" V 7543 5650 50  0000 C CNN
F 1 "330R" V 7634 5650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7680 5650 50  0001 C CNN
F 3 "~" H 7750 5650 50  0001 C CNN
F 4 "RT0603FRD07330RL" H 7543 5750 50  0001 C CNN "manf#"
	1    7750 5650
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 60AF896B
P 1800 5200
F 0 "R1" V 1593 5200 50  0000 C CNN
F 1 "4K99" V 1684 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1730 5200 50  0001 C CNN
F 3 "~" H 1800 5200 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 1593 5300 50  0001 C CNN "manf#"
	1    1800 5200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 60AF8972
P 2150 5200
F 0 "R3" V 1943 5200 50  0000 C CNN
F 1 "4K99" V 2034 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2080 5200 50  0001 C CNN
F 3 "~" H 2150 5200 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 1943 5300 50  0001 C CNN "manf#"
	1    2150 5200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 60AF8986
P 1900 3500
F 0 "R2" V 1693 3500 50  0000 C CNN
F 1 "4k99" V 1784 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1830 3500 50  0001 C CNN
F 3 "~" H 1900 3500 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 1693 3600 50  0001 C CNN "manf#"
	1    1900 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 60AF898D
P 1900 3900
F 0 "C7" H 2015 3946 50  0000 L CNN
F 1 "10nF" H 2015 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1938 3750 50  0001 C CNN
F 3 "~" H 1900 3900 50  0001 C CNN
F 4 "CL10B103KB8NNNC" H 2015 4046 50  0001 C CNN "manf#"
	1    1900 3900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148W D1
U 1 1 60AF8994
P 2450 3700
F 0 "D1" V 2404 3780 50  0000 L CNN
F 1 "1N4148W" V 2495 3780 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 2450 3525 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2450 3700 50  0001 C CNN
F 4 "1N4148W-7-F" H 2404 3880 50  0001 C CNN "manf#"
	1    2450 3700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 60AF899A
P 1900 4100
F 0 "#PWR0124" H 1900 3850 50  0001 C CNN
F 1 "GND" H 1905 3927 50  0000 C CNN
F 2 "" H 1900 4100 50  0001 C CNN
F 3 "" H 1900 4100 50  0001 C CNN
	1    1900 4100
	1    0    0    -1  
$EndComp
Text GLabel 2950 4600 0    50   BiDi ~ 0
RB4-SDA
Text GLabel 2950 4800 0    50   BiDi ~ 0
RB6-SCL
Text GLabel 4050 4300 0    50   BiDi ~ 0
RA4
Text GLabel 4050 4400 0    50   BiDi ~ 0
RA5
Text GLabel 1200 4900 0    50   BiDi ~ 0
RB7-SDA2
Text GLabel 1200 4700 0    50   BiDi ~ 0
RB5-SCL2
Wire Wire Line
	5300 5450 5300 5300
Wire Wire Line
	5300 5300 5300 5200
Wire Wire Line
	2950 4600 3600 4600
Wire Wire Line
	2950 4800 3250 4800
Wire Wire Line
	3600 5050 3600 4600
Wire Wire Line
	3600 4600 4200 4600
Wire Wire Line
	3250 5050 3250 4800
Wire Wire Line
	2850 5550 2850 5600
Wire Wire Line
	2850 5600 3250 5600
Wire Wire Line
	3600 5600 3600 5350
Wire Wire Line
	3250 5350 3250 5600
Wire Wire Line
	3250 5600 3600 5600
Wire Wire Line
	5700 3300 5700 3150
Wire Wire Line
	5700 2750 5700 2850
Wire Wire Line
	5300 2750 5300 3500
Wire Wire Line
	4050 4300 4200 4300
Wire Wire Line
	4050 4400 4200 4400
Wire Wire Line
	7350 5250 7600 5250
Wire Wire Line
	7900 5250 8300 5250
Wire Wire Line
	8300 5250 8300 5150
Wire Wire Line
	7350 5650 7600 5650
Wire Wire Line
	7900 5650 8300 5650
Wire Wire Line
	8300 5650 8300 5550
Wire Wire Line
	6750 5250 7050 5250
Wire Wire Line
	7050 5650 6650 5650
Wire Wire Line
	1400 5550 1400 5600
Wire Wire Line
	1400 5600 1800 5600
Wire Wire Line
	2150 5600 2150 5350
Wire Wire Line
	1800 5350 1800 5600
Wire Wire Line
	1800 5600 2150 5600
Wire Wire Line
	4200 4700 2150 4700
Wire Wire Line
	1200 4900 1800 4900
Wire Wire Line
	2150 5050 2150 4700
Wire Wire Line
	1800 5050 1800 4900
Wire Wire Line
	1800 4900 4200 4900
Wire Wire Line
	1200 4700 2150 4700
Wire Wire Line
	1900 3350 1900 3300
Wire Wire Line
	1900 3750 1900 3700
Wire Wire Line
	1900 4100 1900 4050
Wire Wire Line
	2300 3700 1900 3700
Wire Wire Line
	1900 3700 1900 3650
Wire Wire Line
	6300 2700 6300 2750
Wire Wire Line
	5700 2750 5300 2750
Wire Wire Line
	4200 3900 3850 3900
Wire Wire Line
	3850 3900 3850 3200
Wire Wire Line
	4200 4000 3950 4000
Wire Wire Line
	3950 4000 3950 3200
Wire Wire Line
	3750 3300 3750 3200
Wire Wire Line
	3650 3450 3650 3200
Wire Wire Line
	3550 3200 3550 3700
Wire Wire Line
	3550 4200 4200 4200
Wire Wire Line
	3250 4800 4200 4800
Wire Wire Line
	2600 3700 3550 3700
Wire Wire Line
	3550 3700 3550 4200
Connection ~ 5300 5300
Connection ~ 3600 4600
Connection ~ 3250 4800
Connection ~ 3250 5600
Connection ~ 1800 5600
Connection ~ 2150 4700
Connection ~ 1800 4900
Connection ~ 1900 3700
Connection ~ 5700 2750
Connection ~ 3550 3700
NoConn ~ 4050 3200
$Comp
L power:VCC #PWR0128
U 1 1 60C1E900
P 6350 10050
F 0 "#PWR0128" H 6350 9900 50  0001 C CNN
F 1 "VCC" H 6365 10223 50  0000 C CNN
F 2 "" H 6350 10050 50  0001 C CNN
F 3 "" H 6350 10050 50  0001 C CNN
	1    6350 10050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 10050 6350 10150
Wire Wire Line
	6350 10150 5950 10150
Connection ~ 5950 10150
$Comp
L power:VCC #PWR0103
U 1 1 60ACA1FA
P 1400 5550
F 0 "#PWR0103" H 1400 5400 50  0001 C CNN
F 1 "VCC" H 1415 5723 50  0000 C CNN
F 2 "" H 1400 5550 50  0001 C CNN
F 3 "" H 1400 5550 50  0001 C CNN
	1    1400 5550
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0115
U 1 1 60AE09F7
P 2850 5550
F 0 "#PWR0115" H 2850 5400 50  0001 C CNN
F 1 "VCC" H 2865 5723 50  0000 C CNN
F 2 "" H 2850 5550 50  0001 C CNN
F 3 "" H 2850 5550 50  0001 C CNN
	1    2850 5550
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0116
U 1 1 60AEBC36
P 1900 3300
F 0 "#PWR0116" H 1900 3150 50  0001 C CNN
F 1 "VCC" H 1915 3473 50  0000 C CNN
F 2 "" H 1900 3300 50  0001 C CNN
F 3 "" H 1900 3300 50  0001 C CNN
	1    1900 3300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0119
U 1 1 60AF7A65
P 3650 3450
F 0 "#PWR0119" H 3650 3300 50  0001 C CNN
F 1 "VCC" H 3665 3623 50  0000 C CNN
F 2 "" H 3650 3450 50  0001 C CNN
F 3 "" H 3650 3450 50  0001 C CNN
	1    3650 3450
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR0120
U 1 1 60B4B332
P 8300 5150
F 0 "#PWR0120" H 8300 5000 50  0001 C CNN
F 1 "VCC" H 8315 5323 50  0000 C CNN
F 2 "" H 8300 5150 50  0001 C CNN
F 3 "" H 8300 5150 50  0001 C CNN
	1    8300 5150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0121
U 1 1 60B4BB63
P 8300 5550
F 0 "#PWR0121" H 8300 5400 50  0001 C CNN
F 1 "VCC" H 8315 5723 50  0000 C CNN
F 2 "" H 8300 5550 50  0001 C CNN
F 3 "" H 8300 5550 50  0001 C CNN
	1    8300 5550
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0123
U 1 1 60B4BF69
P 6300 2700
F 0 "#PWR0123" H 6300 2550 50  0001 C CNN
F 1 "VCC" H 6315 2873 50  0000 C CNN
F 2 "" H 6300 2700 50  0001 C CNN
F 3 "" H 6300 2700 50  0001 C CNN
	1    6300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2750 6300 2750
Text GLabel 7050 4000 2    50   BiDi ~ 0
RC7
Text GLabel 7050 4100 2    50   BiDi ~ 0
RC6
Text GLabel 7050 4200 2    50   BiDi ~ 0
RC5
Text GLabel 7050 4300 2    50   BiDi ~ 0
RC4
Text GLabel 7050 4400 2    50   BiDi ~ 0
RC3
Text GLabel 7050 4500 2    50   BiDi ~ 0
RC2-SDO
Wire Wire Line
	7050 4200 6750 4200
Wire Wire Line
	7050 4300 6650 4300
Wire Wire Line
	7050 4400 6400 4400
Wire Wire Line
	7050 4500 6400 4500
Text GLabel 11950 1900 0    50   BiDi ~ 0
VCCIN
Text GLabel 11950 2000 0    50   BiDi ~ 0
VCCOUT
Text GLabel 11950 2100 0    50   BiDi ~ 0
RA5
Text GLabel 11950 2200 0    50   BiDi ~ 0
RA4
Wire Wire Line
	12100 2200 11950 2200
Wire Wire Line
	11950 2100 12100 2100
Connection ~ 3900 10150
Wire Wire Line
	3900 10150 4250 10150
Wire Wire Line
	3900 10700 4750 10700
Wire Wire Line
	12100 1900 11950 1900
Wire Wire Line
	12100 2000 11950 2000
Text GLabel 11950 5050 0    50   BiDi ~ 0
RB6-SCL
Wire Wire Line
	11900 3950 11900 4050
Wire Wire Line
	11900 4050 12150 4050
Text GLabel 11950 4850 0    50   BiDi ~ 0
RB4-SDA
Text GLabel 11950 2900 0    50   BiDi ~ 0
RB7-SDA2
Text GLabel 11950 4950 0    50   BiDi ~ 0
RB5-SCL2
Wire Wire Line
	12150 4850 11950 4850
Wire Wire Line
	11950 4950 12150 4950
Wire Wire Line
	12150 5050 11950 5050
Wire Wire Line
	11950 2900 12100 2900
Text GLabel 7050 4600 2    50   BiDi ~ 0
RC1
Text GLabel 7050 4700 2    50   BiDi ~ 0
RC0
Wire Wire Line
	6400 4600 6750 4600
Wire Wire Line
	6400 4700 6650 4700
Text GLabel 11950 2400 0    50   BiDi ~ 0
RC5
Text GLabel 11950 2500 0    50   BiDi ~ 0
RC4
Text GLabel 10550 2700 0    50   BiDi ~ 0
RC6
Text GLabel 10550 2800 0    50   BiDi ~ 0
RC7
Wire Wire Line
	11950 2400 12100 2400
Wire Wire Line
	11950 2500 12100 2500
Text GLabel 4050 4100 0    50   BiDi ~ 0
RA2
Wire Wire Line
	4050 4100 4200 4100
Text GLabel 11950 4750 0    50   BiDi ~ 0
RC2-SDO
Text GLabel 11950 4650 0    50   BiDi ~ 0
RC1
Text GLabel 11950 4550 0    50   BiDi ~ 0
RC0
Text GLabel 11950 4450 0    50   BiDi ~ 0
RA2
Wire Wire Line
	11950 4450 12150 4450
Wire Wire Line
	12150 4550 11950 4550
Wire Wire Line
	11950 4650 12150 4650
Wire Wire Line
	11950 4750 12150 4750
Text GLabel 3400 4000 0    50   BiDi ~ 0
RA1
Text GLabel 3400 3900 0    50   BiDi ~ 0
RA0
Wire Wire Line
	3400 3900 3850 3900
Connection ~ 3850 3900
Wire Wire Line
	3400 4000 3950 4000
Connection ~ 3950 4000
Text GLabel 11950 4350 0    50   BiDi ~ 0
RA1
Text GLabel 11950 4250 0    50   BiDi ~ 0
RA0
Text GLabel 3400 4200 0    50   BiDi ~ 0
RA3
Wire Wire Line
	3400 4200 3550 4200
Connection ~ 3550 4200
Text GLabel 11950 2300 0    50   BiDi ~ 0
RA3
Wire Wire Line
	11950 2300 12100 2300
Wire Wire Line
	11950 4350 12150 4350
Wire Wire Line
	11950 4250 12150 4250
Wire Wire Line
	6750 5250 6750 4600
Connection ~ 6750 4600
Wire Wire Line
	6750 4600 7050 4600
Wire Wire Line
	6650 5650 6650 4700
Connection ~ 6650 4700
Wire Wire Line
	6650 4700 7050 4700
$Comp
L Device:LED D4
U 1 1 60C9CB08
P 7200 3200
F 0 "D4" H 7193 3417 50  0000 C CNN
F 1 "LED" H 7193 3326 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 3200 50  0001 C CNN
F 3 "~" H 7200 3200 50  0001 C CNN
F 4 "LG R971-KN-1" H 7193 3517 50  0001 C CNN "manf#"
	1    7200 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 60C9CB0F
P 7200 3600
F 0 "D5" H 7193 3817 50  0000 C CNN
F 1 "LED" H 7193 3726 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 3600 50  0001 C CNN
F 3 "~" H 7200 3600 50  0001 C CNN
F 4 "LG R971-KN-1" H 7193 3917 50  0001 C CNN "manf#"
	1    7200 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 60C9CB16
P 7750 3200
F 0 "R6" V 7543 3200 50  0000 C CNN
F 1 "330R" V 7634 3200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7680 3200 50  0001 C CNN
F 3 "~" H 7750 3200 50  0001 C CNN
F 4 "RT0603FRD07330RL" H 7543 3300 50  0001 C CNN "manf#"
	1    7750 3200
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 60C9CB1D
P 7750 3600
F 0 "R9" V 7543 3600 50  0000 C CNN
F 1 "330R" V 7634 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7680 3600 50  0001 C CNN
F 3 "~" H 7750 3600 50  0001 C CNN
F 4 "RT0603FRD07330RL" H 7543 3700 50  0001 C CNN "manf#"
	1    7750 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 3200 7600 3200
Wire Wire Line
	7900 3200 8300 3200
Wire Wire Line
	8300 3200 8300 3100
Wire Wire Line
	7350 3600 7600 3600
Wire Wire Line
	7900 3600 8300 3600
Wire Wire Line
	8300 3600 8300 3500
Wire Wire Line
	6750 3200 7050 3200
Wire Wire Line
	7050 3600 6650 3600
$Comp
L power:VCC #PWR0104
U 1 1 60C9CB2B
P 8300 3100
F 0 "#PWR0104" H 8300 2950 50  0001 C CNN
F 1 "VCC" H 8315 3273 50  0000 C CNN
F 2 "" H 8300 3100 50  0001 C CNN
F 3 "" H 8300 3100 50  0001 C CNN
	1    8300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0105
U 1 1 60C9CB31
P 8300 3500
F 0 "#PWR0105" H 8300 3350 50  0001 C CNN
F 1 "VCC" H 8315 3673 50  0000 C CNN
F 2 "" H 8300 3500 50  0001 C CNN
F 3 "" H 8300 3500 50  0001 C CNN
	1    8300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 4100 7050 4100
Wire Wire Line
	6400 4000 7050 4000
Wire Wire Line
	6750 3200 6750 4200
Connection ~ 6750 4200
Wire Wire Line
	6750 4200 6400 4200
Wire Wire Line
	6650 3600 6650 4300
Connection ~ 6650 4300
Wire Wire Line
	6650 4300 6400 4300
$Comp
L Device:R R10
U 1 1 60CDC76A
P 11100 3350
F 0 "R10" V 10893 3350 50  0000 C CNN
F 1 "4K99" V 10984 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 11030 3350 50  0001 C CNN
F 3 "~" H 11100 3350 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 10893 3450 50  0001 C CNN "manf#"
	1    11100 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R11
U 1 1 60CDD0A7
P 11400 3350
F 0 "R11" V 11193 3350 50  0000 C CNN
F 1 "4K99" V 11284 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 11330 3350 50  0001 C CNN
F 3 "~" H 11400 3350 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 11193 3450 50  0001 C CNN "manf#"
	1    11400 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	11400 3500 11400 3800
Wire Wire Line
	11400 3800 11100 3800
Wire Wire Line
	11100 3800 11100 3500
$Comp
L power:VCC #PWR0106
U 1 1 60CF535F
P 10200 3800
F 0 "#PWR0106" H 10200 3650 50  0001 C CNN
F 1 "VCC" H 10215 3973 50  0000 C CNN
F 2 "" H 10200 3800 50  0001 C CNN
F 3 "" H 10200 3800 50  0001 C CNN
	1    10200 3800
	1    0    0    -1  
$EndComp
Text GLabel 10550 2600 0    50   BiDi ~ 0
RC3
$Comp
L Device:R R12
U 1 1 60D08D1E
P 10800 3350
F 0 "R12" V 10593 3350 50  0000 C CNN
F 1 "4K99" V 10684 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 10730 3350 50  0001 C CNN
F 3 "~" H 10800 3350 50  0001 C CNN
F 4 "RT0603FRE074K99L" H 10593 3450 50  0001 C CNN "manf#"
	1    10800 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	10550 2600 10800 2600
Wire Wire Line
	10200 3800 10800 3800
Connection ~ 11100 3800
Wire Wire Line
	10800 3500 10800 3800
Connection ~ 10800 3800
Wire Wire Line
	10800 3800 11100 3800
Wire Wire Line
	10550 2800 11400 2800
Wire Wire Line
	10550 2700 11100 2700
Wire Wire Line
	10800 3200 10800 2600
Connection ~ 10800 2600
Wire Wire Line
	10800 2600 12100 2600
Wire Wire Line
	11100 3200 11100 2700
Connection ~ 11100 2700
Wire Wire Line
	11100 2700 12100 2700
Wire Wire Line
	11400 3200 11400 2800
Connection ~ 11400 2800
Wire Wire Line
	11400 2800 12100 2800
$Comp
L Connector:Conn_01x12_Male J1
U 1 1 60D70507
P 12300 2400
F 0 "J1" H 12272 2374 50  0000 R CNN
F 1 "Conn_01x12_Male" H 12272 2283 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 12300 2400 50  0001 C CNN
F 3 "~" H 12300 2400 50  0001 C CNN
	1    12300 2400
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x12_Male J2
U 1 1 60D7E0AA
P 12350 4550
F 0 "J2" H 12322 4524 50  0000 R CNN
F 1 "Conn_01x12_Male" H 12322 4433 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 12350 4550 50  0001 C CNN
F 3 "~" H 12350 4550 50  0001 C CNN
	1    12350 4550
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
