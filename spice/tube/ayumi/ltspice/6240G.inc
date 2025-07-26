*
* Generic triode model: 6240G
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:15 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6240G A G K
BGG   GG   0 V=V(G,K)+0.72455622
BM1   M1   0 V=(0.00866647*(URAMP(V(A,K))+1e-10))**-0.48282918
BM2   M2   0 V=(0.75649482*(URAMP(V(GG)+URAMP(V(A,K))/28.097389)+1e-10))**1.9828292
BP    P    0 V=0.0013034573*(URAMP(V(GG)+URAMP(V(A,K))/37.141548)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00075405166*V(M1)*V(M2)
BIG   IG   0 V=0.00065172867*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0007047229*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.6p
CGK   G    K 3.2p
CAK   A    K 1.2p
.ENDS
