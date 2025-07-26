*
* Generic triode model: 6AQ8
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:09 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6AQ8 A G K
BGG   GG   0 V=V(G,K)+0.46274
BM1   M1   0 V=(0.016397559*(URAMP(V(A,K))+1e-10))**-1.8244468
BM2   M2   0 V=(0.4512029*(URAMP(V(GG)+URAMP(V(A,K))/33.468219)+1e-10))**3.3244468
BP    P    0 V=0.0053412983*(URAMP(V(GG)+URAMP(V(A,K))/74.175541)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0076348*V(M1)*V(M2)
BIG   IG   0 V=0.0026706491*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0027790257*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.5p
CGK   G    K 3.1p
CAK   A    K 1.2p
.ENDS
