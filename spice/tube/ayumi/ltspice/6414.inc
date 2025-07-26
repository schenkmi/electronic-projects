*
* Generic triode model: 6414
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:20 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6414 A G K
BGG   GG   0 V=V(G,K)+-0.25147459
BM1   M1   0 V=(0.026968201*(URAMP(V(A,K))+1e-10))**-2.4186148
BM2   M2   0 V=(0.38278833*(URAMP(V(GG)+URAMP(V(A,K))/22.886646)+1e-10))**3.9186148
BP    P    0 V=0.0056897851*(URAMP(V(GG)+URAMP(V(A,K))/59.789299)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.01806754*V(M1)*V(M2)
BIG   IG   0 V=0.0029092955*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0017392527*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3.6p
CGK   G    K 5p
CAK   A    K 0.6p
.ENDS
