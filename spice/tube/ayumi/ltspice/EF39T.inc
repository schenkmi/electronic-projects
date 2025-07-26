*
* Generic triode model: EF39T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:46:08 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT EF39T A G K
BGG   GG   0 V=V(G,K)+0.0036430998
BM1   M1   0 V=(0.43484193*(URAMP(V(A,K))+1e-10))**-13.214995
BM2   M2   0 V=(0.10193683*(URAMP(V(GG)+URAMP(V(A,K))/2.0652635)+1e-10))**14.714995
BP    P    0 V=0.0015911301*(URAMP(V(GG)+URAMP(V(A,K))/20.260228)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*4892774400*V(M1)*V(M2)
BIG   IG   0 V=0.00079556505*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00091480891*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 16.5p
CGK   G    K 23.5p
CAK   A    K 15.2p
.ENDS
