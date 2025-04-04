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
L Transistor_BJT:BC850 Q2
U 1 1 5F7C47B2
P 8800 7850
F 0 "Q2" H 8991 7896 50  0000 L CNN
F 1 "BC850C" H 8991 7805 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9000 7775 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 8800 7850 50  0001 L CNN
	1    8800 7850
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC860 Q5
U 1 1 5F7C52FE
P 9600 6300
F 0 "Q5" H 9791 6346 50  0000 L CNN
F 1 "BC860C" H 9791 6255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9800 6225 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC857SERIES_BC858SERIES_BC859SERIES_BC860SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541da0e3a1661" H 9600 6300 50  0001 L CNN
	1    9600 6300
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:BC850 Q4
U 1 1 5F7C8FFA
P 9400 7850
F 0 "Q4" H 9591 7896 50  0000 L CNN
F 1 "BC850C" H 9591 7805 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9600 7775 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 9400 7850 50  0001 L CNN
	1    9400 7850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5F7F7F2C
P 9500 8350
F 0 "R6" H 9570 8396 50  0000 L CNN
F 1 "68" H 9570 8305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 9430 8350 50  0001 C CNN
F 3 "~" H 9500 8350 50  0001 C CNN
	1    9500 8350
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC860 Q1
U 1 1 5F7FA604
P 8600 6300
F 0 "Q1" H 8791 6346 50  0000 L CNN
F 1 "BC860C" H 8791 6255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8800 6225 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC857SERIES_BC858SERIES_BC859SERIES_BC860SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541da0e3a1661" H 8600 6300 50  0001 L CNN
	1    8600 6300
	1    0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 5F7FC412
P 7950 6300
F 0 "C2" V 7698 6300 50  0000 C CNN
F 1 "2.2uF" V 7789 6300 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L7.2mm_W7.2mm_P5.00mm_FKS2_FKP2_MKS2_MKP2" H 7988 6150 50  0001 C CNN
F 3 "~" H 7950 6300 50  0001 C CNN
	1    7950 6300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5F7FD1B1
P 8250 6950
F 0 "#PWR09" H 8250 6700 50  0001 C CNN
F 1 "GND" H 8255 6777 50  0000 C CNN
F 2 "" H 8250 6950 50  0001 C CNN
F 3 "" H 8250 6950 50  0001 C CNN
	1    8250 6950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5F7FDDC2
P 8700 8350
F 0 "R3" H 8770 8396 50  0000 L CNN
F 1 "68" H 8770 8305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8630 8350 50  0001 C CNN
F 3 "~" H 8700 8350 50  0001 C CNN
	1    8700 8350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F7FE1A1
P 8250 6650
F 0 "R1" H 8320 6696 50  0000 L CNN
F 1 "22k" H 8320 6605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8180 6650 50  0001 C CNN
F 3 "~" H 8250 6650 50  0001 C CNN
	1    8250 6650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5F7FE6D0
P 10050 6550
F 0 "R8" H 10120 6596 50  0000 L CNN
F 1 "22k" H 10120 6505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 9980 6550 50  0001 C CNN
F 3 "~" H 10050 6550 50  0001 C CNN
	1    10050 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 5F7FEF9F
P 10050 6950
F 0 "C6" H 10168 6996 50  0000 L CNN
F 1 "100uF" H 10168 6905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 10088 6800 50  0001 C CNN
F 3 "~" H 10050 6950 50  0001 C CNN
	1    10050 6950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5F7FF6AB
P 10450 6300
F 0 "R9" V 10243 6300 50  0000 C CNN
F 1 "22k" V 10334 6300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 10380 6300 50  0001 C CNN
F 3 "~" H 10450 6300 50  0001 C CNN
	1    10450 6300
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F7FFBF9
P 8700 5700
F 0 "R2" H 8770 5746 50  0000 L CNN
F 1 "100R" H 8770 5655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8630 5700 50  0001 C CNN
F 3 "~" H 8700 5700 50  0001 C CNN
	1    8700 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5F800152
