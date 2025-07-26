*
* Generic triode model: 6DT8
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:52 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6DT8 A G K
BGG   GG   0 V=V(G,K)+0.65426696
BM1   M1   0 V=(0.023769959*(URAMP(V(A,K))+1e-10))**-2.7472313
BM2   M2   0 V=(0.35317125*(URAMP(V(GG)+URAMP(V(A,K))/27.212026)+1e-10))**4.2472313
BP    P    0 V=0.0033862784*(URAMP(V(GG)+URAMP(V(A,K))/77.050513)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.017852785*V(M1)*V(M2)
BIG   IG   0 V=0.0016931392*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0017592759*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.6p
CGK   G    K 2.7p
CAK   A    K 1.6p
.ENDS
