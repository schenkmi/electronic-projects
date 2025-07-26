*
* Generic triode model: 6DQ5T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:49 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6DQ5T A G K
BGG   GG   0 V=V(G,K)+0.99999998
BM1   M1   0 V=(0.097911417*(URAMP(V(A,K))+1e-10))^-0.59116807
BM2   M2   0 V=(0.71730246*(URAMP(V(GG)+URAMP(V(A,K))/2.8872786)+1e-10))^2.0911681
BP    P    0 V=0.0034387228*(URAMP(V(GG)+URAMP(V(A,K))/4.0251899)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.001983081*V(M1)*V(M2)
BIG   IG   0 V=0.0017193614*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0030773802*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.5p
CGK   G    K 13.5p
CAK   A    K 10.5p
.ENDS
