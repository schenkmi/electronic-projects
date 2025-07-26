*
* Generic triode model: 71A
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:45 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 71A A G K
BGG   GG   0 V=V(G,K)+-0.99999999
BM1   M1   0 V=(0.058225528*(URAMP(V(A,K))+1e-10))^-0.29538374
BM2   M2   0 V=(0.83547598*(URAMP(V(GG)+URAMP(V(A,K))/2.8256337)+1e-10))^1.7953837
BP    P    0 V=0.00034434696*(URAMP(V(GG)+URAMP(V(A,K))/3.3820645)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00021307994*V(M1)*V(M2)
BIG   IG   0 V=0.00017217348*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00033568367*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.5p
CGK   G    K 3.2p
CAK   A    K 2.9p
.ENDS
