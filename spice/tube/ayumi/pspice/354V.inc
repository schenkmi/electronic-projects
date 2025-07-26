*
* Generic triode model: 354V
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:54 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 354V A G K
BGG   GG   0 V=V(G,K)+0.65601816
BM1   M1   0 V=(0.006476558*(URAMP(V(A,K))+1e-10))^-0.39630014
BM2   M2   0 V=(0.79101402*(URAMP(V(GG)+URAMP(V(A,K))/32.268063)+1e-10))^1.8963001
BP    P    0 V=0.0016633526*(URAMP(V(GG)+URAMP(V(A,K))/40.793288)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00098151348*V(M1)*V(M2)
BIG   IG   0 V=0.00083167629*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00089321233*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2p
CGK   G    K 2p
CAK   A    K 2p
.ENDS
