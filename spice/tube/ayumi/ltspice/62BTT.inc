*
* Generic triode model: 62BTT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:25 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 62BTT A G K
BGG   GG   0 V=V(G,K)+0.99999993
BM1   M1   0 V=(0.10647561*(URAMP(V(A,K))+1e-10))**-1.0560332
BM2   M2   0 V=(0.58684685*(URAMP(V(GG)+URAMP(V(A,K))/3.8802609)+1e-10))**2.5560332
BP    P    0 V=0.002839063*(URAMP(V(GG)+URAMP(V(A,K))/6.6120504)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0019598422*V(M1)*V(M2)
BIG   IG   0 V=0.0014195315*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0020873677*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.5p
CGK   G    K 13.5p
CAK   A    K 10.5p
.ENDS
