*
* Generic triode model: 6F5
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:02 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 6F5 A G K
BGG   GG   0 V=V(G,K)+0.58201919
BM1   M1   0 V=(0.0023425283*(URAMP(V(A,K))+1e-10))**-0.39892191
BM2   M2   0 V=(0.7899219*(URAMP(V(GG)+URAMP(V(A,K))/89.68007)+1e-10))**1.8989219
BP    P    0 V=0.00094722724*(URAMP(V(GG)+URAMP(V(A,K))/113.5303)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00055846113*V(M1)*V(M2)
BIG   IG   0 V=0.00047361362*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00048615622*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2p
CGK   G    K 6p
CAK   A    K 12p
.ENDS
