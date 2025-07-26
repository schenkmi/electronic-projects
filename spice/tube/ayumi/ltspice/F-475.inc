*
*   F-475
*
.SUBCKT F-475 P B S1 S0
* Primary inductance (5250ohm 21.5H)
L1 P 1 21.5H
* Primary DC resistance
R1 1 B 514
* Primary stray capacitance
CP P B 5.76846921349867e-10
* Secondary inductance (8ohm)
L2 S1 2 0.0416063133445946H
* Secondary DC resistance
R2 2 S0 1.165
* coupling factor
K L1 L2 0.999999999992657
.ENDS
