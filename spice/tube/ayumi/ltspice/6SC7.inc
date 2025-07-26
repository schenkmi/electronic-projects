*
* Generic triode model: 6SC7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:53 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6SC7 A G K
BGG   GG   0 V=V(G,K)+0.44106944
BM1   M1   0 V=(0.0042907324*(URAMP(V(A,K))+1e-10))**-0.48871674
BM2   M2   0 V=(0.75425523*(URAMP(V(GG)+URAMP(V(A,K))/57.273385)+1e-10))**1.9887167
BP    P    0 V=0.00077042152*(URAMP(V(GG)+URAMP(V(A,K))/75.933693)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00044535539*V(M1)*V(M2)
BIG   IG   0 V=0.00038521076*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00040047972*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2p
CGK   G    K 2p
CAK   A    K 3p
.ENDS
