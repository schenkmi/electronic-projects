*
* Generic triode model: 53
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:36 2008
*          Plate
*          | Grid
*          | | Cathode
*          | | |
.SUBCKT 53 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.00077005461*(URAMP(V(A,K))+1e-10))^-0.038461586
BM2   M2   0 V=(0.97499997*(URAMP(V(GG)+URAMP(V(A,K))/32.465269)+1e-10))^1.5384616
BP    P    0 V=0.00055508206*(URAMP(V(GG)+URAMP(V(A,K))/33.297713)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00048212799*V(M1)*V(M2)
BIG   IG   0 V=0.00016903085*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00042499185*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 4p
CAK   A    K 4p
.ENDS
