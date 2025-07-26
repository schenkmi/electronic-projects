*
* Generic triode model: 6CW5T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:44 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6CW5T A G K
BGG   GG   0 V=V(G,K)+0.38874904
BM1   M1   0 V=(0.09419804*(URAMP(V(A,K))+1e-10))**-1.560546
BM2   M2   0 V=(0.49010862*(URAMP(V(GG)+URAMP(V(A,K))/5.4129723)+1e-10))**3.060546
BP    P    0 V=0.0055371733*(URAMP(V(GG)+URAMP(V(A,K))/11.044434)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0058898823*V(M1)*V(M2)
BIG   IG   0 V=0.0027685867*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0035373923*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5.2p
CGK   G    K 6.9p
CAK   A    K 5.4p
.ENDS
