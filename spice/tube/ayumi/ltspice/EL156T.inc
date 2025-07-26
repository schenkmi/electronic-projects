*
* Generic triode model: EL156T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:51 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT EL156T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.011748081*(URAMP(V(A,K))+1e-10))**-0.24110473
BM2   M2   0 V=(0.86152198*(URAMP(V(GG)+URAMP(V(A,K))/11.787288)+1e-10))**1.7411047
BP    P    0 V=0.0036416815*(URAMP(V(GG)+URAMP(V(A,K))/13.681935)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0023436481*V(M1)*V(M2)
BIG   IG   0 V=0.0018208407*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0022273001*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.9p
CGK   G    K 11.1p
CAK   A    K 7p
.ENDS
