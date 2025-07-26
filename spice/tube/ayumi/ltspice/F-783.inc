*
*   F-783
*
.SUBCKT F-783 P1 B1 B2 P2 S1 S0
* Primary inductance (p-p 5250ohm 24H)
L11 P1 11 6H
L12 12 P2 6H
* Primary DC resistance
R11 11 B1 47.75
R12 B2 12 47.75
* Primary stray capacitance
CP P1 P2 6.69688119070966e-10
* Secondary inductance (8ohm)
L13 S1 21 0.0388460568435348H
* Secondary DC resistance
R13 S0 21 0.343
* coupling factor
K1 L11 L13 0.999910185196216
K2 L12 L13 0.999910185196216
K3 L11 L12 0.999910185196216
.ENDS
