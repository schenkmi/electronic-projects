*
*   F-2021
*
.SUBCKT F-2021 P1 B1 B2 P2 S1 S0
* Primary inductance (p-p 5000ohm 150H)
L11 P1 11 37.5H
L12 12 P2 37.5H
* Primary DC resistance
R11 11 B1 70.6
R12 B2 12 70.6
* Primary stray capacitance
CP P1 P2 6.31185523934445e-10
* Secondary inductance (8ohm)
L13 S1 21 0.254352926648555H
* Secondary DC resistance
R13 S0 21 0.239
* coupling factor
K1 L11 L13 0.99999124811511
K2 L12 L13 0.99999124811511
K3 L11 L12 0.99999124811511
.ENDS
