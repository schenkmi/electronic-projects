*
*   F-485
*
.SUBCKT F-485 P1 B1 B2 P2 S1 S0
* Primary inductance (p-p 8000ohm 26H)
L11 P1 11 6.5H
L12 12 P2 6.5H
* Primary DC resistance
R11 11 B1 198.5
R12 B2 12 198.5
* Primary stray capacitance
CP P1 P2 4.84231318891262e-10
* Secondary inductance (8ohm)
L13 S1 21 0.0293376298829410H
* Secondary DC resistance
R13 S0 21 0.579
* coupling factor
K1 L11 L13 0.999778203873395
K2 L12 L13 0.999778203873395
K3 L11 L12 0.999778203873395
.ENDS
