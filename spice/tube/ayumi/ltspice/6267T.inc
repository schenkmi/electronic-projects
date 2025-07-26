*
* Generic triode model: 6267T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:16 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6267T A G K
BGG   GG   0 V=V(G,K)+0.59868749
BM1   M1   0 V=(0.010782364*(URAMP(V(A,K))+1e-10))**-0.70765893
BM2   M2   0 V=(0.67945278*(URAMP(V(GG)+URAMP(V(A,K))/29.728844)+1e-10))**2.2076589
BP    P    0 V=0.0013378994*(URAMP(V(GG)+URAMP(V(A,K))/43.754099)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00078620809*V(M1)*V(M2)
BIG   IG   0 V=0.00066894969*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00071507731*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.6p
CGK   G    K 2.3p
CAK   A    K 5.3p
.ENDS
