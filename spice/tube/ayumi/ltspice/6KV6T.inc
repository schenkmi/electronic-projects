*
* Generic triode model: 6KV6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:25 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6KV6T A G K
BGG   GG   0 V=V(G,K)+0.5805065
BM1   M1   0 V=(0.16898169*(URAMP(V(A,K))+1e-10))**-1.508747
BM2   M2   0 V=(0.4985464*(URAMP(V(GG)+URAMP(V(A,K))/2.9675026)+1e-10))**3.008747
BP    P    0 V=0.0050541434*(URAMP(V(GG)+URAMP(V(A,K))/5.9523097)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0050986757*V(M1)*V(M2)
BIG   IG   0 V=0.0025270717*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0038528147*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.2p
CGK   G    K 12.9p
CAK   A    K 8.4p
.ENDS
