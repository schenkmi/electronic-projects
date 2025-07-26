*
* Generic triode model: PX4
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:04 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT PX4 A G K
BGG   GG   0 V=V(G,K)+-0.81287548
BM1   M1   0 V=(0.047093515*(URAMP(V(A,K))+1e-10))**-0.41642857
BM2   M2   0 V=(0.78270592*(URAMP(V(GG)+URAMP(V(A,K))/4.6140976)+1e-10))**1.9164286
BP    P    0 V=0.0010767826*(URAMP(V(GG)+URAMP(V(A,K))/5.895059)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.000631487*V(M1)*V(M2)
BIG   IG   0 V=0.00053839132*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00082368923*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 13.7p
CGK   G    K 7.7p
CAK   A    K 3.9p
.ENDS
