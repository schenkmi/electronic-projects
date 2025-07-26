*
* Generic triode model: WE104D
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:08 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT WE104D A G K
BGG   GG   0 V=V(G,K)+-0.56998685
BM1   M1   0 V=(0.125122*(URAMP(V(A,K))+1e-10))^-0.50749668
BM2   M2   0 V=(0.74719924*(URAMP(V(GG)+URAMP(V(A,K))/2.0204341)+1e-10))^2.0074967
BP    P    0 V=0.00015779238*(URAMP(V(GG)+URAMP(V(A,K))/2.7040098)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*9.1039243e-05*V(M1)*V(M2)
BIG   IG   0 V=7.8896192e-05*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00017408127*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.9p
CGK   G    K 4.1p
CAK   A    K 3.4p
.ENDS
