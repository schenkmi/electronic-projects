*
* Generic triode model: 59Th
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:43 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 59Th A G K
BGG   GG   0 V=V(G,K)+0.99979071
BM1   M1   0 V=(0.073387615*(URAMP(V(A,K))+1e-10))**-5.8658889
BM2   M2   0 V=(0.20364141*(URAMP(V(GG)+URAMP(V(A,K))/10.851403)+1e-10))**7.3658889
BP    P    0 V=0.00056363412*(URAMP(V(GG)+URAMP(V(A,K))/53.286819)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*1.6789061*V(M1)*V(M2)
BIG   IG   0 V=0.00021213204*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00038183766*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 4p
CAK   A    K 4p
.ENDS
