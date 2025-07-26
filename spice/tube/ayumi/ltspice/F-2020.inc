*
*   F-2020
*
.SUBCKT F-2020 P1 B1 B2 P2 S1 S0
* Primary inductance (p-p 3500ohm 90H)
L11 P1 11 22.5H
L12 12 P2 22.5H
* Primary DC resistance
R11 11 B1 50
R12 B2 12 50
* Primary stray capacitance
CP P1 P2 6.619300489053e-10
* Secondary inductance (8ohm)
L13 S1 21 0.218779411764706H
* Secondary DC resistance
R13 S0 21 0.265
* coupling factor
K1 L11 L13 0.999996846103945
K2 L12 L13 0.999996846103945
K3 L11 L12 0.999996846103945
.ENDS
