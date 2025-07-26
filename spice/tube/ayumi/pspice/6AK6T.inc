*
* Generic triode model: 6AK6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:03 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6AK6T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.047037015*(URAMP(V(A,K))+1e-10))^-0.80231696
BM2   M2   0 V=(0.65151759*(URAMP(V(GG)+URAMP(V(A,K))/7.4086847)+1e-10))^2.302317
BP    P    0 V=0.00071109747*(URAMP(V(GG)+URAMP(V(A,K))/11.371427)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00043043074*V(M1)*V(M2)
BIG   IG   0 V=0.00035554873*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00045138222*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.5p
CGK   G    K 2.1p
CAK   A    K 4.1p
.ENDS
