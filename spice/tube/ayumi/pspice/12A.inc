*
* Generic triode model: 12A
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:27 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 12A A G K
BGG   GG   0 V=V(G,K)+-0.99999998
BM1   M1   0 V=(0.02099402*(URAMP(V(A,K))+1e-10))^-0.30518364
BM2   M2   0 V=(0.83094039*(URAMP(V(GG)+URAMP(V(A,K))/8.0527506)+1e-10))^1.8051836
BP    P    0 V=0.00060950916*(URAMP(V(GG)+URAMP(V(A,K))/9.6911291)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00037491826*V(M1)*V(M2)
BIG   IG   0 V=0.00030475458*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00040148822*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 8.5p
CGK   G    K 4p
CAK   A    K 2p
.ENDS
