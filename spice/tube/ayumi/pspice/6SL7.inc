*
* Generic triode model: 6SL7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:56 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6SL7 A G K
BGG   GG   0 V=V(G,K)+0.34892993
BM1   M1   0 V=(0.00093777395*(URAMP(V(A,K))+1e-10))^-0.098159943
BM2   M2   0 V=(0.9385794*(URAMP(V(GG)+URAMP(V(A,K))/65.496168)+1e-10))^1.5981599
BP    P    0 V=0.00080166786*(URAMP(V(GG)+URAMP(V(A,K))/69.782235)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00061341966*V(M1)*V(M2)
BIG   IG   0 V=0.00040083393*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00041812772*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.8p
CGK   G    K 3.4p
CAK   A    K 3.8p
.ENDS
