*
* Generic triode model: 6EW72
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:00 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6EW72 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.13863586*(URAMP(V(A,K))+1e-10))^-1.9260987
BM2   M2   0 V=(0.43781576*(URAMP(V(GG)+URAMP(V(A,K))/4.0551143)+1e-10))^3.4260987
BP    P    0 V=0.0052367933*(URAMP(V(GG)+URAMP(V(A,K))/9.262148)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0084764746*V(M1)*V(M2)
BIG   IG   0 V=0.0026183967*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.003488988*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9p
CGK   G    K 7p
CAK   A    K 1.2p
.ENDS
