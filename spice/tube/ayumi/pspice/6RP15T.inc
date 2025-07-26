*
* Generic triode model: 6RP15T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:50 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 6RP15T A G K
BGG   GG   0 V=V(G,K)+0.81734398
BM1   M1   0 V=(0.014236687*(URAMP(V(A,K))+1e-10))^-0.37474407
BM2   M2   0 V=(0.80010921*(URAMP(V(GG)+URAMP(V(A,K))/14.040541)+1e-10))^1.8747441
BP    P    0 V=0.0033159507*(URAMP(V(GG)+URAMP(V(A,K))/17.548281)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0019718712*V(M1)*V(M2)
BIG   IG   0 V=0.0016579754*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0019454182*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.6p
CGK   G    K 6.2p
CAK   A    K 6p
.ENDS
