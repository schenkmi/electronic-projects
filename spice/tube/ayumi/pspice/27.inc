*
* Generic triode model: 27
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:29 2008
*          Plate
*          | Grid
*          | | Cathode
*          | | |
.SUBCKT 27 A G K
BGG   GG   0 V=V(G,K)+0.99999994
BM1   M1   0 V=(0.041269212*(URAMP(V(A,K))+1e-10))^-0.69845105
BM2   M2   0 V=(0.68229856*(URAMP(V(GG)+URAMP(V(A,K))/7.6982676)+1e-10))^2.1984511
BP    P    0 V=0.00036339312*(URAMP(V(GG)+URAMP(V(A,K))/11.282843)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00021306994*V(M1)*V(M2)
BIG   IG   0 V=0.00018169656*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00023106309*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3.3p
CGK   G    K 3.1p
CAK   A    K 2.3p
.ENDS
