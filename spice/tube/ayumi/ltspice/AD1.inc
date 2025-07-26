*
* Generic triode model: AD1
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:28 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT AD1 A G K
BGG   GG   0 V=V(G,K)+0.99548209
BM1   M1   0 V=(0.033599669*(URAMP(V(A,K))+1e-10))**-0.23303356
BM2   M2   0 V=(0.8655343*(URAMP(V(GG)+URAMP(V(A,K))/4.0019946)+1e-10))**1.7330336
BP    P    0 V=0.0011960914*(URAMP(V(GG)+URAMP(V(A,K))/4.6237273)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00077502632*V(M1)*V(M2)
BIG   IG   0 V=0.00059804568*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0010063534*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 23p
CGK   G    K 7.5p
CAK   A    K 5.5p
.ENDS
