*
* Generic triode model: ML4
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:01 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT ML4 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.09991405*(URAMP(V(A,K))+1e-10))^-2.2677255
BM2   M2   0 V=(0.39811818*(URAMP(V(GG)+URAMP(V(A,K))/6.0239958)+1e-10))^3.7677255
BP    P    0 V=0.0012796938*(URAMP(V(GG)+URAMP(V(A,K))/15.131175)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0032670893*V(M1)*V(M2)
BIG   IG   0 V=0.0006398469*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00076878036*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 4p
CAK   A    K 4p
.ENDS
