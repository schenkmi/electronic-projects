*
* Generic triode model: 6W6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:06 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6W6T A G K
BGG   GG   0 V=V(G,K)+0.99999997
BM1   M1   0 V=(0.032441217*(URAMP(V(A,K))+1e-10))**-0.3672418
BM2   M2   0 V=(0.80332392*(URAMP(V(GG)+URAMP(V(A,K))/6.062537)+1e-10))**1.8672418
BP    P    0 V=0.0022625178*(URAMP(V(GG)+URAMP(V(A,K))/7.546815)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.001349448*V(M1)*V(M2)
BIG   IG   0 V=0.0012737812*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0012049281*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 6.5p
CGK   G    K 8.6p
CAK   A    K 8.2p
.ENDS
