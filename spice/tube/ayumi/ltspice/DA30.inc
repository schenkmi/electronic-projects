*
* Generic triode model: DA30
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:30 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT DA30 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.07753701*(URAMP(V(A,K))+1e-10))**-0.45364741
BM2   M2   0 V=(0.76779464*(URAMP(V(GG)+URAMP(V(A,K))/2.9947681)+1e-10))**1.9536474
BP    P    0 V=0.00090166046*(URAMP(V(GG)+URAMP(V(A,K))/3.9004806)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00052412019*V(M1)*V(M2)
BIG   IG   0 V=0.00045083023*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00081893623*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 13p
CGK   G    K 10p
CAK   A    K 6.5p
.ENDS
