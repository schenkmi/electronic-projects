*
* Generic triode model: 5751
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:03 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 5751 A G K
BGG   GG   0 V=V(G,K)+0.5559861
BM1   M1   0 V=(0.0052861104*(URAMP(V(A,K))+1e-10))**-0.6766372
BM2   M2   0 V=(0.68913644*(URAMP(V(GG)+URAMP(V(A,K))/58.807619)+1e-10))**2.1766372
BP    P    0 V=0.0013669039*(URAMP(V(GG)+URAMP(V(A,K))/85.335234)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00079762831*V(M1)*V(M2)
BIG   IG   0 V=0.00068345195*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00070754928*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.4p
CGK   G    K 1.4p
CAK   A    K 0.5p
.ENDS
