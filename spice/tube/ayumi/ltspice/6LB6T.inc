*
* Generic triode model: 6LB6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:40 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6LB6T A G K
BGG   GG   0 V=V(G,K)+0.99700414
BM1   M1   0 V=(0.23985722*(URAMP(V(A,K))+1e-10))**-1.8495045
BM2   M2   0 V=(0.44782743*(URAMP(V(GG)+URAMP(V(A,K))/2.3020886)+1e-10))**3.3495045
BP    P    0 V=0.0060056363*(URAMP(V(GG)+URAMP(V(A,K))/5.1405708)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0088470322*V(M1)*V(M2)
BIG   IG   0 V=0.0030028181*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.004837887*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 13.5p
CGK   G    K 19.5p
CAK   A    K 17.6p
.ENDS
