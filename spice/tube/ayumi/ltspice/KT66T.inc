*
* Generic triode model: KT66T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:54 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT KT66T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.051887963*(URAMP(V(A,K))+1e-10))**-0.76669755
BM2   M2   0 V=(0.66175569*(URAMP(V(GG)+URAMP(V(A,K))/6.5187433)+1e-10))**2.2666975
BP    P    0 V=0.0018223197*(URAMP(V(GG)+URAMP(V(A,K))/9.8506796)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0010893248*V(M1)*V(M2)
BIG   IG   0 V=0.00091115984*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0011955789*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 6.5p
CGK   G    K 8.1p
CAK   A    K 9p
.ENDS
