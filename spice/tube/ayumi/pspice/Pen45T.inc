*
* Generic triode model: Pen45T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:02 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT Pen45T A G K
BGG   GG   0 V=V(G,K)+0.77688676
BM1   M1   0 V=(0.013260501*(URAMP(V(A,K))+1e-10))^-0.37488998
BM2   M2   0 V=(0.80004694*(URAMP(V(GG)+URAMP(V(A,K))/15.078846)+1e-10))^1.87489
BP    P    0 V=0.0032965978*(URAMP(V(GG)+URAMP(V(A,K))/18.847452)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0019602521*V(M1)*V(M2)
BIG   IG   0 V=0.0016482989*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.001914113*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.6p
CGK   G    K 13.2p
CAK   A    K 11.9p
.ENDS
