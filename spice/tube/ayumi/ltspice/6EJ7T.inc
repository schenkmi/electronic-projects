*
* Generic triode model: 6EJ7T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:53 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6EJ7T A G K
BGG   GG   0 V=V(G,K)+0.40321166
BM1   M1   0 V=(0.0054275937*(URAMP(V(A,K))+1e-10))**-0.61801526
BM2   M2   0 V=(0.7082102*(URAMP(V(GG)+URAMP(V(A,K))/53.760436)+1e-10))**2.1180153
BP    P    0 V=0.019963362*(URAMP(V(GG)+URAMP(V(A,K))/75.910283)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.011540933*V(M1)*V(M2)
BIG   IG   0 V=0.0099816812*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.010377457*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 6p
CAK   A    K 3p
.ENDS
