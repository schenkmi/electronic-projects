*
* Generic triode model: 6BQ6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:21 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6BQ6T A G K
BGG   GG   0 V=V(G,K)+-0.12830687
BM1   M1   0 V=(0.15009144*(URAMP(V(A,K))+1e-10))^-1.2848724
BM2   M2   0 V=(0.53862432*(URAMP(V(GG)+URAMP(V(A,K))/3.0739639)+1e-10))^2.7848724
BP    P    0 V=0.0022372419*(URAMP(V(GG)+URAMP(V(A,K))/5.7070648)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0018337045*V(M1)*V(M2)
BIG   IG   0 V=0.0011186209*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0017316916*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 6.4p
CGK   G    K 8.7p
CAK   A    K 6.4p
.ENDS
