*
* Generic triode model: 14AF7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:46:24 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 14AF7 A G K
BGG   GG   0 V=V(G,K)+0.77793251
BM1   M1   0 V=(0.0061210583*(URAMP(V(A,K))+1e-10))^-0.15593519
BM2   M2   0 V=(0.90583256*(URAMP(V(GG)+URAMP(V(A,K))/15.384177)+1e-10))^1.6559352
BP    P    0 V=0.0006681181*(URAMP(V(GG)+URAMP(V(A,K))/16.983467)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00046940316*V(M1)*V(M2)
BIG   IG   0 V=0.00033405905*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00039392832*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.3p
CGK   G    K 2.2p
CAK   A    K 1.6p
.ENDS
