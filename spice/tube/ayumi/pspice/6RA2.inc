*
* Generic triode model: 6RA2
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:44 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6RA2 A G K
BGG   GG   0 V=V(G,K)+0.99999998
BM1   M1   0 V=(0.16011188*(URAMP(V(A,K))+1e-10))^-0.98934882
BM2   M2   0 V=(0.60256722*(URAMP(V(GG)+URAMP(V(A,K))/2.4822192)+1e-10))^2.4893488
BP    P    0 V=0.0023398311*(URAMP(V(GG)+URAMP(V(A,K))/4.1194063)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0015501289*V(M1)*V(M2)
BIG   IG   0 V=0.0011699156*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0020717035*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5.2p
CGK   G    K 6.9p
CAK   A    K 5.4p
.ENDS
