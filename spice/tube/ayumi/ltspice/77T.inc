*
* Generic triode model: 77T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:48 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 77T A G K
BGG   GG   0 V=V(G,K)+-1
BM1   M1   0 V=(0.0016865419*(URAMP(V(A,K))+1e-10))**-0.038461538
BM2   M2   0 V=(0.975*(URAMP(V(GG)+URAMP(V(A,K))/14.823231)+1e-10))**1.5384615
BP    P    0 V=0.00049759802*(URAMP(V(GG)+URAMP(V(A,K))/15.203314)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00043219909*V(M1)*V(M2)
BIG   IG   0 V=0.00024879901*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00029869203*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.9p
CGK   G    K 2.8p
CAK   A    K 11p
.ENDS
