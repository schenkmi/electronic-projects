*
* Generic triode model: 6U8PT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:03 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6U8PT A G K
BGG   GG   0 V=V(G,K)+0.65071871
BM1   M1   0 V=(0.046006989*(URAMP(V(A,K))+1e-10))**-2.7651713
BM2   M2   0 V=(0.35168575*(URAMP(V(GG)+URAMP(V(A,K))/14.091647)+1e-10))**4.2651713
BP    P    0 V=0.003445744*(URAMP(V(GG)+URAMP(V(A,K))/40.068859)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.018698107*V(M1)*V(M2)
BIG   IG   0 V=0.001722872*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0018526668*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2p
CGK   G    K 3p
CAK   A    K 3.5p
.ENDS
