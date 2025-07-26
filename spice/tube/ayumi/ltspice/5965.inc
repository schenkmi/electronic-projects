*
* Generic triode model: 5965
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:06 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 5965 A G K
BGG   GG   0 V=V(G,K)+0.61035688
BM1   M1   0 V=(0.024336203*(URAMP(V(A,K))+1e-10))**-2.1648233
BM2   M2   0 V=(0.40929668*(URAMP(V(GG)+URAMP(V(A,K))/24.272617)+1e-10))**3.6648233
BP    P    0 V=0.0045273524*(URAMP(V(GG)+URAMP(V(A,K))/59.303235)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.010017704*V(M1)*V(M2)
BIG   IG   0 V=0.0022636762*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0023786712*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3p
CGK   G    K 4p
CAK   A    K 0.5p
.ENDS
