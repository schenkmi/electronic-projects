*
* Generic triode model: 12AY7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:10 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 12AY7 A G K
BGG   GG   0 V=V(G,K)+0.71171435
BM1   M1   0 V=(0.0094119714*(URAMP(V(A,K))+1e-10))**-0.68363668
BM2   M2   0 V=(0.68692746*(URAMP(V(GG)+URAMP(V(A,K))/33.263227)+1e-10))**2.1836367
BP    P    0 V=0.00092634255*(URAMP(V(GG)+URAMP(V(A,K))/48.423202)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00054133951*V(M1)*V(M2)
BIG   IG   0 V=0.00046317128*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00049201413*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.3p
CGK   G    K 1.3p
CAK   A    K 0.6p
.ENDS
