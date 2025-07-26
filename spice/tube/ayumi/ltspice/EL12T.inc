*
* Generic triode model: EL12T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:44 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT EL12T A G K
BGG   GG   0 V=V(G,K)+0.99999993
BM1   M1   0 V=(0.014506242*(URAMP(V(A,K))+1e-10))**-0.43509457
BM2   M2   0 V=(0.77515592*(URAMP(V(GG)+URAMP(V(A,K))/15.499816)+1e-10))**1.9350946
BP    P    0 V=0.0044414767*(URAMP(V(GG)+URAMP(V(A,K))/19.99574)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0025921537*V(M1)*V(M2)
BIG   IG   0 V=0.0022207383*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0025580516*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.4p
CGK   G    K 5.7p
CAK   A    K 5.9p
.ENDS
