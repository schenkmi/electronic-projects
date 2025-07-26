*
* Generic triode model: 6C4
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:26 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 6C4 A G K
BGG   GG   0 V=V(G,K)+0.736372
BM1   M1   0 V=(0.038076967*(URAMP(V(A,K))+1e-10))**-1.295136
BM2   M2   0 V=(0.53664652*(URAMP(V(GG)+URAMP(V(A,K))/12.168865)+1e-10))**2.795136
BP    P    0 V=0.0010502869*(URAMP(V(GG)+URAMP(V(A,K))/22.675755)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00086837935*V(M1)*V(M2)
BIG   IG   0 V=0.00055989418*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00049903612*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.6p
CGK   G    K 1.8p
CAK   A    K 1.3p
.ENDS
