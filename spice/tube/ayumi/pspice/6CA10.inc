*
* Generic triode model: 6CA10
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:34 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6CA10 A G K
BGG   GG   0 V=V(G,K)+0.85922191
BM1   M1   0 V=(0.052995899*(URAMP(V(A,K))+1e-10))^-0.89537568
BM2   M2   0 V=(0.62620658*(URAMP(V(GG)+URAMP(V(A,K))/7.0532519)+1e-10))^2.3953757
BP    P    0 V=0.0063159843*(URAMP(V(GG)+URAMP(V(A,K))/11.263459)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.003979238*V(M1)*V(M2)
BIG   IG   0 V=0.0031579921*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.004017519*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 16p
CGK   G    K 24p
CAK   A    K 16p
.ENDS
