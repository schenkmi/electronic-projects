*
* Generic triode model: 12AT7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:07 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 12AT7 A G K
BGG   GG   0 V=V(G,K)+0.67585931
BM1   M1   0 V=(0.015420581*(URAMP(V(A,K))+1e-10))^-1.768756
BM2   M2   0 V=(0.45889017*(URAMP(V(GG)+URAMP(V(A,K))/35.090106)+1e-10))^3.268756
BP    P    0 V=0.0031809222*(URAMP(V(GG)+URAMP(V(A,K))/76.46733)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0042575005*V(M1)*V(M2)
BIG   IG   0 V=0.0015904611*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0016530623*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.5p
CGK   G    K 2.2p
CAK   A    K 0.5p
.ENDS
