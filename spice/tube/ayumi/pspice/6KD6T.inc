*
* Generic triode model: 6KD6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:31 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6KD6T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.14076535*(URAMP(V(A,K))+1e-10))^-1.0380568
BM2   M2   0 V=(0.59100333*(URAMP(V(GG)+URAMP(V(A,K))/2.905521)+1e-10))^2.5380568
BP    P    0 V=0.0075955054*(URAMP(V(GG)+URAMP(V(A,K))/4.9162515)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0051832527*V(M1)*V(M2)
BIG   IG   0 V=0.0037977527*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0062293504*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 16.5p
CGK   G    K 23.5p
CAK   A    K 15.2p
.ENDS
