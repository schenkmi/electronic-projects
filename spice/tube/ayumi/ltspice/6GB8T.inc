*
* Generic triode model: 6GB8T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:09 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6GB8T A G K
BGG   GG   0 V=V(G,K)+0.18361766
BM1   M1   0 V=(0.023367579*(URAMP(V(A,K))+1e-10))**-0.5778846
BM2   M2   0 V=(0.72188802*(URAMP(V(GG)+URAMP(V(A,K))/11.901617)+1e-10))**2.0778846
BP    P    0 V=0.0065222813*(URAMP(V(GG)+URAMP(V(A,K))/16.486791)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0037584671*V(M1)*V(M2)
BIG   IG   0 V=0.0032611407*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0038634597*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 10.8p
CGK   G    K 13.4p
CAK   A    K 16.3p
.ENDS
