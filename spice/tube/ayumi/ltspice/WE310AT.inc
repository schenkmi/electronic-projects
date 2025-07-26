*
* Generic triode model: WE310AT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:11 2008
*               Plate
*               | Grid
*               | | Cathode
*               | | |
.SUBCKT WE310AT A G K
BGG   GG   0 V=V(G,K)+0.54054476
BM1   M1   0 V=(0.010235898*(URAMP(V(A,K))+1e-10))**-0.32209043
BM2   M2   0 V=(0.82323027*(URAMP(V(GG)+URAMP(V(A,K))/17.269587)+1e-10))**1.8220904
BP    P    0 V=0.00076747724*(URAMP(V(GG)+URAMP(V(A,K))/20.977833)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00046759791*V(M1)*V(M2)
BIG   IG   0 V=0.00038373862*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00043926524*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.4p
CGK   G    K 3.6p
CAK   A    K 9p
.ENDS
