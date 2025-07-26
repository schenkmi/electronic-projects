*
* Generic triode model: 6900
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:22 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6900 A G K
BGG   GG   0 V=V(G,K)+0.77471006
BM1   M1   0 V=(0.027887036*(URAMP(V(A,K))+1e-10))**-0.93085057
BM2   M2   0 V=(0.61706796*(URAMP(V(GG)+URAMP(V(A,K))/13.731543)+1e-10))**2.4308506
BP    P    0 V=0.0043178017*(URAMP(V(GG)+URAMP(V(A,K))/22.252886)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0027693634*V(M1)*V(M2)
BIG   IG   0 V=0.0021589009*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0024531966*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5.2p
CGK   G    K 8p
CAK   A    K 1p
.ENDS
