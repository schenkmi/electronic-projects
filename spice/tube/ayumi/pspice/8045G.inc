*
* Generic triode model: 8045G
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:25 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 8045G A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.16254949*(URAMP(V(A,K))+1e-10))^-1.8473377
BM2   M2   0 V=(0.44811732*(URAMP(V(GG)+URAMP(V(A,K))/3.3951672)+1e-10))^3.3473377
BP    P    0 V=0.006744417*(URAMP(V(GG)+URAMP(V(A,K))/7.5765141)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0099093555*V(M1)*V(M2)
BIG   IG   0 V=0.0033722085*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0047506048*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 16p
CGK   G    K 24p
CAK   A    K 16p
.ENDS
