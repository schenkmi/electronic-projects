*
* Generic triode model: 6072
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:09 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6072 A G K
BGG   GG   0 V=V(G,K)+0.75743218
BM1   M1   0 V=(0.0057774859*(URAMP(V(A,K))+1e-10))**-0.42611934
BM2   M2   0 V=(0.77876794*(URAMP(V(GG)+URAMP(V(A,K))/38.292098)+1e-10))**1.9261193
BP    P    0 V=0.00098547839*(URAMP(V(GG)+URAMP(V(A,K))/49.1701)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00057643098*V(M1)*V(M2)
BIG   IG   0 V=0.0004927392*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00052295488*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.4p
CGK   G    K 1.4p
CAK   A    K 0.5p
.ENDS
