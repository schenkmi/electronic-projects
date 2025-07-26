*
* Generic triode model: 6GY5T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:13 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6GY5T A G K
BGG   GG   0 V=V(G,K)+0.32801613
BM1   M1   0 V=(0.13136914*(URAMP(V(A,K))+1e-10))^-1.2504039
BM2   M2   0 V=(0.54537444*(URAMP(V(GG)+URAMP(V(A,K))/3.4606724)+1e-10))^2.7504039
BP    P    0 V=0.0046747506*(URAMP(V(GG)+URAMP(V(A,K))/6.345498)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0037232771*V(M1)*V(M2)
BIG   IG   0 V=0.0023373753*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0034848868*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.1p
CGK   G    K 12.9p
CAK   A    K 8.5p
.ENDS
