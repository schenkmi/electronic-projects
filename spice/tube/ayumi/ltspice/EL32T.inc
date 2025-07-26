*
* Generic triode model: EL32T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:47 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT EL32T A G K
BGG   GG   0 V=V(G,K)+0.99999999
BM1   M1   0 V=(0.12471331*(URAMP(V(A,K))+1e-10))**-1.9909547
BM2   M2   0 V=(0.42968188*(URAMP(V(GG)+URAMP(V(A,K))/4.5730334)+1e-10))**3.4909547
BP    P    0 V=0.0011713028*(URAMP(V(GG)+URAMP(V(A,K))/10.642835)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0020582453*V(M1)*V(M2)
BIG   IG   0 V=0.00058565141*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00075455382*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5.6p
CGK   G    K 2.4p
CAK   A    K 4p
.ENDS
