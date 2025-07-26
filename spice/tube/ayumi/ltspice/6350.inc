*
* Generic triode model: 6350
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:18 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6350 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.018707344*(URAMP(V(A,K))+1e-10))**-0.6749557
BM2   M2   0 V=(0.68966922*(URAMP(V(GG)+URAMP(V(A,K))/16.588714)+1e-10))**2.1749557
BP    P    0 V=0.0025107579*(URAMP(V(GG)+URAMP(V(A,K))/24.053145)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0014646013*V(M1)*V(M2)
BIG   IG   0 V=0.001255379*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0014135709*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3.2p
CGK   G    K 3.6p
CAK   A    K 0.6p
.ENDS
