*
* Generic triode model: 6CD6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:38 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6CD6T A G K
BGG   GG   0 V=V(G,K)+-0.11853336
BM1   M1   0 V=(0.13222789*(URAMP(V(A,K))+1e-10))^-1.0472626
BM2   M2   0 V=(0.58886744*(URAMP(V(GG)+URAMP(V(A,K))/3.1092727)+1e-10))^2.5472626
BP    P    0 V=0.0032013575*(URAMP(V(GG)+URAMP(V(A,K))/5.2800894)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0021974746*V(M1)*V(M2)
BIG   IG   0 V=0.0016006788*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0025519299*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.5p
CGK   G    K 12.6p
CAK   A    K 7.5p
.ENDS