P 9500 5700
F 0 "R5" H 9570 5746 50  0000 L CNN
F 1 "100R" H 9570 5655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 9430 5700 50  0001 C CNN
F 3 "~" H 9500 5700 50  0001 C CNN
	1    9500 5700
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC860 Q3
U 1 1 5F80055B
P 9200 5150
F 0 "Q3" H 9391 5196 50  0000 L CNN
F 1 "BC860C" H 9391 5105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9400 5075 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC857SERIES_BC858SERIES_BC859SERIES_BC860SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541da0e3a1661" H 9200 5150 50  0001 L CNN
	1    9200 5150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 5F800CD9
P 9100 4650
F 0 "R4" H 9170 4696 50  0000 L CNN
F 1 "150R" H 9170 4605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 9030 4650 50  0001 C CNN
F 3 "~" H 9100 4650 50  0001 C CNN
	1    9100 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5F80125C
P 10050 5450
F 0 "R7" H 10120 5496 50  0000 L CNN
F 1 "22k" H 10120 5405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 9980 5450 50  0001 C CNN
F 3 "~" H 10050 5450 50  0001 C CNN
	1    10050 5450
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148W D2
U 1 1 5F801FDC
P 10050 4850
F 0 "D2" V 10096 4770 50  0000 R CNN
F 1 "1N4148W" V 10005 4770 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 10050 4675 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 10050 4850 50  0001 C CNN
	1    10050 4850
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148W D1
U 1 1 5F80332A
P 10050 4400
F 0 "D1" V 10096 4320 50  0000 R CNN
F 1 "1N4148W" V 10005 4320 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 10050 4225 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 10050 4400 50  0001 C CNN
	1    10050 4400
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_BJT:BC860 Q7
U 1 1 5F803B7E
P 11400 5150
F 0 "Q7" H 11591 5196 50  0000 L CNN
F 1 "BC860C" H 11591 5105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11600 5075 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC857SERIES_BC858SERIES_BC859SERIES_BC860SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541da0e3a1661" H 11400 5150 50  0001 L CNN
	1    11400 5150
	1    0    0    1   
$EndComp
$Comp
L Transistor_BJT:BC860 Q9
U 1 1 5F804E0F
P 12250 5150
F 0 "Q9" H 12441 5196 50  0000 L CNN
F 1 "BC860C" H 12441 5105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 12450 5075 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC857SERIES_BC858SERIES_BC859SERIES_BC860SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541da0e3a1661" H 12250 5150 50  0001 L CNN
	1    12250 5150
	1    0    0    1   
$EndComp
$Comp
L Device:R R11
U 1 1 5F8055E7
P 11500 4450
F 0 "R11" H 11570 4496 50  0000 L CNN
F 1 "100R" H 11570 4405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 11430 4450 50  0001 C CNN
F 3 "~" H 11500 4450 50  0001 C CNN
	1    11500 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 5F805B16
P 12350 4450
F 0 "R12" H 12420 4496 50  0000 L CNN
F 1 "100R" H 12420 4405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 12280 4450 50  0001 C CNN
F 3 "~" H 12350 4450 50  0001 C CNN
	1    12350 4450
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC850 Q6
U 1 1 5F805D7B
P 10650 7550
F 0 "Q6" H 10841 7596 50  0000 L CNN
F 1 "BC850C" H 10841 7505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10850 7475 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 10650 7550 50  0001 L CNN
	1    10650 7550
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC850 Q8
U 1 1 5F807D61
P 11400 7950
F 0 "Q8" H 11591 7996 50  0000 L CNN
F 1 "BC850C" H 11591 7905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11600 7875 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 11400 7950 50  0001 L CNN
	1    11400 7950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5F80C07F
