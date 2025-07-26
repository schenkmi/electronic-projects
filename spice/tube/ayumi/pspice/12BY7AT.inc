*
* Generic triode model: 12BY7AT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:15 2008
*               Plate
*               | Grid
*               | | Cathode
*               | | |
.SUBCKT 12BY7AT A G K
BGG   GG   0 V=V(G,K)+-0.02185341
BM1   M1   0 V=(0.014593712*(URAMP(V(A,K))+1e-10))^-0.7027291
BM2   M2   0 V=(0.68097344*(URAMP(V(GG)+URAMP(V(A,K))/21.860549)+1e-10))^2.2027291
BP    P    0 V=0.0061475247*(URAMP(V(GG)+URAMP(V(A,K))/32.101912)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0036081888*V(M1)*V(M2)
BIG   IG   0 V=0.0030737623*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0033632383*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.1p
CGK   G    K 6.1p
CAK   A    K 3.4p
.ENDS
