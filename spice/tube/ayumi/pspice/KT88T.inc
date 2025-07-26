*
* Generic triode model: KT88T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:55 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT KT88T A G K
BGG   GG   0 V=V(G,K)+0.99999999
BM1   M1   0 V=(0.097534908*(URAMP(V(A,K))+1e-10))^-1.4398564
BM2   M2   0 V=(0.51022901*(URAMP(V(GG)+URAMP(V(A,K))/5.0214944)+1e-10))^2.9398564
BP    P    0 V=0.0031096914*(URAMP(V(GG)+URAMP(V(A,K))/9.8416483)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0029317575*V(M1)*V(M2)
BIG   IG   0 V=0.0015548457*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0020406477*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.2p
CGK   G    K 9p
CAK   A    K 10.9p
.ENDS
