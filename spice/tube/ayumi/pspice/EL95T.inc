*
* Generic triode model: EL95T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:50 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT EL95T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.012612458*(URAMP(V(A,K))+1e-10))^-0.34815571
BM2   M2   0 V=(0.81161992*(URAMP(V(GG)+URAMP(V(A,K))/14.936032)+1e-10))^1.8481557
BP    P    0 V=0.001923993*(URAMP(V(GG)+URAMP(V(A,K))/18.402742)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0011570767*V(M1)*V(M2)
BIG   IG   0 V=0.00096199651*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0011209319*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.5p
CGK   G    K 3.2p
CAK   A    K 3.5p
.ENDS
