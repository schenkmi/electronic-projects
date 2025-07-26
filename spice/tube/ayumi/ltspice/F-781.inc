*
*   F-781
*
.SUBCKT F-781 P1 B1 B2 P2 S1 S0
* Primary inductance (p-p 2500ohm 20H)
L11 P1 11 5H
L12 12 P2 5H
* Primary DC resistance
R11 11 B1 49.5
R12 B2 12 49.5
* Primary stray capacitance
CP P1 P2 8.71753516139691e-10
* Secondary inductance (8ohm)
L13 S1 21 0.0695710120783007H
* Secondary DC resistance
R13 S0 21 0.352
* coupling factor
K1 L11 L13 0.999981246432688
K2 L12 L13 0.999981246432688
K3 L11 L12 0.999981246432688
.ENDS