P 10750 8350
F 0 "R10" H 10820 8396 50  0000 L CNN
F 1 "2k2" H 10820 8305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 10680 8350 50  0001 C CNN
F 3 "~" H 10750 8350 50  0001 C CNN
	1    10750 8350
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC860 Q10
U 1 1 5F80DAD5
P 12250 7300
F 0 "Q10" H 12441 7346 50  0000 L CNN
F 1 "BC860C" H 12441 7255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 12450 7225 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC857SERIES_BC858SERIES_BC859SERIES_BC860SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541da0e3a1661" H 12250 7300 50  0001 L CNN
	1    12250 7300
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5F812BE9
P 10050 7200
F 0 "#PWR013" H 10050 6950 50  0001 C CNN
F 1 "GND" H 10055 7027 50  0000 C CNN
F 2 "" H 10050 7200 50  0001 C CNN
F 3 "" H 10050 7200 50  0001 C CNN
	1    10050 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 6500 8700 7550
Wire Wire Line
	8700 8200 8700 8050
Wire Wire Line
	9500 7650 9500 7600
Wire Wire Line
	9200 7850 9100 7850
Wire Wire Line
	9100 7850 9100 7600
Wire Wire Line
	9100 7600 9500 7600
Connection ~ 9100 7850
Wire Wire Line
	9100 7850 9000 7850
Connection ~ 9500 7600
Wire Wire Line
	9500 7600 9500 6500
Wire Wire Line
	9500 8200 9500 8050
$Comp
L Device:C C7
U 1 1 5F82148C
P 11150 7300
F 0 "C7" V 10898 7300 50  0000 C CNN
F 1 "270pF" V 10989 7300 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D7.0mm_W2.5mm_P5.00mm" H 11188 7150 50  0001 C CNN
F 3 "~" H 11150 7300 50  0001 C CNN
	1    11150 7300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5F823495
P 10750 6950
F 0 "#PWR014" H 10750 6700 50  0001 C CNN
F 1 "GND" H 10755 6777 50  0000 C CNN
F 2 "" H 10750 6950 50  0001 C CNN
F 3 "" H 10750 6950 50  0001 C CNN
	1    10750 6950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5F8253E5
P 7800 6950
F 0 "#PWR04" H 7800 6700 50  0001 C CNN
F 1 "GND" H 7805 6777 50  0000 C CNN
F 2 "" H 7800 6950 50  0001 C CNN
F 3 "" H 7800 6950 50  0001 C CNN
	1    7800 6950
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5F826EF7
P 10200 10500
F 0 "H1" H 10300 10546 50  0000 L CNN
F 1 "MountingHole" H 10300 10455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10200 10500 50  0001 C CNN
F 3 "~" H 10200 10500 50  0001 C CNN
	1    10200 10500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5F827B60
P 10900 10500
F 0 "H3" H 11000 10546 50  0000 L CNN
F 1 "MountingHole" H 11000 10455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10900 10500 50  0001 C CNN
F 3 "~" H 10900 10500 50  0001 C CNN
	1    10900 10500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5F827E6E
P 10200 10800
F 0 "H2" H 10300 10846 50  0000 L CNN
F 1 "MountingHole" H 10300 10755 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10200 10800 50  0001 C CNN
F 3 "~" H 10200 10800 50  0001 C CNN
	1    10200 10800
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5F828446
P 10900 10800
F 0 "H4" H 11000 10846 50  0000 L CNN
F 1 "MountingHole" H 11000 10755 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10900 10800 50  0001 C CNN
F 3 "~" H 10900 10800 50  0001 C CNN
	1    10900 10800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 5F828F01
P 7450 6300
F 0 "J4" H 7368 6075 50  0000 C CNN
F 1 "Conn_01x01" H 7368 6166 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 7450 6300 50  0001 C CNN
F 3 "~" H 7450 6300 50  0001 C CNN
	1    7450 6300
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 5F829B5B
P 7450 6700
F 0 "J5" H 7368 6475 50  0000 C CNN
F 1 "Conn_01x01" H 7368 6566 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 7450 6700 50  0001 C CNN
F 3 "~" H 7450 6700 50  0001 C CNN
	1    7450 6700
	-1   0    0    1   
$EndComp
Wire Wire Line
	8250 6950 8250 6800
Wire Wire Line
	8250 6500 8250 6300
Wire Wire Line
	8700 5550 8700 5450
