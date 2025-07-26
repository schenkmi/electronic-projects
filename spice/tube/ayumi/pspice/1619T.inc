*
* Generic triode model: 1619T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:00 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 1619T A G K
BGG   GG   0 V=V(G,K)+-0.99999999
BM1   M1   0 V=(0.021726327*(URAMP(V(A,K))+1e-10))^-0.34437983
BM2   M2   0 V=(0.8132815*(URAMP(V(GG)+URAMP(V(A,K))/8.5941123)+1e-10))^1.8443798
BP    P    0 V=0.00095297512*(URAMP(V(GG)+URAMP(V(A,K))/10.567205)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00057412229*V(M1)*V(M2)
BIG   IG   0 V=0.00047648756*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0006149126*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.4p
CGK   G    K 6.1p
CAK   A    K 12.2p
.ENDS
