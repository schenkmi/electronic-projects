*
* Generic triode model: 6GA4
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:06 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6GA4 A G K
BGG   GG   0 V=V(G,K)+0.99999993
BM1   M1   0 V=(0.049332301*(URAMP(V(A,K))+1e-10))^-1.0124121
BM2   M2   0 V=(0.59703582*(URAMP(V(GG)+URAMP(V(A,K))/8.1683638)+1e-10))^2.5124121
BP    P    0 V=0.0045336089*(URAMP(V(GG)+URAMP(V(A,K))/13.681531)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0030450256*V(M1)*V(M2)
BIG   IG   0 V=0.0022668045*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0027728299*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 6.5p
CGK   G    K 5p
CAK   A    K 1.2p
.ENDS
