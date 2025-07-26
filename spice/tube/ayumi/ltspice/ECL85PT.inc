*
* Generic triode model: ECL85PT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Wed Oct 22 16:34:56 2008
*               Plate
*               | Grid
*               | | Cathode
*               | | |
.SUBCKT ECL85PT A G K
BGG   GG   0 V=V(G,K)+0.61401316
BM1   M1   0 V=(0.075869075*(URAMP(V(A,K))+1e-10))**-1.148877
BM2   M2   0 V=(0.56627772*(URAMP(V(GG)+URAMP(V(A,K))/5.7167203)+1e-10))**2.648877
BP    P    0 V=0.0037731888*(URAMP(V(GG)+URAMP(V(A,K))/10.095259)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0027774625*V(M1)*V(M2)
BIG   IG   0 V=0.0018865944*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0024608947*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.4p
CGK   G    K 5.1p
CAK   A    K 7.1p
.ENDS