Wire Wire Line
	8700 5450 9100 5450
Wire Wire Line
	9500 5450 9500 5550
Wire Wire Line
	9100 5350 9100 5450
Connection ~ 9100 5450
Wire Wire Line
	9100 5450 9500 5450
Wire Wire Line
	8700 6100 8700 5850
Wire Wire Line
	9500 6100 9500 5850
$Comp
L power:GND #PWR012
U 1 1 5F832579
P 10050 5750
F 0 "#PWR012" H 10050 5500 50  0001 C CNN
F 1 "GND" H 10055 5577 50  0000 C CNN
F 2 "" H 10050 5750 50  0001 C CNN
F 3 "" H 10050 5750 50  0001 C CNN
	1    10050 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 5150 10050 5150
Wire Wire Line
	10050 5150 10050 5000
Wire Wire Line
	10050 5300 10050 5150
Connection ~ 10050 5150
Wire Wire Line
	10050 5750 10050 5600
Wire Wire Line
	9100 4950 9100 4800
Wire Wire Line
	9100 4500 9100 4000
Wire Wire Line
	9100 4000 10050 4000
Wire Wire Line
	10050 4000 10050 4250
Wire Wire Line
	10050 4550 10050 4700
Wire Wire Line
	11200 5150 11000 5150
Wire Wire Line
	11500 4950 11500 4600
Wire Wire Line
	11500 4300 11500 4000
Wire Wire Line
	11500 4000 10050 4000
Connection ~ 10050 4000
Wire Wire Line
	12350 4300 12350 4000
Wire Wire Line
	12350 4000 11500 4000
Connection ~ 11500 4000
Wire Wire Line
	12350 4950 12350 4600
Wire Wire Line
	12350 7100 12350 6300
Wire Wire Line
	11500 7750 11500 7300
Wire Wire Line
	11300 7300 11500 7300
Connection ~ 11500 7300
Wire Wire Line
	11500 7300 11500 5350
Wire Wire Line
	11500 7300 12050 7300
Wire Wire Line
	11200 7950 10750 7950
Connection ~ 10750 7950
Wire Wire Line
	9800 6300 10050 6300
Wire Wire Line
	10050 6400 10050 6300
Connection ~ 10050 6300
Wire Wire Line
	10050 6300 10300 6300
Wire Wire Line
	10050 6800 10050 6700
Wire Wire Line
	10050 7200 10050 7100
Wire Wire Line
	10450 7300 10450 7550
Wire Wire Line
	10450 7550 8700 7550
Connection ~ 10450 7550
Connection ~ 8700 7550
Wire Wire Line
	8700 7550 8700 7650
Wire Wire Line
	10450 7300 11000 7300
Wire Wire Line
	10750 7350 10750 6950
Wire Wire Line
	10600 6300 12350 6300
Connection ~ 12350 6300
Wire Wire Line
	12350 6300 12350 5350
Wire Wire Line
	12050 5150 12050 5550
Wire Wire Line
	12050 5550 11000 5550
Wire Wire Line
	11000 5550 11000 5150
Connection ~ 11000 5150
Wire Wire Line
	11000 5150 10050 5150
$Comp
L power:+15V #PWR05
U 1 1 5F8542B0
P 7650 3950
F 0 "#PWR05" H 7650 3800 50  0001 C CNN
F 1 "+15V" H 7665 4123 50  0000 C CNN
F 2 "" H 7650 3950 50  0001 C CNN
F 3 "" H 7650 3950 50  0001 C CNN
	1    7650 3950
	1    0    0    -1  
$EndComp
Connection ~ 9100 4000
Wire Wire Line
	12350 7500 12350 8800
Wire Wire Line
	12350 8800 11500 8800
Wire Wire Line
	8700 8800 8700 8500
Wire Wire Line
	9500 8500 9500 8800
Connection ~ 9500 8800
Wire Wire Line
	9500 8800 8700 8800
Wire Wire Line
	10750 8500 10750 8800
Connection ~ 10750 8800
Wire Wire Line
	10750 8800 9500 8800
