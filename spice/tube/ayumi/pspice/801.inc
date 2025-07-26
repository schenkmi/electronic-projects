*
* Generic triode model: 801
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:56 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 801 A G K
BGG   GG   0 V=V(G,K)+0.99999971
BM1   M1   0 V=(0.0050075033*(URAMP(V(A,K))+1e-10))^-0.062819059
BM2   M2   0 V=(0.95980401*(URAMP(V(GG)+URAMP(V(A,K))/8.027152)+1e-10))^1.5628191
BP    P    0 V=0.00024894009*(URAMP(V(GG)+URAMP(V(A,K))/8.3633241)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00020395304*V(M1)*V(M2)
BIG   IG   0 V=4.8000001e-05*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.000225*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 6p
CGK   G    K 4.5p
CAK   A    K 1.5p
.ENDS
