*
*   F-2003
*
.SUBCKT F-2003 P B S1 S0
* Primary inductance (3500ohm 13H)
L1 P 1 13H
* Primary DC resistance
R1 1 B 26.7
* Primary stray capacitance
CP P B 6.82221963993683e-10
* Secondary inductance (8ohm)
L2 S1 2 0.0315146978377911H
* Secondary DC resistance
R2 2 S0 0.42
* coupling factor
K L1 L2 0.999999999998897
.ENDS