Wire Wire Line
	11500 8150 11500 8800
Connection ~ 11500 8800
Wire Wire Line
	11500 8800 10750 8800
$Comp
L power:-15V #PWR08
U 1 1 5F85C667
P 7650 9000
F 0 "#PWR08" H 7650 9100 50  0001 C CNN
F 1 "-15V" H 7665 9173 50  0000 C CNN
F 2 "" H 7650 9000 50  0001 C CNN
F 3 "" H 7650 9000 50  0001 C CNN
	1    7650 9000
	-1   0    0    1   
$EndComp
Connection ~ 8700 8800
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 5F85FA68
P 13150 6300
F 0 "J6" H 13230 6342 50  0000 L CNN
F 1 "Conn_01x01" H 13230 6251 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 13150 6300 50  0001 C CNN
F 3 "~" H 13150 6300 50  0001 C CNN
	1    13150 6300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 5F8602F3
P 13150 6750
F 0 "J7" H 13230 6792 50  0000 L CNN
F 1 "Conn_01x01" H 13230 6701 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 13150 6750 50  0001 C CNN
F 3 "~" H 13150 6750 50  0001 C CNN
	1    13150 6750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 5F860746
P 2150 10100
F 0 "J1" H 2068 9875 50  0000 C CNN
F 1 "Conn_01x01" H 2068 9966 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 2150 10100 50  0001 C CNN
F 3 "~" H 2150 10100 50  0001 C CNN
	1    2150 10100
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5F860D1D
P 1000 10650
F 0 "J2" H 918 10425 50  0000 C CNN
F 1 "Conn_01x01" H 918 10516 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 1000 10650 50  0001 C CNN
F 3 "~" H 1000 10650 50  0001 C CNN
	1    1000 10650
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 5F861111
P 4700 10100
F 0 "J3" H 4618 9875 50  0000 C CNN
F 1 "Conn_01x01" H 4618 9966 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 4700 10100 50  0001 C CNN
F 3 "~" H 4700 10100 50  0001 C CNN
	1    4700 10100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F8644ED
P 1700 10650
F 0 "#PWR02" H 1700 10400 50  0001 C CNN
F 1 "GND" V 1705 10522 50  0000 R CNN
F 2 "" H 1700 10650 50  0001 C CNN
F 3 "" H 1700 10650 50  0001 C CNN
	1    1700 10650
	0    -1   -1   0   
$EndComp
$Comp
L power:+15V #PWR01
U 1 1 5F8653DA
P 4150 10100
F 0 "#PWR01" H 4150 9950 50  0001 C CNN
F 1 "+15V" V 4165 10228 50  0000 L CNN
F 2 "" H 4150 10100 50  0001 C CNN
F 3 "" H 4150 10100 50  0001 C CNN
	1    4150 10100
	0    1    1    0   
$EndComp
$Comp
L Device:CP C3
U 1 1 5F86C1B0
P 7650 8350
F 0 "C3" H 7768 8396 50  0000 L CNN
F 1 "100uF" H 7768 8305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 7688 8200 50  0001 C CNN
F 3 "~" H 7650 8350 50  0001 C CNN
	1    7650 8350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5F86D3F9
P 8150 8350
F 0 "C5" H 8035 8304 50  0000 R CNN
F 1 "100nF" H 8035 8395 50  0000 R CNN
F 2 "Capacitor_THT:C_Rect_L7.2mm_W2.5mm_P5.00mm_FKS2_FKP2_MKS2_MKP2" H 8188 8200 50  0001 C CNN
F 3 "~" H 8150 8350 50  0001 C CNN
	1    8150 8350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5F870D74
P 7650 8100
F 0 "#PWR07" H 7650 7850 50  0001 C CNN
F 1 "GND" H 7655 7927 50  0000 C CNN
F 2 "" H 7650 8100 50  0001 C CNN
F 3 "" H 7650 8100 50  0001 C CNN
	1    7650 8100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5F8716F0
