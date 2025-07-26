*
* Generic triode model: 829BT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:56 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 829BT A G K
BGG   GG   0 V=V(G,K)+-0.31275554
BM1   M1   0 V=(0.031067512*(URAMP(V(A,K))+1e-10))^-0.44774132
BM2   M2   0 V=(0.7701228*(URAMP(V(GG)+URAMP(V(A,K))/7.3992794)+1e-10))^1.9477413
BP    P    0 V=0.0023834096*(URAMP(V(GG)+URAMP(V(A,K))/9.6079215)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0013870937*V(M1)*V(M2)
BIG   IG   0 V=0.0013863621*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0016211493*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5.9p
CGK   G    K 8.6p
CAK   A    K 6.9p
.ENDS
