*
* Generic triode model: 6GB5T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:07 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6GB5T A G K
BGG   GG   0 V=V(G,K)+0.84509256
BM1   M1   0 V=(0.074600608*(URAMP(V(A,K))+1e-10))^-0.78902807
BM2   M2   0 V=(0.65529996*(URAMP(V(GG)+URAMP(V(A,K))/4.6206063)+1e-10))^2.2890281
BP    P    0 V=0.0051497371*(URAMP(V(GG)+URAMP(V(A,K))/7.0511317)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0031020384*V(M1)*V(M2)
BIG   IG   0 V=0.0025748686*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0037083507*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 10.4p
CGK   G    K 12.9p
CAK   A    K 9.4p
.ENDS