P 8150 8100
F 0 "#PWR011" H 8150 7850 50  0001 C CNN
F 1 "GND" H 8155 7927 50  0000 C CNN
F 2 "" H 8150 8100 50  0001 C CNN
F 3 "" H 8150 8100 50  0001 C CNN
	1    8150 8100
	-1   0    0    1   
$EndComp
Wire Wire Line
	8150 8800 8150 8500
Wire Wire Line
	7650 8800 7650 8500
Wire Wire Line
	7650 9000 7650 8800
Connection ~ 7650 8800
Wire Wire Line
	7650 8200 7650 8100
Wire Wire Line
	8150 8200 8150 8100
$Comp
L Device:R R13
U 1 1 5F87BEE5
P 12650 6300
F 0 "R13" V 12443 6300 50  0000 C CNN
F 1 "47R" V 12534 6300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 12580 6300 50  0001 C CNN
F 3 "~" H 12650 6300 50  0001 C CNN
	1    12650 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 4000 7650 3950
$Comp
L Device:CP C1
U 1 1 5F87FECA
P 7650 4350
F 0 "C1" H 7768 4396 50  0000 L CNN
F 1 "100uF" H 7768 4305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 7688 4200 50  0001 C CNN
F 3 "~" H 7650 4350 50  0001 C CNN
	1    7650 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F88163E
P 7650 4650
F 0 "#PWR06" H 7650 4400 50  0001 C CNN
F 1 "GND" H 7655 4477 50  0000 C CNN
F 2 "" H 7650 4650 50  0001 C CNN
F 3 "" H 7650 4650 50  0001 C CNN
	1    7650 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5F881A3A
P 8150 4650
F 0 "#PWR010" H 8150 4400 50  0001 C CNN
F 1 "GND" H 8155 4477 50  0000 C CNN
F 2 "" H 8150 4650 50  0001 C CNN
F 3 "" H 8150 4650 50  0001 C CNN
	1    8150 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5F88B1AF
P 12800 6900
F 0 "#PWR015" H 12800 6650 50  0001 C CNN
F 1 "GND" H 12805 6727 50  0000 C CNN
F 2 "" H 12800 6900 50  0001 C CNN
F 3 "" H 12800 6900 50  0001 C CNN
	1    12800 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	12500 6300 12350 6300
Wire Wire Line
	12950 6300 12800 6300
Wire Wire Line
	12950 6750 12800 6750
Wire Wire Line
	12800 6750 12800 6900
Wire Wire Line
	7650 4200 7650 4000
Connection ~ 7650 4000
Wire Wire Line
	8150 4200 8150 4000
Wire Wire Line
	8150 4650 8150 4500
$Comp
L Device:C C4
U 1 1 5F881005
P 8150 4350
F 0 "C4" H 8035 4304 50  0000 R CNN
F 1 "100nF" H 8035 4395 50  0000 R CNN
F 2 "Capacitor_THT:C_Rect_L7.2mm_W2.5mm_P5.00mm_FKS2_FKP2_MKS2_MKP2" H 8188 4200 50  0001 C CNN
F 3 "~" H 8150 4350 50  0001 C CNN
	1    8150 4350
	-1   0    0    1   
$EndComp
Connection ~ 8150 4000
Wire Wire Line
	8150 4000 9100 4000
Wire Wire Line
	7650 4000 8150 4000
Connection ~ 8150 8800
Wire Wire Line
	8150 8800 8700 8800
Wire Wire Line
	7650 8800 8150 8800
$Comp
L power:-15V #PWR0101
U 1 1 5F8CEA6A
P 6650 10100
F 0 "#PWR0101" H 6650 10200 50  0001 C CNN
F 1 "-15V" V 6665 10228 50  0000 L CNN
F 2 "" H 6650 10100 50  0001 C CNN
F 3 "" H 6650 10100 50  0001 C CNN
	1    6650 10100
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 4500 7650 4650
Wire Wire Line
	10750 7950 10750 8200
