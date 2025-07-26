*
* Generic triode model: ECC35
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:39 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT ECC35 A G K
BGG   GG   0 V=V(G,K)+0.62544373
BM1   M1   0 V=(0.0050202395*(URAMP(V(A,K))+1e-10))^-0.5890158
BM2   M2   0 V=(0.71804148*(URAMP(V(GG)+URAMP(V(A,K))/56.164356)+1e-10))^2.0890158
BP    P    0 V=0.001261268*(URAMP(V(GG)+URAMP(V(A,K))/78.218818)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00072725712*V(M1)*V(M2)
BIG   IG   0 V=0.000630634*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00065489844*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3p
CGK   G    K 3p
CAK   A    K 1.3p
.ENDS
