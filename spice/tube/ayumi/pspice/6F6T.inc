*
* Generic triode model: 6F6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:04 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6F6T A G K
BGG   GG   0 V=V(G,K)+0.99999999
BM1   M1   0 V=(0.043621772*(URAMP(V(A,K))+1e-10))^-0.51782633
BM2   M2   0 V=(0.74337419*(URAMP(V(GG)+URAMP(V(A,K))/5.8829755)+1e-10))^2.0178263
BP    P    0 V=0.00053269576*(URAMP(V(GG)+URAMP(V(A,K))/7.9138819)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00030710831*V(M1)*V(M2)
BIG   IG   0 V=0.00019764236*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00037552047*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 5p
CAK   A    K 6.9p
.ENDS
