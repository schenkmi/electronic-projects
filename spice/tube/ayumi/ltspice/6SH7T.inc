*
* Generic triode model: 6SH7T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:54 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6SH7T A G K
BGG   GG   0 V=V(G,K)+0.69566782
BM1   M1   0 V=(0.0053973753*(URAMP(V(A,K))+1e-10))**-0.3342013
BM2   M2   0 V=(0.81779465*(URAMP(V(GG)+URAMP(V(A,K))/33.758141)+1e-10))**1.8342013
BP    P    0 V=0.0026548433*(URAMP(V(GG)+URAMP(V(A,K))/41.279484)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0016073552*V(M1)*V(M2)
BIG   IG   0 V=0.0013274216*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0014244744*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3.4p
CGK   G    K 5.1p
CAK   A    K 7p
.ENDS