Wire Wire Line
	10750 7750 10750 7950
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5F8EAC97
P 1600 10650
F 0 "#FLG0101" H 1600 10725 50  0001 C CNN
F 1 "PWR_FLAG" H 1600 10823 50  0000 C CNN
F 2 "" H 1600 10650 50  0001 C CNN
F 3 "~" H 1600 10650 50  0001 C CNN
	1    1600 10650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 10650 1600 10650
Wire Wire Line
	1600 10650 1700 10650
Connection ~ 1600 10650
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5F8F23BA
P 4050 10100
F 0 "#FLG0102" H 4050 10175 50  0001 C CNN
F 1 "PWR_FLAG" H 4050 10273 50  0000 C CNN
F 2 "" H 4050 10100 50  0001 C CNN
F 3 "~" H 4050 10100 50  0001 C CNN
	1    4050 10100
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5F8F26FB
P 6550 10100
F 0 "#FLG0103" H 6550 10175 50  0001 C CNN
F 1 "PWR_FLAG" H 6550 10273 50  0000 C CNN
F 2 "" H 6550 10100 50  0001 C CNN
F 3 "~" H 6550 10100 50  0001 C CNN
	1    6550 10100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 10100 6650 10100
$Comp
L Transistor_BJT:BC850 Q11
U 1 1 5F91DD7E
P 3450 10200
F 0 "Q11" H 3641 10246 50  0000 L CNN
F 1 "BC850C" H 3641 10155 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3650 10125 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 3450 10200 50  0001 L CNN
	1    3450 10200
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C8
U 1 1 5F91F753
P 2600 10450
F 0 "C8" H 2718 10496 50  0000 L CNN
F 1 "4.7uF" H 2718 10405 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 2638 10300 50  0001 C CNN
F 3 "~" H 2600 10450 50  0001 C CNN
	1    2600 10450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C9
U 1 1 5F9206EE
P 3450 10650
F 0 "C9" H 3568 10696 50  0000 L CNN
F 1 "4.7uF" H 3568 10605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 3488 10500 50  0001 C CNN
F 3 "~" H 3450 10650 50  0001 C CNN
	1    3450 10650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 5F92244F
P 3200 10450
F 0 "R14" V 2993 10450 50  0000 C CNN
F 1 "22k" V 3084 10450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3130 10450 50  0001 C CNN
F 3 "~" H 3200 10450 50  0001 C CNN
	1    3200 10450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5F92341A
P 3450 10900
F 0 "#PWR0102" H 3450 10650 50  0001 C CNN
F 1 "GND" H 3455 10727 50  0000 C CNN
F 2 "" H 3450 10900 50  0001 C CNN
F 3 "" H 3450 10900 50  0001 C CNN
	1    3450 10900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 10900 3450 10800
Wire Wire Line
	3450 10500 3450 10450
Wire Wire Line
	3350 10450 3450 10450
Connection ~ 3450 10450
Wire Wire Line
	3450 10450 3450 10400
Wire Wire Line
	3250 10100 2950 10100
Wire Wire Line
	2600 10100 2600 10300
Wire Wire Line
	3050 10450 2950 10450
Wire Wire Line
	2950 10450 2950 10100
Connection ~ 2950 10100
Wire Wire Line
	2950 10100 2600 10100
$Comp
L power:GND #PWR0103
U 1 1 5F933420
P 2600 10900
F 0 "#PWR0103" H 2600 10650 50  0001 C CNN
F 1 "GND" H 2605 10727 50  0000 C CNN
F 2 "" H 2600 10900 50  0001 C CNN
F 3 "" H 2600 10900 50  0001 C CNN
	1    2600 10900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 10900 2600 10600
$Comp
L Device:R R15
U 1 1 5F937162
P 3450 9600
F 0 "R15" V 3243 9600 50  0000 C CNN
F 1 "0R" V 3334 9600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3380 9600 50  0001 C CNN
F 3 "~" H 3450 9600 50  0001 C CNN
	1    3450 9600
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 10100 3800 10100
Wire Wire Line
	3800 10100 3800 9600
Wire Wire Line
	3800 9600 3600 9600
Wire Wire Line
	3300 9600 2950 9600
