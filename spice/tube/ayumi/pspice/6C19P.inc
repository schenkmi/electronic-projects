*
* Generic triode model: 6C19P
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:31 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6C19P A G K
BGG   GG   0 V=V(G,K)+0.10684511
BM1   M1   0 V=(0.32782347*(URAMP(V(A,K))+1e-10))^-1.8567866
BM2   M2   0 V=(0.44685593*(URAMP(V(GG)+URAMP(V(A,K))/1.687323)+1e-10))^3.3567866
BP    P    0 V=0.0032573245*(URAMP(V(GG)+URAMP(V(A,K))/3.7759889)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0048409525*V(M1)*V(M2)
BIG   IG   0 V=0.0016286622*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0030048458*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 8p
CGK   G    K 6.5p
CAK   A    K 2.5p
.ENDS
