*
* Generic triode model: 6080
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:10 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6080 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.37781455*(URAMP(V(A,K))+1e-10))^-1.6383781
BM2   M2   0 V=(0.47795388*(URAMP(V(GG)+URAMP(V(A,K))/1.3817523)+1e-10))^3.1383781
BP    P    0 V=0.0026607218*(URAMP(V(GG)+URAMP(V(A,K))/2.8909741)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0030745874*V(M1)*V(M2)
BIG   IG   0 V=0.0013303609*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0028241574*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 8.6p
CGK   G    K 6p
CAK   A    K 2.2p
.ENDS
