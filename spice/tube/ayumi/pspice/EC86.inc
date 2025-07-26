*
* Generic triode model: EC86
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:35 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT EC86 A G K
BGG   GG   0 V=V(G,K)+0.22760069
BM1   M1   0 V=(0.0026112468*(URAMP(V(A,K))+1e-10))^-0.29355976
BM2   M2   0 V=(0.83632563*(URAMP(V(GG)+URAMP(V(A,K))/62.680543)+1e-10))^1.7935598
BP    P    0 V=0.0095464624*(URAMP(V(GG)+URAMP(V(A,K))/74.947533)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0059140675*V(M1)*V(M2)
BIG   IG   0 V=0.0047732312*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00496493*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.2p
CGK   G    K 3.5p
CAK   A    K 0.2p
.ENDS
