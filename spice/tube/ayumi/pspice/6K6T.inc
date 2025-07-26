*
* Generic triode model: 6K6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:22 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6K6T A G K
BGG   GG   0 V=V(G,K)+0.99999995
BM1   M1   0 V=(0.055289504*(URAMP(V(A,K))+1e-10))^-0.63369812
BM2   M2   0 V=(0.70300479*(URAMP(V(GG)+URAMP(V(A,K))/5.3716382)+1e-10))^2.1336981
BP    P    0 V=0.00053448807*(URAMP(V(GG)+URAMP(V(A,K))/7.6409696)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00030960116*V(M1)*V(M2)
BIG   IG   0 V=0.00022926513*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00032413346*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.5p
CGK   G    K 3p
CAK   A    K 5.5p
.ENDS
