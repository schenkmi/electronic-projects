*
* Generic triode model: 12AU7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:08 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 12AU7 A G K
BGG   GG   0 V=V(G,K)+0.89005722
BM1   M1   0 V=(0.028826571*(URAMP(V(A,K))+1e-10))**-0.90897681
BM2   M2   0 V=(0.622671*(URAMP(V(GG)+URAMP(V(A,K))/13.089625)+1e-10))**2.4089768
BP    P    0 V=0.00087237591*(URAMP(V(GG)+URAMP(V(A,K))/21.021735)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00055330711*V(M1)*V(M2)
BIG   IG   0 V=0.00043618795*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00049917061*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.5p
CGK   G    K 1.6p
CAK   A    K 0.4p
.ENDS
