*
* Generic triode model: 75
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:46 2008
*          Plate
*          | Grid
*          | | Cathode
*          | | |
.SUBCKT 75 A G K
BGG   GG   0 V=V(G,K)+0.62861222
BM1   M1   0 V=(0.0015984063*(URAMP(V(A,K))+1e-10))^-0.25776155
BM2   M2   0 V=(0.85335807*(URAMP(V(GG)+URAMP(V(A,K))/91.742588)+1e-10))^1.7577615
BP    P    0 V=0.00073974709*(URAMP(V(GG)+URAMP(V(A,K))/107.50773)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00046981663*V(M1)*V(M2)
BIG   IG   0 V=0.00036987355*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00038021882*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.7p
CGK   G    K 1.7p
CAK   A    K 3.8p
.ENDS
