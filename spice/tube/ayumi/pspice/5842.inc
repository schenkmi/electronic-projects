*
* Generic triode model: 5842
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:05 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 5842 A G K
BGG   GG   0 V=V(G,K)+-0.46951652
BM1   M1   0 V=(0.0042897418*(URAMP(V(A,K))+1e-10))^-0.30633316
BM2   M2   0 V=(0.8304116*(URAMP(V(GG)+URAMP(V(A,K))/39.533476)+1e-10))^1.8063332
BP    P    0 V=0.017297881*(URAMP(V(GG)+URAMP(V(A,K))/47.607086)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.010632968*V(M1)*V(M2)
BIG   IG   0 V=0.0086489406*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0091968129*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.8p
CGK   G    K 9p
CAK   A    K 0.5p
.ENDS
