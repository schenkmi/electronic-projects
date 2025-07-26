*
* Generic triode model: 12BH7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:14 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 12BH7 A G K
BGG   GG   0 V=V(G,K)+0.99999999
BM1   M1   0 V=(0.044635144*(URAMP(V(A,K))+1e-10))**-1.6555735
BM2   M2   0 V=(0.47534942*(URAMP(V(GG)+URAMP(V(A,K))/11.754204)+1e-10))**3.1555735
BP    P    0 V=0.0021126435*(URAMP(V(GG)+URAMP(V(A,K))/24.727503)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0024875937*V(M1)*V(M2)
BIG   IG   0 V=0.00112*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00112*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.6p
CGK   G    K 3.2p
CAK   A    K 0.5p
.ENDS
