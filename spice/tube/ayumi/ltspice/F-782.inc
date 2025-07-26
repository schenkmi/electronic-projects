*
*   F-782
*
.SUBCKT F-782 P1 B1 B2 P2 S1 S0
* Primary inductance (p-p 4000ohm 20H)
L11 P1 11 5H
L12 12 P2 5H
* Primary DC resistance
R11 11 B1 34.65
R12 B2 12 34.65
* Primary stray capacitance
CP P1 P2 8.63341776882608e-10
* Secondary inductance (8ohm)
L13 S1 21 0.0424402778131122H
* Secondary DC resistance
R13 S0 21 0.341
* coupling factor
K1 L11 L13 0.999914449226873
K2 L12 L13 0.999914449226873
K3 L11 L12 0.999914449226873
.ENDS
