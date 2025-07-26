*
* Generic triode model: 6CB6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:37 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6CB6T A G K
BGG   GG   0 V=V(G,K)+0.7350712
BM1   M1   0 V=(0.031445788*(URAMP(V(A,K))+1e-10))^-2.20504
BM2   M2   0 V=(0.40485393*(URAMP(V(GG)+URAMP(V(A,K))/18.926098)+1e-10))^3.70504
BP    P    0 V=0.0046867337*(URAMP(V(GG)+URAMP(V(A,K))/46.747967)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.010960467*V(M1)*V(M2)
BIG   IG   0 V=0.0023433669*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0024945513*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.6p
CGK   G    K 3.9p
CAK   A    K 1.9p
.ENDS
