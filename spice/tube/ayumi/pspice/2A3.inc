*
* Generic triode model: 2A3
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:38:56 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 2A3 A G K
BGG   GG   0 V=V(G,K)+-0.47258991
BM1   M1   0 V=(0.056835059*(URAMP(V(A,K))+1e-10))^-0.4044593
BM2   M2   0 V=(0.78762513*(URAMP(V(GG)+URAMP(V(A,K))/3.7366878)+1e-10))^1.9044593
BP    P    0 V=0.0012053852*(URAMP(V(GG)+URAMP(V(A,K))/4.7442465)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.000709416*V(M1)*V(M2)
BIG   IG   0 V=0.00060269261*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0010032299*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 16.5p
CGK   G    K 7.5p
CAK   A    K 5.5p
.ENDS
