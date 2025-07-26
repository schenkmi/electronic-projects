*
* Generic triode model: ECC88
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:43 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT ECC88 A G K
BGG   GG   0 V=V(G,K)+0.34001426
BM1   M1   0 V=(0.009343174*(URAMP(V(A,K))+1e-10))^-0.49661195
BM2   M2   0 V=(0.75127268*(URAMP(V(GG)+URAMP(V(A,K))/26.621288)+1e-10))^1.9966119
BP    P    0 V=0.007130155*(URAMP(V(GG)+URAMP(V(A,K))/35.434921)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0041180199*V(M1)*V(M2)
BIG   IG   0 V=0.0035650775*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0038690245*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.4p
CGK   G    K 3.3p
CAK   A    K 1.8p
.ENDS
