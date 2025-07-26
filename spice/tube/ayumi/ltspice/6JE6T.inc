*
* Generic triode model: 6JE6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:16 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6JE6T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.15531724*(URAMP(V(A,K))+1e-10))**-0.92957636
BM2   M2   0 V=(0.61739158*(URAMP(V(GG)+URAMP(V(A,K))/2.4633995)+1e-10))**2.4295764
BP    P    0 V=0.0036485186*(URAMP(V(GG)+URAMP(V(A,K))/3.9900115)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0023385402*V(M1)*V(M2)
BIG   IG   0 V=0.0018242593*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0032785303*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.1p
CGK   G    K 12.9p
CAK   A    K 10.5p
.ENDS
