*
* Generic triode model: 6CB5T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:35 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6CB5T A G K
BGG   GG   0 V=V(G,K)+0.12233722
BM1   M1   0 V=(0.099225459*(URAMP(V(A,K))+1e-10))^-0.68051603
BM2   M2   0 V=(0.68791056*(URAMP(V(GG)+URAMP(V(A,K))/3.1452557)+1e-10))^2.180516
BP    P    0 V=0.0027158296*(URAMP(V(GG)+URAMP(V(A,K))/4.572187)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0015860374*V(M1)*V(M2)
BIG   IG   0 V=0.0013579148*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0022959718*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9p
CGK   G    K 13p
CAK   A    K 9.6p
.ENDS
