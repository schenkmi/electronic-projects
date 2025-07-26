*
* Generic triode model: RE604
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:07 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT RE604 A G K
BGG   GG   0 V=V(G,K)+0.99997938
BM1   M1   0 V=(0.030921607*(URAMP(V(A,K))+1e-10))**-0.18515194
BM2   M2   0 V=(0.89012745*(URAMP(V(GG)+URAMP(V(A,K))/3.5532613)+1e-10))**1.6851519
BP    P    0 V=0.00042470572*(URAMP(V(GG)+URAMP(V(A,K))/3.9918568)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00028831412*V(M1)*V(M2)
BIG   IG   0 V=0.00021235286*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00038155471*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 4p
CAK   A    K 4p
.ENDS
