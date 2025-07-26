*
* Generic triode model: 3C33
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:38:58 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 3C33 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.045418916*(URAMP(V(A,K))+1e-10))^-0.95262383
BM2   M2   0 V=(0.61158991*(URAMP(V(GG)+URAMP(V(A,K))/8.5517252)+1e-10))^2.4526238
BP    P    0 V=0.0048487914*(URAMP(V(GG)+URAMP(V(A,K))/13.982777)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0031463341*V(M1)*V(M2)
BIG   IG   0 V=0.0024243957*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0029537409*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5p
CGK   G    K 8.5p
CAK   A    K 4p
.ENDS