Wire Wire Line
	2950 9600 2950 10100
Wire Wire Line
	8250 6300 8400 6300
Wire Wire Line
	7800 6950 7800 6700
Wire Wire Line
	7800 6700 7650 6700
Wire Wire Line
	7650 6300 7800 6300
Wire Wire Line
	8100 6300 8250 6300
Connection ~ 8250 6300
$Comp
L Device:CP C10
U 1 1 5F9B2DB2
P 5100 10450
F 0 "C10" H 4982 10404 50  0000 R CNN
F 1 "4.7uF" H 4982 10495 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 5138 10300 50  0001 C CNN
F 3 "~" H 5100 10450 50  0001 C CNN
	1    5100 10450
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C11
U 1 1 5F9B2DB8
P 5950 10650
F 0 "C11" H 5832 10604 50  0000 R CNN
F 1 "4.7uF" H 5832 10695 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 5988 10500 50  0001 C CNN
F 3 "~" H 5950 10650 50  0001 C CNN
	1    5950 10650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R16
U 1 1 5F9B2DBE
P 5700 10450
F 0 "R16" V 5493 10450 50  0000 C CNN
F 1 "22k" V 5584 10450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5630 10450 50  0001 C CNN
F 3 "~" H 5700 10450 50  0001 C CNN
	1    5700 10450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5F9B2DC4
P 5950 10900
F 0 "#PWR016" H 5950 10650 50  0001 C CNN
F 1 "GND" H 5955 10727 50  0000 C CNN
F 2 "" H 5950 10900 50  0001 C CNN
F 3 "" H 5950 10900 50  0001 C CNN
	1    5950 10900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 10900 5950 10800
Wire Wire Line
	5950 10500 5950 10450
Wire Wire Line
	5850 10450 5950 10450
Connection ~ 5950 10450
Wire Wire Line
	5950 10450 5950 10400
Wire Wire Line
	5750 10100 5450 10100
Wire Wire Line
	5100 10100 5100 10300
Wire Wire Line
	5550 10450 5450 10450
Wire Wire Line
	5450 10450 5450 10100
Connection ~ 5450 10100
Wire Wire Line
	5450 10100 5100 10100
$Comp
L power:GND #PWR03
U 1 1 5F9B2DD5
P 5100 10900
F 0 "#PWR03" H 5100 10650 50  0001 C CNN
F 1 "GND" H 5105 10727 50  0000 C CNN
F 2 "" H 5100 10900 50  0001 C CNN
F 3 "" H 5100 10900 50  0001 C CNN
	1    5100 10900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 10900 5100 10600
$Comp
L Device:R R17
U 1 1 5F9B2DDC
P 5950 9600
F 0 "R17" V 5743 9600 50  0000 C CNN
F 1 "0R" V 5834 9600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5880 9600 50  0001 C CNN
F 3 "~" H 5950 9600 50  0001 C CNN
	1    5950 9600
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 10100 6300 10100
Wire Wire Line
	6300 10100 6300 9600
Wire Wire Line
	6300 9600 6100 9600
Wire Wire Line
	5800 9600 5450 9600
Wire Wire Line
	5450 9600 5450 10100
$Comp
L Transistor_BJT:BC860 Q12
U 1 1 5F9DAB67
P 5950 10200
F 0 "Q12" H 6141 10246 50  0000 L CNN
F 1 "BC860C" H 6141 10155 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6150 10125 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC857SERIES_BC858SERIES_BC859SERIES_BC860SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541da0e3a1661" H 5950 10200 50  0001 L CNN
	1    5950 10200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 10100 3800 10100
Connection ~ 3800 10100
Wire Wire Line
	4150 10100 4050 10100
Connection ~ 4050 10100
Wire Wire Line
	2350 10100 2600 10100
Connection ~ 2600 10100
Wire Wire Line
	4900 10100 5100 10100
Connection ~ 5100 10100
Wire Wire Line
	6300 10100 6550 10100
Connection ~ 6300 10100
Connection ~ 6550 10100
$EndSCHEMATC
