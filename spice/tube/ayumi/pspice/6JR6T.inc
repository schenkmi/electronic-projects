*
* Generic triode model: 6JR6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:20 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6JR6T A G K
BGG   GG   0 V=V(G,K)+0.99994363
BM1   M1   0 V=(0.13323481*(URAMP(V(A,K))+1e-10))^-1.5275541
BM2   M2   0 V=(0.49544944*(URAMP(V(GG)+URAMP(V(A,K))/3.7869273)+1e-10))^3.0275541
BP    P    0 V=0.0072054321*(URAMP(V(GG)+URAMP(V(A,K))/7.6434182)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0074085952*V(M1)*V(M2)
BIG   IG   0 V=0.003602716*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0050620509*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.2p
CGK   G    K 12.8p
CAK   A    K 8.3p
.ENDS
