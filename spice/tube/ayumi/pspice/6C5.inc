*
* Generic triode model: 6C5
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:28 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 6C5 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.02848961*(URAMP(V(A,K))+1e-10))^-1.0152318
BM2   M2   0 V=(0.5963665*(URAMP(V(GG)+URAMP(V(A,K))/14.167744)+1e-10))^2.5152318
BP    P    0 V=0.00080299639*(URAMP(V(GG)+URAMP(V(A,K))/23.756774)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00054026317*V(M1)*V(M2)
BIG   IG   0 V=0.0004014982*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00045272916*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.8p
CGK   G    K 4p
CAK   A    K 13p
.ENDS
