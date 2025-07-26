*
* Generic triode model: 6AN8PT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:07 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 6AN8PT A G K
BGG   GG   0 V=V(G,K)+-1
BM1   M1   0 V=(0.024591513*(URAMP(V(A,K))+1e-10))^-1.3002423
BM2   M2   0 V=(0.53566794*(URAMP(V(GG)+URAMP(V(A,K))/18.881801)+1e-10))^2.8002423
BP    P    0 V=0.0063199577*(URAMP(V(GG)+URAMP(V(A,K))/35.249078)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0052482203*V(M1)*V(M2)
BIG   IG   0 V=0.0031599788*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0034308188*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.8p
CGK   G    K 4.2p
CAK   A    K 2.4p
.ENDS
