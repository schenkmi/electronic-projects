*
* Generic triode model: 6BQ5T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:19 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6BQ5T A G K
BGG   GG   0 V=V(G,K)+0.03372597
BM1   M1   0 V=(0.014266539*(URAMP(V(A,K))+1e-10))^-0.43210132
BM2   M2   0 V=(0.7763568*(URAMP(V(GG)+URAMP(V(A,K))/15.676066)+1e-10))^1.9321013
BP    P    0 V=0.0040800354*(URAMP(V(GG)+URAMP(V(A,K))/20.191832)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0023829269*V(M1)*V(M2)
BIG   IG   0 V=0.0020400177*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0023468355*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.6p
CGK   G    K 6.2p
CAK   A    K 6p
.ENDS
