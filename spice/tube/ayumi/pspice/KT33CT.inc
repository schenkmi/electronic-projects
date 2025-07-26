*
* Generic triode model: KT33CT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:52 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT KT33CT A G K
BGG   GG   0 V=V(G,K)+0.96267547
BM1   M1   0 V=(0.055090322*(URAMP(V(A,K))+1e-10))^-0.90062349
BM2   M2   0 V=(0.62483768*(URAMP(V(GG)+URAMP(V(A,K))/6.8099498)+1e-10))^2.4006235
BP    P    0 V=0.0032650112*(URAMP(V(GG)+URAMP(V(A,K))/10.89875)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0020623072*V(M1)*V(M2)
BIG   IG   0 V=0.0016325056*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0020920259*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 8.4p
CGK   G    K 10.8p
CAK   A    K 10.9p
.ENDS
