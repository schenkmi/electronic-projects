*
* Generic triode model: 6LG6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:42 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6LG6T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.11768156*(URAMP(V(A,K))+1e-10))^-0.95241752
BM2   M2   0 V=(0.61164136*(URAMP(V(GG)+URAMP(V(A,K))/3.3000807)+1e-10))^2.4524175
BP    P    0 V=0.0055353672*(URAMP(V(GG)+URAMP(V(A,K))/5.3954505)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.003591442*V(M1)*V(M2)
BIG   IG   0 V=0.0027676836*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0043758251*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 10.5p
CGK   G    K 14.5p
CAK   A    K 12.2p
.ENDS
