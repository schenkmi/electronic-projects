*
* Generic triode model: 6BL8T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:13 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6BL8T A G K
BGG   GG   0 V=V(G,K)+0.9999996
BM1   M1   0 V=(0.034840251*(URAMP(V(A,K))+1e-10))**-1.1549542
BM2   M2   0 V=(0.5649815*(URAMP(V(GG)+URAMP(V(A,K))/12.48609)+1e-10))**2.6549542
BP    P    0 V=0.002049189*(URAMP(V(GG)+URAMP(V(A,K))/22.099998)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0015151796*V(M1)*V(M2)
BIG   IG   0 V=0.0010245945*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0011652414*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.5p
CGK   G    K 2.5p
CAK   A    K 1.8p
.ENDS
