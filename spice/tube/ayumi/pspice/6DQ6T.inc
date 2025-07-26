*
* Generic triode model: 6DQ6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:50 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6DQ6T A G K
BGG   GG   0 V=V(G,K)+-1
BM1   M1   0 V=(0.17812317*(URAMP(V(A,K))+1e-10))^-1.6443126
BM2   M2   0 V=(0.47705181*(URAMP(V(GG)+URAMP(V(A,K))/2.9358797)+1e-10))^3.1443126
BP    P    0 V=0.0034562529*(URAMP(V(GG)+URAMP(V(A,K))/6.1542156)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0040197798*V(M1)*V(M2)
BIG   IG   0 V=0.0017281264*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0026038839*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 6.3p
CGK   G    K 8.7p
CAK   A    K 6.5p
.ENDS
