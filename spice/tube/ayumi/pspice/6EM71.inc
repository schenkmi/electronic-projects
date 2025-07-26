*
* Generic triode model: 6EM71
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:56 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6EM71 A G K
BGG   GG   0 V=V(G,K)+0.75136004
BM1   M1   0 V=(0.00038946438*(URAMP(V(A,K))+1e-10))^-0.038461538
BM2   M2   0 V=(0.975*(URAMP(V(GG)+URAMP(V(A,K))/64.190723)+1e-10))^1.5384615
BP    P    0 V=0.00085260112*(URAMP(V(GG)+URAMP(V(A,K))/65.836639)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00074054441*V(M1)*V(M2)
BIG   IG   0 V=0.00042630056*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00044579952*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.8p
CGK   G    K 2.2p
CAK   A    K 0.6p
.ENDS
