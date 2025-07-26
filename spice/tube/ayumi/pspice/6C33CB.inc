*
* Generic triode model: 6C33CB
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:32 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 6C33CB A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.31995431*(URAMP(V(A,K))+1e-10))^-1.9846926
BM2   M2   0 V=(0.43045404*(URAMP(V(GG)+URAMP(V(A,K))/1.7800853)+1e-10))^3.4846926
BP    P    0 V=0.015432878*(URAMP(V(GG)+URAMP(V(A,K))/4.1353667)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.026902304*V(M1)*V(M2)
BIG   IG   0 V=0.0077164388*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.013640208*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 31p
CGK   G    K 30p
CAK   A    K 10.5p
.ENDS
