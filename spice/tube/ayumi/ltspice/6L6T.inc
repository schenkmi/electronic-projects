*
* Generic triode model: 6L6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:38 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6L6T A G K
BGG   GG   0 V=V(G,K)+0.91804059
BM1   M1   0 V=(0.10751078*(URAMP(V(A,K))+1e-10))**-1.743575
BM2   M2   0 V=(0.4624527*(URAMP(V(GG)+URAMP(V(A,K))/4.9999386)+1e-10))**3.243575
BP    P    0 V=0.0016883841*(URAMP(V(GG)+URAMP(V(A,K))/10.811784)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0021948901*V(M1)*V(M2)
BIG   IG   0 V=0.0022135943*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00056920996*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.4p
CGK   G    K 5.7p
CAK   A    K 5.9p
.ENDS
