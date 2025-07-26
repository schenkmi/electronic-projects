*
* Generic triode model: 50HB26T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:23 2008
*               Plate
*               | Grid
*               | | Cathode
*               | | |
.SUBCKT 50HB26T A G K
BGG   GG   0 V=V(G,K)+0.99999978
BM1   M1   0 V=(0.092479665*(URAMP(V(A,K))+1e-10))**-0.92218999
BM2   M2   0 V=(0.6192743*(URAMP(V(GG)+URAMP(V(A,K))/4.1168586)+1e-10))**2.42219
BP    P    0 V=0.0043389918*(URAMP(V(GG)+URAMP(V(A,K))/6.6478758)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0027704924*V(M1)*V(M2)
BIG   IG   0 V=0.0021694959*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0031844715*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.6p
CGK   G    K 9.8p
CAK   A    K 6.7p
.ENDS
