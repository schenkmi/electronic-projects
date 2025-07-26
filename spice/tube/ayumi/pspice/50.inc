*
* Generic triode model: 50
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:33 2008
*          Plate
*          | Grid
*          | | Cathode
*          | | |
.SUBCKT 50 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.053592842*(URAMP(V(A,K))+1e-10))^-0.32643301
BM2   M2   0 V=(0.82127294*(URAMP(V(GG)+URAMP(V(A,K))/3.3349055)+1e-10))^1.826433
BP    P    0 V=0.00024452775*(URAMP(V(GG)+URAMP(V(A,K))/4.0606543)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0001486389*V(M1)*V(M2)
BIG   IG   0 V=0.00012226387*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00021794382*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 4p
CAK   A    K 4p
.ENDS
