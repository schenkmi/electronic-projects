*
* Generic triode model: 6LF6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:41 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6LF6T A G K
BGG   GG   0 V=V(G,K)+0.95447628
BM1   M1   0 V=(0.32637983*(URAMP(V(A,K))+1e-10))^-2.7688412
BM2   M2   0 V=(0.35138341*(URAMP(V(GG)+URAMP(V(A,K))/1.987306)+1e-10))^4.2688412
BP    P    0 V=0.0091876684*(URAMP(V(GG)+URAMP(V(A,K))/5.6556625)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.05015216*V(M1)*V(M2)
BIG   IG   0 V=0.0045938342*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0071353288*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 16.4p
CGK   G    K 20.9p
CAK   A    K 16.2p
.ENDS
