*
* Generic triode model: 5998
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:08 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 5998 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.1360498*(URAMP(V(A,K))+1e-10))^-1.7828871
BM2   M2   0 V=(0.4569149*(URAMP(V(GG)+URAMP(V(A,K))/3.9918111)+1e-10))^3.2828871
BP    P    0 V=0.0069534109*(URAMP(V(GG)+URAMP(V(A,K))/8.7364434)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0094617726*V(M1)*V(M2)
BIG   IG   0 V=0.0034767055*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0047041065*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 8.6p
CGK   G    K 6p
CAK   A    K 2.2p
.ENDS
