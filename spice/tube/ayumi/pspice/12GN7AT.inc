*
* Generic triode model: 12GN7AT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:16 2008
*               Plate
*               | Grid
*               | | Cathode
*               | | |
.SUBCKT 12GN7AT A G K
BGG   GG   0 V=V(G,K)+-0.52499611
BM1   M1   0 V=(0.0070794303*(URAMP(V(A,K))+1e-10))^-0.51284817
BM2   M2   0 V=(0.74521269*(URAMP(V(GG)+URAMP(V(A,K))/35.989804)+1e-10))^2.0128482
BP    P    0 V=0.032317671*(URAMP(V(GG)+URAMP(V(A,K))/48.294674)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.018638041*V(M1)*V(M2)
BIG   IG   0 V=0.016158835*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.017167779*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.1p
CGK   G    K 10.4p
CAK   A    K 3.9p
.ENDS
