*
* Generic triode model: 9002
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:28 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 9002 A G K
BGG   GG   0 V=V(G,K)+0.90658712
BM1   M1   0 V=(0.01433184*(URAMP(V(A,K))+1e-10))^-0.61356953
BM2   M2   0 V=(0.70969986*(URAMP(V(GG)+URAMP(V(A,K))/20.255608)+1e-10))^2.1135695
BP    P    0 V=0.00098929697*(URAMP(V(GG)+URAMP(V(A,K))/28.541091)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00057163937*V(M1)*V(M2)
BIG   IG   0 V=0.00049464849*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00054709459*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.4p
CGK   G    K 1.2p
CAK   A    K 1.1p
.ENDS
