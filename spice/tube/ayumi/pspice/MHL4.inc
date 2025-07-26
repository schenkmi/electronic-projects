*
* Generic triode model: MHL4
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:00 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT MHL4 A G K
BGG   GG   0 V=V(G,K)+0.4016137
BM1   M1   0 V=(0.017679176*(URAMP(V(A,K))+1e-10))^-0.56606943
BM2   M2   0 V=(0.72601626*(URAMP(V(GG)+URAMP(V(A,K))/15.49754)+1e-10))^2.0660694
BP    P    0 V=0.00078960956*(URAMP(V(GG)+URAMP(V(A,K))/21.345996)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00045482006*V(M1)*V(M2)
BIG   IG   0 V=0.00039480478*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00045093613*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3.9p
CGK   G    K 5.4p
CAK   A    K 4.5p
.ENDS
