*
* Generic triode model: MH40
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:57 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT MH40 A G K
BGG   GG   0 V=V(G,K)+0.39906513
BM1   M1   0 V=(0.011821777*(URAMP(V(A,K))+1e-10))^-0.91482169
BM2   M2   0 V=(0.62116387*(URAMP(V(GG)+URAMP(V(A,K))/32.045617)+1e-10))^2.4148217
BP    P    0 V=0.0012108021*(URAMP(V(GG)+URAMP(V(A,K))/51.589634)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00077021291*V(M1)*V(M2)
BIG   IG   0 V=0.00060540103*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00064077588*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.3p
CGK   G    K 6p
CAK   A    K 4p
.ENDS
