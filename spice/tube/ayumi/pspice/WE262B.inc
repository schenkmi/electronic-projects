*
* Generic triode model: WE262B
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:09 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT WE262B A G K
BGG   GG   0 V=V(G,K)+0.88434569
BM1   M1   0 V=(0.017408503*(URAMP(V(A,K))+1e-10))^-0.46076878
BM2   M2   0 V=(0.76500606*(URAMP(V(GG)+URAMP(V(A,K))/13.498802)+1e-10))^1.9607688
BP    P    0 V=0.00032011417*(URAMP(V(GG)+URAMP(V(A,K))/17.645353)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00018582795*V(M1)*V(M2)
BIG   IG   0 V=0.00016005708*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0001876514*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.9p
CGK   G    K 2.4p
CAK   A    K 3.8p
.ENDS
