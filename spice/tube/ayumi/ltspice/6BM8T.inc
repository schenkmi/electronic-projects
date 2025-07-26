*
* Generic triode model: 6BM8T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:16 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6BM8T A G K
BGG   GG   0 V=V(G,K)+0.43636433
BM1   M1   0 V=(0.0039399689*(URAMP(V(A,K))+1e-10))**-0.44800866
BM2   M2   0 V=(0.77001711*(URAMP(V(GG)+URAMP(V(A,K))/58.371753)+1e-10))**1.9480087
BP    P    0 V=0.0015179644*(URAMP(V(GG)+URAMP(V(A,K))/75.805787)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00088337368*V(M1)*V(M2)
BIG   IG   0 V=0.00075898218*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0007891176*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 2.7p
CAK   A    K 4p
.ENDS
